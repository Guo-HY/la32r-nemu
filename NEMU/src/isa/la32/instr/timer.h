def_EHelper(rdcntvl_w) { 
  // printf("this is rdcntvl_w instruction\n"); 
  rtl_li(s, ddest, cpu.stable_counter_lo);
}

def_EHelper(rdcntvh_w) { 
  // printf("this is rdcntvh_w instruction\n"); 
  rtl_li(s, ddest, cpu.stable_counter_hi);
}

def_EHelper(rdcntid_w) { 
  // printf("this is rdcntid_w instruction\n"); 
  rtl_li(s, dsrc1, cpu.stable_counter_id);
}
