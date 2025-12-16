/* boot.S */
    .section .multiboot
    .align 8
    .long 0xe85250d6          /* magic */
    .long 0                   /* architecture (i386) */
    .long boot_end - boot_start
    .long -(0xe85250d6 + 0 + (boot_end - boot_start))

boot_start:
    /* no tags, just end tag */
    .align 8
    .word 0
    .word 0
    .long 8
boot_end:

    .section .text
    .global _start
_start:
    /* Multiboot2 passes multiboot info pointer in rdi on x86_64 */
    call kernel_main
1:  hlt
    jmp 1b