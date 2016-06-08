/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;

tss tss_idle;

void inicializar_idle(tss* t) {
	t->cr3 = 0x27000;
    t->eip = 0x00010000;
    t->eflags = 0x202;
    t->es = 0x6 << 3;
	t->cs = 0x4 << 3;
	t->ss = 0x6 << 3;
	t->ds = 0x6 << 3;
	t->fs = 0x8 << 3;
	t->gs = 0x6 << 3;
    t->esp = 0x00027000;
    t->ebp = 0x00027000;
   	};

void inicializar_tarea(tss* t) {
	t->cr3 = 0x27000;
    t->eip = 0x00011000;
    t->eflags = 0x202;
    t->es = 0x6 << 3;
	t->cs = 0x4 << 3;
	t->ss = 0x6 << 3;
	t->ds = 0x6 << 3;
	t->fs = 0x8 << 3;
	t->gs = 0x6 << 3;
    t->esp = 0x00027000;
    t->ebp = 0x00027000;
    t->esp2 = 0x00011000; //frijolito

    mmu_inicializar_dir_tarea();

   	};


void tss_inicializar() {

	inicializar_idle(&tss_idle);
	gdt_agregar_tss(9,&tss_inicial); 
	gdt_agregar_tss(10,&tss_idle);
	//cargar tarea idle a TR

		
	//kernel
	//calll tss_inicializar 
	//cargar inicial
	//hacer jump a idle
}

/*	ptl = ;
    unused0 = ;
    esp0;
    ss0;
    unused1;
    esp1;
    ss1;
    unused2;
    esp2;
    ss2;
    unused3;
    cr3;
    eip;
    eflags;
    eax;
    ecx;
    edx;
    ebx;
    esp;
    ebp;
    esi;
    edi;
    es;
    unused4;
    cs;
    unused5;
    ss;
    unused6;
    ds;
    unused7;
    fs;
    unused8;
    gs;
    unused9;
    ldt;
    unused10;
    dtrap;
    iomap;
*/