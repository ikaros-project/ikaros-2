//
//		Recorder.h		This file is a part of the IKAROS project
//
//
//    Copyright (C) 2015 Christian Balkenius
///
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

#ifndef Recorder_
#define Recorder_

#include "IKAROS.h"

class Recorder: public Module
{
public:
	static Module * Create(Parameter * p) { return new Recorder(p); }
	
    int         start;
    int         length;
    int         count;
    
    int         measure_start;
    int         measure_end;
    int         operation;
    
    float       minimum;
    float       maximum;
    
    int         row;
    int         col;
    int         rcol;

    float       scale;      // for ourput
    float       offset;
    float       margin;
    float       increment;

    float *		input;
    float **    output;
    float **    recording;
    float *     measurements;

    void        SetSizes();

				Recorder(Parameter * p) : Module(p) {};
    virtual		~Recorder();

    void		Init();
    void		Tick();
};

#endif

