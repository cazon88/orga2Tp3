/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#ifndef __MMU_H__
#define __MMU_H__

#include "defines.h"
#include "i386.h"
#include "tss.h"
#include "game.h"

void mmu_inicializar_dir_kernel();
unsigned int mmu_proxima_pagina_fisica_libre();
unsigned int mmu_mapear_tarea(unsigned int dir_codigo, unsigned int x, unsigned int y);


typedef struct str_pd_entry {
	unsigned char   p:1;
	unsigned char   rw:1;
	unsigned char   us:1;
	unsigned char   pwt:1;
	unsigned char   pcd:1;
	unsigned char   a:1;
	unsigned char   i:1;
	unsigned char   ps:1;
	unsigned char   g:1;
	unsigned char   dpl:3;
	unsigned int  dir:20; //aca habia un 20
} __attribute__((__packed__)) pd_entry;

typedef struct str_pt_entry {
	unsigned char   p:1;
	unsigned char   rw:1;
	unsigned char   us:1;
	unsigned char   pwt:1;
	unsigned char   pcd:1;
	unsigned char   a:1;
	unsigned char   d:1;
	unsigned char   pat:1;
	unsigned char   g:1;
	unsigned char   dpl:3;
	unsigned int  dir:20;
} __attribute__((__packed__)) pt_entry;

extern pd_entry* pd ;
extern pt_entry* pt ;

#endif	/* !__MMU_H__ */




