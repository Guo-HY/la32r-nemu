# 1 "n58_rdcnt.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "n58_rdcnt.S"
# 1 "../include/asm.h" 1



# 1 "../include/regdef.h" 1
# 5 "../include/asm.h" 2
# 1 "../include/sysdep.h" 1
# 6 "../include/asm.h" 2
# 2 "n58_rdcnt.S" 2
# 1 "../include/regdef.h" 1
# 3 "n58_rdcnt.S" 2
# 1 "../include/inst_test.h" 1

# 1 "../include/cpu_cde.h" 1
# 3 "../include/inst_test.h" 2
# 4 "n58_rdcnt.S" 2

.text; .globl n58_rdcnt_test; .align 3; .cfi_startproc ; .type n58_rdcnt_test, @function; n58_rdcnt_test:
### disable trace comp
    li $r12, 0xbfafff30
    li $r13, 0xbfaf8ffc
    st.w $r0, $r13, 0
    st.w $r0, $r13, 0
    st.w $r0, $r12, 0
    st.w $r0, $r13, 0
    st.w $r0, $r13, 0
    ld.w $r0, $r13, 0
    ld.w $r12, $r12, 0

    addi.w $r23, $r23 ,1
    li $r25, 0x0
    li $r30, 0x1111ffff
    move $r13, $r30
    csrwr $r13, 0x40

##inst test
###1
    rdcntvl.w $r13
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r14
    rdcntid $r12
    bne $r12, $r30, inst_error
    li $r30, 0xffff1111
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r15
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r16
    rdcntid $r12
    bne $r12, $r30, inst_error
    sub.w $r13, $r15, $r13
    sub.w $r14, $r16, $r14
    bltu $r13, $r14, inst_error

###2
    li $r30, 0xffffffff
    move $r13, $r30
    csrwr $r13, 0x40
    li $r19, (0xd0100000 +0xd0004)
    st.w $r19, $r19, 4
    st.w $r27, $r19, 4
    rdcntvl.w $r13
    rdcntid $r12
    st.w $r27, $r19, 0
    ld.w $r17, $r19, 4
    bne $r17, $r27, inst_error
    bne $r12, $r30, inst_error
    st.w $r19, $r19, 4
    st.w $r27, $r19, 4
    rdcntvh.w $r14
    rdcntid $r12
    st.w $r27, $r19, 0
    ld.w $r17, $r19, 4
    bne $r17, $r27, inst_error
    bne $r12, $r30, inst_error
    li $r30, 0xffff0000
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r15
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r16
    rdcntid $r12
    bne $r12, $r30, inst_error
    sub.w $r13, $r15, $r13
    sub.w $r14, $r16, $r14
    bltu $r13, $r14, inst_error

###3
    li $r30, 0xffff
    move $r13, $r30
    csrwr $r13, 0x40
    li $r19, 0xf
    li $r20, 0xf
    div.w $r19, $r13, $r23
    rdcntvl.w $r13
    rdcntid $r12
    beq $r20, $r19, inst_error
    bne $r12, $r30, inst_error
    li $r19, 0xf
    li $r20, 0xf
    div.w $r19, $r13, $r23
    rdcntvh.w $r14
    rdcntid $r12
    beq $r20, $r19, inst_error
    bne $r12, $r30, inst_error
    li $r30, 0x0
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r15
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r16
    rdcntid $r12
    bne $r12, $r30, inst_error
    sub.w $r13, $r15, $r13
    sub.w $r14, $r16, $r14
    bltu $r13, $r14, inst_error

###4
    li $r30, 0xff
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r13
    rdcntid $r12
    div.w $r19, $r12, $r23
    bne $r12, $r30, inst_error
    rdcntvh.w $r14
    rdcntid $r12
    div.w $r19, $r12, $r23
    bne $r12, $r30, inst_error
    li $r30, 0xffff11
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r15
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r16
    rdcntid $r12
    bne $r12, $r30, inst_error
    sub.w $r13, $r15, $r13
    sub.w $r14, $r16, $r14
    bltu $r13, $r14, inst_error

###5
    li $r30, 0xf
    move $r13, $r30
    csrwr $r13, 0x40
    li $r19, 0xf
    li $r20, 0xf
    mul.w $r19, $r23, $r19
    rdcntvl.w $r13
    rdcntid $r12
    beq $r20, $r19, inst_error
    bne $r12, $r30, inst_error
    li $r19, 0xf
    li $r20, 0xf
    mul.w $r19, $r23, $r19
    rdcntvh.w $r14
    rdcntid $r12
    beq $r20, $r19, inst_error
    bne $r12, $r30, inst_error
    li $r30, 0xf11
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r15
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r16
    rdcntid $r12
    bne $r12, $r30, inst_error
    sub.w $r13, $r15, $r13
    sub.w $r14, $r16, $r14
    bltu $r13, $r14, inst_error

###6
    li $r30, 0xfffff
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r13
    rdcntid $r12
    mul.w $r19, $r12, $r23
    bne $r12, $r30, inst_error
    rdcntvh.w $r14
    rdcntid $r12
    mul.w $r19, $r12, $r23
    bne $r12, $r30, inst_error
    li $r30, 0x11fff
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r15
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r16
    rdcntid $r12
    bne $r12, $r30, inst_error
    sub.w $r13, $r15, $r13
    sub.w $r14, $r16, $r14
    bltu $r13, $r14, inst_error

###7
    li $r30, 0x23232
    move $r13, $r30
    csrwr $r13, 0x40
    csrwr $r19, 0x6
    rdcntvl.w $r13
    rdcntid $r12
    csrwr $r20, 0x6
    bne $r12, $r30, inst_error
    csrwr $r19, 0x6
    rdcntvh.w $r14
    rdcntid $r12
    csrwr $r20, 0x6
    bne $r12, $r30, inst_error
    li $r30, 0xabab
    move $r13, $r30
    csrwr $r13, 0x40
    rdcntvl.w $r15
    rdcntid $r12
    bne $r12, $r30, inst_error
    rdcntvh.w $r16
    rdcntid $r12
    bne $r12, $r30, inst_error
    sub.w $r13, $r15, $r13
    sub.w $r14, $r16, $r14
    bltu $r13, $r14, inst_error

###detect exception
  bne $r25, $r0, inst_error
###score +++
  addi.w $r26, $r26, 1
###output ($r23<<24)|$r26
inst_error:
### enable trace comp
  li $r12, 0xbfafff30
  li $r13, 0xbfaf8ffc
  st.w $r0, $r13, 0
  st.w $r0, $r13, 0
  st.w $r12, $r12, 0
  st.w $r0, $r13, 0
  st.w $r0, $r13, 0
  ld.w $r0, $r13, 0
  ld.w $r12, $r12, 0

  slli.w $r13, $r23, 24
  or $r12, $r13, $r26
  st.w $r12, $r24, 0
  jirl $r0, $r1, 0


.cfi_endproc ; .size n58_rdcnt_test,.-n58_rdcnt_test;
