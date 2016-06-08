/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de la tabla de descriptores globales
*/

#include "gdt.h"

gdt_entry gdt[GDT_COUNT] = {
    /* Descriptor nulo*/
    /* Offset = 0x00 */
    /*Segmento para código nivel 0*/
        [4] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p FRIJOLITO  */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l FRIJOLITO  */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /*Segmento para código nivel 3*/
        [5] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x0A,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p FRIJOLITO  */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l FRIJOLITO  */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /*Segmento para datos nivel 0*/
        [6] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p FRIJOLITO  */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l FRIJOLITO  */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

    /*Segmento para datos nivel 3*/
        [7] = (gdt_entry) {
        (unsigned short)    0x6DFF,         /* limit[0:15]  */
        (unsigned short)    0x0000,         /* base[0:15]   */
        (unsigned char)     0x00,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x03,           /* dpl          */
        (unsigned char)     0x01,           /* p FRIJOLITO  */
        (unsigned char)     0x03,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l FRIJOLITO  */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
    },

	/*Segmento para datos nivel 0 para Video*/
        [8] = (gdt_entry) {
        (unsigned short)    0xBFD0,         /* limit[0:15]  */
        (unsigned short)    0x8000,         /* base[0:15]   */
        (unsigned char)     0x0b,           /* base[23:16]  */
        (unsigned char)     0x02,           /* type         */
        (unsigned char)     0x01,           /* s            */
        (unsigned char)     0x00,           /* dpl          */
        (unsigned char)     0x01,           /* p FRIJOLITO  */
        (unsigned char)     0x00,           /* limit[16:19] */
        (unsigned char)     0x00,           /* avl          */
        (unsigned char)     0x00,           /* l FRIJOLITO  */
        (unsigned char)     0x01,           /* db           */
        (unsigned char)     0x01,           /* g            */
        (unsigned char)     0x00,           /* base[31:24]  */
	}
    
};

gdt_descriptor GDT_DESC = {
    sizeof(gdt) - 1,
    (unsigned int) &gdt
};



void gdt_agregar_tss(int p, tss* t) {
//completar la entrada a la gdt
short tam = sizeof(tss) -1;
short base_1 = t;           //FRIJOLITO
char base_2 = t >> 16;      //FRIJOLITO
char base_3 = >> 24;        //FRIJOLITO

gdt[p].limit_0_15 = tam; //FRIJOLITO!! -1 ?
gdt[p].base_0_15 = base_1;
gdt[p].base_23_16 = base_2;
gdt[p].type = 0x09;
gdt[p].s = 0x00;
gdt[p].dpl = 0x00;          //FRIJOLITO
gdt[p].p = 0x01;
gdt[p].limit_16_19= tam >> 16;
gdt[p].avl = 0x00;
gdt[p].l = 0x00;
gdt[p].db = 0x00;
gdt[p].g = 0x00;  //4k??
gdt[p].base_31_24 = base_3;

}

