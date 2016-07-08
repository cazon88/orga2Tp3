/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "colors.h"
#include "defines.h"
#include "game.h"
#include "syscall.h" 

void task() {
//   breakpoint();
	syscall_soy(0x842);
  while(1) { 
  	//syscall_soy(0x842);
  	__asm __volatile("mov $2, %%eax":::"eax"); }
}