#include <cpu/decode.h>
#include "../local-include/rtl.h"


#define INSTR_NULLARY(f) \
  f(inv) f(nemu_trap) f(print_led) f(ertn) 
#define INSTR_UNARY(f) \
  f(b) f(bl) f(syscall) f(break) f(idle) f(dbar) f(ibar)
#define INSTR_BINARY(f) \
  f(lu12i_w) f(pcaddu12i) \
  f(csrrd) f(csrwr)
  
#define INSTR_TERNARY(f) \
  f(add_w) f(addi_w) f(sub_w) f(slt) f(sltu) f(slti) f(sltui) f(xor) f(nor) f(and) f(or) \
  f(xori) f(ori) f(andi) f(mul_w) f(mulh_w) f(mulh_wu) f(div_w) f(div_wu) f(mod_w) f(mod_wu) \
  f(sll_w) f(srl_w) f(sra_w) f(slli_w) f(srli_w) f(srai_w) \
  f(beq) f(bne) f(blt) f(bge) f(bltu) f(bgeu) f(jirl) \
  f(preld) f(ld_b) f(ld_h) f(ld_w) f(ld_bu) f(ld_hu) f(st_b) f(st_h) f(st_w) \
  f(csrxchg) f(cacop) f(ll_w) f(sc_w)
def_all_EXEC_ID();

