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


#define IDT_ENTRY(numero)                                                                                        \
    idt[numero].offset_0_15 = (unsigned short) ((unsigned int)(&_isr ## numero) & (unsigned int) 0xFFFF);        \
    idt[numero].segsel = (unsigned short) 0x00;                                                                  \
    idt[numero].attr = (unsigned short) 0x0000;                                                                  \
    idt[numero].offset_16_31 = (unsigned short) ((unsigned int)(&_isr ## numero) >> 16 & (unsigned int) 0xFFFF);

attr:
1##dpl0111##type

void idt_inicializar() {
    // Excepciones
	for(int i =0; i<20;i++){
		IDT_ENTRY(i);
	}
	
	/*
	0 	- Fault 		-  Priority 10
	1 	- Fault 		-	 Priority 1?? SUPERFRIJOLITO
	2		-	Interrupt -  Priority 5 
	3		- Trap 			-  Priority 4o7??
	4		-	Trap 			-  Priority 10
	5		-	Fault 		-	 Priority 10
	6		-	Fault 		-  Priority 9
	7		-	Fault 		-  Priority 10
	8		-	Abort 		-  Priority 9 FRIJOLITO
	9		-	Fault 		-  Priority 10
	10	-	Fault 		-  Priority 10
	11	-	Fault 		-  Priority 10
	12	-	Fault 		-  Priority 10
	13	-	Fault 		-	 Priority 10
	14	-	Fault 		-  Priority 10
	15	DO not use 
	16	-	Fault 		-  Priority 10
	17	-	Fault 		-  Priority 10
	18	-	Abort 		-  Priority 1
	19	-	Fault	 		-  Priority 10
	*/


}
