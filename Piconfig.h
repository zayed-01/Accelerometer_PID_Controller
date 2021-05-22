

#ifndef __PICONFIG_H    /* Guard against multiple inclusion */
#define __PICONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#define _SUPPRESS_PLIB_WARNING 
#define _DISABLE_OPENADC10_CONFIGPORT_WARNING
// serial stuff
#include <plib.h>
#include<stdbool.h>
#include<math.h>
    

//=============================================================
// 60 MHz

#pragma config FNOSC = FRCPLL, POSCMOD = OFF
//#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20, FPLLODIV = DIV_2  //40 MHz
//#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_16, FPLLODIV = DIV_256  //250Khz
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_16, FPLLODIV = DIV_1  //64 MHz
// #pragma config FPBDIV = DIV_8 // PB 31.25Khz  // 8mhz
//#pragma config FPBDIV = DIV_1 // PB 40 MHz
#pragma config FPBDIV = DIV_2 // PB 32 MHz



#pragma config FWDTEN = OFF,  JTAGEN = OFF
#pragma config FSOSCEN = OFF  //PINS 11 and 12 to secondary oscillator!
#pragma config DEBUG = OFF   // RB4 and RB5
//==============================================================



// Protothreads configure

// IF use_vref_debug IS defined, pin 25 is Vref output
//#define use_vref_debug

// IF use_uart_serial IS defined, two pins are used by the uart `11`
// Go to pt_cornell_1_2_2.h and search for "SET UART i/o PINS"
//#define use_uart_serial

//#define BAUDRATE 250000 // must match PC terminal emulator setting //57600

/////////////////////////////////
// set up clock parameters
// system cpu clock
#define sys_clock 64000000
//#define sys_clock 250000



// sys_clock/FPBDIV
#define pb_clock        (sys_clock/2)      // divide by two in this case
//#define pb_clock  sys_clock/8 // divide by two in this case


#define period (((pb_clock/1000)- 1))



    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PICONFIG_H */

