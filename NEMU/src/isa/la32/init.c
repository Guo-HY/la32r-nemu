#include <isa.h>
#include <memory/paddr.h>
#include "local-include/csr.h"
#include "local-include/mmu.h"

//load some inst for test
static const uint32_t img [] = {
0x06488000,
0x04006020, //	csrwr	$r0,0x18
0x04022020, //	csrwr	$r0,0x88

};

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = 0x1c000000;

  /* The zero register is always 0. */
  cpu.gpr[0]._32 = 0;
}


void init_isa() {
  printf("####### INIT HERE ########\n");
  printf("TLB_ENTRY = %d\n",CONFIG_TLB_ENTRIES);
  init_csr();

  CRMD->plv  = 0;
  CRMD->ie   = 0;
  CRMD->da   = 1;
  CRMD->pg   = 0;
  CRMD->datf = 0;
  CRMD->datm = 0;
  EUEN->fpe = 0;
  ECFG->lie  = 0;
  ESTAT->is_01 = 0;
  TCFG->en   = 0;
  LLBCTL->klo = 0;
  DMW0->plv0 = 0;
  DMW0->plv3 = 0;
  DMW1->plv0 = 0;
  DMW1->plv3 = 0;

  CPUID->coreid = 0;
  TID->val = 0;

  cpu.ll_bit = 0;
  cpu.inst_idle = 0;
  ASID->asidbits = 10;

  /* Load built-in image. */
  memcpy(guest_to_host(0x1c000000), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();

  init_mmu();

}