# 1 "n49_ti_ex.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "n49_ti_ex.S"
# 1 "../include/asm.h" 1



# 1 "../include/regdef.h" 1
# 5 "../include/asm.h" 2
# 1 "../include/sysdep.h" 1
# 6 "../include/asm.h" 2
# 2 "n49_ti_ex.S" 2
# 1 "../include/regdef.h" 1
# 3 "n49_ti_ex.S" 2
# 1 "../include/inst_test.h" 1

# 1 "../include/cpu_cde.h" 1
# 3 "../include/inst_test.h" 2
# 4 "n49_ti_ex.S" 2

.text; .globl n49_ti_ex_test; .align 3; .cfi_startproc ; .type n49_ti_ex_test, @function; n49_ti_ex_test:

  addi.w $r23, $r23, 1
  li $r12, (0xd0100000 +0xd0000)
  li $r25, 0x4
  st.w $r25, $r12, 0

  li $r12, 0x1
  csrwr $r12, 0x44

  li $r12, 0x3
  li $r13, 0x7
  csrxchg $r12, $r13, 0x0
  lu12i.w $r30, 0x40
  li $r17, 0x7

##inst test
###1
  la.local $r27, 1f
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0x120; ori $r12, $r12, 0x1; csrwr $r12, 0x41; 1:; b 1b; csrwr $r0, 0x41
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


  la.local $r27, 1f
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0xe20; ori $r12, $r12, 0x3; csrwr $r12, 0x41; 1:; b 1b; la.local $r27, 2f; 2:; b 2b; csrwr $r0, 0x41
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


###2
  li $r19, 0xd0000
  li $r25, 0x04
  la.local $r27, 1f
  st.w $r19, $r19, 4
  st.w $r27, $r19, 4
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0x74; ori $r12, $r12, 0x1; csrwr $r12, 0x41; 1:; b 1b; csrwr $r0, 0x41
  st.w $r27, $r19, 0
  ld.w $r13, $r19, 4
  bne $r13, $r27, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error
  li $r25, 0x4
  st.w $r25, $r19, 0


  li $r28, 0x66
  li $r25, 0x04
  la.local $r27, 1f
  st.w $r19, $r19, 4
  st.w $r28, $r19, 4
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0xe74; ori $r12, $r12, 0x3; csrwr $r12, 0x41; 1:; b 1b; la.local $r27, 2f; 2:; b 2b; csrwr $r0, 0x41
  st.w $r27, $r19, 0
  ld.w $r13, $r19, 4
  bne $r13, $r28, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error
  li $r25, 0x4
  st.w $r25, $r19, 0


###3
  li $r25, 0x04
  la.local $r27, 1f
  li $r19, 0xf
  li $r20, 0xf
  div.w $r19, $r13, $r23
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0x10; ori $r12, $r12, 0x1; csrwr $r12, 0x41; 1:; b 1b; csrwr $r0, 0x41
  beq $r20, $r19, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


  li $r25, 0x04
  la.local $r27, 1f
  li $r19, 0xf
  li $r20, 0xf
  div.w $r19, $r13, $r23
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0xe50; ori $r12, $r12, 0x3; csrwr $r12, 0x41; 1:; b 1b; la.local $r27, 2f; 2:; b 2b; csrwr $r0, 0x41
  beq $r20, $r19, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


###4
  li $r25, 0x04
  la.local $r27, 1f
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0x0; ori $r12, $r12, 0x1; csrwr $r12, 0x41; 1:; b 1b; csrwr $r0, 0x41
  div.w $r12, $r12, $r23
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


  li $r25, 0x04
  la.local $r27, 1f
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0xe55; ori $r12, $r12, 0x3; csrwr $r12, 0x41; 1:; b 1b; la.local $r27, 2f; 2:; b 2b; csrwr $r0, 0x41
  div.w $r12, $r12, $r23
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


###5
  li $r25, 0x04
  la.local $r27, 1f
  li $r19, 0xf
  li $r20, 0xf
  mul.w $r19, $r23, $r19
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0x4; ori $r12, $r12, 0x1; csrwr $r12, 0x41; 1:; b 1b; csrwr $r0, 0x41
  beq $r20, $r19, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


  li $r25, 0x04
  la.local $r27, 1f
  li $r19, 0xf
  li $r20, 0xf
  mul.w $r19, $r23, $r19
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0xe60; ori $r12, $r12, 0x3; csrwr $r12, 0x41; 1:; b 1b; la.local $r27, 2f; 2:; b 2b; csrwr $r0, 0x41
  beq $r20, $r19, inst_error
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


###6
  li $r25, 0x04
  la.local $r27, 1f
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0x8; ori $r12, $r12, 0x1; csrwr $r12, 0x41; 1:; b 1b; csrwr $r0, 0x41
  mul.w $r12, $r12, $r23
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


  li $r25, 0x04
  la.local $r27, 1f
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0xe70; ori $r12, $r12, 0x3; csrwr $r12, 0x41; 1:; b 1b; la.local $r27, 2f; 2:; b 2b; csrwr $r0, 0x41
  mul.w $r12, $r12, $r23
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


###7
  li $r25, 0x04
  la.local $r27, 1f
  csrwr $r25, 0x6
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0x34; ori $r12, $r12, 0x1; csrwr $r12, 0x41; 1:; b 1b; csrwr $r0, 0x41
  csrwr $r12, 0x6
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


  li $r25, 0x04
  la.local $r27, 1f
  csrwr $r25, 0x6
  li $r12, 0x4; li $r13, 0x4; csrxchg $r12, $r13, 0x0; li $r12, 0x1fff; csrwr $r12, 0x4; li $r12, 0xe80; ori $r12, $r12, 0x3; csrwr $r12, 0x41; 1:; b 1b; la.local $r27, 2f; 2:; b 2b; csrwr $r0, 0x41
  csrwr $r12, 0x6
  bne $r25, $r30, inst_error
  csrrd $r12, 0x0
  li $r13, 0x7
  and $r12, $r12, $r13
  li $r13, 0x7
  bne $r13, $r12, inst_error


###8 LIE disable
  li $r12, 0x0
  li $r13, 0x3
  csrxchg $r12, $r13, 0x0

  li $r12, (0xd0100000 +0xd0000)
  li $r25, 0xa
  st.w $r25, $r12, 0
  li $r12, 0x7
  li $r13, 0x7
  csrxchg $r12, $r13, 0x0
  li $r12, 0x0
  csrwr $r12, 0x4
  li $r12, 0x4
  ori $r12, $r12, 0x1
  csrwr $r12, 0x41
  li $r12, 0x80
  li $r13, 0x0
1:
  addi.w $r12, $r12, -0x1
  bne $r12, $r13, 1b

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
.cfi_endproc ; .size n49_ti_ex_test,.-n49_ti_ex_test;
