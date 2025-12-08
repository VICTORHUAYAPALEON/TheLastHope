/****************************************************************************************/
/****************************************************************************************/
/*****                  PONTIFICIA UNIVERSIDAD CATOLICA DEL PERU                    *****/
/*****                     FACULTAD DE CIENCIAS E INGENIERÍA                        *****/
/*****                            SISTEMAS DIGITALES                                *****/
/*************************************************************************** *************/
/*****          Archivo:            mostrar_ocultar.h                               *****/
/*****          Microcontrolador:   TM4C123GH6PM                                    *****/
/*****          Modulo(s) uC:       ST7735                                          *****/
/*****          EvalBoard:          Tiva C Series TM4C123G LaunchPad                *****/
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Organización:       Victor Javier Huayapa León                     *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/

	#ifndef   _mostrar_ocultar_H_
  #define _mostrar_ocultar_H_
	


//funciones de Harif para mostrar y ocultar las cadenas q aparecen en el menú
void mostrar_menuPrincipal(void);

void mostrarInicio (void); 
	
void ocultarInicio(void);

void ocultar_menuPrincipal(void);

void mostrar_menuPartida(void);

void ocultar_menuPartida(void);

void mostrar_instrucciones (void);

void ocultar_instrucciones (void);


#endif