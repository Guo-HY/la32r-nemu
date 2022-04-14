def_EHelper(csrrd) { 
  rtl_hostcall(s, HOSTCALL_CSR, s0, NULL, NULL, id_src1->imm);
  rtl_mv(s, ddest, s0);
}

def_EHelper(csrwr) { 
  rtl_mv(s, s1, ddest);
  rtl_hostcall(s, HOSTCALL_CSR, s0, s1, NULL, id_src1->imm);
  rtl_mv(s, ddest, s0);
}

def_EHelper(csrxchg) { 
/* ((old_value & ~rj) | (new_value & rj)) & W_MASK */

  rtlreg_t inv_rj = 0;
  rtlreg_t * temp = &inv_rj;
  rtl_and(s, s1, dsrc2, ddest);
  rtl_hostcall(s, HOSTCALL_CSR, s0, NULL, NULL, id_src1->imm);
  *temp = ~(*dsrc2);  // ~ rj
  rtl_and(s, s2, s0, temp);
  rtl_or(s, s1, s1, s2);
  rtl_hostcall(s, HOSTCALL_CSR, s0, s1, NULL, id_src1->imm);
  rtl_mv(s, ddest, s0);
}