#include "../local-include/rtl.h"
#include "../local-include/intr.h"
#include "../local-include/csr.h"
#include <cpu/difftest.h>


/* do nothing for now.. just for pass compiler */


word_t raise_intr(uint32_t ecode, vaddr_t epc) {
  PRMD->pplv = CRMD->plv;
  PRMD->pie  = CRMD->ie;
  CRMD->plv  = 0;
  CRMD->ie   = 0;
  ESTAT->ecode = ecode;

  if(cpu.inst_idle){
    ERA->val = epc + 4;
    cpu.inst_idle = 0;
  }else{
    ERA->val = epc;
  }
  
  switch (ecode) {
    case EX_ADE:
    // case EX_ALE: ALE write mem addr in BADV, handled in ../instr/ldst.h
    case EX_PIL:
    case EX_PIS:
    case EX_PIF:
    case EX_PME:
    case EX_PPI: BADV->val=epc; break;
  }
  // TODO: ADD TLB INTR
  return EENTRY->val;
}

word_t isa_query_intr() {

  // TODO: TIMER AND HARD INTERUPT
  // if(cpu.INTR) 
  // ...

  word_t intvec = 0; // 0~12 bits
  if(CRMD->ie){
    intvec = ECFG->lie & ((ESTAT->is_2_12 << 2) | ESTAT->is_01);
    printf("PC: 0x%x [DEBUG]: intvec is 0x%x in isa_query_intr\n",cpu.pc,intvec);
    if(intvec != 0)
      return EX_INT;
    else
      return INTR_EMPTY;
  }else{
    return INTR_EMPTY;
  }

//   if (cpu.INTR && (cpu.status.ie) && !(cpu.status.exl)) {
//     cpu.INTR = false;
//     cpu.pc = raise_intr(0, cpu.pc);
//   }
  return INTR_EMPTY;
}

