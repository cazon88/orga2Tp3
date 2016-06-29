/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

tarea* tarea_actual; /*FALTA  HACER EL SET DE ESTE PUNTERO*/

unsigned int tipoActual = 0;

tarea jugadorA[5];
unsigned int actualA = 0;
unsigned int totalA = 0; //total de tareas validas en A

tarea jugadorB[5];
unsigned int actualB = 0; //va de 0 a 4
unsigned int totalB = 0; //total de tareas validas en B, va del 0 al 4

tarea npc[15];
unsigned int actualNpc = 0;

void inicializar_sched(){
  inicializar_sched_h();
}


unsigned int x_actual(){

  if(tipoActual == 0){
    return jugadorA[actualA].x;
  }else if (tipoActual == 1){
    return jugadorB[actualB].x;
  }else {
    return npc[actualNpc].x;
  }
}

 

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
		npc[i] = t_h;
  }
}

void crear_taea(short x, short y, unsigned int dir_fisica, infectado infec, unsigned int gdt_indice ){
/*  tarea t;
  t.x = x;
  t.y = y;
  t.dir_fisica = dir_fisica;
  t.infec = infec;
  t.gdt = gdt_indice;
*/
/* llenar array de tarea */
  
}

void agregar_tarea_a_scheduler(tarea * t, unsigned char tipo){
  if (tipo == 'A'){

  }else{
    
  }
}


// - lanzar_tarea(x,y,tipo,slot en el scheduler)
// - - crear directorio cr3 para la tarea
// - - completar la tss correspondiente ( slot en el scheduler)
// - - listop




unsigned short sched_proximo_indice() {
	int original;
	if(tipoActual == 0){
  		tipoActual = 1;
  	
  		if(totalA == 0){
  		  return sched_proximo_indice();
  		}

  		original = actualA;
  	
  		if(actualA < totalA){
  		  actualA++;
  		}else{
  		  actualA = 0;
  		}
  
  		return jugadorA[original].gdt;
  }


  if(tipoActual == 1){
  	tipoActual = 2;
  	if(totalB == 0){
  	 return sched_proximo_indice();
  	}
  	original = actualB;
  	if(actualB < totalB){
  	 actualB++; 
  	}else{
  	 actualB = 0;
  	}

  	return jugadorB[original].gdt;
 }

  if(tipoActual == 2){
 	tipoActual = 0; 

  	original = actualNpc;
  	if(actualNpc < 14){
  	actualNpc++;
  	}else{
  	actualNpc = 0;
  	}
  	return npc[original].gdt;
  }
  return 0;
}








