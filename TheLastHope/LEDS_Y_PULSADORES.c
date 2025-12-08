/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            LEDS_Y_PULSADORES.c                                        *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       GPIO PORTF                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Victor Huayapa Leon                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
/***** Funciones para el control del led RGB y de los pulsadores SW1 y SW2 .       *****/

#include <stdint.h>
#include "tm4c123gh6pm.h"
#include  "LEDS_Y_PULSADORES.h"
/****************************************************************************************/
/*****                      config_puertoF()                                     *****/
/****************************************************************************************/
/***** Configura los pines del microcontrolador de la tarjeta TIVA que controlan    *****/
/***** los tres leds (rojo, verde y azul) y los dos pulsadores (SW1 y SW2).         *****/
/****************************************************************************************/
/***** ENTRADAS:    Ninguna                                                         *****/
/***** SALIDA:      Ninguna                                                         *****/
/****************************************************************************************/
void config_puertoF(void){
  //reloj
	SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R5; 
  //activacion reloj
	while (!(SYSCTL_PRGPIO_R & SYSCTL_PRGPIO_R5) );
	//desbloquear PF0
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R |= 0x01;
	
	//entradas salidas
	GPIO_PORTF_DIR_R |= 0x0E;
	GPIO_PORTF_DIR_R &= ~(0x11);
	//resistencias pull up 
	GPIO_PORTF_PUR_R |= 0x11;
	//drivers de 8mA
	GPIO_PORTF_DR8R_R |= 0x0E;
	//desactivar funciones alternativas
	GPIO_PORTF_AFSEL_R &= ~(0x1F);
  //pctl controlados por GPIO
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFF00000)|0x00000000;
  //funciones analogicas y digitales
	GPIO_PORTF_AMSEL_R &= ~(0x1F);
	GPIO_PORTF_DEN_R |= 0x1F;
  //data inicial
	GPIO_PORTF_DATA_R &= ~(0x0E);
}



/****************************************************************************************/
/*****                     sondea_pulsador()                                 *****/
/****************************************************************************************/
/***** Revisa si se ha producido el evento de presionar el pulsador conectado al    *****/
/***** pin especificado en la entrada de la función.                               *****/
/****************************************************************************************/
/***** ENTRADAS:                                                                    *****/
/*****              *antSW: estado anterior del switch   1: presionado                 *****/
/*****                                                   0: no presionado              *****/
/*****              mask_SW: es el que elije con que pulsador estamos tratando         *****/
/*****             *flanco_bajadaSW: solo devuelve 1 si es que el pulsador esta suelto   
                    y la vez anterior que se uso  el pulsador estaba presionado     *****/
/***** SALIDAS: Ninguna                                                             *****/
/*****                                                                              *****/
/****************************************************************************************/
void sondea_pulsador(uint8_t *antSW,uint8_t mask_SW,uint8_t *flanco_bajadaSW) {
uint8_t actSW=1;
*flanco_bajadaSW=0;


	//esta suelto el switch?
	if ( GPIO_PORTF_DATA_R &mask_SW ) {
	   actSW=0;
		}
    if ( (*antSW ==1) && (actSW==0)) {
    	*flanco_bajadaSW=1;
	}
	
    *antSW= actSW;	
		
}


/****************************************************************************************/
/*****                      maneja_led()                                       *****/
/****************************************************************************************/
/***** Enciende o apaga el led RGB de la tarjeta TIVA con el color indicado en la entrada.  *****/
/****************************************************************************************/
/***** ENTRADAS:                                                                    *****/
/*****    color:    Puede ser una de las ocho constantes para colores definidas     *****/
/*****              previamente: ROJO, AZUL, VERDE, MAGENTA, AMARILLO, CIAN, BLANCO *****/
/*****              o NEGRO.                                                        *****/
/***** SALIDA:      Ninguna                                                         *****/
/****************************************************************************************/
void maneja_led(uint8_t color,uint8_t encender){

	if (encender) {
	GPIO_PORTF_DATA_R |=color;
	}
	else {
	GPIO_PORTF_DATA_R &= ~color;
	}
}


/****************************************************************************************/
/*****                    parpadea_led()                                    *****/
/****************************************************************************************/
/***** Parpadea el led RGB de la tarjeta TIVA con el color y con un tiempo de     *****/
/***** definido por el programador                                      *****/
/****************************************************************************************/
/***** ENTRADAS:                                                                    *****/
/*****    color:    Puede ser uno de las ocho constantes para colores definidas     *****/
/*****              previamente.                                                    *****/
/*****   retardo: lo define el programador,Fsysclk= 16Mhz                           *****/
/***** SALIDA:      Ninguna                                                         *****/
/****************************************************************************************/
void parpadea_led(uint8_t color, uint32_t retardo ){
uint32_t i;	
	 maneja_led(color, 1);
	for(i=0;i< retardo;i++ ){
	}	
	 maneja_led(color, 0);
}


