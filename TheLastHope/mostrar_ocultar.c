/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/*************************************************************************** *************/
/*****          Archivo:            mostrar_ocultar.c                               *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       ST7735                                          *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Organización:       Victor Javier Huayapa León                     *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/

#include <stdint.h>
#include "ST7735.h"
#include "tm4c123gh6pm.h"
#include "mostrar_ocultar.h"

void mostrar_menuPrincipal() {
	uint32_t cant_palabras;
cant_palabras=ST7735_DrawString(4,1,"MENU PRINCIPAL", ST7735_WHITE);
			cant_palabras=ST7735_DrawString(1,3,"Iniciar Partida", ST7735_WHITE);
			cant_palabras=ST7735_DrawString(1,5,"Instrucciones", ST7735_WHITE);
			cant_palabras=ST7735_DrawString(1,7,"Mutear", ST7735_WHITE);
			cant_palabras=ST7735_DrawString(1,9,"Salir", ST7735_WHITE)
;}

void mostrarInicio () {
	uint32_t cant_palabras;
		 cant_palabras=ST7735_DrawString(4,1,"THE LAST HOPE", ST7735_GREEN);
	cant_palabras=ST7735_DrawString(1,9,"Para continuar,", ST7735_WHITE);
			cant_palabras=ST7735_DrawString(5,11,"presione s", ST7735_WHITE);
}

void ocultarInicio() {
	uint32_t cant_palabras;
			cant_palabras=ST7735_DrawString(4,1,"THE LAST HOPE", ST7735_BLACK);
	    cant_palabras=ST7735_DrawString(1,9,"Para continuar,", ST7735_BLACK);
			cant_palabras=ST7735_DrawString(5,11,"presione s", ST7735_BLACK)
	;}

void ocultar_menuPrincipal() {
uint32_t cant_palabras;	
cant_palabras=ST7735_DrawString(4,1,"MENU PRINCIPAL", ST7735_BLACK);
cant_palabras=ST7735_DrawString(1,3,"Iniciar Partida", ST7735_BLACK);
cant_palabras=ST7735_DrawString(1,5,"Instrucciones", ST7735_BLACK);
cant_palabras=ST7735_DrawString(1,7,"Mutear", ST7735_BLACK);
cant_palabras=ST7735_DrawString(1,9,"Salir", ST7735_BLACK)
;}

void mostrar_menuPartida() {
	uint32_t cant_palabras;
	cant_palabras=ST7735_DrawString(3,1,"INICIAR PARTIDA", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(1,3,"Nueva partida", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(1,5,"Leaderboard", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(1,7,"Retornar", ST7735_WHITE)
;}

void ocultar_menuPartida() {
	uint32_t cant_palabras;
cant_palabras=ST7735_DrawString(3,1,"INICIAR PARTIDA", ST7735_BLACK);
cant_palabras=ST7735_DrawString(1,3,"Nueva partida", ST7735_BLACK);
cant_palabras=ST7735_DrawString(1,5,"Leaderboard", ST7735_BLACK);
cant_palabras=ST7735_DrawString(1,7,"Retornar", ST7735_BLACK)
;}

void mostrar_instrucciones () {
	uint32_t cant_palabras;
	cant_palabras=ST7735_DrawString(4,1,"INSTRUCCIONES", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(1,3,"a = movimiento izq", ST7735_WHITE);	
	cant_palabras=ST7735_DrawString(1,5,"d = movimiento der", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(1,7,"SW1 = disparo izq", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(1,9,"SW2 = disparo der", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(1,11,"Presione e", ST7735_WHITE);
	cant_palabras=ST7735_DrawString(3,12,"para retornar", ST7735_WHITE);	
	cant_palabras=ST7735_DrawString(5,13,"al menu", ST7735_WHITE)
	;}

void ocultar_instrucciones () {
	uint32_t cant_palabras;
	cant_palabras=ST7735_DrawString(4,1,"INSTRUCCIONES", ST7735_BLACK);
	cant_palabras=ST7735_DrawString(1,3,"a = movimiento izq", ST7735_BLACK);	
	cant_palabras=ST7735_DrawString(1,5,"d = movimiento der", ST7735_BLACK);
	cant_palabras=ST7735_DrawString(1,7,"SW1 = disparo izq", ST7735_BLACK);
	cant_palabras=ST7735_DrawString(1,9,"SW2 = disparo der", ST7735_BLACK);
	cant_palabras=ST7735_DrawString(1,11,"Presione e", ST7735_BLACK);
	cant_palabras=ST7735_DrawString(3,12,"para retornar", ST7735_BLACK);	
	cant_palabras=ST7735_DrawString(5,13,"al menu", ST7735_BLACK)
	;}