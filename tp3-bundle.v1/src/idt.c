/* ** por compatibilidad se omiten tildes **
================================================================================
 TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
================================================================================
  definicion de las rutinas de atencion de interrupciones
*/

#include "defines.h"
#include "idt.h"
#include "isr.h"

#include "tss.h"

idt_entry idt[255] = { };

idt_descriptor IDT_DESC = {
    sizeof(idt) - 1,
    (unsigned int) &idt
};

/*
    La siguiente es una macro de EJEMPLO para ayudar a armar entradas de
    interrupciones. Para usar, descomentar y completar CORRECTAMENTE los
    atributos y el registro de segmento. Invocarla desde idt_inicializar() de
    la siguiene manera:

    void idt_inicializar() {
        IDT_ENTRY(0);
        ...
        IDT_ENTRY(19);

        ...
    }
*/

/*
#define IDT_ENTRY(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x00;                                                                  \
    idt[numero].attr = (unsigned short) 0x0000;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);
*/


#define IDT_ENTRY(numero,atributos)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x20;    /*Segmento de codigo nivel 0*/                                \
    idt[numero].attr = atributos;                                                                                \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);



void idt_inicializar() {
    // Excepciones
	IDT_ENTRY(0, (unsigned short) 0x8E00);
	IDT_ENTRY(1, (unsigned short) 0x8E00);
	IDT_ENTRY(2, (unsigned short) 0x8E00);
	IDT_ENTRY(3, (unsigned short) 0x8E00);
	IDT_ENTRY(4, (unsigned short) 0x8E00);
	IDT_ENTRY(5, (unsigned short) 0x8E00);
	IDT_ENTRY(6, (unsigned short) 0x8E00);
	IDT_ENTRY(7, (unsigned short) 0x8E00);
	IDT_ENTRY(8, (unsigned short) 0x8E00);
	IDT_ENTRY(9, (unsigned short) 0x8E00);
	IDT_ENTRY(10, (unsigned short) 0x8E00);
	IDT_ENTRY(11, (unsigned short) 0x8E00);
	IDT_ENTRY(12, (unsigned short) 0x8E00);
	IDT_ENTRY(13, (unsigned short) 0x8E00);
	IDT_ENTRY(14, (unsigned short) 0x8E00);
	IDT_ENTRY(16, (unsigned short) 0x8E00);
	IDT_ENTRY(17, (unsigned short) 0x8E00);
	IDT_ENTRY(18, (unsigned short) 0x8E00);
	IDT_ENTRY(19, (unsigned short) 0x8E00);

    IDT_ENTRY(32, (unsigned short) 0x8E00);
    IDT_ENTRY(33, (unsigned short) 0x8E00); // DPL = 00 (0)
    IDT_ENTRY(102, (unsigned short) 0xEE00); //102 = 0x66 en dec. DPL = 11 (3)
}
