This Code is target on: 

MCU: PIC32MX250128B
ADC: ADS131A04
DAC : MAX532
This file contains versions and mistakes in the code..

Version 1 : Mistake -->>
pid->prev_meas = measured_value;
pid->diff = (pid->Kd*(measured_voltage-pid->prev_meas))*(pid->T); 

Correction: 
pid->prev_meas = measured_voltage;
pid->diff = (pid->Kd*(measured_voltage-pid->prev_meas)) / pid->T; 

and all the results previously have been taken with this code
and gain values need to be scaled if requires for publication
There is one batch of results with this results.

Version 2 : Mistake 
   pid->diff = (pid->Kd*(measured_voltage-pid->prev_meas))*pid->T; 

Correction :    pid->diff = (pid->Kd*(measured_voltage-pid->prev_meas)) / pid->T; 


and all the results previously have been taken with this code
and gain values need to be scaled if requires for publication
There is one batch of result with this error

Try LQR gains with the correct codes

Version 3 : THe differential and propotional part is all corrected
Gains will be tunes based on it.


Last updatd: 15 may 2020

Smaller values would be zero of differential term went zero because of the addition of very small number


Update : 5/21/2021 : 
Updating the final PID code here

 


