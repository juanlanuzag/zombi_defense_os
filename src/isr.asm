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
extern game_lanzar_zombi
extern game_jugador_mover
extern game_change_zombie
extern game_move_current_zombi

extern girar_reloj_actual

extern game_reiniciar
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    push %1
    call catch_exception
    pop edi
    jmp 0x70:0xFAFAFA
    ;iret

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
offset:              dd 0
selector:            dw 0

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

    call sched_proximo_indice

    cmp ax, 0
    je .nojump
        push eax
        call girar_reloj_actual
        pop eax
        mov [selector], ax
        call fin_intr_pic1
        jmp far [offset]
        jmp .end

    .nojump:
    call fin_intr_pic1

    .end:
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
    cmp al, 0x15
    je .y
    
    .fin:
        call fin_intr_pic1
        popad
        iret

; INSTRUCCIONES DE MOVER AL JUGADOR

.w:  ; A hacia arriba
    mov ebx, -1
    push ebx
    mov ebx, 0
    push ebx
    call game_jugador_mover
    add esp, 8
    jmp .fin

.s:  ; A hacia abajo
    mov ebx, 1
    push ebx
    mov ebx, 0
    push ebx
    call game_jugador_mover
    add esp, 8
    jmp .fin

.i:   ; B hacia arriba
    mov ebx, -1
    push ebx
    mov ebx, 1
    push ebx
    call game_jugador_mover
    add esp, 8
    jmp .fin

.k:   ; B hacia abajo
    mov ebx, 1
    push ebx
    mov ebx, 1
    push ebx
    call game_jugador_mover
    add esp, 8
    jmp .fin

; INSTRUCCIONES PARA CAMBIAR DE ZOMBIE

.a: ; A hacia izq
    mov ebx, -1
    push ebx
    mov ebx, 0
    push ebx
    call game_change_zombie
    add esp, 8
    jmp .fin

.d: ; A hacia der
    mov ebx, 1
    push ebx
    mov ebx, 0
    push ebx
    call game_change_zombie
    add esp, 8
    jmp .fin

.j: ; B hacia izq
    mov ebx, -1
    push ebx
    mov ebx, 1
    push ebx
    call game_change_zombie
    add esp, 8
    jmp .fin

.l: ; B hacia der
    mov ebx, 1
    push ebx
    mov ebx, 1
    push ebx
    call game_change_zombie
    add esp, 8
    jmp .fin


; INSTRUCCIONES PARA LANZAR UNO ZOMBIE

.sh_left:
    mov ebx, 0
    push ebx    
    call game_lanzar_zombi
    pop ebx    
    jmp .fin

.sh_right:
    mov ebx, 1
    push ebx    
    call game_lanzar_zombi
    pop ebx
    jmp .fin

; INSTRUCCION DE REINICIO

.y:   
    call game_reiniciar
    jmp .fin

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;
global _isr102
_isr102:
    pushad
    push eax
    call game_move_current_zombi
    pop eax
    ;jump a la tarea idle
    jmp 0x70:0xFAFAFA    
    popad
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

global nuestro_proximo_reloj
nuestro_proximo_reloj:
        pop esi
            mov edi, [isrnumero]
            add edi, isrClock
            imprimir_texto_mp edi, 1, 0x0f, esi, 48
        sub esp,4
        ret

        
        
