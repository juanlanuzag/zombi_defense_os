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

unsigned short sched_proximo_indice() {
  return playerA.gdt_indexes_tasks[0];
}

