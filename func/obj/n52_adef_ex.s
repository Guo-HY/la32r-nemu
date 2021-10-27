# 1 "n52_adef_ex.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "n52_adef_ex.S"
# 1 "../include/asm.h" 1



# 1 "../include/regdef.h" 1
# 5 "../include/asm.h" 2
# 1 "../include/sysdep.h" 1
# 6 "../include/asm.h" 2
# 2 "n52_adef_ex.S" 2
# 1 "../include/regdef.h" 1
# 3 "n52_adef_ex.S" 2
# 1 "../include/inst_test.h" 1

# 1 "../include/cpu_cde.h" 1
# 3 "../include/inst_test.h" 2
# 4 "n52_adef_ex.S" 2

.text; .globl n52_adef_ex_test; .align 3; .cfi_startproc ; .type n52_adef_ex_test, @function; n52_adef_ex_test:

  addi.w $r23, $r23, 1
  li $r12, (0xd0100000 +0xd0000)
  li $r25, 0x5
  st.w $r25, $r12, 0

  li $r12, 0x1
  csrwr $r12, 0x44

  li $r12, 0x3
  li $r13, 0x7
  csrxchg $r12, $r13, 0x0
  lu12i.w $r30, 0x50
  li $r17, 0x3

##inst test
###1
  li $r27, 0xb27f9789; li $r7, 0xb27f9789; li $r29, 0xb27f9789
  jirl $r28, $r27, 0
  add.w $r0, $r0, $r0
  bne $r25, $r30, inst_error
  csrrd $r12, 0x7
  bne $r7, $r12, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x3
  bne $r13, $r12, inst_error

###2
  li $r19, 0xd0000
  li $r25, 0x05
  li $r27, 0xa101bbed; li $r7, 0xa101bbed; li $r29, 0xa101bbed
  csrwr $r29, 0x6
  la.local $r28, 1f
  st.w $r19, $r19, 4
  st.w $r27, $r19, 4
1: ertn
  st.w $r27, $r19, 0
  ld.w $r13, $r19, 4
  bne $r13, $r27, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x7
  bne $r7, $r12, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x3
  bne $r13, $r12, inst_error
  li $r25, 0x5
  st.w $r25, $r19, 0

###3
  li $r25, 0x05
  li $r27, 0x84790977; li $r7, 0x84790977; li $r29, 0x84790977
  csrwr $r29, 0x6
  la.local $r28, 1f
  li $r19, 0xf
  li $r20, 0xf
  div.w $r19, $r13, $r23
1: ertn
  beq $r20, $r19, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x7
  bne $r7, $r12, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x3
  bne $r13, $r12, inst_error

###4
  li $r25, 0x05
  li $r27, 0x92b0a2c3; li $r7, 0x92b0a2c3; li $r29, 0x92b0a2c3
  jirl $r28, $r27, 0
  add.w $r0, $r0, $r0
  div.w $r12, $r12, $r23
  bne $r25, $r30, inst_error
  csrrd $r12, 0x7
  bne $r7, $r12, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x3
  bne $r13, $r12, inst_error

###5
  li $r25, 0x05
  li $r27, 0xaf9edafa; li $r7, 0xaf9edafa; li $r29, 0xaf9edafa
  csrwr $r29, 0x6
  la.local $r28, 1f
  li $r19, 0xf
  li $r20, 0xf
  mul.w $r19, $r23, $r19
1: ertn
  beq $r20, $r19, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x7
  bne $r7, $r12, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x3
  bne $r13, $r12, inst_error

###6
  li $r25, 0x05
  li $r27, 0xb088f329; li $r7, 0xb088f329; li $r29, 0xb088f329
  jirl $r28, $r27, 0
  add.w $r0, $r0, $r0
  mul.w $r12, $r12, $r23
  bne $r25, $r30, inst_error
  csrrd $r12, 0x7
  bne $r7, $r12, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x3
  bne $r13, $r12, inst_error

###7
  li $r25, 0x05
  li $r27, 0x827f97ab; li $r7, 0x827f97ab; li $r29, 0x827f97ab
  csrwr $r29, 0x6
  la.local $r28, 1f
1: ertn
  csrwr $r12, 0x6
  bne $r25, $r30, inst_error
  csrrd $r12, 0x7
  bne $r7, $r12, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x3
  bne $r13, $r12, inst_error

  li $r12, 0x0
  li $r13, 0x3
  csrxchg $r12, $r13, 0x0
###score +++
  addi.w $r26, $r26, 1
###output ($r23<<24)|$r26
inst_error:
  slli.w $r13, $r23, 24
  or $r12, $r13, $r26
  st.w $r12, $r24, 0
  jirl $r0, $r1, 0
.cfi_endproc ; .size n52_adef_ex_test,.-n52_adef_ex_test;
