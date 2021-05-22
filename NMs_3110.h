/* 
 * File:   Ms_3110.h
 * Author: cduruaku
 * Created on March 9, 2020, 1:28 PM
 */

#ifndef NMS_3110_H
#define	NMS_3110_H

#ifdef	__cplusplus
extern "C" {
#endif

    
    //   ------V2P25 REF VOLT TRIM (~19mV/st) - (T) ------------------------//  
#define V2P25_VREF_TR5_1                                                   0b0000
#define V2P25_VREF_TRN                                                      0b1000
#define V2P25_VREF_TR_5_1                                                  0b1111  


#define IV2P25_VREF_TR5_1                                                   0b0000    
#define IV2P25_VREF_TRN                                                      0b0001
#define IV2P25_VREF_TR_5_1                                                  0b1111  
         
    
    //   ------ CURRENT REF TRIM (~0.8A/st) - (R) ------------------------//
#define V2P25_IREF_TRN                                                     0b110
#define V2P25_IREF_TR_32                                                  0b111
#define V2P25_IREF_TR32                                                    0b000

#define IV2P25_IREF_TRN                                                     0b011
#define IV2P25_IREF_TR_32                                                  0b111
#define IV2P25_IREF_TR32                                                    0b000
    
    
    
         //   ------OSC TRIM - (D) --------------*----------//
#define OSC_TRN                                                            0b000
#define OSC_TR15                                                           0b001
#define OSC_TR24                                                           0b010
#define OSC_TR33                                                           0b011
#define OSC_TR_N                                                          0b100
#define OSC_TR_35                                                         0b101
#define OSC_TR_47                                                         0b110
#define OSC_TR_81                                                         0b111
    

    //   ------FEEDBACK CAPACITOR ARRAY - (CF) ------------------------//
#define CF_0                                                            0b0000000000//NOMINAL
#define CF_0019pF                                                   0b0000000001        
#define CF_0038pF                                                   0b0000000010   
#define CF_9728pF                                                   0b1000000000       
#define CF_9747pF                                                   0b1000000001       
#define CF_9756pF                                                   0b1000000010       

 
#define CF_19437pF                                                  0b1111111111   

    
#define ICF_0                                                            0b0000000000//NOMINAL
#define ICF_0019pF                                                   0b1000000000        
#define ICF_0038pF                                                   0b0100000000
#define ICF_9728pF                                                   0b0000000001        
#define ICF_19437pF                                                 0b1111111111   
    



    
    
    
    
    
    //   ------COMPENSATION CAPACITOR ARRAY - (CS1) ------------------------//
#define CS1_0                                                            0b000000000//NOMINAL
#define CS1_0019pF                                                   0b000000001        
#define CS1_0038pF                                                   0b000000010

#define CS1_4864pF                                                   0b100000000//NOMINAL
        
#define CS1_9709pF                                                   0b111111111
    
    
    
#define ICS1_0                                                            0b0000000000//NOMINAL
#define ICS1_0019pF                                                   0b0000000001        
#define ICS1_0038pF                                                   0b0000000010
    
#define ICS1_4864pF                                                   0b000000001//NOMINAL
        
#define ICS1_9709pF                                                   0b111111111
    
    
 //   ------COMPENSATION CAPACITOR ARRAY - (CS2) ------------------------//
#define CS2_0                                                            0b000000//NOMINAL
#define CS2_0019pF                                                   0b000001        
#define CS2_0038pF                                                   0b000010
#define CS2_1197pF                                                   0b111111

    


    
    
    

        //------LOW PASS FILTER BANDWIDTH - (CSELECT) ------------------------//
#define LPF_BW_8k                                                  0b0000
#define LPF_BW_5_8k                                               0b0001
#define LPF_BW_4_2k                                               0b0010
#define LPF_BW_3k                                                  0b0011 
#define LPF_BW_2k                                                  0b0100     
#define LPF_BW_1_4k                                               0b0101
#define LPF_BW_1k                                                  0b0110
#define LPF_BW_0_8k                                               0b0111
#define LPF_BW_0_5k                                               0b1000
    

#define ILPF_BW_8k                                                  0b0000
#define ILPF_BW_5_8k                                               0b1000
#define ILPF_BW_4_2k                                               0b0100
#define ILPF_BW_3k                                                  0b1100 
#define ILPF_BW_2k                                                  0b0010     
#define ILPF_BW_1_4k                                               0b1010
#define ILPF_BW_1k                                                  0b0110
#define ILPF_BW_0_8k                                               0b1110
#define ILPF_BW_0_5k                                               0b0001    
    
    
    
    
    
    

         //   ------Off REf LEv - (SOFF) ------------------------// 
#define OFFSET_REF_2_25                                           0b0
#define OFFSET_REF_0_5                                             0b1
    

    
    //------DC OFFSET TRIM (~6.25mV/ste) - (OFF) ------------------------// 


    
   //------DC OFFSET TRIM (~6.25mV/ste) - (OFF) ------------------------// 
#define DC_OFFSET_100m                                            0b00000     
#define DC_OFFSET_N                                                  0b10000                 
#define DC_OFFSET100m                                              0b11110

    
 //------Gain Control (~0.0024V/V per step) - (B) gor GAINSEL = 0 ------------------------// 
#define GAIN_CNT_15                                             0b00000000     
#define GAIN_CNTN                                                0b10000000                 
#define GAIN_CNT15                                               0b11111111
    
    

 //------ Nominal Output Buffer Gain  ------------------------// 
#define GAIN_4V                                              0b1     
#define GAIN_2V                                              0b0
    

 //------ EEPROM ADDRESS  ------------------------// 
#define ADDR9                                              0b1001     
#define ADDR8                                              0b1000   
#define ADDR7                                              0b0111     
#define ADDR6                                              0b0110
#define ADDR5                                              0b0101     
#define ADDR4                                              0b0100    
#define ADDR3                                              0b0011    
#define ADDR2                                              0b0010    
#define ADDR1                                              0b0001    
#define ADDR0                                              0b0000    
    
    
 /*Sample WRITE_CNT_REG ((CS2,inv(CS1),inv(CF),GAIN,inv(BW),SOFF,OFF,GAINCNT,OSC,inv(VREF),inv(IREf))  */   
//#define WRITE_CNT_REG(CS2,CS1,CF,GAIN,BW,SOFF,OFF,GAINCNT,OSC,IVREF,IREF)         (((unsigned long long int)00<<58)|((unsigned long long int)CS2<<52)|((unsigned long long int)CS1<<43)|((unsigned long long int)CF<<33)|((unsigned long long int)0<<32)|((unsigned long long int)GAIN<<31)|((unsigned long long int)00<<29)|((unsigned long long int)BW<<25)|((unsigned long long int)SOFF<<24)|((unsigned long long int)OFF<<19)|((unsigned long long int)GAINCNT<<11)|((unsigned long long int)0<<10)|((long long int)OSC<<7)|((long long int)IVREF<<3)|((long long int)IREF)) ;
	
#define WRITE_CNT_REG(CS2,CS1,CF,GAIN,BW,SOFF,OFF,GAINCNT,OSC,IVREF,IREF)         (((unsigned long long int)000000<<58)|((unsigned long long int)CS2<<52)|((unsigned long long int)CS1<<43)|((unsigned long long int)CF<<33)|((unsigned long long int)0<<32)|((unsigned long long int)GAIN<<31)|((unsigned long long int)00<<29)|((unsigned long long int)BW<<25)|((unsigned long long int)SOFF<<24)|((unsigned long long int)OFF<<19)|((unsigned long long int)GAINCNT<<11)|((unsigned long long int)0<<10)|((long long int)OSC<<7)|((long long int)IVREF<<3)|((long long int)IREF)) ;
   

    
/*    
#define READ_CNT_REG(CS2,CS1,CF,GAIN,BW,SOFF,OFF,GAINCNT,OSC,VREF,IREf) { \
(2<<58|CS2<<52|CS1<<43|CF<<33|1<<32|GAIN<<31|2<<29|BW<<25|SOFF<<24|OFF<<19|GAINCNT<<11|1<<10|OSC<<7|VREF<<3|IREF);\	
                    }   */
    


    /**********MS3110_MACROS*************************/
#define RST             LATBbits.LATB9  // pin 18 - CHPRST

#define TST             LATBbits.LATB8       // pin17 - TST 

#define WRT             LATAbits.LATA2 // WRT pin 9

#define SHFT            LATAbits.LATA4 // SHFT pin 12

#define WRT_I             PORTAbits.RA2 // WRT

#define CLK_Pin           LATBbits.LATB15
#define MOSI_Pin          LATBbits.LATB13

/********SWITCHING CIRCUIT**************************/
#define SWT1             LATBbits.LATB5       // pin14 - SWT1
#define SWT2             LATBbits.LATB7       // pin16 - SWT2    
    
void RST_CHP(void);
void BIT_BANG (void);
void INIT_SPI (void);
int REV(int val,int len);    
    

 /*sample WRITE_EEPROM(inv(ADDR),inv(DATA))   */   
#define WRITE_EEPROM_MAC(ADDR,DATA)     ((1<<15)|(ADDR<<11)|(DATA<<1)|1) 
    
    
    
    
    

  
#ifdef	__cplusplus
}
#endif

#endif	/* NMS_3110_H */