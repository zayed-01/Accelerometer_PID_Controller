
#include "ADC.h"


/*****************************************************
* Local Functions
*****************************************************/
bool ADC_Ready(unsigned int timeout_ms){

  unsigned int timeout = timeout_ms * 6000; // convert to # of loop iterations
  // wait for nDRDY interrupt or timeout - each iteration is about 20 ticks
  do{
    timeout--;
  } while (DRDY&& (timeout > 0));

  return (timeout > 0); // Did a nDRDY interrupt occur?
}

unsigned int send(unsigned int des){
  ADC_Ready(100);

  CS = 0; // start transaction

  SPI1BUF = des; //write

  while (!SPI1STATbits.SPIRBF)
    ;
  CS = 1; // end transaction
                     

  return SPI1BUF;
}

signed int readADC(unsigned int dummy){

  SPI1BUF = dummy; //write
  while (!SPI1STATbits.SPIRBF)
    ;
  return SPI1BUF;
}

void get_data(volatile signed int packets[5],unsigned int dummy[5] ){
    
  int i;
  for (i = 0; i < 5; i++)
    dummy[i] = 0x00; //  clear previous values 
 
  for (i = 0; i < 5; i++)
    packets[i] = 0x00; //  clear previous values 
    
  CS = 0; // start transaction
  for (i = 0; i < 5; i++)
    packets[i] = readADC(dummy[i]);
  
  CS = 1; // end transaction
}


void INIT_ADC_SPI (void){
 
  PPSInput(2, SDI1, RPB8);  // pin 17 //-> pin 5
  PPSOutput(3, RPB2, SDO1); // pin 6

  SPI1STATCLR = 0x40;
  SPI1CON = 0;
  int clearB = SPI1BUF;
  SPI1BRG = 0; // Fpb/2 
  SPI1CON = 0x8E20;

  mPORTBSetPinsDigitalOut(BIT_4 | BIT_14); // cs||SCK
  mPORTASetPinsDigitalIn(BIT_3);           // DRDY - pin12(PCB))
  CS = 1;                    // initial CS state pin 11
 
 } 

void init_EXT_INT(void){
  __builtin_disable_interrupts();
  PPSInput(4, INT1, RPA3);

  ConfigINT1(EXT_INT_PRI_3 | FALLING_EDGE_INT | EXT_INT_ENABLE);

  INTCONbits.MVEC = 1;
  //INTCONbits.INT1EP = 0;

  __builtin_enable_interrupts();
}

/*******************************************************/

void init_ADC(void){
    unsigned int trash[5] = {0, 0,0,0,0};
    signed int reponse[5] = {0, 0,0,0,0};
    
  do
  {
    send(0x00000000);
     } while (SPI1BUF != 0xFF040000); //(2) ADC Ready 
                                   
  do
  {
    send(0x06550000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x06550000); // Unlock
                                   

  do
  {
    send(0x4BE00000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x2BE00000); //(A_SYS_CFG) //6-E
                                   

  do
  {
    send(0x4C000000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x2C000000); //(D_SYS_CFG)
                                   
  do
  {
    send(0x4D020000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x2D020000); //(CLCKIN(1)
                                   
  do
  {
    send(0x4E220000); //4E25 change
    send(0x00000000);
   
  } while (SPI1BUF != 0x2E220000); //(2) CLCKIN

  
  do
  {
    send(0x4F0F0000);
    send(0x00000000);
   
  } while (SPI1BUF != 0x2F0F0000); //(2) ADC ENABLED
                                   
                                   

  do
  {
    send(0x00330000);
   get_data(reponse,trash);
     
  } while (reponse[0] != 0x00330000); // WAKE UP
                                
                                   
  // send (0x00000000);

  do
  {
    
    trash[0] = 0x05550000;
   get_data(reponse,trash);
    
   trash[0]= 0x00000000; 
    get_data(reponse,trash);
    
  } while (reponse[0] != 0x05550000); //LOCK
               
  
 get_data(reponse,trash);
 
 trash[0] = 0x25000000;
 get_data(reponse,trash);
 
 trash[0] = 0x25000000;
 get_data(reponse,trash);
}

void ADC(void){
    unsigned int trash[5] = {0, 0,0,0,0};
    signed int reponse[5] = {0, 0,0,0,0};
    
      do
  {
    send(0x06550000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x06550000); // Unlock
                                   
    do
  {
    send(0x00110000);
    send(0x00000000);
    
  } while (SPI1BUF != 0xff040000); // Reset
                                   
  
    do
  {
    send(0x06550000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x06550000); // Unlock
                                   
 
  
  do
  {
    //EVM //send(0x4BE00000); 
    send(0x4B680000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x2B680000); //(A_SYS_CFG) //6-E
                                   

  do
  {
    send(0x4C000000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x2C000000); //(D_SYS_CFG)
                                   
  do
  {
    send(0x4D020000);
    send(0x00000000);
    
  } while (SPI1BUF != 0x2D020000); //(CLCKIN(1)
                                   
  do
  {
    send(0x4E260000); //4E25 change
    send(0x00000000);
   
  } while (SPI1BUF != 0x2E260000); //CLCKIN(2)

  
  do
  {
    send(0x4F0F0000);
    send(0x00000000);
   
  } while (SPI1BUF != 0x2F0F0000); //(2) ADC ENABLED
                                   
                                   

  do
  {
    send(0x00330000);
   get_data(reponse,trash);
     
  } while (reponse[0] != 0x00330000); // WAKE UP
                               
        
  do
  {   
    send (0x05550000);
    send (0x00000000);

  } while(SPI1BUF!=0x05550000); //LOCK

  int i;
  for( i= 0; i < 5 ; i++)
    reponse[0]=readADC(trash[i]);
                                  
}
