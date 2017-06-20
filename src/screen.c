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

    //Inicializo jugadores en posicion 22
    print(zombie_to_char(A_MONK),0,START_Y_PLAYERS + 1, C_FG_WHITE_BG_RED);
    print(zombie_to_char(B_MONK),79,START_Y_PLAYERS + 1, C_FG_WHITE_BG_BLUE);
}

void print_group_name() {
    print("aca va el nombre", 63, 0, C_FG_LIGHT_GREY);
}

void print_move_player(int player, unsigned int orig_y, unsigned int dest_y, zombie z){
    unsigned int x = player ? 79 : 0;
    unsigned short color = player ? C_FG_WHITE_BG_BLUE : C_FG_WHITE_BG_RED; 
    print(" ", x, orig_y+1, color);
    print(zombie_to_char(z), x, dest_y+1, color);
}

void print_change_zombie(int player, unsigned int y, zombie z) {
    unsigned int x = player ? 79 : 0;
    unsigned short color = player ? C_FG_WHITE_BG_BLUE : C_FG_WHITE_BG_RED;
    print(zombie_to_char(z), x, y+1, color);
}

char* zombie_to_char(zombie z){
    char* letter = "a"; 
    switch (z) {
        case A_MONK:
            *letter = 0xEB;
            break;
        case A_SUICIDE_UNIT:
            *letter = 0xE6;
            break;
        case A_DRUNK_DRIVER:
            *letter = 0x0E;
            break;
        case B_MONK:
            *letter = 0x06;
            break;
        case B_SUICIDE_UNIT:
            *letter = 0x0F;
            break;
        case B_DRUNK_DRIVER:
            *letter = 0xEC;
            break;
    }
    return letter;
}

void print_throw_zombie(int player, unsigned int y, zombie z){
    unsigned int x = player ? POS_INIT_ZOMBI_B : POS_INIT_ZOMBI_A ;
    unsigned short color = player ? C_FG_WHITE_BG_BLUE : C_FG_WHITE_BG_RED;
    print(zombie_to_char(z), x, y+1, color);
}

void print_move_zombie(int player, unsigned int x_orig, unsigned int y_orig, unsigned int x_dst, unsigned int y_dst, zombie z){
    unsigned short color = player ? C_FG_WHITE_BG_BLUE : C_FG_WHITE_BG_RED;
    print("X", x_orig, y_orig+1, C_FG_LIGHT_GREY_BG_GREEN);
    print(zombie_to_char(z), x_dst, y_dst+1, color);
}

void print_death_zombie(int player, unsigned int x, unsigned int y){
    unsigned short color = player ? C_FG_BLUE_BG_GREEN : C_FG_RED_BG_GREEN;
    short offset = x==1 ? 1 : -1;
    print("X", x, y+1, color);
    print("X",x+offset,y+1,C_FG_LIGHT_GREY_BG_GREEN);
}


void print_info_player(int player){
    int j;
    for(j=18; j<32; j++){
        print("                                  ",18,j,C_FG_WHITE);
    }    
    info_player* jugador = player ? &playerB : &playerA;
    print("INFO PLAYER:", 20, 20, C_FG_WHITE );
    print_int(player,35, 20, C_FG_WHITE);
    print("SELECTED:", 20, 22, C_FG_WHITE );
    print_int((int)jugador->selected_type,35, 22, C_FG_WHITE);
    
    print("Y:", 20, 24, C_FG_WHITE );
    print_int(jugador->y,35, 24, C_FG_WHITE);


    print("CANT LANZ:", 20, 26, C_FG_WHITE );
    print_int(jugador->cant_lanzados,35, 26, C_FG_WHITE);


    print("ACT ZOMBIE:", 20, 28, C_FG_WHITE );
    print_int(jugador->curr_zombie,35, 28, C_FG_WHITE);


    print("GDT_IND_TASKS:", 20, 30, C_FG_WHITE );
    print_int(jugador->gdt_indexes_tasks[0],35, 30, C_FG_WHITE);
    print_int(jugador->gdt_indexes_tasks[1],37, 30, C_FG_WHITE);
    print_int(jugador->gdt_indexes_tasks[2],39, 30, C_FG_WHITE);
    print_int(jugador->gdt_indexes_tasks[3],41, 30, C_FG_WHITE);
    print_int(jugador->gdt_indexes_tasks[4],43, 30, C_FG_WHITE);
    print_int(jugador->gdt_indexes_tasks[5],45, 30, C_FG_WHITE);
    print_int(jugador->gdt_indexes_tasks[6],47, 30, C_FG_WHITE);
    print_int(jugador->gdt_indexes_tasks[7],49, 30, C_FG_WHITE);
}
void print_current_zombi(int player, int zombie_index){
    info_player* jugador = player ? &playerB : &playerA;
    info_zombie* zombie =&(jugador->info_zombies[zombie_index]);

    int j;
    for(j=18; j<32; j++){
        print("                                  ",18,j,C_FG_WHITE);
    }
    print("INFO PLAYER:", 20, 20, C_FG_WHITE );
    print_int(player,35, 20, C_FG_WHITE);
    print("CURRENT_ZOMBIE:", 20, 21, C_FG_WHITE );
    print_int(zombie_index,35, 21, C_FG_WHITE);
    print("TYPE:", 20, 22, C_FG_WHITE );
    print_int((int)zombie->type,35, 22, C_FG_WHITE);
    print("X:", 20, 24, C_FG_WHITE );
    print_int(zombie->x,35, 24, C_FG_WHITE);
    print("Y:", 20, 25, C_FG_WHITE );
    print_int(zombie->y,35, 25, C_FG_WHITE);
    
}

void girar_reloj_actual(){
   return;
    info_player* player = playerActual ? &playerB : &playerA;

    unsigned short posReloj_x = playerActual ? 61 : 4;

    posReloj_x += 2* player->curr_zombie;

    nuestro_proximo_reloj(posReloj_x);
}

void print_puntos(unsigned int jugador, unsigned int puntos){
    unsigned int x = jugador ? 42 : 37;
    unsigned short color = jugador ? C_FG_WHITE_BG_BLUE : C_FG_WHITE_BG_RED;
    print_int(puntos,x,47,color);
}