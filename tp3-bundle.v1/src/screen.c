/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "screen.h"

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
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


void print_uno(char text, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
        p[y][x].c = (unsigned char) text;
        p[y][x].a = (unsigned char) attr;
}

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr) {
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
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
    ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    if( n > 9 ) {
      int a = n / 10;
      n -= 10 * a;
      print_int(a,x-1,y,attr);
    }
    p[y][x].c = '0'+n;
    p[y][x].a = attr;
}

void pintar_a(unsigned int x, unsigned int y) {
    print_uno(' ', x, y, C_BG_RED + C_FG_WHITE);
}

void pintar_b(unsigned int x, unsigned int y) {
    print_uno(' ', x, y, C_BG_BLUE + C_FG_WHITE);
}

void pintar_h(unsigned int x, unsigned int y) {
    print_uno(' ', x, y, C_BG_GREEN);
}

void pintar_gris(unsigned int x, unsigned int y) {
    print_uno(' ', x, y, C_BG_LIGHT_GREY);
}

void pintar_infectada_a(unsigned int x, unsigned int y) {
    print_uno('A', x, y, C_BG_RED);
}

void pintar_infectada_b(unsigned int x, unsigned int y) {
    print_uno('B', x, y, C_BG_RED);
}

void pintar_letra_a(unsigned int x, unsigned int y){
    print_uno('A', x, y, C_FG_DARK_GREY);
}

void pintar_letra_b(unsigned int x, unsigned int y){
    print_uno('B', x, y, C_FG_DARK_GREY);
}

void avanzarRelojito(unsigned int x, unsigned int y){
 ca (*p)[VIDEO_COLS] = (ca (*)[VIDEO_COLS]) VIDEO_SCREEN;
    char par = '|';
    char der = '/';
    char aco = '-';
    char izq = '\\';
    if(p[y][x].c == par){
    p[y][x].c = der;
    }else{
        if(p[y][x].c == der){
        p[y][x].c = aco;
        }else{
            if(p[y][x].c == aco){
            p[y][x].c = izq;
            }else{
                if(p[y][x].c == izq){
                p[y][x].c = par;
                } 
            }
        }
    }    
}

void pintar_pantalla(unsigned int x_a, unsigned int y_a,
                     unsigned int x_b, unsigned int y_b) {
    unsigned int i;
    unsigned int j;

    /*Cabecera*/
    for (i = 0; i < 80; ++i){
            print_uno(' ', i, 0, C_BG_BLACK);
        }

    /*Banner pie*/
    for (j = 45; j < 50; ++j){    
    for (i = 0; i < 80; ++i){
            print_uno(' ', i, j, C_BG_BLACK);
        }
    }

    /*Cuadrados de puntos Rojo y Azul*/
    for (j = 45; j < 50; ++j){
        for (i = 47; i < 53; ++i){
            print_uno(' ', i, j, C_BG_RED);
            print_uno(' ', i+6, j, C_BG_BLUE);
        }
    }

    /*Vidas*/
    print("vidas",41,46,C_FG_WHITE);
    print("vidas",60,46,C_FG_WHITE);

    /*<A   B>*/
    print("<A   B>",14,46,C_FG_WHITE);

    /* Relojitos */
    print("| / - \\ |",3,46,C_FG_WHITE);
    print("| / - \\ |",23,46,C_FG_WHITE);    
    print("- - - / / / / | \\ \\ \\ \\ - - -",3,48,C_FG_WHITE);

    /* Pintar jugadores*/
    pintar_a(x_a,y_a);
    pintar_b(x_b,y_b);

}
