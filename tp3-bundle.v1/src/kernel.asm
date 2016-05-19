; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
%include "a20.asm"      ;FIRJOLITO

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

gdt_dir: dw 0x8FA0  ;REVISAR FRIJOLITO x2 ;dw porque es una dir de 16b

memoria_video: dw 0xB800     ;CRISIS EN FRIJOLITOS INFINITOS
fin_memoria_video: db 0xBFD0

gris: dw 0x08
caracter_espacio: dw 0x20

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

ORG 0x1200  ; Direccion de origen FRIJOLITO

;; Punto de entrada del kernel.
BITS 16
start:
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
    call habilitar_A20      ; SE PUEDE HACER CALL?
    
    ; Cargar la GDT
    LGDT [gdt_dir] ;QUE VA ACA? gdt_dir es el offset?
    ;O va esto: lgdt [gdtr]

    ; Setear el bit PE del registro CR0
    mov eax, cr0
    or eax, 1
    MOV cr0, eax

    ; Saltar a modo protegido
    jmp 0x08:modoProtegido

BITS  32
modoProtegido:

    ; Establecer selectores de segmentos
    xor eax, eax

    mov ax, 0101000b     ;{index: 0101=5 |  gdt/ldt:0 | rpl:00}
    mov ds, ax

    mov ax, 0110000b     ;{index: 0110=6 |  gdt/ldt:0 | rpl:00}
    mov es, ax

    mov ax, 0111000b     ;{index: 0111=7 |  gdt/ldt:0 | rpl:00}
    mov gs, ax

    mov ax, 1000000b     ;{index: 1000=8 |  gdt/ldt:0 | rpl:00}
    mov fs, ax    


    ; Establecer la base de la pila
    mov sb, 0x27000     ;FRIJOLITO SS?
    
    ; Imprimir mensaje de bienvenida

    ; Inicializar pantalla

    mov eax, [memoria_video] 
    .ciclo
    mov byte [eax], 0x08
    add eax, 1
    mov byte [eax], 0x20
    add eax, 1
    cmp eax, 0xBFD0
    jne .ciclo


    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    
    ; Cargar directorio de paginas

    ; Habilitar paginacion
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    
    ; Cargar IDT
 
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

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
