//
//	EpiSpeech.cc		This file is a part of the IKAROS project
//
//    Copyright (C) 2022-2024 Christian Balkenius
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//    See http://www.ikaros-project.org/ for more information.
//

#include "EpiSpeech.h"

#include <spawn.h>

using namespace ikaros;



void
SpeechSound::Play(const char * command)
{
    timer->Restart();
    frame = 0;
    char * argv[5] = { (char *)command, (char *)sound_path.c_str(), NULL };
    pid_t pid;

    int status = posix_spawn(&pid, (char *) command, NULL, NULL, argv, NULL);
}

bool
SpeechSound::UpdateVolume(float * rms, float lag)
{
    float rt = 0.001*(timer->GetTime() - lag);
    while(frame < time.size() && time[frame] < rt)
        frame++;

    if(frame == time.size())
    {
        rms[0] = -50; // dB with no signal
        rms[1] = -50;
        return false;
    }

    rms[0] = left[frame];
    rms[1] = right[frame];
    return true;
}



SpeechSound
EpiSpeech::CreateSound(std::string text, std::string path, int id)
{
    std::string sound_path = path + std::to_string(id)+".aiff";
    SpeechSound sound(sound_path);

    int err = 0;

    // synthesize speech

    std::string com = speech_command + " -o " + sound_path +" \""+ text +"\"";
    system(com.c_str());

    // Calculate volume  using ffprobe

    char * command_line = create_formatted_string("ffprobe -f lavfi -i amovie=%s,astats=metadata=1:reset=1 -show_entries frame=pkt_pts_time:frame_tags=lavfi.astats.Overall.RMS_level,lavfi.astats.1.RMS_level,lavfi.astats.2.RMS_level -of csv=p=0 2>/dev/null", sound_path.c_str());
    float t, l, r;
    FILE * fp = popen(command_line, "r"); 
    if(fp != NULL)
    {
        while(fscanf(fp, "%f,%f,%f\n", &t, &l, &r) == 3)
        {
            sound.time.push_back(t);
            sound.left.push_back(l);
            sound.right.push_back(r);
        }
        err = pclose(fp);
    }
    if(err != 0) // Command failed - fake 1s output
    {
            sound.time.push_back(0);
            sound.left.push_back(-15);
            sound.right.push_back(-15);
            sound.time.push_back(1);
            sound.left.push_back(-15);
            sound.right.push_back(-15);
    }
    return sound;
}



void
EpiSpeech::Init()
{
    trig = GetInputArray("TRIG");
    size = GetInputSize("TRIG");
    last_trig = create_array(size);
    queued_sound = -1;
    current_sound = -1;
    last_sound = -1;
    inhibition = GetInputArray("INHIBITION");

    attribute1 = GetInputArray("ATTRIBUTE1");
    attribute2 = GetInputArray("ATTRIBUTE2");

    playing = GetOutputArray("PLAYING");
    completed = GetOutputArray("COMPLETED");
    active = GetOutputArray("ACTIVE");

    rms = GetOutputArray("RMS");
    volume = GetOutputArray("VOLUME");
    
    speaking = false;

    command = GetValue("command");
    speech_command = GetValue("speech_command");

    Bind(scale_volume, "scale_volume");
    Bind(lag, "lag");

    int id = 0;
    for(auto t: split(GetValue("text"), ","))
        sound.push_back(CreateSound(trim(t), this->kernel->ikc_dir, id++));
}


void
EpiSpeech::Tick()
{
    if(speaking && speaking_timer.GetTime() > lag)
    {
        volume[0] = 0.015 + random(0, 0.015);
        volume[1] = volume[0];
        return;
    }
    else
    {
        volume[0] = 0.0;
        volume[1] = 0.0;
    }

    // Check for trig and queue sound

    for(int i=0; i<size; i++)
        if(trig[i] == 1 && last_trig[i] == 0 && i < sound.size())
        {
                queued_sound = i;
        }

    // Start play if sound in queue and no inhibition

        if(current_sound == -1 && queued_sound != -1 && (!inhibition || *inhibition == 0))
        {
            current_sound = queued_sound;
            queued_sound = -1;
            sound[current_sound].Play(command);
        }

    // Update volume

    rms[0] = -50; // dB with no signal
    rms[1] = -50;

    if(current_sound != -1)
        if(!sound[current_sound].UpdateVolume(rms, lag))
            current_sound = -1;

    volume[0] = scale_volume * pow(10, 0.1*rms[0]); // convert to linear volume scale
    volume[1] = scale_volume * pow(10, 0.1*rms[1]);

    // Set playing status outputs

    
    if(current_sound == -1)
    {
        reset_array(playing, size);
        *active = 0;
    }
    else
    {
        set_one(playing, current_sound, size);
        *active = 1;
    }

    // Set completed status

    if((current_sound != last_sound) && (last_sound != -1))
    {
        set_one(completed, last_sound, size);
    }
    else
    {
        reset_array(completed, size);
    }


    // Store last trig and sound

    copy_array(last_trig, trig, size);
    last_sound = current_sound;
}



void 
EpiSpeech::SayText(const std::string &text) 
{
    speaking_timer.Reset();
    speaking = true;
    std::thread([this, text]() {
        std::string com = speech_command + " \""+ text +"\"";
        int result = system(com.c_str());
        speaking = false; 
    }).detach();
}
    

void
EpiSpeech::Command(std::string s, float x, float y, std::string value)
{
    SayText(value);
}

static InitClass init("EpiSpeech", &EpiSpeech::Create, "Source/Modules/IOModules/EpiSpeech/");


