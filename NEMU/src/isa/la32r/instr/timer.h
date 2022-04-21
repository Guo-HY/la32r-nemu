def_EHelper(rdcntvl_w) { 
  rtl_li(s, ddest, cpu.stable_counter_lo);
}

def_EHelper(rdcntvh_w) { 
  rtl_li(s, ddest, cpu.stable_counter_hi);
}

def_EHelper(rdcntid_w) { 
  rtl_li(s, dsrc1, cpu.stable_counter_id);
}
