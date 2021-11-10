#include "../local-include/intr.h"
#include "../local-include/csr.h"

def_EHelper(syscall) {
  printf("PC: 0x%x [DEBUG]: this is syscall\n",cpu.pc);
  rtl_li(s, s1, s->pc);
  rtl_hostcall(s, HOSTCALL_TRAP, s0, s1, NULL, EX_SYS);
  rtl_jr(s, s0);
}

def_EHelper(break) {
  printf("PC: 0x%x [DEBUG]: this is break\n",cpu.pc);  
  rtl_li(s, s1, s->pc);
  rtl_hostcall(s, HOSTCALL_TRAP, s0, s1, NULL, EX_BRK);
  rtl_jr(s, s0);  
}

def_EHelper(ertn) {
  printf("PC: 0x%x [DEBUG]: this is ertn\n",cpu.pc);  
  rtl_hostcall(s, HOSTCALL_PRIV, s0, NULL, NULL, PRIV_ERET);  
  if(LLBCTL->klo == 1){
    LLBCTL->klo = 0;
  }else{
    cpu.ll_bit = 0;
  }
  rtl_jr(s, s0); 
}

def_EHelper(idle) {
  // TODO: when intr comes, the next instr of IDLE while be marked, not IDLE itself
  printf("PC: 0x%x [DEBUG]: this is idle\n",cpu.pc);  
  cpu.inst_idle = 1;
  rtl_hostcall(s, HOSTCALL_PRIV, s0, NULL, NULL, PRIV_IDLE);  
  rtl_jr(s, s0); 
}