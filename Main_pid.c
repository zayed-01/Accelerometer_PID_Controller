
#include "Header_constant.h"
#include "PID_acc.h"
#include "ADC.h"

#define CNTRL    LATBbits.LATB3
#define DECIMATE 0

signed int dac_value ;
double chanelA , chanelB ; 
int out_data;
signed int container ; 

//Define  PID controller .5, 50 ,0.000001  -0.1, 0 ,0.000000009 .5, 0 ,0.00009, .1, 0 ,0.0000009 //.1, 0 ,0.0009,
PIDcontroller pid = {0,0,0, time_constant, Sample_time, In_min_lim, In_max_lim, Pid_voltage_max, Pid_voltage_min };

void SWITCH(void);


 /***********************************************
  Interrupt service routine for ADC data (intput 24 bit data coming in)
 *************************************************/
void __ISR(_EXTERNAL_1_VECTOR, IPL3AUTO) INT1_ISR(void){
    mINT1ClearIntFlag();
    CS = 0; // start transaction
    int i; 
    for (i = 0; i < 5; i++){
        packets[i] = readADC(dummy[i]);
    }
    CS = 1; // end transaction
    D2 = packets[2] >> 8;  D3 = packets[3] >> 8; D4 = packets[4] >> 8; 
    ADC_Data = moving_average_filter(&moving_average, D2);
    out_data1 = ADC_Data >> 13 ; 
} 

 /***********************************************
  Interrupt service routine for controller action
 *************************************************/

void __ISR(_TIMER_3_VECTOR ,IPL2AUTO) Timer3_ISR(void){
    mT3ClearIntFlag();
    TOGGLE_LED( ); 
      
    output = (int)PIDController_update(&pid,0,ADC_Data);
    out_data = (unsigned short)(abs(output)) ; 
    if (ADC_Data > 0){ //going towards bottom electrode  //chn A is top electrode. Write the higher value to the channel                       
        //DAC_WRITE(2047-out_data,2047+out_data);
        DAC_WRITE(0,0);
        elect_type = 'U';
    }else{
        //DAC_WRITE(2047+out_data,2047-out_data); // (2147,1947)
        DAC_WRITE(0,0);
    }
    
    if (buffer_control){
      //CIRCULAR_BUFFER(ADC_Data,(signed int)out_data);
        CIRCULAR_BUFFER(ADC_Data,float_out);
     }
    
    TOGGLE_LED( ); 
}

void main(void){  
    SYSTEMConfig(sys_clock, SYS_CFG_WAIT_STATES | SYS_CFG_PCACHE);
    ANSELA = 0; //make sure analog is cleared
    ANSELB = 0;    

    int i;
    /*Clearing the buffer*/
    for ( i = 0; i < max_count; i++){
        FIFO[i] = 0x000000;
        Test[i] = 0x000000;
    }
    for ( i = 0; i < BUFF_SIZE; i++)
        buffer[i] = 0;  
    
 /***********************************************
  Initialization of ADC, UART, DAC, LED, Interrupt
  save_data function is for printing the values in the circular buffer
 *************************************************/
//save_data();
    INIT_LED();
    INIT_UART();
    INIT_ADC_SPI();
    INIT_DACSPI ();
    SWITCH();
    ADC();
    Init_timer3();
    INTEnableSystemMultiVectoredInt();
    init_EXT_INT();

/************************************
  controller parameter initialization
  Setting gain to the controller
 *************************************/
    PIDController_init(&pid);
//setGain(&pid, 10, 0,0);

/************************************
 Initializing the filters : 1st order exponential filter
 moving average filter
 IIR filter : 4th order , biquad type
 *************************************/  
    init_moving_average(&moving_average );
    init_low_pass(&filter_1);
 //   CNTRL = 1;
  
  
while (1){     
    do{
        ;
    }while(!print_control); 
    
        save_data(); 
 
}
}

/***********************
Function Definition
*************************/     

void SWITCH(void)
 {
    mPORTBSetPinsDigitalOut(BIT_3); //LED OUT
    CNTRL = 0;         // initial LED state
                        }

void INIT_DACSPI (void){
    mPORTBSetPinsDigitalOut(BIT_15 | BIT_11| BIT_7 ); // SCK||SDO||CS
    PPSOutput(2,RPB11,SDO2); // pin 22
    SPI2STATCLR = 0x40;
    SPI2CON = 0;
    char clr_Buf = SPI2BUF;
    SPI2BRG = 2; // Fpb/2/1 MHz  //determine the clock speed of SPI connection
    SPI2CON = 0x8320;
    DAC_CS = 1;                    // initial CS state pin 16
 } 

unsigned char DAC_send(unsigned char des){
    SPI2BUF = des; //write
    while (SPI2STATbits.SPIBUSY);
    return SPI2BUF;
    

}

void DAC_WRITE(unsigned short chnB,unsigned short chnA){ 
    byte0 = (unsigned char) (chnB >> 4) ;
    byte1 = (unsigned char) ((chnB << 4) | (chnA >> 8));
    byte2 = (unsigned char) (chnA & 0xff);

    DAC_CS  = 0;
    
    DAC_send(byte0);
    DAC_send(byte1);
    DAC_send(byte2);
    
    DAC_CS  = 1;

}



void save_data(){
    for(sent = 0; sent < NSAMPLES; ++sent){
       // sprintf(buffer,"%f\t%f\t%f\n",((double)(sent+1)*0.0002),((double)(FIFO[k]*4.884)/pow(2,24)), ((double)Test[k]*4.884)/pow(2,24));  //((double)Test[k]*10)/pow(2,12));
        sprintf(buffer,"%f\t%f\t%f\n",((double)(sent+1)*0.0002),((double)(FIFO[sent]*4.884)/pow(2,24)), Test[sent]); //for float
        while(!UARTTransmitterIsReady(UART2));
       
        SendString(buffer);                                    
        FIFO[sent] = 0x00;
        Test[sent] = 0x00;
    }
    count_send =0 ;  
   print_control = false;
   buffer_control = true;

}


void  End_transfer(void){
    CloseTimer3();
    CloseOC3();
    CloseINT1();
}


//void CIRCULAR_BUFFER(signed int Avg1, signed int Avg2){  //signed short Avg2
////    if (type == 'L') 
////        Avg2 = -Avg2 ;
//            
//    if(!buffer_full()){
//        FIFO[count_send] = Avg1;   
//        Test[count_send] = Avg2;   
////        channel[count_send] = type;
//        
//        ++count_send;   
//
//        if (count_send >= max_count){
//            count_send = 0;         
//        }          
//    }
//    else{   
//        FIFO[count_send] = 0x55;   
//        Test[count_send] = 0x55;
//      //  channel[count_send] = 0x55;
//    }
//                                       
//    if (count_send >= NSAMPLES){
//        End_transfer();
//        buffer_control = true;       
//    }
//}



/* For printing the float 
 */
                

void CIRCULAR_BUFFER(signed int Avg1, float Avg2){  //signed short Avg2

        FIFO[count_send] = Avg1;   
        Test[count_send] = Avg2;   

        ++count_send;   
                                       
    if (count_send >= NSAMPLES){
        buffer_control = false; // cannot collect more data
        print_control = true;
        
    }
}


/**************************************************
    Configure timer and output compares to make pulses
 ****************************************************/
void INIT_PWM (void){

    // set up timer2 to generate the wave period
    OpenTimer2(T2_ON | T2_SOURCE_INT | T2_PS_1_1, pwm_period);

    //ConfigIntTimer2(T2_INT_ON | T2_INT_PRIOR_3);
    //mT2ClearIntFlag(); // and clear the interrupt flag
    //set up compare3 for PWM mode

    OpenOC3(OC_ON | OC_TIMER2_SRC | OC_PWM_FAULT_PIN_DISABLE , pwm_on_time, pwm_on_time);

    //OC3 is PPS group 4, map to RPB9 (pin 18)
    PPSOutput(4, RPB9, OC3);
}

                
/**************************************************
 Initialize timer module of PIC32
 ****************************************************/
void Init_timer3(void){
    OpenTimer3(T3_ON | T3_SOURCE_INT | T3_PS_1_1, controller_period);
    ConfigIntTimer3(T3_INT_ON | T3_INT_PRIOR_2);
    mT3ClearIntFlag(); // and clear the interrupt flag
}


