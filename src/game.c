/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

void game_jugador_mover(unsigned int jugador, unsigned int value) {
	info_player* player = jugador ? playerB : playerA;
	player->y += value;
}

void game_lanzar_zombi(unsigned int jugador) {
	info_player* player = jugador ? playerB : playerA;
	unsigned int x = jugador ? 78 : 1;
	int indice = tss_inicializar_zombie(x,player->y,player->selected_type);
    player->gdt_indexes_tasks[(indice>>3) - 15] = indice;
    player->cant_lanzados++;
    //return indice;
}
void game_move_current_zombi(direccion dir) {
}
