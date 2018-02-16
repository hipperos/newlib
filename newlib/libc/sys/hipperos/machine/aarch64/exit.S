_exit:
    /* Store the syscall ID (0) in x4 */
    mov x4, xzr
    /* Do the supervisor call */
    svc #0
loop:
    /* Infinite loop */
    b loop
