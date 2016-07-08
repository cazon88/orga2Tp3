/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

gameStatus gStatus = {
/*vidasA*/				(unsigned int) 0,	//cantidad corriendo simultaneamente. <=5
/*vidasB*/				(unsigned int) 0,
/*pntajeA*/				(unsigned int) 0,
/*puntajeB*/			(unsigned int) 0,
/*cursorAX*/			(unsigned int) 4,
/*cursorAY*/			(unsigned int) 4,
/*cursorBX*/			(unsigned int) 75,
/*cursorBY*/			(unsigned int) 40,
/*tareasRestantesA*/	(unsigned int) 5, //total tareas. 
/*tareasREstantesB*/	(unsigned int) 5,
};

//1 <= y <= 44
//0 <= x <= 79 

void game_mover_A_arriba(){
	if (gStatus.cursorAY > 1){ //Me aseguro que no se pase	
		pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
		gStatus.cursorAY--;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_A_abajo(){
	if (gStatus.cursorAY < 44){ //Me aseguro que no se pase	
		pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
		gStatus.cursorAY++;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_A_derecha(){
	if (gStatus.cursorAX < 79){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
		gStatus.cursorAX++;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_A_izquierda(){
	if (gStatus.cursorAX > 0){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
		gStatus.cursorAX--;
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);
	}
}

void game_mover_B_arriba(){
	if (gStatus.cursorBY > 1){ //Me aseguro que no se pase	
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
		gStatus.cursorBY--;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

void game_mover_B_abajo(){
	if (gStatus.cursorBY < 44){ //Me aseguro que no se pase	
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
		gStatus.cursorBY++;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

void game_mover_B_derecha(){
	if (gStatus.cursorBX < 79){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
		gStatus.cursorBX++;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

void game_mover_B_izquierda(){
	if (gStatus.cursorBX > 0){ //Me aseguro que no se pase
		pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
		gStatus.cursorBX--;
		pintar_b(gStatus.cursorBX,gStatus.cursorBY);
	}
}

/*void game_mover_cursor(int jugador, direccion dir) {
	if (jugador == 0x00000000){ //Pregunto Jugador
	
		if (dir == ARB){ //Pregunto direccion
		
			if (gStatus.cursorAY < 1){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAY--;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		} else if (dir == ABA){
			if (gStatus.cursorAY < 44){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAY++;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		} else if (dir == IZQ){
			if (gStatus.cursorAX < 0){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAX--;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		} else if (dir == DER){
			if (gStatus.cursorAX < 79){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAX++;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		}
	}else{
		if (dir == ARB){ //Pregunto direccion
		
			if (gStatus.cursorBY < 1){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBY--;
				pintar_b(gStatus.cursorBX,gStatus.cursorBY);
			}
		} else if (dir == ABA){
			if (gStatus.cursorBY < 44){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBY++;
				pintar_b(gStatus.cursorBX,gStatus.cursorBY);
			}
		} else if (dir == IZQ){
			if (gStatus.cursorBX < 0){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBX--;
				pintar_b(gStatus.cursorBX,gStatus.cursorBY);
			}
		} else if (dir == DER){
			if (gStatus.cursorBX < 79){ //Me aseguro que no se pase
				
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBX++;
				pintar_b(gStatus.cursorBX,gStatus.cursorBY);
			}
		}

	}
}*/

void game_lanzar_jug1(){
	agregar_tarea_a_scheduler( gStatus.cursorAX, gStatus.cursorAY, A);
	pintar_a(gStatus.cursorAX,gStatus.cursorAY); 
}

void game_lanzar_jug2(){
	agregar_tarea_a_scheduler(gStatus.cursorBX, gStatus.cursorBY, B);
	pintar_b(gStatus.cursorBX,gStatus.cursorBY);
}

/*
* Indica si esta infectado o no. Y pinta la
* tarea del color que le corresponde
*/
void game_soy(unsigned int yoSoy) {
	//breakpoint();
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
		mmu_mapear_tarea_solo_mapa(0x08001000, (unsigned short)x, (unsigned short)y);
	}else if (tarea_actual()->infec == B){
		mmu_mapear_tarea_solo_mapa(0x08001000, (unsigned short)x, (unsigned short)y);
	}else{
		mmu_mapear_tarea_solo_mapa(0x08001000, (unsigned short)x, (unsigned short)y);
	}
	
}

