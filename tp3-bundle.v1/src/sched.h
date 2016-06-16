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

unsigned short sched_proximo_indice();
void inicializar_sched();
void inicializar_sched_h();

typedef enum infectado_e { A = 0x001, B = 0x002, N = 0x000 } infectado;

typedef struct s_tarea{
	unsigned short x;
	unsigned short y;
	unsigned int   dir_fisica;
	infectado infec;
	unsigned short gdt;
}tarea;

	
#endif	/* !__SCHED_H__ */
