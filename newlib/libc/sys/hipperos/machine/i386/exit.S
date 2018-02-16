_exit:
    /* Store the syscall ID (0) in r4 */
    mov eax, 0
    /* Do the supervisor call */
    int 0x80
loop:
    /* Infinite loop */
    jmp loop
