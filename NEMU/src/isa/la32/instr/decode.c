#include "../local-include/rtl.h"
#include "../local-include/intr.h"
#include "../local-include/csr.h"
#include <cpu/ifetch.h>
#include <cpu/cpu.h>
#include <cpu/decode.h>
#include <isa-all-instr.h>

/* follow codes in isa/mips32/instr/decode.c */

def_all_THelper();


static inline uint32_t get_instr(Decode *s) {
  return s->isa.instr.val;
}

// decode operand helper
#define def_DopHelper(name) \
  void concat(decode_op_, name) (Decode *s, Operand *op, uint32_t val, bool flag)

static inline def_DopHelper(i) {
  op->imm = val;
  //printf("[debug]: get imm: %08x\n",op->imm);
  print_Dop(op->str, OP_STR_SIZE, (flag ? "0x%x" : "%d"), op->imm);
}

static inline def_DopHelper(r) {
  bool load_val = flag;
  static word_t zero_null = 0;
  op->preg = (!load_val && val == 0) ? &zero_null : &reg_l(val);
  print_Dop(op->str, OP_STR_SIZE, "%s", reg_name(val, 4));
}


static inline def_DHelper(r3) {
  decode_op_r(s, id_src1, s->isa.instr.r3.rj, true);
  decode_op_r(s, id_src2, s->isa.instr.r3.rk, true);
  decode_op_r(s, id_dest, s->isa.instr.r3.rd, false);
}

static inline def_DHelper(r2_i12) {
  decode_op_r(s, id_src1, s->isa.instr.r2_i12.rj, true);
  decode_op_i(s, id_src2, s->isa.instr.r2_i12.i12, false);
  decode_op_r(s, id_dest, s->isa.instr.r2_i12.rd, false);
}

static inline def_DHelper(r2_i12_u) {
  decode_op_r(s, id_src1, s->isa.instr.r2_i12.rj, true);
  decode_op_i(s, id_src2, ((s->isa.instr.r2_i12.i12) & (0x00000fff)), true);
  decode_op_r(s, id_dest, s->isa.instr.r2_i12.rd, false);
}

static inline def_DHelper(r1_i20) {
  decode_op_i(s, id_src1, s->isa.instr.r1_i20.i20 << 12, true);
  decode_op_r(s, id_dest, s->isa.instr.r1_i20.rd, false);
}

static inline def_DHelper(r2_i8) {
  decode_op_r(s, id_src1, s->isa.instr.r2_i8.rj, true);
  decode_op_i(s, id_src2, s->isa.instr.r2_i8.i5, true);
  decode_op_r(s, id_dest, s->isa.instr.r2_i8.rd, false);
}

static inline def_DHelper(r2_i14) {
  decode_op_i(s, id_src1, s->isa.instr.r2_i14.i14, true);
  decode_op_r(s, id_src2, s->isa.instr.r2_i14.rj, true);
  decode_op_r(s, id_dest, s->isa.instr.r2_i14.rd, true);
}

static inline def_DHelper(r2_i14s) {
  decode_op_i(s, id_src1, s->isa.instr.r2_i14s.i14, false);
  decode_op_r(s, id_src2, s->isa.instr.r2_i14s.rj, true);
  decode_op_r(s, id_dest, s->isa.instr.r2_i14s.rd, true);
}

static inline def_DHelper(r2_i16) {
  int32_t offset = (s->isa.instr.r2_i16.i16 << 2);
  decode_op_i(s, id_dest, s->pc + offset, true);
  decode_op_r(s, id_src1, s->isa.instr.r2_i16.rj, true);
  decode_op_r(s, id_src2, s->isa.instr.r2_i16.rd, true);
}

static inline def_DHelper(i_26) {
  int32_t offset = ((s->isa.instr.i_26.i26_25_16 << 16) | s->isa.instr.i_26.i26_15_0) << 2 ;
  decode_op_i(s, id_src1, s->pc + offset, true);
}

static inline def_DHelper(code_15) {
  decode_op_i(s, id_src1, s->isa.instr.code_15.code, true);
}

static inline def_DHelper(bl) {
  decode_i_26(s,width);
  decode_op_r(s, id_dest, (uint32_t)1, false);
  id_src2->imm = s->snpc;
}

static inline def_DHelper(pcaddu12i) {
  decode_r1_i20(s, width);
  id_src1->imm += s->pc;
}

static inline def_DHelper(jirl) {
  decode_op_r(s, id_src1, s->isa.instr.r2_i16.rj, true);
  decode_op_i(s, id_src2, s->isa.instr.r2_i16.i16 << 2, false);
  decode_op_r(s, id_dest, s->isa.instr.r2_i16.rd, false);
}

static inline def_DHelper(cacop) {
  decode_op_i(s, id_src1, s->isa.instr.r2_i12.rd, false);
  decode_op_i(s, id_src2, s->isa.instr.r2_i12.i12, false);
  decode_op_i(s, id_dest, s->isa.instr.r2_i12.rj, false);
}


/* use 'IDTAB' like codes written in isa/misp32 cannot pass compile
 * so i use 'def_INSTR_TAB' like codes in isa/riscv64
 */

/*
def_THelper(load) {
  print_Dop(id_src1->str, OP_STR_SIZE, "%ld(%s)", id_src2->imm, reg_name(s->isa.instr.i.rs1, 4));
  int mmu_mode = isa_mmu_state();
  if (mmu_mode == MMU_DIRECT) {
    def_INSTR_TAB("0010100000 ???????????? ????? ?????", ld_b);
    def_INSTR_TAB("0010100001 ???????????? ????? ?????", ld_h);
    def_INSTR_TAB("0010100010 ???????????? ????? ?????", ld_w);
    def_INSTR_TAB("0010101000 ???????????? ????? ?????", ld_bu);
    def_INSTR_TAB("0010101001 ???????????? ????? ?????", ld_hu);
  } else if (mmu_mode == MMU_TRANSLATE) {

  } else { assert(0); }
  return EXEC_ID_inv;
}

def_THelper(store) {
  print_Dop(id_src1->str, OP_STR_SIZE, "%ld(%s)", id_src2->imm, reg_name(s->isa.instr.i.rs1, 4));
  int mmu_mode = isa_mmu_state();
  if (mmu_mode == MMU_DIRECT) {
    def_INSTR_TAB("0010100100 ???????????? ????? ?????", st_b);
    def_INSTR_TAB("0010100101 ???????????? ????? ?????", st_h);
    def_INSTR_TAB("0010100110 ???????????? ????? ?????", st_w);
  } else if (mmu_mode == MMU_TRANSLATE) {

  } else { assert(0); }
  return EXEC_ID_inv;
}
*/


def_THelper(main) {

  def_INSTR_IDTAB("00000000000100000 ????? ????? ?????",r3, add_w);
  def_INSTR_IDTAB("00000000000100010 ????? ????? ?????",r3, sub_w);
  def_INSTR_IDTAB("00000000000100100 ????? ????? ?????",r3, slt);
  def_INSTR_IDTAB("00000000000100101 ????? ????? ?????",r3, sltu);
  def_INSTR_IDTAB("00000000000101000 ????? ????? ?????",r3, nor);
  def_INSTR_IDTAB("00000000000101001 ????? ????? ?????",r3, and);
  def_INSTR_IDTAB("00000000000101010 ????? ????? ?????",r3, or);
  def_INSTR_IDTAB("00000000000101011 ????? ????? ?????",r3, xor);  
  def_INSTR_IDTAB("00000000000111000 ????? ????? ?????",r3, mul_w);
  def_INSTR_IDTAB("00000000000111001 ????? ????? ?????",r3, mulh_w);
  def_INSTR_IDTAB("00000000000111010 ????? ????? ?????",r3, mulh_wu);   
  def_INSTR_IDTAB("00000000001000000 ????? ????? ?????",r3, div_w);
  def_INSTR_IDTAB("00000000001000010 ????? ????? ?????",r3, div_wu);   
  def_INSTR_IDTAB("00000000001000001 ????? ????? ?????",r3, mod_w);
  def_INSTR_IDTAB("00000000001000011 ????? ????? ?????",r3, mod_wu);  
  def_INSTR_IDTAB("00000000000101110 ????? ????? ?????",r3, sll_w);   
  def_INSTR_IDTAB("00000000000101111 ????? ????? ?????",r3, srl_w);
  def_INSTR_IDTAB("00000000000110000 ????? ????? ?????",r3, sra_w);    

  def_INSTR_IDTAB("0001010 ???????????????????? ?????",r1_i20, lu12i_w);
  def_INSTR_IDTAB("0001110 ???????????????????? ?????",pcaddu12i, pcaddu12i);

  def_INSTR_IDTAB("0000001010 ???????????? ????? ?????",r2_i12, addi_w);
  def_INSTR_IDTAB("0000001000 ???????????? ????? ?????",r2_i12, slti);
  def_INSTR_IDTAB("0000001001 ???????????? ????? ?????",r2_i12, sltui);

  def_INSTR_IDTAB("0000011000 ???????????? ????? ?????",cacop, cacop);

  def_INSTR_IDTAB("0010100000 ???????????? ????? ?????",r2_i12, ld_b);
  def_INSTR_IDTAB("0010100001 ???????????? ????? ?????",r2_i12, ld_h);
  def_INSTR_IDTAB("0010100010 ???????????? ????? ?????",r2_i12, ld_w);
  def_INSTR_IDTAB("0010101000 ???????????? ????? ?????",r2_i12, ld_bu);
  def_INSTR_IDTAB("0010101001 ???????????? ????? ?????",r2_i12, ld_hu);
  def_INSTR_IDTAB("0010100100 ???????????? ????? ?????",r2_i12, st_b);
  def_INSTR_IDTAB("0010100101 ???????????? ????? ?????",r2_i12, st_h);
  def_INSTR_IDTAB("0010100110 ???????????? ????? ?????",r2_i12, st_w);
  def_INSTR_IDTAB("0010101011 ???????????? ????? ?????",r2_i12, preld);

  def_INSTR_IDTAB("0000001101 ???????????? ????? ?????",r2_i12_u, andi);
  def_INSTR_IDTAB("0000001110 ???????????? ????? ?????",r2_i12_u, ori);
  def_INSTR_IDTAB("0000001111 ???????????? ????? ?????",r2_i12_u, xori);  
  
  def_INSTR_IDTAB("00000000010000001 ????? ????? ?????",r2_i8, slli_w);
  def_INSTR_IDTAB("00000000010001001 ????? ????? ?????",r2_i8, srli_w);
  def_INSTR_IDTAB("00000000010010001 ????? ????? ?????",r2_i8, srai_w);

  def_INSTR_IDTAB("010110 ???????????????? ????? ?????",r2_i16, beq);
  def_INSTR_IDTAB("010111 ???????????????? ????? ?????",r2_i16, bne);
  def_INSTR_IDTAB("011000 ???????????????? ????? ?????",r2_i16, blt);  
  def_INSTR_IDTAB("011001 ???????????????? ????? ?????",r2_i16, bge);
  def_INSTR_IDTAB("011010 ???????????????? ????? ?????",r2_i16, bltu);
  def_INSTR_IDTAB("011011 ???????????????? ????? ?????",r2_i16, bgeu);

  def_INSTR_IDTAB("010011 ???????????????? ????? ?????",jirl, jirl);

  def_INSTR_IDTAB("010100 ???????????????? ??????????",i_26, b);
  def_INSTR_IDTAB("010101 ???????????????? ??????????",bl, bl);  

  def_INSTR_IDTAB("00000100 ?????????????? 00000 ?????",r2_i14, csrrd);
  def_INSTR_IDTAB("00000100 ?????????????? 00001 ?????",r2_i14, csrwr);
  def_INSTR_IDTAB("00000100 ?????????????? ????? ?????",r2_i14, csrxchg);

  def_INSTR_IDTAB("00100000 ?????????????? ????? ?????",r2_i14s, ll_w);
  def_INSTR_IDTAB("00100001 ?????????????? ????? ?????",r2_i14s, sc_w);
  
  def_INSTR_IDTAB("00000000001010110 ???????????????",code_15, syscall);
  def_INSTR_IDTAB("00000000001010100 ???????????????",code_15, break);
  def_INSTR_IDTAB("00000110010010001 ???????????????",code_15, idle);
  def_INSTR_TAB("00000110010010000011100000000000",ertn);

  def_INSTR_TAB("00111000011100100???????????????",ibar);
  def_INSTR_TAB("00111000011100101???????????????",dbar);

  def_INSTR_TAB("10000000000000000000000000000000",nemu_trap);
  def_INSTR_TAB("11000000000000000000000000000000",print_led);
  

  return table_inv(s);
}


int isa_fetch_decode(Decode *s) {
  //printf("[DEBUG]: current cpu.pc = 0x%x in isa_fetch_decode\n",cpu.pc);
  //printf("[DEBUG]: current s->pc = 0x%x in isa_fetch_decode\n",s->pc);

  if(cpu.pc & ((vaddr_t)0x3)){
    printf("PC: 0x%x [DEBUG]: inst fetch, PC = 0x%x, not 4 aligned\n", cpu.pc, cpu.pc);
    longjmp_exception(EX_ALE); 
  }
  if((CRMD->plv == 0x3) && (cpu.pc & ((vaddr_t)0x80000000))){ 
    printf("PC: 0x%x [DEBUG]: current PC = 0x%x, user visited high half\n",cpu.pc,cpu.pc);
    longjmp_exception(EX_ADE); 
  } 


  s->isa.instr.val = instr_fetch(&s->snpc, 4);
  int idx = table_main(s);

  s->type = INSTR_TYPE_N;

  return idx;
}
