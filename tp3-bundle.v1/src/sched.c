/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

unsigned int sched[3];

/* [ A* | B* | H* ]
*    |   
*    |
* ACTUAL = 0    */

unsigned int actual = 0;
tarea jugadorA[5];
unsigned int indiceA = 0;
unsigned int totalA = 0; //total de tareas validas en A
tarea jugadorB[5];
unsigned int indiceB = 0; //va de 0 a 4
unsigned int totalB = 0; //total de tareas validas en B, va del 0 al 4
tarea npc[15];
unsigned int indiceNPC = 0;

void inicializar_sched(){
sched[0] = (unsigned int) &jugadorA;
sched[1] = (unsigned int) &jugadorB;
sched[2] = (unsigned int) &npc;
inicializar_sched_h();
}


/*
unsigned int x_actual(){

if(actual == 0){
 sched[actual][]
}

}

unsigned int y_actual(){
}
*/


// - entradas de gdt  		OK
// - conectar a las tss  	OK

// - vector de indices de gdt para cada una de las tareas segun el tipo + info  (LO PASAMOS HARDCODEADO)

void inicializar_sched_h(){
	int i;
	for(i = 0; i < 15 ; i++){
		tarea t_h;
		t_h.x = i*4 + 9;
		t_h.y = i*3 + 2;
		t_h.dir_fisica = 0x00013000;
		t_h.infec = N;
		t_h.gdt = i+11;
		sched[i] = (unsigned int) &t_h;
  }
}


// - lanzar_tarea(x,y,tipo,slot en el scheduler)
// - - crear directorio cr3 para la tarea
// - - completar la tss correspondiente ( slot en el scheduler)
// - - listop




unsigned short sched_proximo_indice() {
	int original;
	if(actual == 0){
  		actual = 1;
  	
  		if(totalA == 0){
  		  return sched_proximo_indice();
  		}

  		original = indiceA;
  	
  		if(indiceA < totalA){
  		  indiceA++;
  		}else{
  		  indiceA = 0;
  		}
  
  		return jugadorA[original].gdt;
  }


  if(actual == 1){
  	actual = 2;
  	if(totalB == 0){
  	 return sched_proximo_indice();
  	}
  	original = indiceB;
  	if(indiceB < totalB){
  	 indiceB++;
  	}else{
  	 indiceB = 0;
  	}

  	return jugadorB[original].gdt;
 }

  if(actual == 2){
 	actual = 0; 

  	original = indiceNPC;
  	if(indiceNPC < 14){
  	indiceNPC++;
  	}else{
  	indiceNPC = 0;
  	}
  	return npc[original].gdt;
  }
  return 0;
}








