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

extern catch_exception
extern interrupcion_teclado
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    push %1
    call catch_exception
    pop edi
    ; iret

%endmacro

;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'
char_a:              db 'a'
char_s:              db 's'
char_d:              db 'd'            
char_w:              db 'w' 
char_shl:            db '>' 
char_i:              db 'i' 
char_j:              db 'j' 
char_k:              db 'k' 
char_l:              db 'l' 
char_shr:            db '<' 


;a: 1e s:1f d:20 w:11    shift: 2a  i:17 j:24  k:25 l:26  right_shift:36
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
ISR 15
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
    call proximo_reloj
    call fin_intr_pic1
    popad
    iret

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;
global _isr33
_isr33:
    ;jxchg bx, bx
    pushad
    xor eax, eax
    in al, 0x60
    
    cmp al, 0x1e
    je .a
    cmp al, 0x1f
    je .s
    cmp al, 0x20
    je .d
    cmp al, 0x11
    je .w
    cmp al, 0x2a
    je .sh_left
    cmp al, 0x17
    je .i
    cmp al, 0x24
    je .j
    cmp al, 0x25
    je .k
    cmp al, 0x26
    je .l
    cmp al, 0x36
    je .sh_right
    
    .fin:
        call fin_intr_pic1
        popad
        iret

.a:
    mov ebx, char_a
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin

.s:
    mov ebx, char_s
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.d:
    mov ebx, char_d
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.w:
    mov ebx, char_w
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.sh_left:
    mov ebx, char_shl
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.i:
    mov ebx, char_i
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.j:
    mov ebx, char_j
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.k:
    mov ebx, char_k
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.l:
    mov ebx, char_l
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin
.sh_right:
    mov ebx, char_shr
    imprimir_texto_mp ebx, 1, 0x0f, 0, 39
    jmp .fin




;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
global _isr66
_isr66:
    mov eax, 0x42
    iret




%define IZQ 0xAAA
%define DER 0x441
%define ADE 0x83D
%define ATR 0x732


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
        
        
