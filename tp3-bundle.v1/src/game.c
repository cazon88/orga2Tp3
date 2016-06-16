/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
*/

#include "game.h"

gameStatus gStatus = nuevoJuego();

gameStatus nuevoJuego(){
	gameStatus gstatus = {
		vidasA = 0;	//cantidad corriendo simultaneamente. <=5
		vidasB = 0;
		puntajeA = 0;
		puntajeB = 0;
		cursorAX = 4;
		cursorAY = 4;
		cursorBX = 75;
		cursorBY = 40;
		tareasRestantesA = 5; //total tareas. 
		tareasRestantesB = 5;
	}
}

//1 <= x <= 44
//0 <= y <= 79 

void game_mover_cursor(int jugador, direccion dir) {
	if (jugador == 0x0000){ //Preunto Jugador
	
		if (dir = ARB){ //Pregunto direccion
		
			if (gStatus.cursorAX < 44){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAX++;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		} else if (dir = ABA){
			if (gStatus.cursorAX > 1){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAX--;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		} else if (dir = IZQ){
			if (gStatus.cursorAY > 0){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAY--;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		} else if (dir = DER){
			if (gStatus.cursorAY < 79){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorAX,gStatus.cursorAY);
				gStatus.cursorAY++;
				pintar_a(gStatus.cursorAX,gStatus.cursorAY);
			}
		}
	}else{
		if (dir = ARB){ //Pregunto direccion
		
			if (gStatus.cursorBX < 44){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBX++;
				pintar_a(gStatus.cursorBX,gStatus.cursorBY);
			}
		} else if (dir = ABA){
			if (gStatus.cursorBX > 1){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBX--;
				pintar_a(gStatus.cursorBX,gStatus.cursorBY);
			}
		} else if (dir = IZQ){
			if (gStatus.cursorBY > 0){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBY--;
				pintar_a(gStatus.cursorBX,gStatus.cursorBY);
			}
		} else if (dir = DER){
			if (gStatus.cursorBY < 79){ //Me aseguro que no se pase
			
				pintar_gris(gStatus.cursorBX,gStatus.cursorBY);
				gStatus.cursorBY++;
				pintar_a(gStatus.cursorBX,gStatus.cursorBY);
			}
		}

	}
}

void game_lanzar(unsigned int jugador) {
}

void game_soy(unsigned int yoSoy) {

}

void game_donde(unsigned int* pos) {
}

void game_mapear(int x, int y) {
}

