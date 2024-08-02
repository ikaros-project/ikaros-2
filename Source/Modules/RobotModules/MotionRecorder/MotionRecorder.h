//
//	MotionRecorder.h		This file is a part of the IKAROS project
//
//    Copyright (C) 2015-2018 Christian Balkenius
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

#ifndef MotionRecorder_
#define MotionRecorder_

#include "IKAROS.h"

class MotionRecorder: public Module
{
public:
    static Module * Create(Parameter * p) { return new MotionRecorder(p); }

    MotionRecorder(Parameter * p) : Module(p) {}
    virtual ~MotionRecorder();

    void 		Init();
    void 		Tick();

    // Commands

    void        Command(std::string s, float x, float y, std::string value);

    void        ToggleMode(int x, int y);
    void        Off();
    void        Stop();
    void        Record();
    void        Play();
    void        SaveAsJSON();
    void 		Save();
    void 		Load();

    float *     torque_on_record;
    float *     trig;
    float *     trig_last;
    int         trig_size;
    float *     trig_out;
    
    float *     state;
    float *     completed;

    float *     input;
    float *     output;

    int         smoothing_time; // for torque and position
    float *     stop_position;
    float *     start_position;
    float *     start_torque;

    float **     mode; // record, play, hold, free in matrix format
    std::string  mode_string;
    std::string  status_string;
    int          size;

    long        timebase;

    std::string *   motion_name;
    float ***       position_data;
    float **        timestamp_data;
    
    float **        keypoints; // of currently selected motion
    float *         timestamps; // of currently selected motion

    int         max_motions;
    int         current_motion;


    float *     lengths; // lengths of each recording

    int         position_data_max;
    int   *     position_data_count;

    float *     time; // in ms

    float *     enable;

    const char * file_name;
    const char * json_file_name;
    const char * directory;

    bool        record_on_trig;
    bool        auto_save;
};

#endif

