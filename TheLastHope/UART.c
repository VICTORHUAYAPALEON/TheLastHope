/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            UART.c                                        *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       UART                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/


#include <stdint.h>
#include "UART.h"
#include "tm4c123gh6pm.h"


#define UART_FR_TXFF            0x00000020  // UART FIFO TRANSMISOR LLENO
#define UART_FR_RXFE            0x00000010  // UART FIFO RECEPTOR VACÍO
#define UART_LCRH_WLEN_8        0x00000060  // Longitud de palabra de 8
#define UART_LCRH_FEN           0x00000010  // UART Habilitar FIFO
#define UART_CTL_UARTEN         0x00000001  // Habilitar UART

//Harif Meza
//------------UART_Init------------
// 115,200 baud rate
void UART_Init(void){
  SYSCTL_RCGCUART_R |= 0x01;            // activar UART0
  SYSCTL_RCGCGPIO_R |= 0x01;            // activar puerto A
  while((SYSCTL_PRGPIO_R&0x01) == 0){};
  UART0_CTL_R &= ~UART_CTL_UARTEN;      // deshabilitar UART
  UART0_IBRD_R = 43;                    // IBRD = int(80,000,000 / (16 * 115,200)) = int(43.4028)
  UART0_FBRD_R = 26;                     // FBRD = int(0.4028 * 64 + 0.5) = 26
                                        // 8,N,1
  UART0_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART0_CTL_R |= 0x301;                 // habilitar uart
  GPIO_PORTA_AFSEL_R |= 0x03;           
  GPIO_PORTA_DEN_R |= 0x03;             
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011;
  GPIO_PORTA_AMSEL_R &= ~0x03;          // desabilitar funciones aanalógicas
}

//------------UART_InChar------------
// Espera que se ingrese una tecla
// Output: código ASCCI de la tecla ingresada
char UART_InChar(void){
  while((UART0_FR_R&UART_FR_RXFE) != 0);
  return((char)(UART0_DR_R&0xFF));
}
//------------UART_OutChar------------
//Muestra el código ascci del valor ingresado
//Código ASCII a transferir
void UART_OutChar(char data){
  while((UART0_FR_R&UART_FR_TXFF) != 0);
  UART0_DR_R = data;
}

//------------UART_Caracter------------Elaborado por Harif Meza
// Output: caracter leído

uint8_t UART_Caracter(){                // Recepción de un caracter
	uint8_t temp;
	while ((UART0_FR_R & UART_FR_RXFE)); // Se espera que el buffer de recepción no esté vacío
	temp = (uint8_t)UART0_DR_R; 								// Se consideran solo 8 bits y se recibe el caracter
	return temp;
}

//------------UART_OutString------------
// Input: arreglo de donde se obtiene la cadena
void UART_OutString(char *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}

//------------UART_InString------------
// Recibe una cadena de caracteres
//    y los une a una cadena hasta que se presiona enter
//    o hasta que se llegue a la longitud máxima
// Muestra la cadena de caracteres.
// Si se 'borra' se muestra el caracter reemplazante
// Input: arreglo donde se almacenará
// Output: largo de la cadena
void UART_InString(char *bufPt, uint16_t max) {
int length=0;
char character;
  character = UART_InChar();
  while(character != CR){
    if(character == BS){
      if(length){
        bufPt--;
        length--;
        UART_OutChar(BS);
      }
    }
    else if(length < max){
      *bufPt = character;
      bufPt++;
      length++;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  *bufPt = 0;
}


//Elaborado por Huayapa, Victor
//------------sondea_UART------------
// Detecta si se ha ingresado un caracter sin esperar
// Input:*caracter : es el caracter ingresado, si lo hubiese
//*flag_hay_caracter: solo se pone en 1 si hay caracter y la vez anterior q se ingresó
//										a esta funcion no había.
// Output: ---
void sondea_UART(uint8_t *flag_hay_caracter,uint8_t *caracter){
    
  *flag_hay_caracter=0;
    if(!(UART0_FR_R & UART_FR_RXFE)){
        *caracter = (uint8_t)UART0_DR_R;
      	*flag_hay_caracter=1;
    }

}
