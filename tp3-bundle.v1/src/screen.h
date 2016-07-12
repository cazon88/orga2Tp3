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
/* Estructura de para acceder a memoria de video */
typedef struct ca_s {
    unsigned char c;
    unsigned char a;
} ca;

void print(const char * text, unsigned int x, unsigned int y, unsigned short attr);

void print_hex(unsigned int numero, int size, unsigned int x, unsigned int y, unsigned short attr);

void print_int(unsigned int n, unsigned int x, unsigned int y, unsigned short attr);

void print_uno(char text, unsigned int x, unsigned int y, unsigned short attr);

void pintar_a(unsigned int x, unsigned int y);

void pintar_b(unsigned int x, unsigned int y);

void pintar_h(unsigned int x, unsigned int y);

void pintar_gris(unsigned int x, unsigned int y);

void pintar_infectada_a(unsigned int x, unsigned int y);

void pintar_infectada_b(unsigned int x, unsigned int y);

void pintar_pantalla(unsigned int x_a, unsigned int y_a, unsigned int x_b, unsigned int y_b);
void pintar_letra_b(unsigned int x, unsigned int y);
void pintar_letra_a(unsigned int x, unsigned int y);

void avanzarRelojito(unsigned int x, unsigned int y);

void imprimir_debugger( unsigned int ecx, unsigned int edx, 
                        unsigned int ebx, unsigned int ebp, 
                        unsigned int esi, unsigned int edi, 
                        unsigned int cs, 
                        unsigned int ds, unsigned int es, 
                        unsigned int fs, unsigned int gs,
                        unsigned int ss, 
                        unsigned int stack0, unsigned int stack1, 
                        unsigned int stack2, unsigned int stack3, 
                        unsigned int stack4, unsigned int cr0, 
                        unsigned int cr2, unsigned int cr3, 
                        unsigned int cr4, unsigned int esp, 
                        unsigned int eflags, 
                        unsigned int eax);

extern  unsigned int estaPausado();

#endif  /* !__SCREEN_H__ */
