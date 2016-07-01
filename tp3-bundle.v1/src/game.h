/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#ifndef __GAME_H__
#define __GAME_H__

#include "defines.h"
#include "screen.h"
#include "mmu.h"

typedef enum direccion_e { IZQ = 0x00 , DER = 0x01, ARB = 0x10, ABA = 0x11 } direccion; //se pasa desde asm por pila

void game_lanzar(unsigned int jugador);

void game_soy(unsigned int soy);

void game_donde(unsigned int* pos);

void game_mover_cursor(int jugador, direccion dir);

void mover_cursor_arriba_a();


typedef struct game_Status{
	unsigned int vidasA;	//cantidad corriendo simultaneamente. <=5
	unsigned int vidasB;
	unsigned int puntajeA;
	unsigned int puntajeB;
	unsigned short cursorAX;
	unsigned short cursorAY;
	unsigned short cursorBX;
	unsigned short cursorBY;
	unsigned int tareasRestantesA; //total tareas. 20
	unsigned int tareasRestantesB;

}gameStatus;

#endif  /* !__GAME_H__ */
