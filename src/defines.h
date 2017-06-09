/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================

    Definiciones globales del sistema.
*/

#ifndef __DEFINES_H__
#define __DEFINES_H__

/* Bool */
/* -------------------------------------------------------------------------- */
#define TRUE                    0x00000001
#define FALSE                   0x00000000
#define ERROR                   1


/* Misc */
/* -------------------------------------------------------------------------- */
#define CANT_ZOMBIS             8

#define SIZE_W                  78
#define SIZE_H                  44


/* Indices en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_COUNT 30

#define GDT_IDX_NULL_DESC           0
#define GDT_IDX_COD_KERNEL          8
#define GDT_IDX_DAT_KERNEL          9
#define GDT_IDX_COD_USER            10
#define GDT_IDX_DAT_USER            11
#define GDT_IDX_VIDEO_KERNEL		12

/* Offsets en la gdt */
/* -------------------------------------------------------------------------- */
#define GDT_OFF_NULL_DESC           (GDT_IDX_NULL_DESC      << 3)

/* Direcciones de memoria */
/* -------------------------------------------------------------------------- */
#define VIDEO                   0x000B8000 /* direccion fisica del buffer de video */

#define PAGE_SIZE 0x1000

#define INICIO_PAGINAS_LIBRES 0x100000

#define CR3KERNEL 0x27000

#endif  /* !__DEFINES_H__ */
