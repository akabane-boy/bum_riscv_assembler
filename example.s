    addi x1, x0, 5      # x1 = 5
    add x1, x0, 5      # x1 = 5
    addi x2, x0, 10     # x2 = 10
    add  x3, x1, x2     # x3 = x1 + x2

loop:
    beq  x3, x0, end
    sub x3, x0, end
    addi x3, x3, -1
    jal  x0, loop

end:
    nop
