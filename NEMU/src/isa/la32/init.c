#include <isa.h>
#include <memory/paddr.h>
#include "local-include/csr.h"
#include "local-include/mmu.h"

//load some inst for test
static const uint32_t img [] = {
0x028006f7, // 	addi.w	$r23,$r23,1(0x1)
0x02800019, // 	addi.w	$r25,$r0,0
0x1400002e, // 	lu12i.w	$r14,1(0x1)
0x0280000d, // 	addi.w	$r13,$r0,0
0x14000004, // 	lu12i.w	$r4,0
0x1400000c, // 	lu12i.w	$r12,0
0x00103484, // 	add.w	$r4,$r4,$r13
0x001039ad, // 	add.w	$r13,$r13,$r14
0x5c0f2584, // 	bne	$r12,$r4,3876(0xf24) # 1c0396c4 <inst_error>
0x80000000, // 	nemu_trap

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