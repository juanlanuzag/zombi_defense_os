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
	unsigned int x = jugador ? 78 : 1;
	int indice = tss_inicializar_zombie(x,player->y,player->selected_type);
    player->gdt_indexes_tasks[(indice>>3) - 15] = indice;
    player->cant_lanzados++;

    print_throw_zombie(jugador, player->y, player->selected_type);

    //return indice;
}
void game_move_current_zombi(direccion dir) {
	    /*
    info_player* current_player = get_current_player();
    unsigned short current_zombie = current_player->curr_zombie;
    unsigned short zombie_gdt_selector = (current_player->gdt_indexes_tasks)[current_zombie];
    */
    /* mover su codigo */
    /* remapear sus direcciones */

    breakpoint();
    
    page_directory_entry* zombie_directory = (page_directory_entry*) rcr3();
	print_hex((unsigned int)zombie_directory, 8, 4, 4, 0x07);
	
    breakpoint();
}

