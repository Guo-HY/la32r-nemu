#include "../local-include/rtl.h"
#include "../local-include/intr.h"
#include <cpu/difftest.h>


/* do nothing for now.. just for pass compiler */


word_t raise_intr(uint32_t NO, vaddr_t epc) {
// #define EX_ENTRY 0x80000180
//   vaddr_t target = (NO & TLB_REFILL) ? 0x80000000 : EX_ENTRY;
//   NO &= ~TLB_REFILL;
//   cpu.cause = NO << 2;
//   cpu.epc = epc;
//   cpu.status.exl = 1;

//   difftest_skip_dut(1, 2);



  return 0x1c000000;
}

word_t isa_query_intr() {
//   if (cpu.INTR && (cpu.status.ie) && !(cpu.status.exl)) {
//     cpu.INTR = false;
//     cpu.pc = raise_intr(0, cpu.pc);
//   }
    return INTR_EMPTY;
}

