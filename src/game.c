/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

void game_jugador_mover(unsigned int jugador, int value) {
	info_player* player = jugador ? &playerB : &playerA;
	unsigned int orig_y = player->y;
	int a = value + orig_y;
	player->y = MOD(a, 44);

	//print_info_player(jugador);

	print_move_player(jugador, orig_y, player->y, player->selected_type);
}

void game_change_zombie(unsigned int jugador, int value) {
	info_player* player = jugador ? &playerB : &playerA;
	unsigned int offset = jugador ? 3 : 0;

	player->selected_type = MOD((int)player->selected_type + value, 3) + offset;

	//print_info_player(jugador);

	print_change_zombie(jugador, player->y, player->selected_type);

}

void game_lanzar_zombi(unsigned int jugador) {
	info_player* player = jugador ? &playerB : &playerA;
	unsigned int x = jugador ? POS_INIT_ZOMBI_B : POS_INIT_ZOMBI_A;
	int indice = tss_inicializar_zombie(x,player->y,player->selected_type);
    player->gdt_indexes_tasks[(indice>>3) - 15] = indice;
    (player->info_zombies[(indice>>3) - 15]).x = x;
    (player->info_zombies[(indice>>3) - 15]).y = player->y;
    (player->info_zombies[(indice>>3) - 15]).type = player->selected_type; 
    player->cant_lanzados++;
    print_throw_zombie(jugador, player->y, player->selected_type);

    //return indice;
}
void game_move_current_zombi(direccion dir) {
//	breakpoint();

    unsigned int* orig = (unsigned int*) VIRTUAL_COD_ZOMBIE_1;
    unsigned int* dest;
	switch (dir) {
	case IZQ:
    	dest = (unsigned int*)VIRTUAL_COD_ZOMBIE_6;
		break;
    case DER:
    	dest = (unsigned int*)VIRTUAL_COD_ZOMBIE_5; 
    	break;
    case ADE:
    	dest = (unsigned int*)VIRTUAL_COD_ZOMBIE_2;
    	break;
    case ATR:
    	dest = (unsigned int*)VIRTUAL_COD_ZOMBIE_7;
    	break;
    }
    info_player* current_player = get_current_player();
    unsigned short current_zombie = current_player->curr_zombie;
    unsigned short x_orig = (current_player->info_zombies[current_zombie]).x;
    unsigned short y_orig = (current_player->info_zombies[current_zombie]).y;
    unsigned short x_dst = x_orig;
    unsigned short y_dst = y_orig;

    if ((dir == IZQ && playerActual == 0) || (dir == DER && playerActual == 1)) {
    	y_dst--;
    } else if ((dir == DER && playerActual == 0) || (dir == IZQ && playerActual == 1)) {
    	y_dst++;
    } else if ((dir == ADE && playerActual == 0) || (dir == ATR && playerActual == 1)) {
    	x_dst++;
    } else if ((dir == ATR && playerActual == 0) || (dir == ADE && playerActual == 1)) {
    	x_dst--;
    }
    (current_player->info_zombies[current_zombie]).x = x_dst;
	(current_player->info_zombies[current_zombie]).y = y_dst;
    /* mover su codigo */
    int i;
    for(i=0; i<1024; i++){
    	dest[i] = orig[i];
    }
    /* remapear sus direcciones */
    
	mmu_map_adjacent_to_zombi(playerActual, rcr3(), x_dst, y_dst);
    
    print_move_zombie(playerActual, x_orig, y_orig, x_dst, y_dst, (current_player->info_zombies[current_zombie]).type);
 //   breakpoint();
}

