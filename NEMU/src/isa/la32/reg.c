#include <isa.h>
#include "local-include/reg.h"

/* copy from isa/mips32 */

const char *regsl[] = {
  "r0", "ra", "tp", "sp", "a0", "a1", "a2", "a3",
  "a4", "a5", "a6", "a7", "t0", "t1", "t2", "t3",
  "t4", "t5", "t6", "t7", "t8", " x", "fp", "s0",
  "s1", "s2", "s3", "s4", "s5", "s6", "s7", "s8"
};

void isa_reg_display() {
  int i;
  for (i = 0; i < 32; i ++) {
    printf("%s(r%2d): 0x%08x ", regsl[i], i, cpu.gpr[i]._32);
    if (i % 4 == 3) printf("\n");
  }
  printf("pc: 0x%08x\n", cpu.pc);
  printf("CRMD: 0x%08x,    PRMD: 0x%08x,   EUEN: 0x%08x\n", csr_array[0], csr_array[1], csr_array[2]);
  printf("ECFG: 0x%08x,   ESTAT: 0x%08x,    ERA: 0x%08x\n", csr_array[4], csr_array[5], csr_array[6]);  
  printf("BADV: 0x%08x,  EENTRY: 0x%08x, LLBCTL: 0x%08x\n", csr_array[7], csr_array[12], csr_array[96]);    
  printf("cpu.ll_bit: %d\n",cpu.ll_bit);
}

word_t isa_reg_str2val(const char *s, bool *success) {
  int i;
  *success = true;
  for (i = 0; i < 32; i ++) {
    if (strcmp(regsl[i], s) == 0) return reg_l(i);
  }

  if (strcmp("pc", s) == 0) return cpu.pc;

  *success = false;
  return 0;
}
