# 1 "start.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "start.S"
# 1 "include/asm.h" 1



# 1 "include/regdef.h" 1
# 5 "include/asm.h" 2
# 1 "include/sysdep.h" 1
# 6 "include/asm.h" 2
# 2 "start.S" 2
# 1 "include/regdef.h" 1
# 3 "start.S" 2
# 1 "include/cpu_cde.h" 1
# 4 "start.S" 2
# 13 "start.S"
##$r23, number
##$r24, number adress
##$r25, exception use
##$r26, score
##$r27, exception pc
 .globl _start
 .globl start
 .globl __main
_start:
start:
    li $r12, 0xffffffff
    addi.w $r12, $r0, -1
    bl reg_init
 b locate

##avoid "j locate" not taken
    lu12i.w $r12, -0x80000
    addi.w $r13, $r13, 1
    or $r14, $r12, $r0
    add.w $r15, $r17, $r18
    ld.w $r16, $r12, 0

##avoid cpu run error
.org 0x0ec
    lu12i.w $r12, -0x80000
    addi.w $r13, $r13, 1
    or $r14, $r12, $r0
    add.w $r15, $r17, $r18
    ld.w $r16, $r12, 0
.org 0x100
test_finish:
    addi.w $r12, $r12, 1
    lu12i.w $r14 , (((0xbfafff10>>12)+((0xbfafff10&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfafff10>>12)+((0xbfafff10&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfafff10>>12)+((0xbfafff10&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r14, $r14, (0xbfafff10 & 0x00000fff)&0x800?(0xbfafff10 & 0x00000fff)-0x1000:(0xbfafff10 & 0x00000fff)
    st.w $r0, $r14, 0
1:
    .word 0x80000000
    b 1b

##avoid cpu run error
    lu12i.w $r12, -0x80000
    addi.w $r13, $r13, 1
    or $r14, $r12, $r0
    add.w $r15, $r17, $r18
    ld.w $r16, $r12, 0



.org 0x8000
1:
    li $r12, (0xd0100000 +0xd0000)
    ld.w $r13, $r12, 0
    li $r12, 0x1
    beq $r13, $r12, syscall_ex #syscall
    li $r12, 0x2
    beq $r13, $r12, brk_ex #break
    li $r12, 0x3
    beq $r13, $r12, ine_ex #reserved inst
    li $r12, 0x4
    beq $r13, $r12, int_ex #interrupt
    li $r12, 0x5
    beq $r13, $r12, adef_ex #adef
    li $r12, 0x6
    beq $r13, $r12, ale_ex #ale
# li $r12, 0x7
# beq $r13, $r12, ipe_ex #ipe
 b test_end


syscall_ex:
    add.w $r25, $r0, $r0
    csrrd $r12, 0x6
    bne $r27, $r12, ex_finish
    csrrd $r12, 0x5
    li $r13, 0x7fff0000
    and $r12, $r12, $r13
    li $r13, 0x000b0000
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x0
    li $r13, 0x7
    and $r12, $r12, $r13
    li $r13, 0x0
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x1
    li $r13, 0x7
    and $r12, $r12, $r13
    bne $r12, $r17, ex_finish
    lu12i.w $r25, 0x10
    b ex_finish

brk_ex:
    add.w $r25, $r0, $r0
    csrrd $r12, 0x6
    bne $r27, $r12, ex_finish
    csrrd $r12, 0x5
    li $r13, 0x7fff0000
    and $r12, $r12, $r13
    li $r13, 0x000c0000
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x0
    li $r13, 0x7
    and $r12, $r12, $r13
    li $r13, 0x0
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x1
    li $r13, 0x7
    and $r12, $r12, $r13
    bne $r12, $r17, ex_finish
    lu12i.w $r25, 0x20
    b ex_finish

ine_ex:
    add.w $r25, $r0, $r0
    csrrd $r12, 0x6
    bne $r27, $r12, ex_finish
    csrrd $r12, 0x5
    li $r13, 0x7fff0000
    and $r12, $r12, $r13
    li $r13, 0x000d0000
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x0
    li $r13, 0x7
    and $r12, $r12, $r13
    li $r13, 0x0
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x1
    li $r13, 0x7
    and $r12, $r12, $r13
    bne $r12, $r17, ex_finish
    lu12i.w $r25, 0x30
    b ex_finish

int_ex:
    add.w $r25, $r0, $r0
    csrrd $r12, 0x6
    bne $r27, $r12, ex_finish
    csrrd $r12, 0x5
    li $r13, 0x7fff0000
    and $r12, $r12, $r13
    li $r13, 0x00000000
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x0
    li $r13, 0x7
    and $r12, $r12, $r13
    li $r13, 0x0
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x1
    li $r13, 0x7
    and $r12, $r12, $r13
    bne $r12, $r17, ex_finish
    li $r13, 0x1
    csrwr $r13, 0x44
    bne $r13, $r0, ex_finish
    li $r13, 0x0
    li $r12, 0x3
    csrxchg $r13, $r12, 0x5
    csrrd $r13, 0x5
    li $r12, 0x1fff
    and $r12, $r12, $r13
    bne $r12, $r0, ex_finish
    lu12i.w $r25, 0x40
    b ex_finish

adef_ex:
    add.w $r25, $r0, $r0
    csrwr $r28, 0x6
    bne $r27, $r28, ex_finish
    csrrd $r12, 0x5
    li $r13, 0x7fff0000
    and $r12, $r12, $r13
    li $r13, 0x00080000
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x0
    li $r13, 0x7
    and $r12, $r12, $r13
    li $r13, 0x0
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x1
    li $r13, 0x7
    and $r12, $r12, $r13
    bne $r12, $r17, ex_finish
    lu12i.w $r25, 0x50
    b ex_finish

ale_ex:
    add.w $r25, $r0, $r0
    csrrd $r12, 0x6
    bne $r27, $r12, ex_finish
    csrrd $r12, 0x5
    li $r13, 0x7fff0000
    and $r12, $r12, $r13
    li $r13, 0x00090000
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x0
    li $r13, 0x7
    and $r12, $r12, $r13
    li $r13, 0x0
    bne $r13, $r12, ex_finish
    csrrd $r12, 0x1
    li $r13, 0x7
    and $r12, $r12, $r13
    bne $r12, $r17, ex_finish
    lu12i.w $r25, 0x60
    b ex_finish

ex_finish:
    csrrd $r13, 0x6
    addi.w $r13, $r13, 0x4
    csrwr $r13, 0x6
    bne $r25, $r0, ex_ret
    lu12i.w $r25, 0xffff
ex_ret:
    ertn

locate:

    lu12i.w $r4 , (((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r4, $r4, (0xbfaff040 & 0x00000fff)&0x800?(0xbfaff040 & 0x00000fff)-0x1000:(0xbfaff040 & 0x00000fff)
    lu12i.w $r5 , (((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r5, $r5, (0xbfaff030 & 0x00000fff)&0x800?(0xbfaff030 & 0x00000fff)-0x1000:(0xbfaff030 & 0x00000fff)
    lu12i.w $r6 , (((0xbfaff020>>12)+((0xbfaff020&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff020>>12)+((0xbfaff020&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff020>>12)+((0xbfaff020&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r6, $r6, (0xbfaff020 & 0x00000fff)&0x800?(0xbfaff020 & 0x00000fff)-0x1000:(0xbfaff020 & 0x00000fff)
    lu12i.w $r24 , (((0xbfaff050>>12)+((0xbfaff050&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff050>>12)+((0xbfaff050&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff050>>12)+((0xbfaff050&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r24, $r24, (0xbfaff050 & 0x00000fff)&0x800?(0xbfaff050 & 0x00000fff)-0x1000:(0xbfaff050 & 0x00000fff)

    lu12i.w $r13 , (((0x0002>>12)+((0x0002&0x00000800)>>11))&0x000fffff)&0x80000?(((0x0002>>12)+((0x0002&0x00000800)>>11))&0x000fffff)-0x100000:(((0x0002>>12)+((0x0002&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r13, $r13, (0x0002 & 0x00000fff)&0x800?(0x0002 & 0x00000fff)-0x1000:(0x0002 & 0x00000fff)
    lu12i.w $r14 , (((0x0001>>12)+((0x0001&0x00000800)>>11))&0x000fffff)&0x80000?(((0x0001>>12)+((0x0001&0x00000800)>>11))&0x000fffff)-0x100000:(((0x0001>>12)+((0x0001&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r14, $r14, (0x0001 & 0x00000fff)&0x800?(0x0001 & 0x00000fff)-0x1000:(0x0001 & 0x00000fff)
    lu12i.w $r15 , (((0x0000ffff>>12)+((0x0000ffff&0x00000800)>>11))&0x000fffff)&0x80000?(((0x0000ffff>>12)+((0x0000ffff&0x00000800)>>11))&0x000fffff)-0x100000:(((0x0000ffff>>12)+((0x0000ffff&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r15, $r15, (0x0000ffff & 0x00000fff)&0x800?(0x0000ffff & 0x00000fff)-0x1000:(0x0000ffff & 0x00000fff)
    lu12i.w $r26, 0
    ;;;

    st.w $r13, $r4, 0
    st.w $r14, $r5, 0
    st.w $r15, $r6, 0
    st.w $r26, $r24, 0
    lu12i.w $r23, 0
    ;;;
inst_test:
############################
###1 test

    bl n1_lu12i_w_test #lu12i.w
    .word 0xc0000000

    # bl idle_1s

    bl n2_add_w_test #add.w
    .word 0xc0000000
    # bl idle_1s

    bl n3_addi_w_test #add.w
    .word 0xc0000000
    # bl idle_1s

    bl n4_sub_w_test #sub.w
    .word 0xc0000000
    # bl idle_1s

    bl n5_slt_test #slt
    .word 0xc0000000
    # bl idle_1s

    bl n6_sltu_test #sltu
    .word 0xc0000000
    # bl idle_1s

    bl n7_and_test #and
    .word 0xc0000000
    # bl idle_1s

    bl n8_or_test #or
    .word 0xc0000000
    # bl idle_1s

    bl n9_xor_test #xor
    .word 0xc0000000
    # bl idle_1s

    bl n10_nor_test #nor
    .word 0xc0000000
    # bl idle_1s

    bl n11_slli_w_test #slli.w
    .word 0xc0000000
    # bl idle_1s

    bl n12_srli_w_test #srli.w
    .word 0xc0000000
    # bl idle_1s

    bl n13_srai_w_test #srai.w
    .word 0xc0000000
    # bl idle_1s

    bl n14_ld_w_test #ld.w
    .word 0xc0000000
    # bl idle_1s

    bl n15_st_w_test #st.w
    .word 0xc0000000
    # bl idle_1s

    bl n16_beq_test #beq
    .word 0xc0000000
    # bl idle_1s

    bl n17_bne_test #bne
    .word 0xc0000000
    # bl idle_1s

    bl n18_bl_test #bl
    .word 0xc0000000
    # bl idle_1s

    bl n19_jirl_test #jirl
    .word 0xc0000000
    # bl idle_1s

    bl n20_b_test #b
    .word 0xc0000000
    # bl idle_1s

############################
############################
###1 test

    bl n21_pcaddu12i_test #pcaddu12i
    .word 0xc0000000
    # bl idle_1s

    bl n22_slti_test #slti
    .word 0xc0000000
    # bl idle_1s

    bl n23_sltui_test #sltui
    .word 0xc0000000
    # bl idle_1s

    bl n24_andi_test #andi
    .word 0xc0000000
    # bl idle_1s

    bl n25_ori_test #ori
    .word 0xc0000000
    # bl idle_1s

    bl n26_xori_test #xori
    .word 0xc0000000
    # bl idle_1s

    bl n27_sll_w_test #sll.w
    .word 0xc0000000
    # bl idle_1s

    bl n28_sra_w_test #sra.w
    .word 0xc0000000
    # bl idle_1s

    bl n29_srl_w_test #srl.w
    .word 0xc0000000
    # bl idle_1s

    bl n30_div_w_test #div.w
    .word 0xc0000000
    # bl idle_1s

    bl n31_div_wu_test #div.wu
    .word 0xc0000000
    # bl idle_1s

    bl n32_mul_w_test #mul.w
    .word 0xc0000000
    # bl idle_1s

    bl n33_mulh_w_test #mulh.w
    .word 0xc0000000
    # bl idle_1s

    bl n34_mulh_wu_test #mulh.wu
    .word 0xc0000000
    # bl idle_1s

    bl n35_mod_w_test #mod.w
    .word 0xc0000000
    # bl idle_1s

    bl n36_mod_wu_test #mod.wu
    .word 0xc0000000
    # bl idle_1s


############################
############################
###1 test

    bl n37_blt_test #blt
    .word 0xc0000000
    # bl idle_1s

    bl n38_bge_test #bge
    .word 0xc0000000
    # bl idle_1s

    bl n39_bltu_test #bltu
    .word 0xc0000000
    # bl idle_1s

    bl n40_bgeu_test #bgeu
    .word 0xc0000000
    # bl idle_1s

    bl n41_ld_b_test #ld.b
    .word 0xc0000000
    # bl idle_1s

    bl n42_ld_h_test #ld.h
    .word 0xc0000000
    # bl idle_1s

    bl n43_ld_bu_test #ld.bu
    .word 0xc0000000
    # bl idle_1s

    bl n44_ld_hu_test #ld.hu
    .word 0xc0000000
    # bl idle_1s

    bl n45_st_b_test #st.b
    .word 0xc0000000
    # bl idle_1s

    bl n46_st_h_test #st.h
    .word 0xc0000000
    # bl idle_1s


############################
############################
###lab8 test
# 458 "start.S"
############################
############################
###lab9 test
# 511 "start.S"
test_end:
    lu12i.w $r23 , ((((1*20 + 1*16 + 1*10)>>12)+(((1*20 + 1*16 + 1*10)&0x00000800)>>11))&0x000fffff)&0x80000?((((1*20 + 1*16 + 1*10)>>12)+(((1*20 + 1*16 + 1*10)&0x00000800)>>11))&0x000fffff)-0x100000:((((1*20 + 1*16 + 1*10)>>12)+(((1*20 + 1*16 + 1*10)&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r23, $r23, ((1*20 + 1*16 + 1*10) & 0x00000fff)&0x800?((1*20 + 1*16 + 1*10) & 0x00000fff)-0x1000:((1*20 + 1*16 + 1*10) & 0x00000fff)
    beq $r23, $r26, 1f

    lu12i.w $r4 , (((0xbfaff020>>12)+((0xbfaff020&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff020>>12)+((0xbfaff020&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff020>>12)+((0xbfaff020&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r4, $r4, (0xbfaff020 & 0x00000fff)&0x800?(0xbfaff020 & 0x00000fff)-0x1000:(0xbfaff020 & 0x00000fff)
   lu12i.w $r5 , (((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r5, $r5, (0xbfaff040 & 0x00000fff)&0x800?(0xbfaff040 & 0x00000fff)-0x1000:(0xbfaff040 & 0x00000fff)
    lu12i.w $r6 , (((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r6, $r6, (0xbfaff030 & 0x00000fff)&0x800?(0xbfaff030 & 0x00000fff)-0x1000:(0xbfaff030 & 0x00000fff)

    lu12i.w $r13 , (((0x0002>>12)+((0x0002&0x00000800)>>11))&0x000fffff)&0x80000?(((0x0002>>12)+((0x0002&0x00000800)>>11))&0x000fffff)-0x100000:(((0x0002>>12)+((0x0002&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r13, $r13, (0x0002 & 0x00000fff)&0x800?(0x0002 & 0x00000fff)-0x1000:(0x0002 & 0x00000fff)
    ;;;

   st.w $r0, $r4, 0
    st.w $r13, $r5, 0
    st.w $r13, $r6, 0
    b 2f

1:
    lu12i.w $r13 , (((0x0001>>12)+((0x0001&0x00000800)>>11))&0x000fffff)&0x80000?(((0x0001>>12)+((0x0001&0x00000800)>>11))&0x000fffff)-0x100000:(((0x0001>>12)+((0x0001&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r13, $r13, (0x0001 & 0x00000fff)&0x800?(0x0001 & 0x00000fff)-0x1000:(0x0001 & 0x00000fff)
    lu12i.w $r4 , (((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff040>>12)+((0xbfaff040&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r4, $r4, (0xbfaff040 & 0x00000fff)&0x800?(0xbfaff040 & 0x00000fff)-0x1000:(0xbfaff040 & 0x00000fff)
   lu12i.w $r5 , (((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff030>>12)+((0xbfaff030&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r5, $r5, (0xbfaff030 & 0x00000fff)&0x800?(0xbfaff030 & 0x00000fff)-0x1000:(0xbfaff030 & 0x00000fff)
    ;;;
    st.w $r13, $r4, 0
    st.w $r13, $r5, 0

2:
 bl test_finish

idle_1s:
    lu12i.w $r12 , (((0xbfaff090>>12)+((0xbfaff090&0x00000800)>>11))&0x000fffff)&0x80000?(((0xbfaff090>>12)+((0xbfaff090&0x00000800)>>11))&0x000fffff)-0x100000:(((0xbfaff090>>12)+((0xbfaff090&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r12, $r12, (0xbfaff090 & 0x00000fff)&0x800?(0xbfaff090 & 0x00000fff)-0x1000:(0xbfaff090 & 0x00000fff)
    lu12i.w $r13 , (((0xaaaa>>12)+((0xaaaa&0x00000800)>>11))&0x000fffff)&0x80000?(((0xaaaa>>12)+((0xaaaa&0x00000800)>>11))&0x000fffff)-0x100000:(((0xaaaa>>12)+((0xaaaa&0x00000800)>>11))&0x000fffff); ;;;; addi.w $r13, $r13, (0xaaaa & 0x00000fff)&0x800?(0xaaaa & 0x00000fff)-0x1000:(0xaaaa & 0x00000fff)

    #initial $r15
    ld.w $r14, $r12, 0 #switch_interleave: {switch[7],1'b0, switch[6],1'b0...switch[0],1'b0}
    ;;;
    xor $r14, $r14, $r13
    ;;;
    slli.w $r15, $r14, 9 #$r15 = switch interleave << 9
    ;;;
    addi.w $r15, $r15, 1
    ;;;

sub1:
    addi.w $r15, $r15, -1

    #select min{$r15, switch_interleave}
    ld.w $r14, $r12, 0 #switch_interleave: {switch[7],1'b0, switch[6],1'b0...switch[0],1'b0}
    ;;;
    xor $r14, $r14, $r13
    ;;;
    slli.w $r14, $r14, 9 #switch interleave << 9
    ;;;
    sltu $r16, $r15, $r14
    ;;;
    bne $r16, $r0, 1f
    addi.w $r15, $r14, 0
    ;;;
1:
    bne $r15, $r0, sub1
    jirl $r0, $r1, 0

reg_init:
    addi.w $r2, $r0, 0
    addi.w $r3, $r0, 0
    addi.w $r4, $r0, 0
    addi.w $r5, $r0, 0
    addi.w $r6, $r0, 0
    addi.w $r7, $r0, 0
    addi.w $r8, $r0, 0
    addi.w $r9, $r0, 0
    addi.w $r10, $r0, 0
    addi.w $r11, $r0, 0
    addi.w $r12, $r0, 0
    addi.w $r13, $r0, 0
    addi.w $r14, $r0, 0
    addi.w $r15, $r0, 0
    addi.w $r16, $r0, 0
    addi.w $r17, $r0, 0
    addi.w $r18, $r0, 0
    addi.w $r19, $r0, 0
    addi.w $r20, $r0, 0
    addi.w $r21 , $r0, 0
    addi.w $r22, $r0, 0
    addi.w $r23, $r0, 0
    addi.w $r24, $r0, 0
    addi.w $r25, $r0, 0
    addi.w $r26, $r0, 0
    addi.w $r27, $r0, 0
    addi.w $r28, $r0, 0
    addi.w $r29, $r0, 0
    addi.w $r30, $r0, 0
    addi.w $r31, $r0, 0
    jirl $r0, $r1, 0
