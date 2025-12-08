
/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            DAC.h                                        *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       DAC                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Adaptación:          Harif Joe Meza Rojas                           *****/
/*****          Fecha:              julio 2020                                    *****/
/****************************************************************************************/
	#ifndef   _DAC_H_
  #define _DAC_H_
	
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define DACOUT                  (*((volatile unsigned long *)0x4000503C))
	//#define NVIC_SYS_PRI3_R         (*((volatile unsigned long *)0xE000ED20))
//#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
//#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
//#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

// Configura PortB para la salida del DAC
void DAC_Init(void);

// Parametros de salida para PORTB
void DAC_Out(unsigned long data);
//void Sound_Init(void);
#endif