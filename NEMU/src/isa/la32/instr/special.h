#include "../local-include/intr.h"
#include "../local-include/csr.h"

def_EHelper(nemu_trap) {
  save_globals(s);
  rtl_hostcall(s, HOSTCALL_EXIT, NULL, &cpu.gpr[4]._32, NULL, 0); // gpr[4] is $v0
  longjmp_exec(NEMU_EXEC_END);
}

def_EHelper(print_led) {
  printf("####  current result: 0x%08x  ####\n", cpu.gpr[12]._32);
}

def_EHelper(inv) {
  // save_globals(s);
  // rtl_hostcall(s, HOSTCALL_INV, NULL, NULL, NULL, 0);
  // longjmp_exec(NEMU_EXEC_END);
  
  /* FOR RUN FUNC, INVALID INST IS AN EXCEPTION NEED TO HANDLE */
  printf("PC: 0x%x [NEMU]: INVALID INST\n",s->pc);  
  printf("[NEMU]: INVALID INST CODE : 0x %x\n",s->isa.instr.val);
  rtl_li(s, s1, s->pc);
  rtl_hostcall(s, HOSTCALL_TRAP, s0, s1, NULL, EX_INE);
  rtl_jr(s, s0);  

}

// below are some inst that did not implement

def_EHelper(preld) { 
  // printf("this is PERLD instruction\n"); 
  //printf("PRELD do nothing in NEMU\n"); 
}

def_EHelper(ibar) { 
  //printf("this is IBAR instruction\n"); 
  //printf("IBAR do nothing in NEMU\n"); 
}

def_EHelper(dbar) { 
  // printf("this is DBAR instruction\n"); 
  //printf("DBAR do nothing in NEMU\n"); 
}

def_EHelper(cacop) { 
    if((id_src1->imm) & (0x10)){
        printf("PC: 0x%x [NEMU]: this is CACOP HIT inst.\n",cpu.pc);
        vaddr_t addr = *ddest + id_src2->simm ;
        isa_mmu_translate(addr, 4,MEM_TYPE_READ);
    }

    if(CRMD->plv == 0x3){
      if((id_src1->imm) & (0x10)){
        //printf("PC: 0x%x [DEBUG]: this is CACOP HIT inst.\n",cpu.pc);
      }else{
        printf("PC: 0x%x [NEMU]: this is CACOP inst but plv is %d, exception.\n",cpu.pc,CRMD->plv);
        longjmp_exception(EX_IPE);
      }
    }
    printf("this is CACOP instruction\n"); 
}
