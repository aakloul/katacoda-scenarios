.S:
    .asciz "Hello, World"
.globl main
main:
    push $.S
    call puts
    add $4, %esp
    xor %eax, %eax
    ret
