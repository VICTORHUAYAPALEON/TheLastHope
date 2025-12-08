/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/****************************************************************************************/
/*****          Archivo:            MODO_JUEGO.c                            *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       ST7735, UART,LEDS_Y_PULSADORES                  *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Victor Huayapa Leon                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
/***** Funciones para toda la logica del juego en si, movimiento de personajes, proyectiles,explosión *****/


#include <stdint.h>
#include "ST7735.h"
#include "tm4c123gh6pm.h"
#include "PLL.h"
#include <stdlib.h>
#include "UART.h"
#include "SysTick.h"
#include "LEDS_Y_PULSADORES.h"
#include "MODO_JUEGO.h"


const uint16_t  proyectil_negro[] = {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,

};

const   uint16_t alien_1[] =  {
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFDF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFDF, 0xFFDF, 0xFFDF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF,
 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xFFFF, 0xFFFF, 0x0000, 0x0000, 0x0000, 0x0000,


}; //dimensiones: 22 ancho , 16 altura


 //dimensiones: 22 ancho , 16 altura
 const   uint16_t proyectil_aliens[] = {
 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF,

	};  //dimensiones: 2 ancho , 4 altura

const uint16_t explosion[] ={
 0x10B7, 0x39DA, 0x000B, 0x0008, 0x0004, 0x0003, 0x0004, 0x0009, 0x10D9, 0x089D, 0x0014, 0x0017, 0x0013, 0x0876, 0x0009, 0x0005,
 0x0001, 0x0002, 0x0009, 0x000D, 0x297A, 0x1077, 0x000C, 0x08D4, 0x1114, 0x21B3, 0x0006, 0x0004, 0x0009, 0x00F1, 0x0139, 0x00BA,
 0x0058, 0x115B, 0x0056, 0x0158, 0x0912, 0x0007, 0x0004, 0x0006, 0x0112, 0x1177, 0x10D5, 0x000D, 0x0008, 0x0009, 0x64FF, 0x0175,
 0x0151, 0x000A, 0x0195, 0x0176, 0x5DFF, 0x245F, 0x00B4, 0x1BDF, 0x0C5F, 0x563F, 0x2BDF, 0x0176, 0x000B, 0x0155, 0x01D7, 0x64FF,
 0x0009, 0x0007, 0x198F, 0x0008, 0x01D6, 0x663F, 0x3D3F, 0x247E, 0x035B, 0x6EBF, 0x01D3, 0x467F, 0x147D, 0x043C, 0x3EBF, 0x0295,
 0x0194, 0x5E3F, 0x0198, 0x1B5F, 0x65DF, 0x0175, 0x002C, 0x20ED, 0x000A, 0x0113, 0x00B3, 0x34DF, 0x3EBF, 0x3F3F, 0x5F3F, 0x7FFF,
 0x673F, 0x5F1F, 0x0497, 0x67BF, 0x5F7F, 0x577F, 0x471F, 0x4F5F, 0x03FB, 0x4DFF, 0x23BF, 0x0118, 0x0914, 0x000A, 0x000C, 0x0136,
 0x33DF, 0x000B, 0x057D, 0x275F, 0x6FFF, 0x675F, 0x87DF, 0x97FF, 0x87BF, 0x7F9F, 0x97FF, 0x679D, 0x6FFF, 0x57FF, 0x04FC, 0x043E,
 0x00D5, 0x443F, 0x0116, 0x000D, 0x0938, 0x43BF, 0x0135, 0x0C7F, 0x269F, 0x0539, 0x4F9E, 0x87FF, 0x9FFF, 0xBFFF, 0xC7BF, 0xCFFF,
 0xAF9E, 0xA7FF, 0x77FF, 0x371E, 0x26DF, 0x043B, 0x0CFF, 0x2C9F, 0x3BDF, 0x00B4, 0x000E, 0x0178, 0x13BF, 0x3E3F, 0x3F3F, 0x3F7F,
 0x4F9D, 0x7FFF, 0x9FBF, 0xCFFF, 0xEFFF, 0xE7DF, 0xD7FF, 0xAFFF, 0x7FFF, 0x57BF, 0x2F1F, 0x375F, 0x2E7F, 0x145E, 0x0136, 0x000E,
 0x000E, 0x00D6, 0x23FF, 0x14DF, 0x051F, 0x3F3F, 0x57DF, 0x7FFE, 0xAFFF, 0xD7FF, 0xEFFF, 0xEFFF, 0xDFFF, 0xAFBF, 0x87FF, 0x579F,
 0x04FA, 0x3F5F, 0x2E1F, 0x1C3F, 0x00F7, 0x0012, 0x08F7, 0x4BBF, 0x0198, 0x03DF, 0x043D, 0x4FBF, 0x3F1E, 0x8FFF, 0x9FBF, 0xC7FF,
 0xCFFF, 0xD7FF, 0xC7DF, 0xB7FF, 0x87FF, 0x67FF, 0x0DDD, 0x041A, 0x03FE, 0x01FA, 0x3ADF, 0x0018, 0x000C, 0x1998, 0x333F, 0x0157,
 0x0D1F, 0x0479, 0x67FF, 0x56DE, 0x97FF, 0xA7FF, 0x8FFF, 0x9FFF, 0xA7FF, 0x8FDF, 0x6FDF, 0x473F, 0x36FF, 0x049F, 0x0138, 0x123F,
 0x197C, 0x10B9, 0x000A, 0x1114, 0x00F7, 0x555F, 0x01F5, 0x4EDF, 0x675F, 0x5EDF, 0x8FFF, 0x6F5F, 0x0454, 0x677F, 0x8FFF, 0x777F,
 0x673F, 0x2DBE, 0x0CDE, 0x35BF, 0x01BB, 0x00FA, 0x0096, 0x000D, 0x31D0, 0x000A, 0x01B8, 0x5D9F, 0x135D, 0x3CDF, 0x0BDE, 0x01F5,
 0x569F, 0x0C7B, 0x1D1D, 0x045B, 0x5F1F, 0x0274, 0x2C7D, 0x137C, 0x1BDF, 0x34FF, 0x563F, 0x01D5, 0x000A, 0x29B2, 0x0008, 0x000A,
 0x5CDF, 0x0115, 0x09B5, 0x000A, 0x01B4, 0x0194, 0x665F, 0x245F, 0x13BE, 0x1BDE, 0x2C9F, 0x4D5F, 0x0193, 0x000D, 0x0135, 0x01D6,
 0x5E3F, 0x1BDA, 0x0008, 0x0008, 0x000D, 0x0895, 0x1177, 0x19B4, 0x0005, 0x0004, 0x0087, 0x8E1F, 0x0136, 0x0077, 0x11BC, 0x00D8,
 0x0095, 0x21F6, 0x0006, 0x0004, 0x0007, 0x32D5, 0x0170, 0xA6FF, 0x1155, 0x000D, 0x18DA, 0x297B, 0x000C, 0x0008, 0x0003, 0x0042,
 0x0001, 0x0006, 0x0938, 0x0012, 0x0018, 0x0011, 0x1898, 0x000A, 0x0004, 0x0001, 0x0004, 0x0006, 0x0008, 0x0009, 0x21B9, 0x193A,


};




#define ALIEN   1
#define JUGADOR 2
#define JUGADOR_MATA_ALIEN 3
#define SW2         0x00000001      // Pulsador conectado a PF0
#define SW1         0x00000010      // Pulsador conectado a PF4




//------------mueve_fila------------
//mueve una fila de aliens, si estan vivos los muestra,caso contrario no
// Input: uint8_t *alien_x2 :es la posicion de la esquina izquierda del alien mas a la izquierda de la fila
//        uint8_t y:  es la posicion de mas abajo del alien de la fila de mas arriba
//        int8_t *sentido2 : es hacia donde se dirigen todos los aliens +2(derecha)  -2(izquierda)
//        uint8_t vida_aliens[]: arreglo que contiene el estado de los 12 aliens(el contenido de cada elemento es 0 o 1)
//        uint8_t nro_fila: es la fila en la cual se está trabajando.
// Output: --- 

void mueve_fila(uint8_t *alien_x2,uint8_t y,int8_t *sentido2,uint8_t vida_aliens[],uint8_t nro_fila) {
uint8_t nro_alien;	
uint8_t alien_x =*alien_x2;
int8_t sentido= *sentido2;

  //borra la anterior imagen del alien y escribe la nueva 2 pixeles a la derecha o a la izquierda sea el caso
	for (nro_alien=0; nro_alien <4;nro_alien++) {
		 
		 
		 ST7735_DrawBitmap( alien_x +nro_alien*26 -sentido ,y,fondo_negro, 22, 16); //recordemos que el ancho(del alien)=22 y la separacion del final de un alien y el inicio de otro es 4,por lo que cada alien esta separado 26 del otro
		                                                                              //ademas;aqui le restamos sentido ya que lo que queremos borrar es la anterior posicion
		 if(vida_aliens[nro_fila*4+ nro_alien] ==1){
	   ST7735_DrawBitmap( alien_x +nro_alien*26 ,y,alien_1, 22, 16);	//recordemos que el ancho(del alien)=22 y la separacion del final de uno y el inicio de otro es 4,por lo que cada alien esta separado 26 del otro
		 }
	}
	
	(*alien_x2) = alien_x;
	
	
}









//------------mueve_aliens------------
//mueve a todos los aliens hacia una direccion que depende de su posicion, invoca a "mueve_fila"
// Input: *alien_x :es la posicion de la esquina izquierda del alien mas a la izquierda de la fila
//          uint8_t alien_y:  es la posicion de mas abajo del alien de la fila de mas arriba
//        int8_t *sentido : es hacia donde se dirigen todos los aliens +2(derecha)  -2(izquierda)
//        uint8_t vida_aliens[]: arreglo que contiene el estado de los 12 aliens(el contenido de cada elemento es 0 o 1)
// Output: --- 
void mueve_aliens(uint8_t *alien_x, uint8_t alien_y,int8_t *sentido,uint8_t vida_aliens[]){ 
	int8_t sentido2;  
	uint8_t nro_fila;	
	uint8_t alien_x2;

		sentido2= *sentido;
		alien_x2= *alien_x;

	//esto nos sirve para las situaciones limite, cuando esté en el limite se mueve para el otro lado
	//cuando el alien de más a la derecha está en el limite	
			if( (alien_x2 + 102) >127 ) {  //recordemos que el ancho=22 y separacion del final de un alien y el inicio de otro es  4, y el numero de aliens por fila es 4  ; (22+4) *4  - 4 =102
		sentido2=-2;
		}
    //cuando el alien de más a la izquierda está en el limite		
		if ( (alien_x2 -2) <0 ) {  
		sentido2=2;	
		}
		
	//mueve una fila de aliens ,ahora solo serán 3 filas
		 for(nro_fila=0; nro_fila <3; nro_fila++) {
			mueve_fila(&alien_x2, alien_y + nro_fila*20,&sentido2,vida_aliens,nro_fila );  //mueve una fila, cada ciclo a alien_y le sumamos 20 
																															 //porque una fila esta 20 pixeles abajo de otra
		 }
		 alien_x2= alien_x2+ sentido2;  //la siguiente vez que escribamos las filas tienen que estar 2 a la derecha o a la izquierda sea el caso
		 
		 (*sentido)= sentido2;
		 (*alien_x)= alien_x2;
	 

}










//------------genera_proyectil------------
//genera el proyectil para los aliens
// Input: uint8_t *cant_proy:es la cantidad de proyectiles que tienen los aliens
//      uint8_t proy_x[]:  es el arreglo que contiene las abscisas de los proyectiles de los aliens
//      uint8_t proy_y[]:es el arreglo que contiene las ordenadas de los proyectiles de los aliens
//      uint8_t alien_x: es la posicion de la esquina izquierda del alien mas a la izquierda de la fila
//      uint8_t alien_y: es la posicion de mas abajo del alien de la fila de mas arriba
//      uint8_t jug_x:es la posicion de la esquina izquierda de la nave defensora(o jugador)
//        uint8_t vida_aliens[]: arreglo que contiene el estado de los 12 aliens(el contenido de cada elemento es 0 o 1)
// Output: --- 
void genera_proyectil(uint8_t *cant_proy,uint8_t proy_x[], uint8_t proy_y[],uint8_t alien_x,uint8_t alien_y,uint8_t jug_x,uint8_t vida_aliens[]) {
uint8_t alien_fila=0;	
uint8_t alien_dispara;
	
	
	alien_dispara= jug_x/26;
	
	if (vida_aliens[alien_dispara]==1 ) {
	ST7735_DrawBitmap(alien_x+	alien_dispara*26+10 ,alien_y +alien_fila*20 ,proyectil_aliens, 2, 4);	
	*cant_proy= *cant_proy+1;
	proy_x[ *cant_proy-1 ] = alien_x+alien_dispara*26+10;
	proy_y[ *cant_proy-1 ] =alien_y +alien_fila*20 ;
	}
	
}







//------------ mueve_proyectiles------------
//mueve todo el arreglo que contiene los proyectiles, existen los casos que los proyectiles sean del jugador o de los aliens
// Input: uint8_t *cant_proy:es la cantidad de proyectiles que hay (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_x[]:  es el arreglo que contiene las abscisas de los proyectiles(podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_y[]:es el arreglo que contiene las ordenadas de los proyectiles (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t alien_x: es la posicion de la esquina izquierda del alien mas a la izquierda de la fila
//      uint8_t alien_y: es la posicion de mas abajo del alien de la fila de mas arriba
//      uint8_t caso: elije proyectiles de quién se va a mover (1: aliens, 2: jugador)

void mueve_proyectiles(uint8_t cant_proy, uint8_t proy_x[],uint8_t proy_y[],uint8_t caso) {
uint8_t i;
	
switch (caso) {

		case ALIEN:
		for(i=0;i<cant_proy;i++) {
			ST7735_DrawBitmap(proy_x[i],proy_y[i],proyectil_negro, 2, 4);	
				proy_y[i] = proy_y[i] +2;
			ST7735_DrawBitmap(proy_x[i],proy_y[i],proyectil_aliens, 2, 4);	
		}	
		break;
		
		case JUGADOR:
		for(i=0;i<cant_proy;i++) {
			ST7735_DrawBitmap(proy_x[i],proy_y[i],proyectil_negro, 2, 4);	
			proy_y[i] = proy_y[i] -2;
			ST7735_DrawBitmap(proy_x[i],proy_y[i],proyectil_nave, 2, 4);	
		}	
		break;



	}	
	
}







//------------modifica_arreglo_proy------------
//elimina el proyectil que debe ser borrado y traslada todos los demas.
// Input: uint8_t *cant_proy2:es la cantidad de proyectiles que hay (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_x[]:  es el arreglo que contiene las abscisas de los proyectiles(podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_y[]:es el arreglo que contiene las ordenadas de los proyectiles (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t det: es el elemento del arreglo que debe ser eliminado
void  modifica_arreglo_proy(uint8_t det,uint8_t *cant_proy2,uint8_t proy_x[],uint8_t proy_y[]){
uint8_t i;
	
	for(i=det;i<(*cant_proy2); i++ ){
		proy_x[i] =	proy_x[i+1]; 
		proy_y[i] =	proy_y[i+1];
		
	}
	*cant_proy2= *cant_proy2 -1;
}







//------------borra_proyectiles------------
//cuando un proyectil impacta o sale del escenario, este debe desaparecer y el arreglo que manipula los proyectiles debe ser actualizado,
//invoca a modifica_arreglo_proy
// Input: uint8_t *cant_proy:es la cantidad de proyectiles que hay (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_x[]:  es el arreglo que contiene las abscisas de los proyectiles(podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_y[]:es el arreglo que contiene las ordenadas de los proyectiles (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t det: es el elemento del arreglo que debe ser eliminado
//      uint8_t caso: elije proyectiles de quién se va a borrar (1: aliens, 2: jugador,3: jugador_mata_alien)
void borra_proyectiles(uint8_t np,uint8_t *cant_proy,uint8_t proy_x[],uint8_t proy_y[],uint8_t caso){
uint8_t cant_proy2 =*cant_proy;
uint8_t i=0;
switch (caso) {
		case ALIEN:
		do{
			if(proy_y[i] >=159) {  //tope 
				if (cant_proy2 >0){
				ST7735_DrawBitmap(proy_x[i],proy_y[i],proyectil_negro, 2, 4);
				modifica_arreglo_proy(i,&cant_proy2,proy_x,proy_y);
				}
			} 
			else{i++;}
		} while( i<(cant_proy2) );

			*cant_proy=cant_proy2;
		break;
			case JUGADOR:
		do{
			if(proy_y[i] <= 0) {  //tope 
				if (cant_proy2 >0){
				ST7735_DrawBitmap(proy_x[i],proy_y[i],proyectil_negro, 2, 4);
				modifica_arreglo_proy(i,&cant_proy2,proy_x,proy_y);
				}
			} 
			else{i++;}
		} while( i<(cant_proy2) );

			*cant_proy=cant_proy2;
		break;
		
			case JUGADOR_MATA_ALIEN:
			if (cant_proy2 >0){
				ST7735_DrawBitmap(proy_x[np],proy_y[np],proyectil_negro, 2, 4);
				modifica_arreglo_proy(np,&cant_proy2,proy_x,proy_y);
				}	
			*cant_proy=cant_proy2;	
			break;
		
	}	

}













//------------ proyectil_a_alguien------------
//evalua si algun proyectil ha colisionado con algun personaje del videojuego
// Input: uint8_t *cant_proy:es la cantidad de proyectiles que hay (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_x[]:  es el arreglo que contiene las abscisas de los proyectiles(podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t proy_y[]:es el arreglo que contiene las ordenadas de los proyectiles (podria ser de los aliens o del jugador, depende de que arreglo ingreses)
//      uint8_t jug_x: contiene la abcisa del personaje a analizar, podría ser el alien o el jugador.
//      uint8_t jug_y: contiene la abcisa del personaje a analizar, podría ser el alien o el jugador.  
//      uint8_t *vidas_jugador : el numero de vidas que tiene el jugador
//      uint8_t caso: elije proyectiles de quién se va a borrar (1: aliens, 2: jugador)
void proyectil_a_alguien(uint8_t *cant_proy,uint8_t proy_x[],uint8_t proy_y[], uint8_t jug_x,uint8_t jug_y,uint8_t *vidas_jugador,uint8_t caso){
uint8_t i;	
uint8_t cant_proy2 =*cant_proy;	
uint8_t cond_borrar_proy ;	
	switch(caso){
	  case JUGADOR:
		for (i=0;i< *cant_proy; i++)  //no disminuyo la cantidad de proyectiles por q disminuye rapido				
		if( (proy_y[i] >= jug_y-8) && (proy_y[i] < jug_y-6) ){  //por la posicion vertical del jugador,como q le cae al centro
					 if( (proy_x[i] >= jug_x+2) && (proy_x[i] <= jug_x+20) ){  //posicion horizontal del jugador, en realidad para q caiga al centro
						*vidas_jugador=*vidas_jugador-1;
					 }
				
		 }
		break;
		
    case ALIEN:
		i=0;
    while(i< cant_proy2){
			  cond_borrar_proy = ( (proy_y[i] >= jug_y-16) && (proy_y[i] <= jug_y-8) )&& (proy_x[i] >= jug_x+2) && (proy_x[i] <= jug_x+20);
				if( cond_borrar_proy==1 ){  //por la posicion vertical del alien,como q le cae al centro
					                          //posicion horizontal del alien, en realidad para q caiga al centro
					 borra_proyectiles(i, &cant_proy2, proy_x, proy_y,JUGADOR_MATA_ALIEN);
				}
				else{i++;}
		} 
		
		 *cant_proy =cant_proy2;
		break;
	
	}
	
}


	







//------------proyectil_por_fila------------
//evalua si alguno de los proyectiles del jugador ha colisionado con algun alien de una fila de aliens, invoca a "proyectil_a_alguien"
// Input: uint8_t *cant_proy_jug2:es la cantidad de proyectiles que tiene el jugador
//      uint8_t jug_proy_x[]:  es el arreglo que contiene las abscisas de los proyectiles del jugador
//      uint8_t jug_proy_y[]:es el arreglo que contiene las ordenadas de los proyectiles del jugador
//      uint8_t alien_x: es la posicion de la esquina izquierda del alien mas a la izquierda de la fila
//      uint8_t alien_y: es la posicion de mas abajo del alien de la fila de mas arriba
//        uint8_t vida_aliens[]: arreglo que contiene el estado de los 12 aliens(el contenido de cada elemento es 0 o 1)
// Output: --- 
void proyectil_por_fila(uint8_t *cant_proy_jug2,uint8_t jug_proy_x[],uint8_t jug_proy_y[],uint8_t alien_x,uint8_t y,uint8_t vida_aliens[],uint8_t nro_fila) {
 uint8_t cant_proy_jug=	*cant_proy_jug2;
 uint8_t temp;
 uint8_t nro_alien;	
uint8_t basura=50;	  
   	  for (nro_alien=0; nro_alien <4;nro_alien++) {
			 temp=cant_proy_jug; 
   	   if(vida_aliens[4*nro_fila+nro_alien] ==1){ 
   	  	 	 proyectil_a_alguien(&cant_proy_jug,jug_proy_x, jug_proy_y, alien_x+nro_alien*26,y,&basura,ALIEN ); //en vidas jugador, que es el penutlimo pongo cualquier cosa;
   	       if(cant_proy_jug != temp) {
					  ST7735_DrawBitmap( alien_x+nro_alien*26 ,y,explosion, 22, 16);	 
   	     	 vida_aliens[4*nro_fila+nro_alien] =0; 
					 }
   	   }	 
   	  	
	  }
	  *cant_proy_jug2=	cant_proy_jug;
 	
 	
 }	
	

 
 
 


 




 //------------proyectil_a_aliens------------
//evalua si alguno de los proyectiles del jugador ha colisionado con algun alien, invoca a proyectil_por_fila
// Input: uint8_t *cant_proy_jug:es la cantidad de proyectiles que tienen los aliens
//      uint8_t jug_proy_x[]:  es el arreglo que contiene las abscisas de los proyectiles del jugador
//      uint8_t jug_proy_y[]:es el arreglo que contiene las ordenadas de los proyectiles del jugador
//      uint8_t alien_x: es la posicion de la esquina izquierda del alien mas a la izquierda de la fila
//      uint8_t alien_y: es la posicion de mas abajo del alien de la fila de mas arriba
//        uint8_t vida_aliens[]: arreglo que contiene el estado de los 12 aliens(el contenido de cada elemento es 0 o 1)
// Output: --- 
 void proyectil_a_aliens(uint8_t *cant_proy_jug,uint8_t jug_proy_x[],uint8_t  jug_proy_y[],uint8_t alien_x,uint8_t alien_y,uint8_t vida_aliens[]) {
uint8_t cant_proy_jug2= *cant_proy_jug;
uint8_t nro_fila;	
    
   for(nro_fila=0;nro_fila<3;nro_fila++) {
      proyectil_por_fila(&cant_proy_jug2,jug_proy_x,jug_proy_y, alien_x, alien_y+nro_fila*20,vida_aliens,nro_fila);
   }
   	
*cant_proy_jug	=cant_proy_jug2;
	
}








 //------------evalua_flags------------
//funcion que evalua si el jugador ha ganado o ha perdido
//Input: uint8_t *flag_gano: solo es 1 si todos los aliens estan muertos , es decir si vida_aliens[i]==0
//      uint8_t *flag_perdio: solo es 1 si vidas_jugador==0
//       uint8_t vidas_jugador:el numero de vidas que tiene el jugador
//uint8_t vida_aliens[]: arreglo que contiene el estado de los 12 aliens(el contenido de cada elemento es 0 o 1)
void evalua_flags(uint8_t *flag_gano,uint8_t vida_aliens[],uint8_t *flag_perdio,uint8_t vidas_jugador){
	*flag_gano=0;
	*flag_perdio=0;
uint8_t i;	
uint8_t cont=0;	
	for(i=0;i<12;i++) {
		if(vida_aliens[i] ==0){
		cont++;
		}
	}
		
	if(cont==12){
		*flag_gano=1;
	} 	
	
	if(vidas_jugador==0) {
	*flag_perdio=1;
	}
}	



