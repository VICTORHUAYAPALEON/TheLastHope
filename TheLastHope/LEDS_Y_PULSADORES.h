/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÕA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            LEDS_Y_PULSADORES.h                             *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       GPIO PORTF                                      *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Victor Huayapa Leon                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
/***** Funciones para el control del led RGB y de los pulsadores SW1 y SW2 .       *****/

#include <stdint.h>
#include "tm4c123gh6pm.h"


#ifndef  _LEDS_Y_PULSADORES_H_
 #define  _LEDS_Y_PULSADORES_H_

/*TOMADO DEL PROFESOR ROLANDO SANCHEZ PONCE DESDE AQUÕ*/
/*****              CONSTANTES PARA M√ÅSCARAS DE LOS PULSADORES                      *****/
#define SW2         0x00000001      // Pulsador conectado a PF0
#define SW1         0x00000010      // Pulsador conectado a PF4

/*****              CONSTANTES PARA COLORES DEL LED RGB                             *****/
#define ROJO        0x00000002      // Led conectado a PF1
#define AZUL        0x00000004      // Led conectado a PF2
#define VERDE       0x00000008      // Led conectado a PF3
#define MAGENTA     (ROJO|AZUL)
#define AMARILLO    (ROJO|VERDE)
#define CIAN        (AZUL|VERDE)
#define BLANCO      (ROJO|VERDE|AZUL)
#define NEGRO       0
/*TOMADO DEL PROFESOR ROLANDO SANCHEZ PONCE HASTA AQUÕ*/


/****************************************************************************************/
/*****                      config_puertoF()                                     *****/
/****************************************************************************************/
/***** Configura los pines del microcontrolador de la tarjeta TIVA que controlan    *****/
/***** los tres leds (rojo, verde y azul) y los dos pulsadores (SW1 y SW2).         *****/
/****************************************************************************************/
/***** ENTRADAS:    Ninguna                                                         *****/
/***** SALIDA:      Ninguna                                                         *****/
/****************************************************************************************/
void config_puertoF(void);



/****************************************************************************************/
/*****                     sondea_pulsador()                                 *****/
/****************************************************************************************/
/***** Revisa si se ha producido el evento de presionar el pulsador conectado al    *****/
/***** pin especificado en la entrada de la funciÛn.                               *****/
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
void sondea_pulsador(uint8_t *antSW,uint8_t mask_SW,uint8_t *flanco_bajadaSW);


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
void maneja_led(uint8_t color,uint8_t encender);

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
void parpadea_led(uint8_t color, uint32_t retardo );

#endif


















