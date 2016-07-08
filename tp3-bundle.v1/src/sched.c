/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de funciones del scheduler
*/

#include "sched.h"

unsigned int gdt_a_proxima = 37;
unsigned int gdt_b_proxima = 43; 

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
  inicializar_sched_a();
  inicializar_sched_b();
}

tarea* tarea_actual(){
  if(tipoActual == 0){
      return &jugadorA[actualA];
  }else  if(tipoActual == 1){
    return &jugadorB[actualB];
 }else{
  tipoActual = 0; 
    return &npc[actualNpc];
  }
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
    t_h.viva = 1;
		npc[i] = t_h;
  }
}

void inicializar_sched_a(){
  int i;
  for(i = 0; i < 5 ; i++){
    tarea t_h;
    t_h.x = 0;
    t_h.y = 0;
    t_h.dir_fisica = 0x00011000;
    t_h.infec = A;
    t_h.gdt = i+26;
    t_h.viva = 0;
    jugadorA[i] = t_h;
  }
}

void inicializar_sched_b(){
  int i;
  for(i = 0; i < 5 ; i++){
    tarea t_h;
    t_h.x = 0;
    t_h.y = 0;
    t_h.dir_fisica = 0x00012000;
    t_h.infec = B;
    t_h.gdt = i+31;
    t_h.viva = 0;
    jugadorB[i] = t_h;
  }
}


void agregar_tarea_a_scheduler(unsigned short x, unsigned short y, infectado tipo){
  if(tipo == A){
    unsigned int i = 0;
    unsigned char encontrado = 0;
    while(i < 5 && encontrado == 0){
      if(jugadorA[i].viva == 0){
        encontrado = 1; /* true */
        jugadorA[i].x = x;
        jugadorA[i].y = y;
        //jugadorA[i].gdt = gdt_a_proxima;
        //gdt_a_proxima++;
        jugadorA[i].viva = 1;
      }
      i++;
    }
    totalA++;
  }else{ /*tipo == B*/
    unsigned int i = 0;
    unsigned char encontrado = 0;
    while(i < 5 && encontrado == 0){
      if(jugadorB[i].viva == 0){
        encontrado = 1; /* true */
        jugadorB[i].x = x;
        jugadorB[i].y = y;
        //jugadorA[i].gdt = gdt_a_proxima;
       // gdt_a_proxima++;
        jugadorB[i].viva = 1;
      }
      i++;
    }
    totalB++;
  }
}


// - lanzar_tarea(x,y,tipo,slot en el scheduler)
// - - crear directorio cr3 para la tarea
// - - completar la tss correspondiente ( slot en el scheduler)
// - - listop




unsigned short sched_proximo_indice() {
	//int original;
  int j = 0;
	if(tipoActual == 0){

  		tipoActual = 1;
  		if(totalA == 0){
  		  return sched_proximo_indice();
  		}

      int i = 1;
      j = actualA;
      while(i < 6) {
        actualA = (j + i) % 5;

        if(jugadorA[actualA].viva == 1){
          return (jugadorA[actualA].gdt << 3);
        }

        i++;
      }
    	
    }


  if(tipoActual == 1){
  	tipoActual = 2;
    if(totalB == 0){
  	 return sched_proximo_indice();
  	}

      int i = 1;
      j = actualB;
      while(i < 6) {
        actualB = (j + i) % 5;

        if(jugadorB[actualB].viva == 1){
          return (jugadorB[actualB].gdt << 3);
        }

        i++;
      }
  }

  if(tipoActual == 2){
 	tipoActual = 0; 

    int i = 1;
    j = actualNpc;
    while(i < 16){
        actualNpc = (j + i) % 15;

        if(npc[actualNpc].viva == 1){
          return (npc[actualNpc].gdt << 3); /* Shifteado 3 porque los primeros dos bits es el RPL y el tercer bit es TI */
        }

        i++;
      }
  
}
  return 0;
}



/* Mata una tarea. El atributo viva se vuelve falso */
void matar_tarea(){
  tarea_actual()->viva = 0;
}






