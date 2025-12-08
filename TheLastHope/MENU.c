
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Fecha:              junio 2020                                    *****/
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

#define ALIEN   1
#define JUGADOR 2
#define JUGADOR_MATA_ALIEN 3

uint8_t antSW1=0;
uint8_t antSW2=0;
uint8_t flanco_bajadaSW1=0;
uint8_t flanco_bajadaSW2=0;
uint8_t flag_hay_caracter;

uint16_t nt_seg=1;
uint8_t enablet_cont_seg=0;
//son parametros que se pasan al main
void temp1(uint16_t *n_seg) {
	nt_seg=*n_seg;}

void temp2(uint8_t *enable_cont_seg) {
	*enable_cont_seg=enablet_cont_seg;}



void trabaja_jugador(uint8_t *jug_x,uint8_t *jug_y,uint8_t *cant_proy_jug, uint8_t jug_proy_x[],uint8_t jug_proy_y[]) {
uint8_t caracter;
	
  ST7735_DrawBitmap(*jug_x,*jug_y,nave_def, 22, 16);	 	
  sondea_UART(&flag_hay_caracter,&caracter);
  	
  if(flag_hay_caracter) {
      ST7735_DrawBitmap(*jug_x,*jug_y,fondo_negro, 22, 16);		
				if (caracter=='a') {
					if( (*jug_x -4) >=0) {
						*jug_x=*jug_x -4;
					}
				}
			if (caracter=='d') {
					if( (*jug_x +22) <=127) {
						*jug_x=*jug_x +4;
					 }
				}
			
    }

	
	sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);
	sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
		if(*cant_proy_jug<=7) {
			if(flanco_bajadaSW1) {
				ST7735_DrawBitmap(*jug_x+4,*jug_y-16,proyectil_nave, 2, 4);	//el cañon 1 esta a 4 pixeles derecha de la esquina izquierda de la nave
				*cant_proy_jug=   *cant_proy_jug+1;
				 jug_proy_x[ *cant_proy_jug-1 ] =*jug_x+4 ;
				 jug_proy_y[*cant_proy_jug -1] =*jug_y-16 ;	//tiene q salir del cañon
			}
				if(flanco_bajadaSW2) {
				 ST7735_DrawBitmap(*jug_x+16,*jug_y-16,proyectil_nave, 2, 4);	//el cañon 1 esta a 16 pixeles derecha de la esquina izquierda de la nave
			*cant_proy_jug=*cant_proy_jug+1 ;
			jug_proy_x[ *cant_proy_jug-1 ] =*jug_x+16 ;
			jug_proy_y[*cant_proy_jug -1] =*jug_y-16 ;	 //tiene q salir del cañon
			}
	  }
		
	
}
	
void juego(uint8_t nivel,uint8_t *flag_gano,uint8_t *flag_perdio) {
uint8_t	alien_x=0;
uint8_t alien_y =20;
int8_t sentido=2;
uint8_t cant_proy=0,cant_proy_jug=0;
uint8_t proy_x[14],proy_y[14];
uint16_t cont_gen_proy=0;	
uint8_t cont_actualiza_aliens=0,cont_actualiza_proy=0;
uint8_t vida_aliens[12]={1,1,1,1,1,1,1,1,1,1,1,1};	
uint8_t	jug_x=54; //al medio
uint8_t jug_y =150;	//casi al final
uint8_t jug_proy_x[7],jug_proy_y[7];  //lesubi proyectiles a 7
uint8_t vidas_jugador=1;
uint8_t flag_gano2,flag_perdio2;


	if(nivel==1){
	 UART_OutString("Nivel 1\n");	
	}
	if(nivel==2){
		 UART_OutString("Nivel 2\n");
	}
	if(nivel==3){
		UART_OutString("Nivel 3\n");
	}
	
flag_gano2=*flag_gano;
flag_perdio2=*flag_perdio;
  nt_seg=0;
	config_puertoF();
	enablet_cont_seg=1; //a partir de aqui empieza a correr el tiempo
	do{
		  //movimiento de los aliens
		if (cont_actualiza_aliens==25) {
			mueve_aliens(&alien_x,alien_y,&sentido,vida_aliens); 
			cont_actualiza_aliens=0;				//alien_x es la posicion del primer alien esquina superior izquierda
																							 //(el que te mostré en paint)
																							 //sentido puede valer 2 o -2 , 2 mueve 2 pixeles a la derecha y -2 a la izquierda
		}	
		else{cont_actualiza_aliens++;}
		
			//generacion de proyectiles por parte de los aliens
		if (cont_gen_proy==(200-40*nivel) ) {
			genera_proyectil(&cant_proy,proy_x,proy_y,alien_x,alien_y,jug_x,vida_aliens);
			cont_gen_proy=0;
		}
		else{cont_gen_proy++;}

		//acciones del jugador, ya sean movimientos o disparos
		trabaja_jugador(&jug_x,&jug_y,&cant_proy_jug,jug_proy_x,jug_proy_y);
		
		//actualizaciones de proyectiles			
		if (cont_actualiza_proy==(8-2*nivel) ){			
			mueve_proyectiles(cant_proy,proy_x,proy_y,ALIEN);
			borra_proyectiles(0,&cant_proy,proy_x,proy_y,ALIEN); //cuando sale de la pantalla

			mueve_proyectiles(cant_proy_jug,jug_proy_x,jug_proy_y,JUGADOR);
			borra_proyectiles(0,&cant_proy_jug,jug_proy_x,jug_proy_y,JUGADOR); //cuando sale de la pantalla
			
			proyectil_a_alguien(&cant_proy, proy_x, proy_y,jug_x,jug_y,&vidas_jugador,JUGADOR); //se evalua si el jugador ha recibido un proyectil
	    proyectil_a_aliens(&cant_proy_jug,jug_proy_x,jug_proy_y, alien_x,alien_y, vida_aliens); //evalua si algun alien recibio proyectil
			cont_actualiza_proy=0;
		}
    else{cont_actualiza_proy++;}
	  
		//evaluacion de flags
    evalua_flags(&flag_gano2,vida_aliens,&flag_perdio2,vidas_jugador);

	} while (flag_gano2==0 &&flag_perdio2==0);
	enablet_cont_seg=0; //desactivamos el systick , ya no queremos contar el tiempo
		GPIO_PORTF_DATA_R &= ~ROJO;
	*flag_gano=flag_gano2;
	*flag_perdio=flag_perdio2;
}
//INFORMACIÓN DEL LEADERBOARD
//variables donde se guardan las letras y los puntajes
uint8_t letra1[4] ={0,0,0,0}; 
uint8_t letra2[4] ={0,0,0,0}; 
uint8_t letra3[4] ={0,0,0,0}; 
uint16_t puntaje[4] ={0,0,0,0}; 
//ordena la lista dependiendo del puntaje
void ordena_puntajes(uint8_t letra1[],uint8_t letra2[],uint8_t letra3[],uint16_t puntaje[]) {
uint8_t temporal = 0;
uint8_t i,j;
    //el 4 es porque por defecto en el 4to lugar siempre vamos a poner el que acaba de llegar
	//ordenamiento por metodo burbuja
    for (i = 0;i < 4; i++){
		for ( j = 0; j< 4-1; j++){
			if (puntaje[j] < puntaje[j+1]){ // Ordena el array de mayor a menor, cambiar el "<" a ">" para ordenar de menor a mayor
			temporal = puntaje[j]; 
			puntaje[j] = puntaje[j+1]; 
			puntaje[j+1] = temporal;
			
			temporal = letra1[j]; 
			letra1[j] = letra1[j+1]; 
			letra1[j+1] = temporal;
			
			temporal = letra2[j]; 
			letra2[j] = letra2[j+1]; 
			letra2[j+1] = temporal;
			
			temporal = letra3[j]; 
			letra3[j] = letra3[j+1]; 
			letra3[j+1] = temporal;
			
			}
		}
	}    
}


//funcion que escribe o lee del leaderboard segun "opcion"
void maneja_leaderboard (uint8_t opcion,uint16_t puntaje_ind)  {
uint8_t datos[6];	//para ingresar los datos solo deben ser 3 caracteres, para mostrarlos, pueden ser 4

uint8_t letra_mayuscula,letra_minuscula;
	
		
	switch (opcion)	{
		 
			case 1:    //escribir puntaje
			 UART_OutString("Escriba su nombre(SOLO 3 LETRAS):\n");
			 //recibiremos como sea una cadena de 3 
      UART_InString(&datos[0], 3);
			letra_mayuscula= ('A'<=datos[0]) && (datos[0]<='Z') && ('A'<=datos[1]) && (datos[1]<='Z')&&('A'<=datos[2]) && (datos[2]<='Z');
			letra_minuscula= ('a'<=datos[0]) && (datos[0]<='z') && ('a'<=datos[1]) && (datos[1]<='z')&&('a'<=datos[2]) && (datos[2]<='z');
			if(letra_mayuscula || letra_minuscula) {
			letra1[3]	=datos[0];
			letra2[3]	=datos[1];
			letra3[3]	=datos[2];
			puntaje[3]	= puntaje_ind;
			ordena_puntajes( letra1,letra2,letra3,puntaje); 
      }	
      for(uint8_t i=0;i<30;i++){ UART_OutChar('\n');} 			
			break;
			
			case 2:			//mostrar el leaderboard
			UART_OutString("\nNombre  Puntaje\n");
			for (uint8_t i = 0;i < 3; i++){
			datos[0]=letra1[i];	
			datos[1]=letra2[i];	
			datos[2]=letra3[i];	
			datos[3]=(puntaje[i]/100) +'0';	
			datos[3]=((puntaje[i]%100)/10) +'0';
			datos[4]=(puntaje[i]%10) +'0';	
			 UART_OutChar(datos[0]);	
			 UART_OutChar(datos[1]);		
			 UART_OutChar(datos[2]);
			 UART_OutChar('\t');
			 UART_OutChar(datos[3]);
			 UART_OutChar(datos[4]);	
			 UART_OutChar(datos[5]);	
			 UART_OutChar('\n');	
			}
			break;
	}		

}











//ORGANIZACION DEL MENU
//variables que manejan el menú
uint8_t	flag_hay_caracter=0,caracter,nivel,flag_gano,flag_perdio;
int8_t flag_opc_iniciar,flag_opc_inst,flag_opc_mutear,flag_opc_salir,opc_menu_iniciar=0,flag_menu_iniciar;
uint8_t flag_opc_nueva,flag_opc_leaderboard,flag_opc_retornar; 
uint32_t cant_palabras;
void nueva() {flag_opc_nueva=0;
              					cant_palabras=ST7735_DrawString(1,7,"Retornar", ST7735_WHITE);
												cant_palabras=ST7735_DrawString(1,3,"Nueva partida", ST7735_BLUE);                       												 
            						 do{
													 sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);				
													if (flanco_bajadaSW1) {flag_opc_nueva=1;opc_menu_iniciar=1;}     //ConSW1 se pasa a la siguiente opción, con SW2 se selecciona
													sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
													if (flanco_bajadaSW2) {
														//Solicitamos ingresar datos, los almacenamos y vamos a la función partida
													ocultar_menuPartida();
														nivel=1;
														do {
													
														flag_gano=0;
														flag_perdio=0;
														juego(nivel,&flag_gano,&flag_perdio);
														if (flag_gano) {
														ST7735_FillScreen(0);
														ST7735_DrawBitmap(50 ,90 ,gano, 30, 12);
														nivel++;	
														}
														if(flag_perdio) {
														ST7735_FillScreen(0);
														ST7735_DrawBitmap(50 ,90 ,perdio, 30, 12);	
														}
														for(uint32_t i=0; i<12000000;i++){};
									          ST7735_FillScreen(0);} while ((nivel<4) && (flag_perdio==0));
														if (flag_gano){
														maneja_leaderboard(1,40+ 100/nt_seg); //opcion 1 es escribir en el arreglo que contiene los nombres y puntajes(50* nivel +1000/n_seg)
														}
														if(flag_perdio) {
														maneja_leaderboard(1,10*nivel + 2*(nt_seg-1));
														}
														mostrar_menuPrincipal();													
													  flag_menu_iniciar=1;
															flag_opc_nueva=1;
															flag_opc_iniciar=1;
														}
												 } while (flag_opc_nueva==0);}
void leaderboard(){flag_opc_leaderboard=0;
												 cant_palabras=ST7735_DrawString(1,3,"Nueva partida", ST7735_WHITE);
									       cant_palabras=ST7735_DrawString(1,5,"Leaderboard", ST7735_BLUE);
												 do {
													 sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);				
													if (flanco_bajadaSW1) {flag_opc_leaderboard=1;opc_menu_iniciar=2;}     //ConSW1 se pasa a la siguiente opción, con SW2 se selecciona
													sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
													if (flanco_bajadaSW2) {
													//Mostramos el leaderboard
														maneja_leaderboard(2,0); //opcion 2 para mostrar todo el leaderboard, el otro caracter no nos importa en este caso
														ocultar_menuPartida();
														cant_palabras=ST7735_DrawString(1,5,"Presione r", ST7735_WHITE);
														cant_palabras=ST7735_DrawString(1,7,"para salir", ST7735_WHITE);
													//Mostrar leaderboard y presionar r para salir
													do {
													caracter=UART_Caracter();
									        if (caracter=='r') {
									        //Ocultar leaderboard
														for(uint8_t i=0;i<30;i++){ UART_OutChar('\n');}
														cant_palabras=ST7735_DrawString(1,5,"Presione r", ST7735_BLACK);
														cant_palabras=ST7735_DrawString(1,7,"para salir", ST7735_BLACK);
												mostrar_menuPartida();														
															flag_opc_leaderboard=1;
															flag_opc_iniciar=1;}} while (flag_opc_leaderboard==0);
														}
												 }while (flag_opc_leaderboard==0);}
void retornar () {flag_opc_retornar=0;
												 cant_palabras=ST7735_DrawString(1,5,"Leaderboard", ST7735_WHITE);
									       cant_palabras=ST7735_DrawString(1,7,"Retornar", ST7735_BLUE);
																 do {
															sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);				//Mostramos opcion salir de otro color;
															if (flanco_bajadaSW1) {opc_menu_iniciar=0;flag_opc_retornar=1;}  //ConSW1 se pasa a opción inicial, con SW2 se selecciona
															sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
															if (flanco_bajadaSW2) {
															ocultar_menuPartida();
									            mostrar_menuPrincipal();						
															flag_menu_iniciar=1;
															flag_opc_retornar=1;
															flag_opc_iniciar=1;
															}
															} while (flag_opc_retornar==0);}
void partida(int8_t *opc_menu) {
flag_opc_iniciar=0;
				           cant_palabras=ST7735_DrawString(1,9,"Salir", ST7735_WHITE);
										cant_palabras=ST7735_DrawString(1,3,"Iniciar Partida", ST7735_BLUE);
				          do {
					         sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);				//Mostramos opcion Iniciar partida de otro color;
									if (flanco_bajadaSW1) {*opc_menu=1;flag_opc_iniciar=1;}  //ConSW1 se pasa a la siguiente opción, con SW2 se selecciona
				          sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
									if (flanco_bajadaSW2) {  flag_menu_iniciar=0;										//Mostramos segundo menú (menú iniciar partida)
		              ocultar_menuPrincipal();
									mostrar_menuPartida();
										opc_menu_iniciar=0;
										do {
											 switch (opc_menu_iniciar) {                              //Mostramos opción nueva partida de otro color
												 case 0: nueva();	break;
												 case 1: leaderboard(); break;
												 case 2: retornar(); break;
												 
											 }
										 } while (flag_menu_iniciar==0);											
									 }
								 }  while (flag_opc_iniciar==0);

;}

void instrucciones(int8_t *opc_menu) {flag_opc_inst=0; 
                                      //Aquí solo falta la imagen de la opcion instucciones de color diferente
					       cant_palabras=ST7735_DrawString(1,3,"Iniciar Partida", ST7735_WHITE);
			           cant_palabras=ST7735_DrawString(1,5,"Instrucciones", ST7735_BLUE);
								 
								 do {
									sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);				//Mostramos opcion Instrucciones de otro color;
									if (flanco_bajadaSW1) {*opc_menu=2;flag_opc_inst=1;}     //ConSW1 se pasa a la siguiente opción, con SW2 se selecciona
								  sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
									if (flanco_bajadaSW2) {
									ocultar_menuPrincipal();
									mostrar_instrucciones();
                  do {										
									caracter=UART_Caracter();
									 if (caracter=='e') {
									ocultar_instrucciones();
									mostrar_menuPrincipal();
										flag_opc_inst=1;}
									 }while(flag_opc_inst==0);}
									} while (flag_opc_inst==0);}

void mutear(int8_t *opc_menu,uint8_t *flag_sonido) {flag_opc_mutear=0; //Aquí falta poner la imagen de la opcion mutear de color diferente y mutear/desmutear (flag)
					        cant_palabras=ST7735_DrawString(1,5,"Instrucciones", ST7735_WHITE);	
									cant_palabras=ST7735_DrawString(1,7,"Mutear", ST7735_BLUE);
									do { 
									sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);				//Mostramos opcion Mutear de otro color;
									if (flanco_bajadaSW1) {*opc_menu=3;flag_opc_mutear=1;} //ConSW1 se pasa a la siguiente opción, con SW2 se selecciona
								  sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
									if (flanco_bajadaSW2) {
									if (*flag_sonido) {*flag_sonido=0;}
									else *flag_sonido=1; 
									flag_opc_mutear=1;
									}
									} while (flag_opc_mutear==0);}
void salir(int8_t *opc_menu,uint8_t *flag_start) {
flag_opc_salir=0; //Aquí solo falta poner la imagen de la opcion salida de color diferente
									cant_palabras=ST7735_DrawString(1,7,"Mutear", ST7735_WHITE);
									cant_palabras=ST7735_DrawString(1,9,"Salir", ST7735_BLUE);
					        do {
									sondea_pulsador(&antSW1,SW1,&flanco_bajadaSW1);				//Mostramos opcion salir de otro color;
									if (flanco_bajadaSW1) {*opc_menu=0;flag_opc_salir=1;}  //ConSW1 se pasa a opción inicial, con SW2 se selecciona
								  sondea_pulsador(&antSW2,SW2,&flanco_bajadaSW2);
									if (flanco_bajadaSW2) {
							    ocultar_menuPrincipal();
									*flag_start=0;	
									flag_opc_salir=1;
									}
									} while (flag_opc_salir==0);}

