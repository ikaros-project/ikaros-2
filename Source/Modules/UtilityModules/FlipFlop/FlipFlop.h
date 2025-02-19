//
//	FlipFlop.h	    This file is a part of the IKAROS project
//					
//
//    Copyright (C) 2022  Christian Balkenius
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

#ifndef OR
#define OR

#include "IKAROS.h"


class FlipFlop: public Module
{
public:
    static Module * Create(Parameter * p) { return new FlipFlop(p); }

    
    float *	set;
    float *	reset;
    float *	enable;
    bool last_enable;
    float *	output;
    float *	inverse;

    bool    invert_inputs;
    int     enable_on;

    FlipFlop(Parameter * p) : Module(p) {}
    virtual ~FlipFlop() {}
    
    void		Init();
    void		Tick();

    int type;
    bool active_high;
    float high;
    float low;
    float threshold;
};


#endif
