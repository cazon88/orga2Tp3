/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#ifndef __SCHED_H__
#define __SCHED_H__

#include "screen.h"
#include "tss.h"
#include "gdt.h"
#include "game.h"

unsigned short sched_proximo_indice();
void inicializar_sched();
void inicializar_sched_h();
void inicializar_sched_a();
void inicializar_sched_b();

typedef enum infectado_e { A = 0x001, B = 0x002, N = 0x000 } infectado;

typedef struct s_tarea{
	unsigned short x;
	unsigned short y;
	infectado infec;
	unsigned short gdt;
	unsigned char viva;
}tarea;

extern tarea* tarea_actual();
extern unsigned int agregar_tarea_a_scheduler(unsigned short x, unsigned short y, infectado tipo);
extern void matar_tarea();
extern tarea jugadorA[5];
extern tarea npc[15];
extern tarea jugadorB[5];
#endif	/* !__SCHED_H__ */
