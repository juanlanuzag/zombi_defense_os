; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"

global start
extern GDT_DESC
extern idt_inicializar
extern mmu_inicializar
extern IDT_DESC
extern clear_screen
extern print_board
extern print_group_name
extern windows_screen
;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

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
    call habilitar_A20
    
    ; Cargar la GDT
    lgdt [GDT_DESC]
    ; Setear el bit PE del registro CR0
    MOV eax,cr0 
    OR eax,1 
    MOV cr0,eax
    ; Saltar a modo protegido
    jmp 0x40:mp

; Establecer selectores de segmentos
    BITS 32    
    mp:
        xor eax, eax
        mov ax, 0x48 ;1001000b
        mov ds, ax
        mov es, ax
        mov gs, ax
        mov ss, ax
        mov ax, 1100000b
        mov fs, ax

    ; Establecer la base de la pila
    
    ; Imprimir mensaje de bienvenida

    ; Inicializar pantalla
    
    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
        call mmu_inicializar    
    ; Cargar directorio de paginas
        mov eax, 0x27000
        mov cr3, eax
    ; Habilitar paginacion
        mov eax, cr0
        or eax, 0x80000000
        mov cr0, eax
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
        call idt_inicializar
        call clear_screen
        call print_board
        call print_group_name
    ; Cargar IDT
        lidt [IDT_DESC]

    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones
       ; sti
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
