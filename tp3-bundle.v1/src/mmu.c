/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
  

void mmu_inicializar_dir_kernel() {   /*OJO CAMBIAR NOMBRE!!!*/

	pd_entry* pd = (pd_entry*)0x27000;
	pt_entry* pt = (pt_entry*)0x28000;

	int i;
	//pd = pd_entry pd[1024];
	for (i = 0; i < 1024; ++i) {
		pd[i] = (pd_entry) {
			(unsigned char)   0x00, //p:1;
			(unsigned char)   0x00, //rw:1;
			(unsigned char)   0x00, //us:1;
			(unsigned char)   0x00, //pwt:1;
			(unsigned char)   0x00, //pcd:1;
			(unsigned char)   0x00, //a:1;
			(unsigned char)   0x00, //i:1;
			(unsigned char)   0x00, //ps:1;
			(unsigned char)   0x00, //g:1;
			(unsigned char)   0x00, //dpl:3;
			(unsigned short)  0x000 //dir:20;
		};
	}

	pd[0].p = 1;
	pd[0].rw = 1;
	pd[0].dir = (0x28000 >> 12); 

    for (i = 0; i < 1024; ++i) {
		//pt[i] = (i << 12) | 3 ;
		pt[i] = (pt_entry){
			(unsigned char)    1,//p:1;
			(unsigned char)    1,//rw:1;
			(unsigned char)    0x00,//us:1;
			(unsigned char)    0x00,//pwt:1;
			(unsigned char)    0x00,//pcd:1;
			(unsigned char)    0x00,//a:1;
			(unsigned char)    0x00,//d:1;
			(unsigned char)    0x00,//pat:1;
			(unsigned char)    0x00,//g:1;
			(unsigned char)    0x00,//dpl:3;
			(unsigned int)   	 i//dir:20;
		};
	}
}

unsigned int proxima_pagina_libre;

void inicializar_mmu(){
	proxima_pagina_libre = 0x100000;
}

unsigned int mmu_proxima_pagina_fisica_libre() {
	unsigned int pagina_libre = proxima_pagina_libre;
	proxima_pagina_libre += 0x1000;//PAGE_SIZE 4K;
	return pagina_libre;
}

void llenar_entry(pd_entry* p, unsigned int direccion){
	p->rw = 1;
	p->p = 1;
	p->dir = direccion >> 12;
}

void llenar_entry_pt(pt_entry* p, unsigned int direccion){
	p->rw = 1;
	p->p = 1;
	p->dir = direccion >> 12;

}

void vaciar_pageTable(pt_entry* pt){
	int i;
	for (i = 0; i < 1024; ++i) {
		//pt[i] = (i << 12) | 3 ;
		pt[i] = (pt_entry){
			(unsigned char)    0x0,//p:1;
			(unsigned char)    0x0,//rw:1;
			(unsigned char)    0x00,//us:1;
			(unsigned char)    0x00,//pwt:1;
			(unsigned char)    0x00,//pcd:1;
			(unsigned char)    0x00,//a:1;
			(unsigned char)    0x00,//d:1;
			(unsigned char)    0x00,//pat:1;
			(unsigned char)    0x00,//g:1;
			(unsigned char)    0x00,//dpl:3;
			(unsigned int)     0X00//dir:20;
		};
	}
}

/*
struct lineal {
	unsigned int offset:12,
	unsigned int table:10,
	unsigned int directory:10
}__attribute__((__packed__));
struct lineal *dir = (struct lineal*) &dirVirtual;
	dir->table;*/

void mmu_mapear_pagina( unsigned int dirVirtual, 
						unsigned int cr3, 
						unsigned int fisica){

	unsigned int id_directory = dirVirtual >> 22;
	unsigned int id_table = (dirVirtual >> 12) & 0x3FF;

	pd_entry* pd = (pd_entry*) ((cr3 >> 12) << 12);
	
	unsigned char presente = pd[id_directory].p;

	if(presente == 0){
		llenar_entry(&(pd[id_directory]), mmu_proxima_pagina_fisica_libre());
		pt_entry* pt = (pt_entry*) ((pd[id_directory].dir)<<12);  //FRIJOLITO
		vaciar_pageTable(&(pt[id_table]));
		llenar_entry_pt(&pt[id_table], fisica);
	}else{
		pt_entry* pt = (pt_entry*) ((pd[id_directory].dir)<<12);
		llenar_entry_pt(&pt[id_table], fisica);
	}

	tlbflush();
}

void mmu_unmapear_pagina(unsigned int dirVirtual, unsigned int cr3){
	
	unsigned int id_directory = dirVirtual >> 22;
	unsigned int id_table = (dirVirtual >> 12) & 0x3FF;

	pd_entry* pd = (pd_entry*) (cr3 & 0xFFF);

	pt_entry* pt = (pt_entry*) ((pd[id_directory].dir)<<12);
	pt[id_table].p = 0;


}

void mmu_inicializar_dir_tarea(){
	
}