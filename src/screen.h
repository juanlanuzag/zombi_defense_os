/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCREEN_H__
#define __SCREEN_H__

/* Definicion de la pantalla */
#define VIDEO_FILS 50
#define VIDEO_COLS 80

#include "colors.h"
#include "defines.h"
#include "sched.h"
/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

void clear_screen();

void print_board();

void windows_screen();

void print_group_name();

void print_move_player(int player, unsigned int orig_y, unsigned int dest_y, zombie z);

void print_change_zombie(int player, unsigned int y, zombie z);

void print_throw_zombie(int player, unsigned int y, zombie z);

void print_move_zombie(int player, unsigned int x_orig, unsigned int y_orig, unsigned int x_dst, unsigned int y_dst, zombie z);

void print_death_zombie(int player, unsigned int x, unsigned int y);

char* zombie_to_char(zombie z);

void print_info_player(int player);

#endif  /* !__SCREEN_H__ */
