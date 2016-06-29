/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

//gameStatus gStatus;

// void nuevoJuego(){
// 		gStatus.vidasA = 0;	//cantidad corriendo simultaneamente. <=5
// 		gStatus.vidasB = 0;
// 		gStatus.puntajeA = 0;
// 		gStatus.puntajeB = 0;
// 		gStatus.cursorAX = 4;
// 		gStatus.cursorAY = 4;
// 		gStatus.cursorBX = 75;
// 		gStatus.cursorBY = 40;
// 		gStatus.tareasRestantesA = 5; //total tareas. 
// 		gStatus.tareasRestantesB = 5;
// }
gameStatus gStatus = {
		(unsigned int) 0,	//cantidad corriendo simultaneamente. <=5
		(unsigned int) 0,
		(unsigned int) 0,
		(unsigned int) 0,
		(unsigned int) 4,
		(unsigned int) 4,
		(unsigned int) 75,
		(unsigned int) 40,
		(unsigned int) 5, //total tareas. 
		(unsigned int) 5,
};

//1 <= x <= 44
//0 <= y <= 79 

void mover_cursor_arriba_a(){
	pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
	gStatus.cursorAY--;
	pintar_a(gStatus.cursorAX,gStatus.cursorAY);
}

void game_mover_cursor(int jugador, direccion dir) {
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
}

void game_lanzar(unsigned int jugador) {
	if (jugador == 0x00000000){ /* Jugador Azul */
		/* Se agrega la tarea al scheduler*/
		agregar_tarea_a_scheduler( gStatus.cursorAX, gStatus.cursorAY, 'A');
		/* Se mapea la tarea */
		mmu_mapear_tarea(/* dir_codigo */ 0x11000, gStatus.cursorAX, gStatus.cursorAY);
		/*Se pinta en pantalla*/
		pintar_a(gStatus.cursorAX,gStatus.cursorAY);  //OJO DEBERIA SER TAREA INFECTADA ????
	}else{
		/* Se agrega la tarea al scheduler*/
		agregar_tarea_a_scheduler(gStatus.cursorBX, gStatus.cursorBY, 'B');
		/* Se mapea la tarea */
		mmu_mapear_tarea(/* dir_codigo */ 0x12000, gStatus.cursorBX, gStatus.cursorBY);
		/*Se pinta en pantalla*/
		pintar_b(gStatus.cursorBX,gStatus.cursorBY); //OJO DEBERIA SER TAREA INFECTADA ????
	}
}


/*
* Indica si esta infectado o no. Y pinta la
* tarea del color que le corresponde
*/
void game_soy(unsigned int yoSoy) {
	if(yoSoy == 0x841){
		tarea_actual->infec = 'A'	;
		pintar_a(tarea_actual->x, tarea_actual->y);
	}else if(yoSoy == 0x325){
		tarea_actual->infec = 'B';
		pintar_b(tarea_actual->x, tarea_actual->y);
	}else{
		tarea_actual->infec= 'N';
		pintar_h(tarea_actual->x, tarea_actual->y);
	}
}

/*
* Devuelve en la dirección de memoria pos
* los vaores XY
*/
void game_donde(unsigned int* pos) {
	(*pos) = ( (tarea_actual->x << 8) || (tarea_actual->y) );
}


/*
*	Mapea la tarea_actual en las coordenadas dadas.
*	Según el tipo de tarea, la dirección de código que copia.
*/
void game_mapear(int x, int y) {
	if(tarea_actual->infec == A){
		mmu_mapear_tarea(/* dir_codigo */ 0x11000, tarea_actual->x, tarea_actual->y);
	}else if (tarea_actual->infec == B){
		mmu_mapear_tarea(/* dir_codigo */ 0x12000, tarea_actual->x, tarea_actual->y);
	}else{
		mmu_mapear_tarea(/* dir_codigo */ 0x13000, tarea_actual->x, tarea_actual->y);
	}
	
}

