.global assembly_phase_1
.global assembly_phase_2
.global assembly_phase_3
.global assembly_phase_4
.global assembly_phase_5
.type assembly_phase_1, @function
.type assembly_phase_2, @function
.type assembly_phase_3, @function
.type assembly_phase_4, @function
.type assembly_phase_5, @function

.text
assembly_phase_1:
  lw a5, 0(a2)
  bne a5, a0, label_42007a4e
  ret
label_42007a4e:
  addi sp, sp, -16
  sw ra, 12(sp)
  call explode
  lw ra, 12(sp)
  addi sp, sp, 16
  ret

assembly_phase_2:
  addi sp, sp, -16
  sw ra, 12(sp)
  li a5, 3
  bne a1, a5, label_42007a78
  lw a5, 0(a2)
  lw a4, 4(a2)
  add a5, a5, a4
  lw a4, 8(a2)
  add a5, a5, a4
  blt a4, a0, label_42007a7c
label_42007a72:
  lw ra, 12(sp)
  addi sp, sp, 16
  ret
label_42007a78:
  call explode
  j label_42007a72
label_42007a7c:
  call explode
  j label_42007a72

assembly_phase_3:
  addi sp, sp, -16
  sw ra, 12(sp)
  li a5, 2
  bne a1, a5, label_42007aa8
  lw a5, 0(a2)
  li a4, 43
  beq a5, a4, label_42007abc
  li a4, 45
  beq a5, a4, label_42007ac0
  li a4, 42
  beq a5, a4, label_42007ab0
  call explode
  j label_42007aaa
label_42007aa8: 
  call explode
label_42007aaa: 
  lw ra, 12(sp)
  addi sp, sp, 16
  ret
label_42007ab0:
  slli a0, a0, 0x1
label_42007ab2:
  lw a5, 4(a2)
  beq a5, a0, label_42007aaa
  call explode
  j label_42007aaa
label_42007abc: 
  addi a0, a0, 2
  j label_42007ab2
label_42007ac0:
  addi a0, a0, -2
  j label_42007ab2 

assembly_phase_4:
  addi sp, sp, -16
  sw ra, 12(sp)
  li a5, 3
  bne a1, a5, label_42007ade
  lw a5, 0(a2)
  andi a5, a5, 15
  sw a5, 0(a2)
  li a4, 9
  bge a4, a5, label_42007b02
  call explode
  j label_42007ae0
label_42007ade:
  call explode
label_42007ae0:
  lw ra, 12(sp)
  addi sp, sp, 16
  ret
label_42007ae6:
  lw a3, 4(a2)
  la a4, mysterious_data
  slli a1, a5, 0x2
  add a4, a4, a1
  lw a4, 0(a4)
  sub a4, a3, a4
  sw a4, 4(a2)
  addi a5, a5, -1
  sw a5, 0(a2)
label_42007b02:
  lw a5, 0(a2)
  bgt a5, x0, label_42007ae6
  lw a4, 4(a2)
  lw a5, 8(a2)
  beq a4, a5, label_42007ae0
  call explode
  j label_42007ae0
  ret

mysterious_function:
  ble a1, x0, label_42007b34
  addi sp, sp, -16
  sw ra, 12(sp)
  sw s0, 8(sp)
  mv s0, a0
  li a5, 1
  beq a1, a5, label_42007b2c
  addi a1, a1, -1
  call mysterious_function
  add a0, a0, s0
label_42007b2c:
  lw ra, 12(sp)
  lw s0, 8(sp)
  addi sp, sp, 16
  ret
label_42007b34:
  li a0, 0
  ret

assembly_phase_5:
  addi sp, sp, -16
  sw ra, 12(sp)
  sw s0, 8(sp)
  li a5, 2
  bne a1, a5, label_42007b66
  mv s0, a2
  lw a1, 0(a2)
  addi a4, a1, -5
  li a5, 5
  bltu a5, a4, label_42007b70
  li a5, 10
  rem a0, a0, a5
  call mysterious_function
  lw a5, 4(s0)
  beq a5, a0, label_42007b68
  call explode
  j label_42007b68
label_42007b66: 
  call explode
label_42007b68: 
  lw ra, 12(sp)
  lw s0, 8(sp)
  addi sp, sp, 16
  ret
label_42007b70: 
  call explode
  j label_42007b68

.data
mysterious_data: 
  .word 0
  .word 1
  .word 2
  .word 3
  .word 4
  .word 5
  .word 6
  .word 7
  .word 8
  .word 9