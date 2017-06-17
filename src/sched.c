/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

info_player playerA = {0,0,0,{0,0,0,0,0,0,0,0},0};
info_player playerB = {0,0,0,{0,0,0,0,0,0,0,0},0};

info_zombie info_zombiesA[CANT_ZOMBIS];
info_zombie info_zombiesB[CANT_ZOMBIS];

int player = 0;



unsigned short sched_proximo_indice() {

	player = player+1 %2;
	info_player player = player == 0 ? playerA : playerB;
	unsigned short* gdt_indexes = player.gdt_indexes_tasks;
	int actual_zombie = player.acct_zombie;
	actual_zombie=actual_zombie +1 %8;
	short gdt_index=0;
	while(actual_zombie!=player.actual_zombie){
		if(gdt_indexes[actual_zombie]!=0){
			gdt_index = gdt_indexes[actual_zombie];
			break;
		}

		actual_zombie=actual_zombie +1 %8;
	}


  return gdt_index;
}

