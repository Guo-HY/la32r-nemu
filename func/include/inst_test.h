// file name: inst_test.h
#include "cpu_cde.h"

#define TEST_LU12I_W(in_a, ref_base) \
    lu12i.w   a0, ref_base&0x80000?ref_base-0x100000:ref_base; \
    lu12i.w   t0, in_a&0x80000?in_a-0x100000:in_a;  \
    NOP4; \
    add.w  a0, a0, t1; \
    add.w  t1, t1, t2; \
    NOP4; \
    bne   t0, a0, inst_error

/* 2 */
#define TEST_ADD_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    add.w v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error

/* 3 */
#define TEST_ADDI_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    NOP4; \
    addi.w v0, t0, in_b&0x800?in_b-0x1000:in_b; \
    NOP4; \
    bne   v0, v1, inst_error

/* 4 */
#define TEST_BEQ(in_a, in_b, back_flag, front_flag, b_flag_ref, f_flag_ref) \
    LI (t4, back_flag); \
    LI (t5, front_flag); \
    lu12i.w v0, 0x0; \
    lu12i.w v1, 0x0; \
    b 2000f; \
    nop; \
1000:; \
    LI (v0, back_flag); \
    beq t1, t0, 3000f; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
2000:; \
    LI (t0, in_a); \
    LI (t1, in_b); \
    NOP4; \
    beq t0, t1, 1000b; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
3000:; \
    LI (v1, front_flag); \
4000:; \
    LI (s5, b_flag_ref); \
    LI (s6, f_flag_ref); \
    NOP4 ; \
    bne v0, s5, inst_error; \
    nop; \
    bne v1, s6, inst_error; \
    nop

/* 5 */
#define TEST_BNE(in_a, in_b, back_flag, front_flag, b_flag_ref, f_flag_ref) \
    LI (t4, back_flag); \
    LI (t5, front_flag); \
    lu12i.w v0, 0x0; \
    lu12i.w v1, 0x0; \
    b 2000f; \
    nop; \
1000:; \
    LI (v0, back_flag); \
    bne t1, t0, 3000f; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
2000:; \
    LI (t0, in_a); \
    LI (t1, in_b); \
    NOP4; \
    bne t0, t1, 1000b; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
3000:; \
    LI (v1, front_flag); \
4000:; \
    LI (s5, b_flag_ref); \
    LI (s6, f_flag_ref); \
    NOP4 ; \
    bne v0, s5, inst_error; \
    nop; \
    bne v1, s6, inst_error; \
    nop

/* 6 */
#define TEST_LD_W(data, base_addr, offset, offset_align, ref) \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (v1, ref); \
    st.w t1, t0, offset_align; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -8; \
    NOP4; \
    st.w a0, a0, offset_align; \
    st.w a1, a1, offset_align; \
    ld.w v0, t0, offset; \
    ld.w a2, a0, offset_align; \
    ld.w a0, a1, offset_align; \
    ld.w a2, a1, offset_align; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 7 */
#define TEST_OR(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    or v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 8 */
#define TEST_SLT(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    slt v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 11 */
#define TEST_SLLI_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    NOP4; \
    slli.w v0, t0, in_b; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 12 */
#define TEST_ST_W(data, base_addr, offset, offset_align, ref) \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (v1, ref); \
    st.w t1, t0, offset; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -4; \
    NOP4; \
    st.w a0, a0, offset; \
    st.w a1, a1, offset; \
    ld.w v0, t0, offset_align; \
    ld.w a2, a0, offset; \
    ld.w a0, a1, offset; \
    ld.w a2, a1, offset; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 14 */
#define TEST_BL(back_flag, front_flag, b_flag_ref, f_flag_ref) \
    add.w s7, zero, $r1; \
    LI (t4, back_flag); \
    LI (t5, front_flag); \
    lu12i.w v0, 0x0; \
    lu12i.w v1, 0x0; \
    bl 2000f; \
    nop; \
1000:; \
    NOP4; \
    add.w a1, ra, zero; \
    LI (v0, back_flag); \
1001:; \
    bl 3000f; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
2000:; \
    nop; \
    nop; \
    nop; \
    nop; \
    add.w a0, ra, zero; \
    bl 1000b; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
3000:; \
    NOP4; \
    add.w a2, ra, zero; \
    LI (v1, front_flag); \
4000:; \
    NOP4; \
    add.w $r1, zero, s7; \
    LI (t5, b_flag_ref); \
    LI (t4, f_flag_ref); \
    bne v0, t5, inst_error; \
    nop; \
    addi.w a2, a2, 3*4; \
    bne v1, t4, inst_error; \
    nop; \
    NOP4; \
    bne a2, a1, inst_error; \
    nop

/* --------------------- */
#define TEST_B(back_flag, front_flag, b_flag_ref, f_flag_ref) \
    LI (t4, back_flag); \
    LI (t5, front_flag); \
    lu12i.w v0, 0x0; \
    lu12i.w v1, 0x0; \
    b 2000f; \
    nop; \
1000:; \
    NOP4; \
    LI (v0, back_flag); \
1001:; \
    b 3000f; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
2000:; \
    nop; \
    nop; \
    nop; \
    nop; \
    b 1000b; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
3000:; \
    NOP4; \
    LI (v1, front_flag); \
4000:; \
    NOP4; \
    LI (t5, b_flag_ref); \
    LI (t4, f_flag_ref); \
    bne v0, t5, inst_error; \
    nop; \
    nop; \
    bne v1, t4, inst_error; \
    nop
  

/* 15 */
#define TEST_JIRL(back_flag, front_flag, b_flag_ref, f_flag_ref) \
    add.w s7, zero, $r1; \
    LI (t4, back_flag); \
    LI (t5, front_flag); \
    lu12i.w v0, 0x0; \
    lu12i.w v1, 0x0; \
    bl 1f; \
    nop;    \
1:  ;       \
    nop;    \
    nop;    \
    nop;    \
    addi.w t0, $r1, 3*4; \
    addi.w t1, $r1, 9*4; \
    b 2000f; \
    nop; \
1000:; \
    LI (v0, back_flag); \
    jirl zero, t1, 0; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
2000:; \
    jirl zero, t0, 0; \
    nop; \
    b 4000f; \
    nop; \
    nop; \
3000:; \
    LI (v1, front_flag); \
4000:; \
    LI (s5, b_flag_ref); \
    LI (s6, f_flag_ref); \
    add.w $r1, zero, s7; \
    bne v0, s5, inst_error; \
    nop; \
    bne v1, s6, inst_error; \
    nop

/* 16 */
#define TEST_BEQ_DS(op, dest, ...) \
    addiu s5, zero, 0x1; \
    NOP4; \
    beq s5, zero, 1000f; \
    op  dest , ##__VA_ARGS__; \
    op  s6 , ##__VA_ARGS__; \
    NOP4; \
    bne dest, s6, inst_error; \
    nop; \
    beq s5, s5, 2000f; \
    op  s7 , ##__VA_ARGS__; \
1000: ; \
    b   inst_error; \
    nop;            \
2000: ; \
    NOP4; \
    bne s7, s6, inst_error; \
    nop

/* 17 */
#define TEST_BNE_DS(op, dest, ...) \
    addiu s5, zero, 0x1; \
    NOP4; \
    bne s5, s5, 1000f; \
    op  dest, ##__VA_ARGS__; \
    op  s6, ##__VA_ARGS__; \
    NOP4; \
    bne dest, s6, inst_error; \
    nop; \
    bne s5, zero, 2000f; \
    op  s7, ##__VA_ARGS__; \
1000: ; \
    b   inst_error; \
    nop;            \
2000: ; \
    NOP4; \
    bne s7, s6, inst_error; \
    nop

/* 19 */
#define TEST_JAL_DS(op, dest, ...) \
    addu s7, zero, $31; \
    op  s6, ##__VA_ARGS__; \
    jal 2000f; \
    op  dest, ##__VA_ARGS__; \
1000: ; \
    b   inst_error; \
    nop;            \
2000: ; \
    NOP4; \
    addu $31, zero, s7; \
    bne dest, s6, inst_error; \
    NOP4

/* 20 */
#define TEST_JR_DS(op, dest, ...) \
    addu s7, zero, $31; \
    jal 1f; \
    nop;    \
1:  ;       \
    nop;    \
    nop;    \
    nop;    \
    addiu  s5, $31, 12*4; \
    NOP4; \
    op  s6, ##__VA_ARGS__; \
    jr  s5; \
    op  dest, ##__VA_ARGS__; \
1000: ; \
    b   inst_error; \
    nop;            \
2000: ; \
    NOP4; \
    addu $31, zero, s7; \
    bne dest, s6, inst_error; \
    NOP4

/* 24 */
#define TEST_SUB_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    sub.w v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 25 */
#define TEST_SLTU(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    sltu v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 26 */
#define TEST_AND(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    and v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 28 */
#define TEST_NOR(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    nor v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 30 */
#define TEST_XOR(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    xor v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 33 */
#define TEST_SRAI_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    NOP4; \
    srai.w v0, t0, in_b; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

/* 35 */
#define TEST_SRLI_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    NOP4; \
    srli.w v0, t0, in_b; \
    NOP4; \
    bne v0, v1, inst_error; \
    nop

#define TEST_PCADDI(data) \
    add.w   t3, zero, ra;\
    lu12i.w t0, data&0x80000?data-0x100000:data;   \
    srai.w  t0, t0, 10;     \
    bl 1f;              \
    pcaddi  t1, data&0x80000?data-0x100000:data;   \
    b  2f;              \
  1:;  \
    add.w   t0, ra, t0; \
    jirl zero, ra, 0;   \
  2:;  \
    add.w   ra, zero, t3;\
    bne  t1, t0, inst_error 

#define TEST_PCADDU12I(data) \
    add.w   t3, zero, ra;\
    lu12i.w t0, data&0x80000?data-0x100000:data;   \
    bl 1f;              \
    pcaddu12i  t1, data&0x80000?data-0x100000:data;   \
    b  2f;              \
  1:;  \
    add.w   t0, ra, t0; \
    jirl    zero, ra, 0;   \
  2:;  \
    add.w   ra, zero, t3;\
    bne  t1, t0, inst_error 


#define TEST_ANDN(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    andn v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error

#define TEST_ORN(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    NOP4; \
    orn v0, t0, t1; \
    NOP4; \
    bne v0, v1, inst_error 

#define TEST_SLTI(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    slti v0, t0, in_b&0x800?in_b-0x1000:in_b; \
    bne v0, v1, inst_error


#define TEST_SLTUI(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    sltui v0, t0, in_b&0x800?in_b-0x1000:in_b; \
    bne v0, v1, inst_error

#define TEST_ANDI(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    andi v0, t0, in_b; \
    bne v0, v1, inst_error

#define TEST_ORI(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    ori v0, t0, in_b; \
    bne v0, v1, inst_error 

#define TEST_XORI(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (v1, ref); \
    xori v0, t0, in_b; \
    bne v0, v1, inst_error 

#define TEST_SLL_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    sll.w v0, t0, t1; \
    bne v0, v1, inst_error

#define TEST_SRA_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    sra.w v0, t0, t1; \
    bne v0, v1, inst_error

#define TEST_SRL_W(in_a, in_b, ref) \
    LI (t0, in_a); \
    LI (t1, in_b); \
    LI (v1, ref); \
    srl.w v0, t0, t1; \
    bne v0, v1, inst_error

#define TEST_DIV_W(in_a, in_b, ref) \
    li t0, in_a; \
    li t1, in_b; \
    div.w t3, t0, t1; \
    li t4, ref; \
    bne t4, t3, inst_error 

#define TEST_DIV_WU(in_a, in_b, ref) \
    li t0, in_a; \
    li t1, in_b; \
    div.wu t3, t0, t1; \
    li t4, ref; \
    bne t4, t3, inst_error  

#define TEST_MUL_W(in_a, in_b, ref) \
    li t0, in_a; \
    li t1, in_b; \
    mul.w t3, t0, t1; \
    li t4, ref; \
    bne t3, t4, inst_error 

#define TEST_MULH_W(in_a, in_b, ref) \
    li t0, in_a; \
    li t1, in_b; \
    mulh.w t3, t0, t1; \
    li t4, ref; \
    bne t3, t4, inst_error  

#define TEST_MULH_WU(in_a, in_b, ref) \
    li t0, in_a; \
    li t1, in_b; \
    mulh.wu t3, t0, t1; \
    li t4, ref; \
    bne t3, t4, inst_error  

#define TEST_MOD_W(in_a, in_b, ref) \
    li t0, in_a; \
    li t1, in_b; \
    mod.w t3, t0, t1; \
    li t4, ref; \
    bne t4, t3, inst_error 

#define TEST_MOD_WU(in_a, in_b, ref) \
    li t0, in_a; \
    li t1, in_b; \
    mod.wu t3, t0, t1; \
    li t4, ref; \
    bne t4, t3, inst_error 

#define TEST_BLT(in_a, in_b, back_flag, front_flag, b_flag_ref, f_flag_ref) \
    li t3, 0x0; \
    li t4, 0x0; \
    b 2000f; \
1000:; \
    li t3, back_flag; \
    blt t0, t1, 3000f; \
    b 4000f; \
2000:; \
    li t0, in_a; \
    li t1, in_b; \
    blt t0, t1, 1000b; \
    b 4000f; \
3000:; \
    li t4, front_flag; \
4000:; \
    li s5, b_flag_ref; \
    li s6, f_flag_ref; \
    bne t3, s5, inst_error; \
    bne t4, s6, inst_error

#define TEST_BGE(in_a, in_b, back_flag, front_flag, b_flag_ref, f_flag_ref) \
    li t3, 0x0; \
    li t4, 0x0; \
    b 2000f; \
1000:; \
    li t3, back_flag; \
    bge t0, t1, 3000f; \
    b 4000f; \
2000:; \
    li t0, in_a; \
    li t1, in_b; \
    bge t0, t1, 1000b; \
    b 4000f; \
3000:; \
    li t4, front_flag; \
4000:; \
    li s5, b_flag_ref; \
    li s6, f_flag_ref; \
    bne t3, s5, inst_error; \
    bne t4, s6, inst_error 

#define TEST_BLTU(in_a, in_b, back_flag, front_flag, b_flag_ref, f_flag_ref) \
    li t3, 0x0; \
    li t4, 0x0; \
    b 2000f; \
1000:; \
    li t3, back_flag; \
    bltu t0, t1, 3000f; \
    b 4000f; \
2000:; \
    li t0, in_a; \
    li t1, in_b; \
    bltu t0, t1, 1000b; \
    b 4000f; \
3000:; \
    li t4, front_flag; \
4000:; \
    li s5, b_flag_ref; \
    li s6, f_flag_ref; \
    bne t3, s5, inst_error; \
    bne t4, s6, inst_error 

#define TEST_BGEU(in_a, in_b, back_flag, front_flag, b_flag_ref, f_flag_ref) \
    li t3, 0x0; \
    li t4, 0x0; \
    b 2000f; \
1000:; \
    li t3, back_flag; \
    bgeu t0, t1, 3000f; \
    b 4000f; \
2000:; \
    li t0, in_a; \
    li t1, in_b; \
    bgeu t0, t1, 1000b; \
    b 4000f; \
3000:; \
    li t4, front_flag; \
4000:; \
    li s5, b_flag_ref; \
    li s6, f_flag_ref; \
    bne t3, s5, inst_error; \
    bne t4, s6, inst_error 

#define TEST_LD_B(data, base_addr, offset, offset_align, ref) \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (t3, ref); \
    st.w t1, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -8; \
    st.w a0, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.w a1, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.b t4, t0, offset&0x800?offset-0x1000:offset; \
    ld.w a1, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a0, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a2, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    bne t3, t4, inst_error  

#define TEST_LD_BU(data, base_addr, offset, offset_align, ref) \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (t3, ref); \
    st.w t1, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -8; \
    st.w a0, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.w a1, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.bu t4, t0, offset&0x800?offset-0x1000:offset; \
    ld.w a1, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a0, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a2, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    bne t3, t4, inst_error 

#define TEST_LD_H(data, base_addr, offset, offset_align, ref) \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (t3, ref); \
    st.w t1, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -8; \
    st.w a0, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.w a1, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.h t4, t0, offset&0x800?offset-0x1000:offset; \
    ld.w a1, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a0, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a2, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    bne t3, t4, inst_error 

#define TEST_LD_HU(data, base_addr, offset, offset_align, ref) \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (t3, ref); \
    st.w t1, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -8; \
    st.w a0, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.w a1, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.hu t4, t0, offset&0x800?offset-0x1000:offset; \
    ld.w a1, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a0, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a2, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    bne t3, t4, inst_error  

#define TEST_ST_B(init_data, data, base_addr, offset, offset_align, ref) \
    LI (t2, init_data); \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (t3, ref); \
    st.w t2, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.b t1, t0, offset&0x800?offset-0x1000:offset; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -4; \
    st.w a0, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.w a1, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w t4, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a0, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a1, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a2, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    bne t3, t4, inst_error  

#define TEST_ST_H(init_data, data, base_addr, offset, offset_align, ref) \
    LI (t2, init_data); \
    LI (t1, data); \
    LI (t0, base_addr); \
    LI (t3, ref); \
    st.w t2, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.h t1, t0, offset&0x800?offset-0x1000:offset; \
    addi.w a0, t0, 4; \
    addi.w a1, t0, -4; \
    st.w a0, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    st.w a1, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w t4, t0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a0, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a1, a0, offset_align&0x800?offset_align-0x1000:offset_align; \
    ld.w a2, a1, offset_align&0x800?offset_align-0x1000:offset_align; \
    bne t3, t4, inst_error  

#define TEST_INE_EX(inst) \
    .word inst

#define TEST_TI_EX(time_val) \
    li      t0, 0x4;    \
    li      t1, 0x4;    \
    csrxchg t0, t1, csr_crmd;  \
    li      t0, 0x1fff; \
    csrwr   t0, csr_ectl; \
    li      t0, time_val; \
    ori     t0, t0, 0x1;  \
    csrwr   t0, csr_tcfg; \
1:;                       \
    b 1b;                 \
    csrwr   zero, csr_tcfg

#define TEST_TI_EX_CYC(time_val) \
    li      t0, 0x4;    \
    li      t1, 0x4;    \
    csrxchg t0, t1, csr_crmd;  \
    li      t0, 0x1fff; \
    csrwr   t0, csr_ectl; \
    li      t0, time_val; \
    ori     t0, t0, 0x3;  \
    csrwr   t0, csr_tcfg; \
1:;                       \
    b 1b;                 \
    la.local s4, 2f;      \
2:;                       \
    b 2b;                 \
    csrwr   zero, csr_tcfg 

#define TEST_TI_EX_WAIT(time_val) \
    li      t0, 0x4;    \
    li      t1, 0x4;    \
    csrxchg t0, t1, csr_crmd;  \
    li      t0, 0x1fff; \
    csrwr   t0, csr_ectl; \
    li      t0, time_val; \
    ori     t0, t0, 0x1;  \
    csrwr   t0, csr_tcfg; \
1:;                       \
    idle    0;            \
    csrwr   zero, csr_tcfg 

#define TEST_SOFT_INT_EX(estat_val) \
    li      t0, 0x4;    \
    li      t1, 0x4;    \
    csrxchg t0, t1, csr_crmd;  \
    li      t0, 0x1fff; \
    csrwr   t0, csr_ectl; \
    li      t0, estat_val; \
    csrwr   t0, csr_estat; \
1:                         \
    b 1b                  

#define TEST_ADEF(addr) \
    li      s4, addr;   \
    li      a3, addr;   \
    li      s6, addr 

#define TEST_LD_W_ALE(data, base_addr, offset, offset_align, ref) \
    li      t2, ref;    \
    li      t3, ref;    \
    li      a0, base_addr; \
    li      a1, data;   \
    addi.w  a3, a0, offset; \
    st.w    a1, a0, offset_align 

#define TEST_LD_H_ALE(data, base_addr, offset, offset_align, ref) \
    li      t2, ref;    \
    li      t3, ref;    \
    li      a0, base_addr; \
    li      a1, data;   \
    addi.w  a3, a0, offset; \
    st.w    a1, a0, offset_align 

#define TEST_LD_HU_ALE(data, base_addr, offset, offset_align, ref) \
    li      t2, ref;    \
    li      t3, ref;    \
    li      a0, base_addr; \
    li      a1, data;   \
    addi.w  a3, a0, offset; \
    st.w    a1, a0, offset_align  

#define TEST_ST_H_ALE(data, base_addr, offset, offset_align, ref) \
    li      t2, ref;    \
    li      t3, ref;    \
    li      a0, base_addr; \
    li      a1, data;   \
    addi.w  a3, a0, offset; \
    st.w    t2, a0, offset_align 

#define TEST_ST_W_ALE(data, base_addr, offset, offset_align, ref) \
    li      t2, ref;    \
    li      t3, ref;    \
    li      a0, base_addr; \
    li      a1, data;   \
    addi.w  a3, a0, offset; \
    st.w    t2, a0, offset_align 
