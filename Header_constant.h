#include"Piconfig.h" // PRagma bits - OScillator config
#include "Uart_Print.h" // Print uart
#include "Pic32_delay.h" // Delay Header
#include "NMs_3110.h" // MS3110 Header
#include <stdio.h>
#include <math.h>
#include "PID_acc.h"
#include"Lowpassfilter.h"
#define Points_No  3


//#define TESTING_MODE
#ifndef TESTING_MODE
#define un32type signed int
#else 
#define un32type float
    
#endif 

#define DAC_CS  PORTBbits.RB7

#define BUFF_SIZE       40
#define TOGGLE_LED( )    (mPORTAToggleBits(BIT_0))
#define Sample_time .0001

char buffer[BUFF_SIZE] = { };

volatile signed int packets[5]= {0,0,0,0,0};
unsigned int dummy[5] = {0x25, 0x00, 0x00, 0x00, 0x00};
volatile signed int D1, D2 = 0, D3 = 0, D4;
volatile signed int D0 = 0;
volatile unsigned int count_send = 0, k = 0,print = 0, count = 0, wait = 0;

unsigned int pwm_period = 320-1;//640-1;//320-1; //PWm period calculation kevinc Lych
unsigned int pwm_on_time = 160-1;//320-1;//160-1 ;

unsigned int controller_period = 6400-1;//320-1;
unsigned int ADC_res = 8388607; //2^24
//output = ADCvalue*Controller Gain*PWM period)

/****FIFO Variables*******************/ 
#define max_count 2500
#define CHN  2

volatile signed int FIFO[max_count] ;
//volatile  signed short Test[max_count];
//volatile char channel[max_count] ;


//volatile signed int Test[max_count];
//for printing float
volatile float Test[max_count];

unsigned int NSAMPLES = 2450;

unsigned int sent = 0;

int output = 0;
signed char byte0,byte1,byte2;



volatile bool print_control = false;
volatile bool buffer_control = true;


char elect_type = 0;
volatile signed int ADC_Data,ADC_New,Data_Avg;
//float ADC_Data;
//unsigned short out_data;
float float_out;

//Define low_pass_filter
low_pass_f filter_1 = {0, cut_off_f};
moving_avg_def moving_average;



/*****************************************************************
                Function Prototypes
 *****************************************************************/
void save_data();
void ADC(void);
void INIT_DACSPI (void);
void  End_transfer(void);
void Init_timer3(void);
void INIT_PWM (void);
//void CIRCULAR_BUFFER(signed int Avg1, signed int Avg2) ;
void CIRCULAR_BUFFER(signed int Avg1, float Avg2) ;
int buffer_empty();
unsigned char DAC_send(unsigned char des);
void DAC_WRITE(unsigned short chnB,unsigned short chnA);