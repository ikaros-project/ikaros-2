//
//	ArrayToMatrix.h		This file is a part of the IKAROS project
// 						
//    Copyright (C) 2014 Birger Johansson
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


#ifndef ArrayToMatrix_
#define ArrayToMatrix_

#include "IKAROS.h"
#include <vector>
class ArrayToMatrix: public Module
{
public:
    static Module * Create(Parameter * p) { return new ArrayToMatrix(p); }

    ArrayToMatrix(Parameter * p);
    virtual ~ArrayToMatrix(); 

    void 		Init();
    void 		Tick();
    void        SetSizes();
    
    float **     input;
    // std::vector<float*> inp_vec;
    // std::vector<float**> out_vec;
    float ***    output;
    
    int         inputSizeX;
    int         arrayLength;
    int         nrArrays;
    int         channels;
    bool        debug_mode;

};

#endif

