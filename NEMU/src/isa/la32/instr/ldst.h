#include "../local-include/intr.h"
#include "../local-include/csr.h"


#define def_ldst_template(name, rtl_instr, width, mmu_mode) \
  def_EHelper(name) { \
    vaddr_t addr = *dsrc1 + id_src2->imm; \
    if(width == 4){ \
      if(addr & ((vaddr_t)0x3)){ \
        printf("PC: 0x%x [DEBUG]: current mem addr = 0x%x not %d aligned\n",cpu.pc,addr,width);\
        BADV->val = addr; \
        longjmp_exception(EX_ALE); \
      } \
    } \
    else if(width == 2){ \
      if(addr & ((vaddr_t)0x1)){ \
        printf("PC: 0x%x [DEBUG]: current mem addr = 0x%x not %d aligned\n",cpu.pc,addr,width);\
        BADV->val = addr; \
        longjmp_exception(EX_ALE); \
      } \
    } \
    concat(rtl_, rtl_instr) (s, ddest, dsrc1, id_src2->imm, width, mmu_mode); \
  }

#define def_all_ldst(suffix, mmu_mode) \
  def_ldst_template(concat(ld_w , suffix), lms, 4, mmu_mode) \
  def_ldst_template(concat(ld_h , suffix), lms, 2, mmu_mode) \
  def_ldst_template(concat(ld_b , suffix), lms, 1, mmu_mode) \
  def_ldst_template(concat(ld_hu, suffix), lm , 2, mmu_mode) \
  def_ldst_template(concat(ld_bu, suffix), lm , 1, mmu_mode) \
  def_ldst_template(concat(st_w , suffix), sm , 4, mmu_mode) \
  def_ldst_template(concat(st_h , suffix), sm , 2, mmu_mode) \
  def_ldst_template(concat(st_b , suffix), sm , 1, mmu_mode)

def_all_ldst(, isa_mmu_state())


def_EHelper(ll_w) { 
    vaddr_t addr = *dsrc2 + (id_src1->imm << 2); 
    printf("PC: 0x%x [DEBUG]: this is ll_w, mem addr 0x%x\n", cpu.pc, addr);
    if(addr & ((vaddr_t)0x3)){ 
      printf("PC: 0x%x [DEBUG]: current mem addr = 0x%x not 4 aligned\n",cpu.pc,addr);
      BADV->val = addr; 
      longjmp_exception(EX_ALE); 
    } 
    
    rtl_lms(s, ddest, dsrc2, (id_src1->imm << 2), 4, MMU_DIRECT); 
    cpu.ll_bit = 1;
}

def_EHelper(sc_w) { 
    vaddr_t addr = *dsrc2 + (id_src1->imm << 2); 
    printf("PC: 0x%x [DEBUG]: this is sc_w, mem addr 0x%x\n", cpu.pc, addr);
    if(addr & ((vaddr_t)0x3)){ 
      printf("PC: 0x%x [DEBUG]: current mem addr = 0x%x not 4 aligned\n",cpu.pc,addr);
      BADV->val = addr; 
      longjmp_exception(EX_ALE); 
    } 

    if(cpu.ll_bit == 1){
      rtl_sm(s, ddest, dsrc2, (id_src1->imm << 2), 4, MMU_DIRECT);
      rtl_mv(s, ddest, &(cpu.ll_bit));
      cpu.ll_bit = 0;
    }else{
      rtl_mv(s, ddest, &(cpu.ll_bit));
    }
}

