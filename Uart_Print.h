/* ************************************************************************** */
 // Header containing print functions
/* ************************************************************************** */

#ifndef _UART_PRINT_H    /* Guard against multiple inclusion */
#define _UART_PRINT_H


#ifdef __cplusplus
extern "C" {
#endif

#define clrscr()  printf("\033[2J")    
#define sys_clk      64000000

/* -----UART parameters-- ------------------ -= = */
void SendChar(char c);
void SendString(char *string);
char ReadChar(void);
void ReadString(char *string, int length);
void ReadUART(char * message, int maxLength);

//void SendDataBuffer(const char *buffer, UINT32 size);
void DMA_send(char *data_byte);
//void CIRCULAR_BUFFER(signed int Avg);

/* -----UART INIT parameters-- ------------------ -= = */
void INIT_UART(void);
//void INIT_DMA(void);
void INIT_DMA(unsigned int BUFF_SIZE, char buffer[BUFF_SIZE] );

    /* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _EXAMPLE_FILE_NAME_H */

