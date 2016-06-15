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
    t->es = 0x6 << 3;
	t->cs = 0x4 << 3;
	t->ss = 0x6 << 3;
	t->ds = 0x6 << 3;
	t->fs = 0x8 << 3;
	t->gs = 0x6 << 3;
    t->esp = 0x08001000;
    t->ebp = 0x08001000;
    t->esp0 = nueva libre + 0x1000; //frijolito
    t->ss0 = segmento de dato del kernel (nivel 0)
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
        inicializar_tarea(tss[i],0x00013000,i*3,i*2);
        gdt_agregar_tss(i+11,&tss[i]); 
        //pintar()
    }    
}

void tss_inicializar() {

	inicializar_idle(&tss_idle);
	gdt_agregar_tss(9,&tss_inicial); 
	gdt_agregar_tss(10,&tss_idle);
	//cargar tarea idle a TR
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