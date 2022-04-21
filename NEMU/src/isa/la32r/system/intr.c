#include "../local-include/rtl.h"
#include "../local-include/intr.h"
#include "../local-include/csr.h"
#include <cpu/difftest.h>


word_t raise_intr(uint32_t ecode, vaddr_t epc) {
  PRMD->pplv = CRMD->plv;
  PRMD->pie  = CRMD->ie;
  CRMD->plv  = 0;
  CRMD->ie   = 0;
  ESTAT->ecode = ecode;
  if(ecode != EX_ADE){
    ESTAT->esubcode = 0;
  }

  if(cpu.inst_idle){
    ERA->val = epc + 4;
    cpu.inst_idle = 0;
  }else{
    ERA->val = epc;
  }
  
  //BAV is set before call raise_intr

  if(ecode == EX_TLBR){
    CRMD->da = 1;
    CRMD->pg = 0;
    return TLBRENTRY->val;
  }else{
    return EENTRY->val;
  }
}

word_t isa_query_intr() {
  word_t intvec = 0; // 0~12 bits
  if(CRMD->ie){
    intvec = ECFG->lie & ((ESTAT->is_2_12 << 2) | ESTAT->is_01);
    if(intvec != 0)
      return EX_INT;
    else
      return INTR_EMPTY;
  }else{
    return INTR_EMPTY;
  }
  return INTR_EMPTY;
}

