/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO;
    int i;
    for (i = 0; text[i] != 0; i++) {
        p[y][x].c = (unsigned char) text[i];
        p[y][x].a = (unsigned char) attr;
        x++;
        if (x == VIDEO_COLS) {
            x = 0;
            y++;
        }
    }
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    int i;
    char hexa[8];
    char letras[16] = "0123456789ABCDEF";
    hexa[0] = letras[ ( numero & 0x0000000F ) >> 0  ];
    hexa[1] = letras[ ( numero & 0x000000F0 ) >> 4  ];
    hexa[2] = letras[ ( numero & 0x00000F00 ) >> 8  ];
    hexa[3] = letras[ ( numero & 0x0000F000 ) >> 12 ];
    hexa[4] = letras[ ( numero & 0x000F0000 ) >> 16 ];
    hexa[5] = letras[ ( numero & 0x00F00000 ) >> 20 ];
    hexa[6] = letras[ ( numero & 0x0F000000 ) >> 24 ];
    hexa[7] = letras[ ( numero & 0xF0000000 ) >> 28 ];
    for(i = 0; i < size; i++) {
        p[y][x + size - i - 1].c = hexa[i];
        p[y][x + size - i - 1].a = attr;
    }
}

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO; // magia
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}

void clear_screen() {
    int i;
    for (i=0; i<50; i++){
        print("                                                                                ", 0, i, C_BG_BLACK);
    }
}

void windows_screen() {
    int i;
    print("                                                          ", 10, 10, C_BG_BLACK);
    for (i=11; i<40; i++){
        if (i<38) print(" ", 10, i, C_BG_BLACK);
        print("                                                           ", 11, i, C_BG_BLUE);
    }   
}

void print_board() {
    //Primera linea negra
    print("                                                                                ", 0, 0, C_BG_BLACK);
    int i;
    for (i=1; i<45; i++){
        print(" ", 0, i, C_BG_RED);
        print("                                                                              ", 1, i, C_BG_GREEN);
        print(" ", 79, i, C_BG_BLUE);
    }
    for (i=45; i<50; i++){
        print("     ", 35, i, C_BG_RED);
        print("     ", 40, i, C_BG_BLUE);
    }
    print("1 2 3 4 5 6 7 8", 4, 46, C_FG_WHITE);
    print("1 2 3 4 5 6 7 8", 61, 46, C_FG_WHITE);
}

void print_group_name() {
    print("aca va el nombre", 63, 0, C_FG_LIGHT_GREY);
}


