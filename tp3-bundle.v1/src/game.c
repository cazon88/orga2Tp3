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
	if (jugador == 0x00000000){ //Preunto Jugador
	
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
}

void game_soy(unsigned int yoSoy) {

}

void game_donde(unsigned int* pos) {
}

void game_mapear(int x, int y) {
}

