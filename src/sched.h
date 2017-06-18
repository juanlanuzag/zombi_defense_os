/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "tss.h"
#include "screen.h"

typedef struct str_info_zombie {
    zombie  type;
    unsigned short  x;
    unsigned short  y;
} __attribute__((__packed__, aligned (16))) info_zombie;

typedef struct str_info_player {
    zombie  selected_type;
    unsigned short  y;
    unsigned short cant_lanzados;
    unsigned short gdt_indexes_tasks[8];
    unsigned short curr_zombie;
} __attribute__((__packed__, aligned (16))) info_player;



unsigned short sched_proximo_indice();

info_player* get_current_player();

extern info_player playerA;
extern info_player playerB;

#endif	/* !__SCHED_H__ */
