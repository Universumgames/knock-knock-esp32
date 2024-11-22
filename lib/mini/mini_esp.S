# risc-v assembly cheat sheet https://projectf.io/posts/riscv-cheat-sheet/

.global max
.global min

max:
    bge a0, a1, end_max         # branch if a0 greater or equal to a1, if true jump to end_max
    mv a0, a1                   # a0 = a1
end_max:
    li a1, 0                    # a1 = 0
    ret                         # return


min:
    ble a0, a1, end_min         # branch if a0 less or equal to a1, if true jump to end_min
    mv a0, a1                   # a0 = a1
end_min:
    li a1, 0                    # a1 = 0
    ret                         # return
