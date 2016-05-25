; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

extern GDT_DESC
extern IDT_DESC
extern idt_inicializar
extern habilitar_pic
extern resetear_pic
extern mmu_inicializar
%include "imprimir.mac"

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;


%define videomemo 0xB8000		;CRISIS EN FRIJOLITOS INFINITOS
%define finpantalla 2000		;80x25 = 2000 px
;%define fin_memoria_video: dw 0xBFD0

iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

; ORG 0x1200
; Direccion de origen FRIJOLITO

;; Punto de entrada del kernel.
BITS 16
start:

xchg bx, bx

    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a 80 X 50
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0
  
    ; Habilitar A20
    call habilitar_A20
    
    ; Cargar la GDT
    LGDT [GDT_DESC]

    ; Setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 1
    MOV cr0, eax

    ; Saltar a modo protegido
    jmp 0x20:modoProtegido				;segmento de codigo nivel 0 de la GDT (shifteado 3 veces a la izq)

BITS  32



modoProtegido:

    ; Establecer selectores de segmentos
    xor eax, eax

    mov ax, 110000b     ;{index: 0110=6 |  gdt/ldt:0 | rpl:00}
    mov ds, ax
    mov gs, ax
    mov es, ax
    mov ss, ax


	;Segmento de video;
	mov ax, 1000000b     ;{index: 1000=8 |  gdt/ldt:0 | rpl:00}
    mov fs, ax




    ; Establecer la base de la pila
    mov ebp, 0x27000
    mov esp, 0x27000
    
	;mov word [0xb8000], 0x0041

    ; Imprimir mensaje de bienvenida
    ;imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 3, 0

    ; Inicializar pantalla
	mov eax, videomemo		
	xor edi, edi			;contador
	xor eax, eax
.ciclo:
	;mov [ds:eax], ' '
    ;mov byte[eax], ' '		;caracter: "espacio"
    mov byte [fs:eax], ' '
    add eax, 1
   	mov byte [fs:eax], 0x70	;color
   	add eax, 1
  	;cmp eax, 0xBFD0				
	cmp eax, 8000
	jne .ciclo


    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    xchg bx, bx
    call mmu_inicializar
    
    ; Cargar directorio de paginas

    ; Habilitar paginacion
    mov eax, 0x27000
    mov cr3, eax 
    mov eax, cr0
    or eax, 0x80000000
    mov cr0, eax


    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    call idt_inicializar
    
    ; Cargar IDT
    LIDT [IDT_DESC]
 
 
    ; Configurar controlador de interrupciones
    ;call resetear_pic
    ;call habilitar_pic

    ; Cargar tarea inicial

    ; Habilitar interrupciones
    ;sti
    xchg bx, bx
    xor eax, eax
    div eax

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"