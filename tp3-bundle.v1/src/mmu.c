/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"

  unsigned int cr3_kernel = 0;

  void inicilizar_cr3_kernel(){
  	cr3_kernel = rcr3();
  }
  

void mmu_inicializar_dir_kernel() { 

	pd_entry* pd = (pd_entry*)0x27000;
	pt_entry* pt = (pt_entry*)0x28000;

	unsigned int i;
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
	p->us = 1;
	p->rw = 1;
	p->p = 1;
	p->dir = direccion >> 12;
}

void llenar_entry_pt(pt_entry* p, unsigned int direccion){
	p->us = 1;
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


void mmu_mapear_pagina( unsigned int dirVirtual, 
						unsigned int cr3, 
						unsigned int fisica){

	unsigned int id_directory = dirVirtual >> 22;	
	unsigned int id_table = (dirVirtual >> 12) & 0x3FF;

	pd_entry* pd = (pd_entry*) ((cr3 >> 12) << 12);
	pt_entry* pt;// = (pt_entry*) ((pd[id_directory].dir)<<12);  //FRIJOLITO

	unsigned char presente = pd[id_directory].p;
	if(presente == 0){
		pt = (pt_entry*) mmu_proxima_pagina_fisica_libre();
		vaciar_pageTable(pt);
		llenar_entry(&(pd[id_directory]), (unsigned int)pt);
	}
	else
	{
		pt = (pt_entry*) ((pd[id_directory].dir)<<12);  //FRIJOLITO
	}
	llenar_entry_pt(&pt[id_table], fisica);
	tlbflush();
}

void mmu_unmapear_pagina(unsigned int dirVirtual, unsigned int cr3){
	unsigned int id_directory = dirVirtual >> 22;
	unsigned int id_table = (dirVirtual >> 12) & 0x3FF;

	pd_entry* pd = (pd_entry*) (cr3 & ~0xFFF);

	pt_entry* pt = (pt_entry*) ((pd[id_directory].dir)<<12);
	pt[id_table].p = 0;
	tlbflush();
}

unsigned int mmu_calcular_dir_tarea(unsigned int x, unsigned int y){
	// FIRJOLITO CHEQUEO DE X E Y y no negativo
	unsigned int suma = ( (x + 80*y)  * 4096);
	//suma = 0x3B0000 + suma;
	suma = 3866624 + suma;
	return suma;
}

unsigned int obtenerK(){
	return cr3_kernel;
}

unsigned int mmu_inicializar_dir_tarea(unsigned int dir_fisica_codigo_en_kernel, unsigned int dir_fisica_codigo_en_mapa){
	//rcr3 lee el cr3
	unsigned int cr3 = rcr3();

	//Pedir memo libre -> esto es el  nuevo Cr3
	unsigned int cr3_tarea = mmu_proxima_pagina_fisica_libre();

		//virtual es 0x08000000
	unsigned int dirvirtual = 0x08000000;

	//Calcular la nueva dir fisica del codigo de la tarea
	//Mapear el kernel a esta nueva dir fisica
	mmu_mapear_pagina(dirvirtual,cr3_tarea, dir_fisica_codigo_en_mapa);
	mmu_mapear_pagina(dir_fisica_codigo_en_mapa, cr3, dir_fisica_codigo_en_mapa);

	//Copiar el codigo de la tarea a la dir fisica
	int i;
	/* Se copia el codigo de la tarea del Kernel al Mapa */
	char* dir_virtual_codigo = (char*)dir_fisica_codigo_en_kernel;
	char* dir_virtual_mapa = (char*)dir_fisica_codigo_en_mapa;
	for(i=0;i<4096;i++) {
		dir_virtual_mapa[i] = dir_virtual_codigo[i];
	}
	//Desmapear

	mmu_unmapear_pagina(dir_fisica_codigo_en_mapa, cr3);

	
	//TODO: Limpiar esa pagina!!
	

	/* Mapeo del kernel y el area libre a la Tarea */
	for (i = 0; i < 4096; ++i){
		mmu_mapear_pagina(i*4096,cr3_tarea,i*4096);
	}

	
	return cr3_tarea;
}

unsigned int mmu_mapear_tarea(unsigned int dir_codigo, unsigned int x, unsigned int y){
	unsigned int dir_fisica_tarea = mmu_calcular_dir_tarea(x,y);
	return mmu_inicializar_dir_tarea (dir_codigo, dir_fisica_tarea);
}

void mmu_mapear_tarea_solo_mapa(unsigned int dir_virtual, unsigned int x, unsigned int y){
	unsigned int dir_fisica_tarea = mmu_calcular_dir_tarea(x,y);
	mmu_mapear_pagina(dir_virtual,rcr3(),dir_fisica_tarea);
}