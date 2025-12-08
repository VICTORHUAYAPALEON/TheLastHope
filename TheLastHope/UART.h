
/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            UART.h                                        *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       UART                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
#ifndef   _UART_H_
  #define _UART_H_
// Símbolos ASCII estándar
#define CR   0x0D
#define LF   0x0A
#define BS   0x08
#define ESC  0x1B
#define SP   0x20
#define DEL  0x7F

//------------UART_Init------------
// Inicializar el UART
void UART_Init(void);

//------------UART_InChar------------
// Esperar tecla para almacenar su código ascii
char UART_InChar(void);

//------------UART_OutChar------------
// Mostrar código ascii
void UART_OutChar(char data);

//------------UART_OutString------------
// Mostrar cadena
void UART_OutString(char *pt);

//------------UART_InString------------
// Solicitar que se ingrese la cadena
void UART_InString(char *bufPt, uint16_t max);
//------------UART_Caracter------------
// Output: caracter leído
//Espera a que se ingrese un caracter

//--------UART_Caracter-----------
//Solicita que se ingrese un caracter
uint8_t UART_Caracter(void);

//Elaborado por Victor Huayapa
//------------sondea_UART------------
// Detecta si se ha ingresado un caracter ,sin esperar
// Input: *caracter : es el caracter ingresado, si lo hubiese
//        *flag_hay_caracter: solo se pone en 1 si hay caracter y la vez anterior q se ingresó
//										a esta funcion no había.
// Output: --- 
void sondea_UART(uint8_t *flag_hay_caracter,uint8_t *caracter);

#endif