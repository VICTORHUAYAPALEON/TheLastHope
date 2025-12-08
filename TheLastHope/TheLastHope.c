/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            main.c                                          *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autores:              Victor Huayapa Leon      20181501             *****/
/*****                                Harif Meza Rojas         20180785            *****/
/*****          Fecha:              julio 2020                                    *****/
/****************************************************************************************/

#include <stdint.h>
#include "ST7735.h"
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include <stdlib.h>
#include "UART.h"
#include "SysTick.h"
#include "LEDS_Y_PULSADORES.h"
#include "MODO_JUEGO.h"
#include "mostrar_ocultar.h"
#include "MENU.h"
#include "DAC.h"

#define ROJO        0x00000002      // Led conectado a PF1
#define SW2         0x00000001      // Pulsador conectado a PF0
#define SW1         0x00000010      // Pulsador conectado a PF4


//DAC
uint8_t flag_sonido=1;
const unsigned char SineWave[48] = {
     0,0,1,1,1,2,2,3,4,5,6,7,8,9,10,11,12,13,13,14,14,14,15,15,
     15,15,14,14,14,13,13,12,11,10,9,8,7,6,5,4,3,2,2,1,1,1,0,0
};
uint16_t i=0;
//SYSTICK HANDLER 
//variables que controlan el systick
uint16_t n_ciclos=0;
uint16_t n_seg=1;
uint8_t enable_cont_seg=0;
int8_t opc_menu=0;
uint8_t flag_start=0;
//interrupcion cada 1ms 
void SysTick_Handler(void){
	
	 temp2(&enable_cont_seg); //controla el tiempo de juego
	if(enable_cont_seg==1){
    if(n_ciclos==1000){
			n_seg++;
			temp1(&n_seg);
			GPIO_PORTF_DATA_R ^=ROJO; //cada segundo se va alternando el estado del led rojo, esta prendido 1 seg y apagado 1 seg
			n_ciclos=0;
		}
		else{n_ciclos++;}
	}
	if (flag_sonido) {
	if(i < 49){
        i++;
        if(i == 48){
            i = 0;
        }
    }
    DAC_Out(SineWave[i]);} else {DAC_Out(0);}
}

//MAIN						
int main(void) {	
	uint8_t caracter;
	PLL_Init(Bus80MHz);	// set system clock to 80 MHz
	DAC_Init();
	config_puertoF();
	UART_Init();
	ST7735_InitR(INITR_REDTAB);
	ConfiguraSystick_1ms();
	while (1) {
		mostrarInicio();
		caracter=UART_Caracter();
	if (caracter=='s') {opc_menu=0;flag_start=1;
		  ocultarInicio();
			mostrar_menuPrincipal();}
	while (flag_start) { //Iniciar partida, instrucciones, mutear, salir
			switch (opc_menu){

			  case 0:   partida(&opc_menu); break;	
				case 1:   instrucciones(&opc_menu); break;
				case 2:   mutear(&opc_menu,&flag_sonido); break;
				case 3:   salir(&opc_menu,&flag_start); break;
			}
		}
	}
}
