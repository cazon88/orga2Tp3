; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximo_indice

;; syscall
extern game_donde
extern game_soy
extern game_mapear

error_mp_msg_0: db     'Error! INTERRUPCION, numero: 0'
error_mp_len_0: equ    $ - error_mp_msg_0

error_mp_msg_1: db     'Error! INTERRUPCION, numero: 1'
error_mp_len_1: equ    $ - error_mp_msg_1

error_mp_msg_2: db     'Error! INTERRUPCION, numero: 2'
error_mp_len_2: equ    $ - error_mp_msg_2

error_mp_msg_3: db     'Error! INTERRUPCION, numero: 3'
error_mp_len_3: equ    $ - error_mp_msg_3

error_mp_msg_4: db     'Error! INTERRUPCION, numero: 4'
error_mp_len_4: equ    $ - error_mp_msg_4

error_mp_msg_5: db     'Error! INTERRUPCION, numero: 5'
error_mp_len_5: equ    $ - error_mp_msg_5

error_mp_msg_6: db     'Error! INTERRUPCION, numero: 6'
error_mp_len_6: equ    $ - error_mp_msg_6

error_mp_msg_7: db     'Error! INTERRUPCION, numero: 7'
error_mp_len_7: equ    $ - error_mp_msg_7

error_mp_msg_8: db     'Error! INTERRUPCION, numero: 8'
error_mp_len_8: equ    $ - error_mp_msg_8

error_mp_msg_9: db     'Error! INTERRUPCION, numero: 9'
error_mp_len_9: equ    $ - error_mp_msg_9

error_mp_msg_10: db     'Error! INTERRUPCION, numero: 10'
error_mp_len_10: equ    $ - error_mp_msg_10

error_mp_msg_11: db     'Error! INTERRUPCION, numero: 11'
error_mp_len_11: equ    $ - error_mp_msg_11

error_mp_msg_12: db     'Error! INTERRUPCION, numero: 12'
error_mp_len_12: equ    $ - error_mp_msg_12

error_mp_msg_13: db     'Error! INTERRUPCION, numero: 13'
error_mp_len_13: equ    $ - error_mp_msg_13

error_mp_msg_14: db     'Error! INTERRUPCION, numero: 14'
error_mp_len_14: equ    $ - error_mp_msg_14

error_mp_msg_15: db     'Error! INTERRUPCION, numero: 15'
error_mp_len_15: equ    $ - error_mp_msg_15

error_mp_msg_16: db     'Error! INTERRUPCION, numero: 16'
error_mp_len_16: equ    $ - error_mp_msg_16

error_mp_msg_17: db     'Error! INTERRUPCION, numero: 17'
error_mp_len_17: equ    $ - error_mp_msg_17

error_mp_msg_18: db     'Error! INTERRUPCION, numero: 18'
error_mp_len_18: equ    $ - error_mp_msg_18

error_mp_msg_19: db     'Error! INTERRUPCION, numero: 19'
error_mp_len_19: equ    $ - error_mp_msg_19

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    ;mov eax, %1
    imprimir_texto_mp error_mp_msg_%1, error_mp_len_%1, 0x07, 0, 0
    jmp $                                                                       ;OJO QUE SE QUEDA CLAVADO ACA!

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '\|/-'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 16
ISR 17
ISR 18
ISR 19

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

global _isr32

_isr32:
    pushad
    ;xchg bx, bx
    call proximo_reloj
    call fin_intr_pic1
    popad
    iret

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;

global _isr33
_isr33:
    pushad

    in al, 0x60

    ;xchg bx, bx

    cmp eax, 0x11
    je .letraW

    cmp eax, 0x1e
    je .letraA

    cmp eax, 0x1f
    je .letraS

    cmp eax, 0x20
    je .letraD

    cmp eax, 0x17
    je .letraI

    cmp eax, 0x24
    je .letraJ

    cmp eax, 0x25
    je .letraK

    cmp eax, 0x26
    je .letraL

    jne .fin

    .letraW:
    xor eax, eax
    mov byte [fs:eax], 'w'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .letraA:
    xor eax, eax
    mov byte [fs:eax], 'a'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .letraS:
    xor eax, eax
    mov byte [fs:eax], 's'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .letraD:
    xor eax, eax
    mov byte [fs:eax], 'd'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .letraI:
    xor eax, eax
    mov byte [fs:eax], 'i'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .letraJ:
    xor eax, eax
    mov byte [fs:eax], 'j'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .letraK:
    xor eax, eax
    mov byte [fs:eax], 'k'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .letraL:
    xor eax, eax
    mov byte [fs:eax], 'l'
    add eax, 1
    mov byte [fs:eax], 0x70 ;color
    add eax, 1
    jmp .fin

    .fin:
    call fin_intr_pic1
    popad
    iret


;;
;; Rutina de atención MISTERIO
;; -------------------------------------------------------------------------- ;;
global _isr66
_isr66:
pushad
cmp eax, 0x124
je .donde
cmp eax, 0xA6A
je .soy
cmp eax, 0xFF3
je .mapear
jmp .fin

.donde:
call game_donde
jmp .fin

.soy:
push ebx
call game_soy
pop ebx
jmp .fin

.mapear:
call game_mapear
jmp .fin

;mov eax, 0x42

.fin:
popad
iret

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define DONDE  0x124
%define SOY    0xA6A
%define MAPEAR 0xFF3

%define VIRUS_ROJO 0x841
%define VIRUS_AZUL 0x325


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
        
    
