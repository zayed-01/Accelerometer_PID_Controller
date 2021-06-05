
#include "PID_acc.h"
#include<math.h>
#include "Lowpassfilter.h"
#include <stdbool.h>


double voltage ;
extern low_pass_f filter_1;
bool sat_switch, integrator_switch;  
extern container ;

void PIDController_init(PIDcontroller *pid) {

	pid->integrator = 0;
	pid->prev_error  = 0;

	pid->diff  = 0;
	pid->prev_meas = 0;

	pid->voltage_out = 0;
  //init_low_pass(&filter_1);

}

void setGain(PIDcontroller *pid, var32type kp, var32type ki, var32type kd){
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
}

int PIDController_update(PIDcontroller *pid, var32type sp, signed int measured_value){
    double vel;
    var32type measured_voltage =  (double)(measured_value/pow(2,23))*2.442 ;
    var32type error = measured_voltage ;//- .009 ; //calculation here is in decimal
	pid->proportional = pid->Kp * error;
    
    
	pid->integrator = pid->integrator + pid->Ki*pid->T*0.5*(error+ pid->prev_error) ;
	if (pid->integrator > pid->integral_max){
       	pid->integrator = pid->integral_max;  //integral windup
    }else if (pid->integrator < pid->integral_min){
		pid->integrator = pid->integral_min;
	} 
    
    pid->velo =(measured_voltage - pid->prev_meas)/0.0001;
    vel = (measured_voltage - pid->prev_meas)/0.0001;
    pid->velocity = low_pass_filter(&filter_1, vel);
    pid->diff = (pid->Kd*pid->velocity ); 
    
    
    
	pid->voltage_out = pid->proportional + pid->integrator+ pid->diff ; 
    
	if (pid->voltage_out > pid->voltage_max){
		pid->voltage_out = pid->voltage_max;
        sat_switch = false; 
	}else if (pid->voltage_out < pid->voltage_min){
		pid->voltage_out = pid->voltage_min ;
        sat_switch = false; 
	}else
        pid->voltage_out = pid->voltage_out;
        sat_switch = true ;
        
	pid->prev_error = error;
	pid->prev_meas = measured_voltage;
    
    dac_out =(int)((pid->voltage_out*2047)/5) ;
    
    
    
    return   dac_out  ; // dac_out ;
}

 /************************
    Anti-windup reset scheme
 ************************/
//    if(error*pid->voltage_out >= 0){
//       integrator_switch = true;
//    } 
//    else 
//       integrator_switch = false ;
//        
//     
//    if (sat_switch && integrator_switch)
//        pid->integrator = 0;
//    else   
//        pid->integrator = pid->integrator ;
   