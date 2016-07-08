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
    t->esp0 = mmu_proxima_pagina_fisica_libre() + 0x1000; //frijolito
    t->ss0 = 0x30; // segmento de dato del kernel (nivel 0)  FALTA HACER!!!
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
    int i;
    for (i = 0; i < 15; ++i){
        inicializar_tarea(&tss_h[i],0x00013000,i*4 + 9, i*3 + 2);
        gdt_agregar_tss(i+11,&tss_h[i]); 
    }
}

void tss_inicializar_tarea_a(){
    int i;
    for (i = 0; i < 5; ++i){
        inicializar_tarea(&tss_a[i],0x00011000,0+i, 0+i);
        gdt_agregar_tss(i+26,&tss_a[i]); 
    }    
}

void tss_inicializar_tarea_b(){
    int i;
    for (i = 0; i < 5; ++i){
        inicializar_tarea(&tss_b[i],0x00012000,40+i, 40+i);
        gdt_agregar_tss(i+31,&tss_b[i]); 
    }    
}


void tss_inicializar() {

	inicializar_idle(&tss_idle);
	gdt_agregar_tss(9,&tss_inicial); 
	gdt_agregar_tss(10,&tss_idle);
	tss_inicializar_tarea_h();
    tss_inicializar_tarea_b();
    tss_inicializar_tarea_a();
    
}