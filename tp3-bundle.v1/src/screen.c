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

void imprimir_debugger( unsigned int stack0, unsigned int stack1, unsigned int stack2, unsigned int stack3, unsigned int stack4, unsigned int stack5,
                        unsigned int eax, unsigned int ebx, unsigned int ecx, unsigned int edx, unsigned int esi, unsigned int edi, unsigned int esp,
                        unsigned int ebp, unsigned int eip, unsigned int cs, unsigned int ds, unsigned int es, unsigned int fs, unsigned int gs,
                        unsigned int ss, unsigned int eflags, unsigned int cr0, unsigned int cr2, unsigned int cr3, unsigned int cr4){
    int i, j;
     /* bordes negros */
    for (i = 25; i < 55; ++i){
        print_uno(' ', i, 6, C_BG_BLACK);
        print_uno(' ', i, 42, C_BG_BLACK);  
    }
    for (j = 6; j < 43; ++j){
        print_uno(' ', 25, j, C_BG_BLACK);
        print_uno(' ', 54, j, C_BG_BLACK);  
    }
    /*  TODO GRIS */
    for (i = 26; i < 54; ++i){
        for (j = 8; j < 42; ++j){
            print_uno(' ', i, j, C_BG_LIGHT_GREY);
        }
    }
     /*  CONTEXTO */
    print("EAX", 27, 9, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(eax, 30, 9, C_FG_WHITE);
    print("EBX", 27, 11, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(ebx, 30, 11, C_FG_WHITE);
    print("ECX", 27, 13, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(ecx, 30, 13, C_FG_WHITE);
    print("EDX", 27, 15, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(edx, 30, 15, C_FG_WHITE);
    print("ESI", 27, 17, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(esi, 30, 17, C_FG_WHITE);
    print("EDI", 27, 19, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(edi, 30, 19, C_FG_WHITE);
    print("EBP", 27, 21, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(ebp, 30, 21, C_FG_WHITE);
    print("ESP", 27, 23, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(esp, 30, 23, C_FG_WHITE);
    print("EIP", 27, 25, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(eip, 30, 25, C_FG_WHITE);
    print("CS", 28, 27, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(cs, 30, 27, C_FG_WHITE);
    print("DS", 28, 29, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(ds, 30, 29, C_FG_WHITE);
    print("ES", 28, 31, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(es, 30, 31, C_FG_WHITE);
    print("FS", 28, 33, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(fs, 30, 33, C_FG_WHITE);
    print("GS", 28, 35, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(gs, 30, 35, C_FG_WHITE);
    print("SS", 28, 37, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(ss, 30, 37, C_FG_WHITE);
    print("EFLAGS", 28, 39, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(eflags, 30, 39, C_FG_WHITE);
    print("CR0", 40, 9, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(cr0, 44, 9, C_FG_WHITE);
    print("CR2", 40, 11, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(cr2, 44, 11, C_FG_WHITE);
    print("CR3", 40, 13, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(cr3, 44, 13, C_FG_WHITE);
    print("CR4", 40, 15, C_BG_LIGHT_GREY + C_FG_DARK_GREY);
    print_int(cr4, 44, 15, C_FG_WHITE);
    
}
