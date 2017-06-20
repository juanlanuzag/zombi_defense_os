/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

info_player playerA = {START_SELECTED_ZOMBIE_A, START_Y_PLAYERS,0,{0,0,0,0,0,0,0,0}, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},0};
info_player playerB = {START_SELECTED_ZOMBIE_B, START_Y_PLAYERS,0,{0,0,0,0,0,0,0,0}, {{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}},0};

int playerActual = 0;



unsigned short sched_proximo_indice() {
	playerActual = (playerActual+1) %2;
	info_player* player = get_current_player();
	//Los prints comentados son para debuging.
	//unsigned short* gdt_indexes = player->gdt_indexes_tasks;
	int current_zombie = player->curr_zombie;
	//print_hex(player->gdt_indexes_tasks[current_zombie],2, 20,17, 0xf);
	//print_hex(current_zombie,2, 30,17, 0xf);
	current_zombie=(current_zombie +1) %8;
	short gdt_index=0;
	/*int i=0;
	for (i=0;i<8;i++){
		print_hex(playerA.gdt_indexes_tasks[i],2, 3,20+i, 0xf);
		print_hex(playerB.gdt_indexes_tasks[i],2, 6,20+i, 0xf);
		print_hex(player->gdt_indexes_tasks[i],2, 9,20+i, 0xf);
	}
	i=0;*/
	while(current_zombie!=player->curr_zombie){
		//breakpoint();
		//print_hex(current_zombie,2, 30,20 + i++, 0xf);
		//print_hex(player->gdt_indexes_tasks[current_zombie],2, 20,20 + i, 0xf);
		if(player->gdt_indexes_tasks[current_zombie]!=0){
			//breakpoint();
			gdt_index = player->gdt_indexes_tasks[current_zombie];
			break;
		}

		current_zombie=(current_zombie +1) %8;
	}


  return gdt_index;
	//return 0;
}


info_player* get_current_player(){
	return playerActual == 0 ? &playerA : &playerB;;
}