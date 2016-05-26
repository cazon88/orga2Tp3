/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del manejador de memoria
*/

#include "mmu.h"
  

void mmu_inicializar() {
	// str_pd_entry def{
 
	// (unsigned char)   0x00 //p:1;
	// (unsigned char)   0x00 //rw:1;
	// (unsigned char)   0x00 //us:1;
	// (unsigned char)   0x00 //pwt:1;
	// (unsigned char)   0x00 //pcd:1;
	// (unsigned char)   0x00 //a:1;
	// (unsigned char)   0x00 //i:1;
	// (unsigned char)   0x00 //ps:1;
	// (unsigned char)   0x00 //g:1;
	// (unsigned char)   0x00 //dpl:3;
	// (unsigned short)  0x000 //dir:20;

 //  }

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







