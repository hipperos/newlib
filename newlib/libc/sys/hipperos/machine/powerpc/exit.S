_exit:
    /* Store the syscall ID (0) in r4 */
    li %r4, 0
    /* Do the supervisor call */
    sc
loop:
    /* Infinite loop */
    b loop
