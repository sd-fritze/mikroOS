.section multiboot
#define MB_MAGIC 0x1badb002
#define MB_FLAGS 0x0
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)
 
// Der Multiboot-Header
.align 4
.int    MB_MAGIC
.int    MB_FLAGS
.int    MB_CHECKSUM
 
.section .text
 
// Init ist eine Funktion aus init.c
.extern init
 
// _start muss global sein, damit der Linker es findet und als Einsprungspunkt benutzen kann 
.global _start
_start:
    // Stack initialisieren
    mov $kernel_stack, %esp
 
    // C-Code aufrufen
    call init
 
    // Falls wir jemals aus init zurueckkommen sollten, gehen wir in eine
    // Endlosschleife
    jmp .
 
// 8 kB Stack fuer den Kernel.
.section .bss
.space 8192
kernel_stack:
