/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle;
tss tss_h[15];
tss tss_a[5];
tss tss_b[5];


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
    t->iomap = 0xFFFF;
   	};

void inicializar_tarea(tss* t, unsigned int dir_codigo_fisico, unsigned short x, unsigned short y) {
	t->cr3 = mmu_mapear_tarea(dir_codigo_fisico,  x, y);
    t->eip = 0x08000000;
    t->eflags = 0x202;
    t->es = 0x38|3;
    t->cs = 0x28|3;
	t->ss = 0x38|3;
	t->ds = 0x38|3;
	t->fs = 0x38|3;
	t->gs = 0x38|3;
    t->esp = 0x08001000;
    t->ebp = 0x08001000;
    t->esp0 = mmu_proxima_pagina_fisica_libre() + 0x1000;
    t->ss0 = 0x30; // segmento de dato del kernel (nivel 0) 
   	};

void gdt_agregar_tss(int p, tss* t) {
//completar la entrada a la gdt
short tam = sizeof(tss) -1;
short base_1 = (int) t;           //FRIJOLITO
char base_2 = (int) t >> 16;      //FRIJOLITO
char base_3 = (int) t >> 24;        //FRIJOLITO

gdt[p].limit_0_15 = tam; //FRIJOLITO!! -1 ?
gdt[p].base_0_15 = base_1;
gdt[p].base_23_16 = base_2;
gdt[p].type = 0x09;
gdt[p].s = 0x00;
gdt[p].dpl = 0x00;          //FRIJOLITO
gdt[p].p = 0x01;
gdt[p].limit_16_19= tam >> 16;
gdt[p].avl = 0x00;
gdt[p].l = 0x00;
gdt[p].db = 0x00;
gdt[p].g = 0x00;  //4k??
gdt[p].base_31_24 = base_3;

}

void tss_inicializar_tarea_h(){

    //TAREA 1
    inicializar_tarea(&tss_h[0],0x00013000, 10, 2);
    gdt_agregar_tss(11,&tss_h[0]);

    //TAREA 2
    inicializar_tarea(&tss_h[1],0x00013000, 55, 2);
    gdt_agregar_tss(12,&tss_h[1]);

    //TAREA 3
    inicializar_tarea(&tss_h[2],0x00013000, 29, 6);
    gdt_agregar_tss(13,&tss_h[2]);

    //TAREA 4
    inicializar_tarea(&tss_h[3],0x00013000, 71, 9);
    gdt_agregar_tss(14,&tss_h[3]);

    //TAREA 5
    inicializar_tarea(&tss_h[4],0x00013000, 39, 13);
    gdt_agregar_tss(15,&tss_h[4]);

    //TAREA 6
    inicializar_tarea(&tss_h[5],0x00013000, 3, 16);
    gdt_agregar_tss(16,&tss_h[5]);

    //TAREA 7
    inicializar_tarea(&tss_h[6],0x00013000, 52, 17);
    gdt_agregar_tss(17,&tss_h[6]);

    //TAREA 8
    inicializar_tarea(&tss_h[7],0x00013000, 70, 19);
    gdt_agregar_tss(18,&tss_h[7]);

    //TAREA 9
    inicializar_tarea(&tss_h[8],0x00013000, 37, 22);
    gdt_agregar_tss(19,&tss_h[8]);

    //TAREA 10
    inicializar_tarea(&tss_h[9],0x00013000, 18, 26);
    gdt_agregar_tss(20,&tss_h[9]);

    //TAREA 11
    inicializar_tarea(&tss_h[10],0x00013000, 7, 31);
    gdt_agregar_tss(21,&tss_h[10]);

    //TAREA 12
    inicializar_tarea(&tss_h[11],0x00013000, 56, 30);
    gdt_agregar_tss(22,&tss_h[11]);

    //TAREA 13
    inicializar_tarea(&tss_h[12],0x00013000, 33, 34);
    gdt_agregar_tss(23,&tss_h[12]);

    //TAREA 14
    inicializar_tarea(&tss_h[13],0x00013000, 74, 35);
    gdt_agregar_tss(24,&tss_h[13]);

    //TAREA 15
    inicializar_tarea(&tss_h[14],0x00013000, 47, 42);
    gdt_agregar_tss(25,&tss_h[14]);

}

void crear_tss_a(unsigned int i_gdt, unsigned int x, unsigned int y){
     inicializar_tarea(&tss_a[0],0x00011000, x, y);
     gdt_agregar_tss(i_gdt,&tss_a[0]); 
}

void crear_tss_b(unsigned int i_gdt, unsigned int x, unsigned int y){
     inicializar_tarea(&tss_b[i_gdt - 31],0x00012000, x, y);
     gdt_agregar_tss(i_gdt,&tss_b[i_gdt - 31]); 
}

void tss_inicializar() {

	inicializar_idle(&tss_idle);
	gdt_agregar_tss(9,&tss_inicial); 
	gdt_agregar_tss(10,&tss_idle);
    inicilizar_cr3_kernel();
	tss_inicializar_tarea_h(); 
    breakpoint();  
}