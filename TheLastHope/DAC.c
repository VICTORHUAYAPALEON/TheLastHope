/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            DAC.c                                        *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       DAC                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Adaptación:          Harif Joe Meza Rojas                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
#include "DAC.h"

// OUTPUT PortB(APB) base address: 0x40005000 (Datasheet pg. 657)
#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))
#define GPIO_PORTB_DR8R_R       (*((volatile unsigned long *)0x40005508))

/************************
 * DAC_Init
 ************************/
// Inicializar el Dac de 4 bits
void DAC_Init(void){unsigned int delay;
    SYSCTL_RCGC2_R |= 0x00000002;
    delay = SYSCTL_RCGC2_R;

    GPIO_PORTB_DEN_R        |=      0x0F;
    GPIO_PORTB_DIR_R        |=      0x0F;
		GPIO_PORTB_DR8R_R 			|= 			0x0F;  
	
    GPIO_PORTB_AMSEL_R      &=      ~0x0F;
    GPIO_PORTB_AFSEL_R      &=      ~0x0F;
    GPIO_PORTB_PCTL_R       &=      ~0x0000FFFF;
}

/************************
 * DAC_Out
 ************************/
// salida del DAC
// Input: 4-bit data, 0 a 15
void DAC_Out(unsigned long data){
		DACOUT = data;
}
