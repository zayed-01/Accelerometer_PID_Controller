
//#define MICROCONTROLLER ( for running into microcontroller)



//#ifdef MICROCONTROLLER
//#include <dsplib_dsp.h>
//#define var32type int32
//
//#else
//
// 
//THis controller can be make work as a P, PI, PID controller just set gain at different levels
//#endif
//
#ifndef _PID_CONTROLLER_H

#define _PID_CONTROLLER_H
//macros for constant


#define var32type  int

#define In_max_lim .5
#define In_min_lim -.5
#define Pid_voltage_max 5
#define Pid_voltage_min -5
#define time_constant 0.01


int dac_out;

typedef struct
{
	//PID gains
	var32type Kp;
	var32type Ki;
	var32type Kd;
	//Sample time and time constant of low pass filter
	var32type tau;
	var32type T;

	//Integral windup: saturation limit has to be defined
	var32type integral_min;
	var32type integral_max;
	//Actuator  voltage limitation
	var32type voltage_max;
	var32type voltage_min;

	//control variable
	var32type integrator;
	var32type prev_error;
	var32type diff;
    var32type proportional; 
	var32type prev_meas;
	var32type error;

	//output voltage
	var32type voltage_out;

} PIDcontroller;


/* Objective: Initialization of all parameters
Input : Address of the controller 
Output: Null
Function: Initialization of the controller parameters for computations
Clear controller variables 
*/
void PIDController_init(PIDcontroller *pid);

/* Objective : PID computation and update function 
Input : Address of the controller, set point, value from ADC
Output: Output control voltage
Function: This functions calculates the controller output 
*/
var32type PIDController_update(PIDcontroller *pid, var32type sp, signed int measured_value);

/* Function : Setting gain of the controller 
Input : Address of the controller, PID gains
Output: Null
Function: Setting controller gains for computations
*/
void setGain(PIDcontroller *pid, var32type kp, var32type ki, var32type kd);

#endif
