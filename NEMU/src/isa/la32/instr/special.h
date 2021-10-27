
/* copy from isa/mips32 */

def_EHelper(inv) {
  save_globals(s);
  rtl_hostcall(s, HOSTCALL_INV, NULL, NULL, NULL, 0);
  longjmp_exec(NEMU_EXEC_END);
}

def_EHelper(nemu_trap) {
  save_globals(s);
  rtl_hostcall(s, HOSTCALL_EXIT, NULL, &cpu.gpr[4]._32, NULL, 0); // gpr[4] is $v0
  longjmp_exec(NEMU_EXEC_END);
}

def_EHelper(print_led) {
  printf("####  current result: 0x%08x  ####\n", cpu.gpr[12]._32);
}

