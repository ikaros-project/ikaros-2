//
//	Dynamixel.h		This file is a part of the IKAROS project
//
//    Copyright (C) 2018  Christian Balkenius and Birger Johansson
//
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

#ifndef Dynamixel_
#define Dynamixel_

//#define DYNAMIXEL_DEBUG
//#define DYNAMIXEL_TIMING
//#define DYNAMIXEL_COM_REPORT

#include "IKAROS.h"
#include "DynamixelComm.h"
#include "DynamixelServo.h"

#define IK_IN_TORQUE_ENABLE        0
#define IK_IN_LED                  1
#define IK_IN_D_GAIN               2
#define IK_IN_I_GAIN               3
#define IK_IN_P_GAIN               4
#define IK_IN_GOAL_POSITION        5
#define IK_IN_MOVING_SPEED         6
#define IK_IN_TORQUE_LIMIT         7
#define IK_IN_GOAL_TORQUE          8
#define IK_IN_GOAL_ACCELERATION	   9

#define IK_OUT_TORQUE_ENABLE         0
#define IK_OUT_LED                   1
#define IK_OUT_D_GAIN                2
#define IK_OUT_I_GAIN                3
#define IK_OUT_P_GAIN                4
#define IK_OUT_GOAL_POSITION         5
#define IK_OUT_MOVING_SPEED          6
#define IK_OUT_TORQUE_LIMIT          7
#define IK_OUT_PRESENT_POSITION      8
#define IK_OUT_PRESENT_SPEED         9
#define IK_OUT_PRESENT_LOAD          10
#define IK_OUT_PRESENT_VOLTAGE       11
#define IK_OUT_PRESENT_TEMPERATURE   12
#define IK_OUT_PRESENT_CURRENT       13
#define IK_OUT_GOAL_TORQUE           14
#define IK_OUT_GOAL_ACCELERATION     15

#define IK_INPUTS 10
#define IK_OUTPUTS 16

class Dynamixel: public Module
{
public:
	static Module * Create(Parameter * p) { return new Dynamixel(p); }
	
	Dynamixel(Parameter * p);
	virtual ~Dynamixel();
	void		Init();
	void		Tick();	
	
private:
	int         size;           		// Size of the servo[]. Size != number of servos as in direct mode it can be gap between servos.
	int         nrOfServos = 0;      	// Number of servos found
	
	int         infoLevel;
	int         indexMode;
	int         angleUnit;
	bool		optimizeMode;
	int 		serialLatency;			// serial latency in ms
	bool        useFeedback;
	int         startUpDelay;			// To make sure nothing strange is received from the ikaros system during the first ticks.
	int			torqueUpDelay;			// After startUpDelay the system start reiving real values but will ramp up torque to have a smooth start of the system.
	int         maxTemperature;			// Max temerature before shut down module
	// index of where to find ikaros data in the dynamixel memory block
	int **      inAdress;           	// Array of where to store input data in the dynamixel memory block
	int **      inAdressSize;        	// Array of how many bytes the input parameter. This one is needed to calculate packate size in bulk_write as servos may have different paramter size.
	int **      outAdress;          	// Array of where to grab output data in the dynamixel memory block
	bool **		active;					// Is input connected and exist parameter for selected servo
	bool **		optimize;				// Is inputvalue same as read from servo. Do not resend.
	int         protocol;               // The protocol used. No mixed protocol allowed.

	
	// Inputs
	bool 		connected[IK_INPUTS];	// Connected inputs
	float *     torqueEnable;
	float *     LED;
	float *     dGain;
	float *     iGain;
	float *     pGain;
	float *     goalPosition;
	float *     movingSpeed;
	float *     torqueLimit;
	float *     goalTorque;
	float *     goalAcceleration;
	
	// Outputs
	float *     feedbackTorqueEnable;
	float *     feedbackLED;
	float *     feedbackDGain;
	float *     feedbackIGain;
	float *     feedbackPGain;
	float *     feedbackGoalPosition;
	float *     feedbackMoving;
	float *     feedbackTorqueLimit;
	float *     feedbackPresentPosition;
	float *     feedbackPresentSpeed;
	float *     feedbackPresentLoad;
	float *     feedbackPresentVoltage;
	float *     feedbackPresentTemperature;
	float *     feedbackPresentCurrent;
	float *     feedbackGoalTorque;
	float *     feedbackGoalAcceleration;
	float **	errors;
	int 		errorsSizeX;			// Size of error output matrix  y = nrServos x = errorsSizeX]

	DynamixelServo **   servo; // Array of servo data
	
	int             *   servoIndex;        // Array of indexes of where to find servos in the servo[] array.
	int             *   servoId;           // Array of ids example [1,2,3] or [1,5,19]
	
	const char      *   device;
	DynamixelComm   *   com;
	
	void		OptimizeSends();

	void 		GetErrors(int index);
	void 		ResetComErrors();
	
	void		PrintMinimal();
	void        PrintAll();
	void		PrintMaps();
};

#endif

