
#ifndef _PIC32_DELAY_H    /* Guard against multiple inclusion */
#define _PIC32_DELAY_H


/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif

 #define LED             LATAbits.LATA0


/* -----Delay Functions-- ------------------ -= = */
//void Delay_ms(int delay);
void Delay_ms(int delay);
void Delay_s(int delay);
void Delay_us(int delay);
void INIT_LED(void);

    
       
    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _PIC32_DELAY_H */

