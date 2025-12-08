/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            Systick.h                                        *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       Systick                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
/**********************************Extensión Victor Huayapa***************************/

#ifndef   _SysTick_H_
  #define _SysTick_H_
// Inicializar el Systick
void SysTick_Init(void);  

//CONFIGURACION DEL SYSTICK A 1ms
void ConfiguraSystick_1ms(void); //Extensión Victor Huayapa

// Delay (unidades de 20 nsec
void SysTick_Wait(uint32_t delay);

// Delay (unidades de 10ms)
void SysTick_Wait10ms(uint32_t delay);

#endif