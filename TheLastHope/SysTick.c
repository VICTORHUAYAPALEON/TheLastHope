/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            Systick.c                                        *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       Systick                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
/*****************************Extensión Victor Huayapa***********************************/


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Systick.h"
#define NVIC_ST_CTRL_COUNT      0x00010000  // Cuenta
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock usado
#define NVIC_ST_CTRL_INTEN      0x00000002  // Habilitador de interrupciones
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Habilitador
#define NVIC_ST_RELOAD_M        0x00FFFFFF  // Valor de tope de cuenta

//Elaborado por Meza, Harif
void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;                   // deshabilitamos SysTick
  NVIC_ST_RELOAD_R = NVIC_ST_RELOAD_M;  // valor de cuenta
  NVIC_ST_CURRENT_R = 0;                // cualquier valor lo borra
  NVIC_ST_CTRL_R                                        // habilitar systick con reloj principal
 = NVIC_ST_CTRL_ENABLE+NVIC_ST_CTRL_CLK_SRC;
	
}


//Extensión Huayapa, Victor
void ConfiguraSystick_1ms(void)
	{                                     
 /*Inhabilitamos el módulo SysTick*/
 NVIC_ST_CTRL_R &= ~NVIC_ST_CTRL_ENABLE;
 /* TiempoDeseado=1ms; FreqCPU=16MHZ
 * valor que debe ir en el registro RELOAD=X
 * X=(TiempoDeseado)*(FreqCPU) -1
 * X= [[1*10^(-3)] * [80*10^(6)]] -1 =79999
 *49999 en hexadecimal es 0000C34F*/
 NVIC_ST_RELOAD_R = (NVIC_ST_RELOAD_R&0xFF000000)|0x0001387F;  //Cambio a 80MHz. Meza, Harif
 // Iniciamos el contador con cero (escribiendo cualquier valor)
 NVIC_ST_CURRENT_R &= ~(0x00FFFFFF);
 // Habilitamos el módulo SysTick
 NVIC_ST_CTRL_R |= (NVIC_ST_CTRL_CLK_SRC | NVIC_ST_CTRL_INTEN | NVIC_ST_CTRL_ENABLE); //modificación para interrupción Huayapa,Victor
} 
	


//Elaborado por Meza, Harif
// delay (unidades de 20 nsec)
void SysTick_Wait(uint32_t delay){
  volatile uint32_t transcurrido;
  uint32_t tiempoinicio = NVIC_ST_CURRENT_R;
  do{
    transcurrido = (tiempoinicio-NVIC_ST_CURRENT_R)&0x00FFFFFF;
  }
  while(transcurrido <= delay);
}
//Delay 10 ms
void SysTick_Wait10ms(uint32_t delay){
  uint32_t i;
  for(i=0; i<delay; i++){
    SysTick_Wait(500000); 
  }
}




