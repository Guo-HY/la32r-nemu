#define def_ldst_template(name, rtl_instr, width, mmu_mode) \
  def_EHelper(name) { \
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

def_all_ldst(, MMU_DIRECT)
//def_all_ldst(_mmu, MMU_TRANSLATE)
//mmu is not added yet
