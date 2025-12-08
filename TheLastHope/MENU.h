
/*****          Autor:              Harif Joe Meza Rojas                           *****/
/*****          Fecha:              junio 2020                                    *****/
/****************************************************************************************/
#ifndef   _MENU_H_
  #define _MENU_H_
 
 void temp1(uint16_t *n_seg);
 void temp2(uint8_t *enable_cont_seg);
 void ordena_puntajes(uint8_t letra1[],uint8_t letra2[],uint8_t letra3[],uint16_t puntaje[]);
 void maneja_leaderboard (uint8_t opcion,uint16_t puntaje_ind);
 void nueva();
 void leaderboard(); 
  void retornar ();
  void partida(int8_t *opc_menu) ;
  void instrucciones(int8_t *opc_menu);
  void mutear(int8_t *opc_menu,uint8_t *flag_sonido);
  void salir(int8_t *opc_menu,uint8_t *flag_start);
  void trabaja_jugador(uint8_t *jug_x,uint8_t *jug_y,uint8_t *cant_proy_jug, uint8_t jug_proy_x[],uint8_t jug_proy_y[]);
  void juego(uint8_t nivel,uint8_t *flag_gano,uint8_t *flag_perdio);
 
#endif
