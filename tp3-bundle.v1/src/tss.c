/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de estructuras para administrar tareas
*/

#include "tss.h"

tss tss_inicial;
tss tss_idle;

void tss_inicializar() {

	gdt_agregar_tss(9,&tss_inicial); 
	gdt_agregar_tss(10,&tss_idle);
	//cargar tarea idle a TR

		
	//kernel
	//calll tss_inicializar 
	//cargar inicial
	//hacer jump a idle
}
