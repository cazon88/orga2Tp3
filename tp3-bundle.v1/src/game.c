/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

#define MIN_X   		0
#define MAX_X   		79
#define MIN_Y   		1
#define MAX_Y   		44
#define DIR_TAREA_A		0x11000
#define DIR_TAREA_B		0x12000
#define DIR_TAREA_H		0x13000


gameStatus gStatus = {
/*vidasA*/				(unsigned int) 0,	//cantidad corriendo simultaneamente. <=5
/*vidasB*/				(unsigned int) 0,
/*pntajeA*/				(unsigned int) 0,
/*puntajeB*/			(unsigned int) 0,
/*cursorAX*/			(unsigned int) 2,
/*cursorAY*/			(unsigned int) 44,
/*cursorBX*/			(unsigned int) 77,
/*cursorBY*/			(unsigned int) 44,
/*tareasRestantesA*/	(unsigned int) 20, //total tareas. 
/*tareasREstantesB*/	(unsigned int) 20,
};

//1 <= y <= 44
//0 <= x <= 79 


void inicializar_juego(){
	pintar_pantalla(gStatus.cursorAX, gStatus.cursorAY, gStatus.cursorBX, gStatus.cursorBY);
}

void game_lanzar_jug1(){
	if (gStatus.tareasRestantesA == 0 ){return;} 
	unsigned int i_gdt = agregar_tarea_a_scheduler( gStatus.cursorAX, gStatus.cursorAY, A);
	if (i_gdt == 0 ){return;} 
	crear_tss_a(i_gdt, gStatus.cursorAX, gStatus.cursorAY);
	breakpoint();
	pintar_a(gStatus.cursorAX,gStatus.cursorAY); 
}

void game_lanzar_jug2(){
	if (gStatus.tareasRestantesB == 0){return;}
	unsigned int i_gdt = agregar_tarea_a_scheduler( gStatus.cursorBX, gStatus.cursorBY, B);
	if (i_gdt == 0 ){return;} 
	crear_tss_b(i_gdt, gStatus.cursorBX, gStatus.cursorBY);

	pintar_b(gStatus.cursorBX,gStatus.cursorBY);
}

/*
* Indica si esta infectado o no. Y pinta la
* tarea del color que le corresponde
*/
void game_soy(unsigned int yoSoy) {
	if(yoSoy == 0x841){
		tarea_actual()->infec = A;
		pintar_a(tarea_actual()->x, tarea_actual()->y);
	}else if(yoSoy == 0x325){
		tarea_actual()->infec = B;
		pintar_b(tarea_actual()->x, tarea_actual()->y);
	}else{
		tarea_actual()->infec= N;
		pintar_h(tarea_actual()->x, tarea_actual()->y);
	}
}

/*
* Devuelve en la dirección de memoria pos
* los vaores XY
*/
void game_donde(unsigned int* pos) {
	pos[0] = tarea_actual()->x;
	pos[1] = tarea_actual()->y;
}


/*
*	Mapea la tarea_actual en las coordenadas dadas.
*	Según el tipo de tarea, la dirección de código que copia.
*/
void game_mapear(int x, int y) {
	if(tarea_actual()->infec == A){
		mmu_mapear_tarea(DIR_TAREA_A, tarea_actual()->x, tarea_actual()->y);
	}else if (tarea_actual()->infec == B){
		mmu_mapear_tarea(DIR_TAREA_B, tarea_actual()->x, tarea_actual()->y);
	}else{
		mmu_mapear_tarea(DIR_TAREA_H, tarea_actual()->x, tarea_actual()->y);
	}

}	

/* **************************
*	MOVIMIENTO DE CURSORES  *
*************************** */

void game_mover_A_arriba(){
	if (gStatus.cursorAY > MIN_Y){ //Me aseguro que no se pase	

		pintar_gris(gStatus.cursorAX,gStatus.cursorAY); //Pinto de gris, y eventualmente piso.
		
		int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorAX) && (npc[i].y == gStatus.cursorAY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorAX) && (jugadorA[i].y == gStatus.cursorAY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorAX) && (jugadorB[i].y == gStatus.cursorAY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_b(gStatus.cursorAX,gStatus.cursorAY);
		}

		gStatus.cursorAY--;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_A_abajo(){
	if (gStatus.cursorAY < MAX_Y){ //Me aseguro que no se pase	
		pintar_gris(gStatus.cursorAX,gStatus.cursorAY);

		int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorAX) && (npc[i].y == gStatus.cursorAY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorAX) && (jugadorA[i].y == gStatus.cursorAY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorAX) && (jugadorB[i].y == gStatus.cursorAY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_b(gStatus.cursorAX,gStatus.cursorAY);
		}

		gStatus.cursorAY++;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_A_derecha(){
	if (gStatus.cursorAX < MAX_X){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorAX,gStatus.cursorAY);

		int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorAX) && (npc[i].y == gStatus.cursorAY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorAX) && (jugadorA[i].y == gStatus.cursorAY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorAX) && (jugadorB[i].y == gStatus.cursorAY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_b(gStatus.cursorAX,gStatus.cursorAY);
		}


		gStatus.cursorAX++;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_A_izquierda(){
	if (gStatus.cursorAX > MIN_X){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorAX,gStatus.cursorAY);

		int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorAX) && (npc[i].y == gStatus.cursorAY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorAX) && (jugadorA[i].y == gStatus.cursorAY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorAX) && (jugadorB[i].y == gStatus.cursorAY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorAX,gStatus.cursorAY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorAX,gStatus.cursorAY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorAX,gStatus.cursorAY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_b(gStatus.cursorAX,gStatus.cursorAY);
		}
		

		gStatus.cursorAX--;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_B_arriba(){
	if (gStatus.cursorBY > 1){ //Me aseguro que no se pase	
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);

		int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorBX) && (npc[i].y == gStatus.cursorBY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorBX) && (jugadorA[i].y == gStatus.cursorBY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorBX) && (jugadorB[i].y == gStatus.cursorBY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_a(gStatus.cursorAX,gStatus.cursorAY);
		}

		gStatus.cursorBY--;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

void game_mover_B_abajo(){
	if (gStatus.cursorBY < 44){ //Me aseguro que no se pase	
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);

			int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorBX) && (npc[i].y == gStatus.cursorBY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorBX) && (jugadorA[i].y == gStatus.cursorBY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorBX) && (jugadorB[i].y == gStatus.cursorBY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_a(gStatus.cursorAX,gStatus.cursorAY);
		}

		gStatus.cursorBY++;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

void game_mover_B_derecha(){
	if (gStatus.cursorBX < 79){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);

			int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorBX) && (npc[i].y == gStatus.cursorBY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorBX) && (jugadorA[i].y == gStatus.cursorBY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorBX) && (jugadorB[i].y == gStatus.cursorBY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_a(gStatus.cursorAX,gStatus.cursorAY);
		}

		gStatus.cursorBX++;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

void game_mover_B_izquierda(){
	if (gStatus.cursorBX > 0){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);

			int i,j,k;
		for (i= 0; i < 16; ++i){
			
			if (npc[i].viva == 1 && 
				(npc[i].x == gStatus.cursorBX) && (npc[i].y == gStatus.cursorBY) ){
				if (npc[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (npc[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (npc[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
				
			}
		}

		for (j = 0; j < 6; ++j){
			if (jugadorA[i].viva == 1 && 
				(jugadorA[i].x == gStatus.cursorBX) && (jugadorA[i].y == gStatus.cursorBY) ){
					if (jugadorA[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorA[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorA[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		for (k = 0; k < 6; ++k){
			if (jugadorB[i].viva == 1 && 
				(jugadorB[i].x == gStatus.cursorBX) && (jugadorB[i].y == gStatus.cursorBY) ){
				if (jugadorB[i].infec == A){
					pintar_infectada_a(gStatus.cursorBX,gStatus.cursorBY);
				}else if (jugadorB[i].infec == B){
					pintar_infectada_b(gStatus.cursorBX,gStatus.cursorBY);
				} else if (jugadorB[i].infec == N){
					pintar_h(gStatus.cursorBX,gStatus.cursorBY);
				}
			}
		}

		if (gStatus.cursorAX == gStatus.cursorBX && gStatus.cursorAY == gStatus.cursorBY){
			pintar_a(gStatus.cursorAX,gStatus.cursorAY);
		}

		gStatus.cursorBX--;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

