#include <isa.h>
#include <memory/paddr.h>
#include "local-include/csr.h"

/*** if no .bin is given, nemu will run instructions in img[] *** --from a developer of NEMU 
 *   but when you do it, one assertion will cause <core dumped>
 */


//load some inst for test
static const uint32_t img [] = {
0x028006f7,// 	addi.w	$r23,$r23,1(0x1)
0x0015e739,// 	xor	$r25,$r25,$r25
0x0380080c,// 	ori	$r12,$r0,0x2
0x0380080d,// 	ori	$r13,$r0,0x2
0x0401818d,// 	csrxchg	$r13,$r12,0x60
0x14001a14,// 	lu12i.w	$r20,208(0xd0)
0x03801294,// 	ori	$r20,$r20,0x4
0x15fffe33,// 	lu12i.w	$r19,-15(0xffff1)
0x0388d273,// 	ori	$r19,$r19,0x234
0x29800293,// 	st.w	$r19,$r20,0
0x2000028d,// 	ll.w	$r13,$r20,0
0x5c01d66d,// 	bne	$r19,$r13,468(0x1d4) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x5c01c5cf,// 	bne	$r14,$r15,452(0x1c4) # 1c068ce0 <inst_error>
0x142469f3,// 	lu12i.w	$r19,74575(0x1234f)
0x03bffe73,// 	ori	$r19,$r19,0xfff
0x0015026d,// 	move	$r13,$r19
0x2100028d,// 	sc.w	$r13,$r20,0
0x0380040c,// 	ori	$r12,$r0,0x1
0x5c01adac,// 	bne	$r13,$r12,428(0x1ac) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x0015bdef,// 	xor	$r15,$r15,$r15
0x5c0199cf,// 	bne	$r14,$r15,408(0x198) # 1c068ce0 <inst_error>
0x2880028d,// 	ld.w	$r13,$r20,0
0x5c01926d,// 	bne	$r19,$r13,400(0x190) # 1c068ce0 <inst_error>
0x14001e33,// 	lu12i.w	$r19,241(0xf1)
0x0388d273,// 	ori	$r19,$r19,0x234
0x29800293,// 	st.w	$r19,$r20,0
0x2000028d,// 	ll.w	$r13,$r20,0
0x5c017e6d,// 	bne	$r19,$r13,380(0x17c) # 1c068ce0 <inst_error>
0x0380080c,// 	ori	$r12,$r0,0x2
0x0380080d,// 	ori	$r13,$r0,0x2
0x0401818d,// 	csrxchg	$r13,$r12,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdad,// 	and	$r13,$r13,$r15
0x5c0165af,// 	bne	$r13,$r15,356(0x164) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x0015bdef,// 	xor	$r15,$r15,$r15
0x5c0151cf,// 	bne	$r14,$r15,336(0x150) # 1c068ce0 <inst_error>
0x140009ed,// 	lu12i.w	$r13,79(0x4f)
0x03bffdad,// 	ori	$r13,$r13,0xfff
0x2100028d,// 	sc.w	$r13,$r20,0
0x0015b18c,// 	xor	$r12,$r12,$r12
0x5c013dac,// 	bne	$r13,$r12,316(0x13c) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x0015bdef,// 	xor	$r15,$r15,$r15
0x5c0129cf,// 	bne	$r14,$r15,296(0x128) # 1c068ce0 <inst_error>
0x2880028d,// 	ld.w	$r13,$r20,0
0x5c01226d,// 	bne	$r19,$r13,288(0x120) # 1c068ce0 <inst_error>
0x1401fe33,// 	lu12i.w	$r19,4081(0xff1)
0x03884a73,// 	ori	$r19,$r19,0x212
0x0380100c,// 	ori	$r12,$r0,0x4
0x0380100d,// 	ori	$r13,$r0,0x4
0x0401818d,// 	csrxchg	$r13,$r12,0x60
0x0400000d,// 	csrrd	$r13,0x0
0x03801c0c,// 	ori	$r12,$r0,0x7
0x0400058d,// 	csrxchg	$r13,$r12,0x1
0x1c00000c,// 	pcaddu12i	$r12,0
0x0280b18c,// 	addi.w	$r12,$r12,44(0x2c)
0x0400182c,// 	csrwr	$r12,0x6
0x29800293,// 	st.w	$r19,$r20,0
0x2000028d,// 	ll.w	$r13,$r20,0
0x5c00ea6d,// 	bne	$r19,$r13,232(0xe8) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x5c00d9cf,// 	bne	$r14,$r15,216(0xd8) # 1c068ce0 <inst_error>
0x06483800,// 	ertn
0x0401800e,// 	csrrd	$r14,0x60
0x0380140f,// 	ori	$r15,$r0,0x5
0x0014bdce,// 	and	$r14,$r14,$r15
0x0380040f,// 	ori	$r15,$r0,0x1
0x5c00c1cf,// 	bne	$r14,$r15,192(0xc0) # 1c068ce0 <inst_error>
0x14002433,// 	lu12i.w	$r19,289(0x121)
0x038bfe73,// 	ori	$r19,$r19,0x2ff
0x0015026d,// 	move	$r13,$r19
0x2100028d,// 	sc.w	$r13,$r20,0
0x0380040c,// 	ori	$r12,$r0,0x1
0x5c00a9ac,// 	bne	$r13,$r12,168(0xa8) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x0015bdef,// 	xor	$r15,$r15,$r15
0x5c0095cf,// 	bne	$r14,$r15,148(0x94) # 1c068ce0 <inst_error>
0x2880028d,// 	ld.w	$r13,$r20,0
0x5c008e6d,// 	bne	$r19,$r13,140(0x8c) # 1c068ce0 <inst_error>
0x1401ff53,// 	lu12i.w	$r19,4090(0xffa)
0x03aeae73,// 	ori	$r19,$r19,0xbab
0x0400000d,// 	csrrd	$r13,0x0
0x03801c0c,// 	ori	$r12,$r0,0x7
0x0400058d,// 	csrxchg	$r13,$r12,0x1
0x1c00000c,// 	pcaddu12i	$r12,0
0x0280b18c,// 	addi.w	$r12,$r12,44(0x2c)
0x0400182c,// 	csrwr	$r12,0x6
0x29800293,// 	st.w	$r19,$r20,0
0x2000028d,// 	ll.w	$r13,$r20,0
0x5c00626d,// 	bne	$r19,$r13,96(0x60) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x5c0051cf,// 	bne	$r14,$r15,80(0x50) # 1c068ce0 <inst_error>
0x06483800,// 	ertn
0x0401800e,// 	csrrd	$r14,0x60
0x0380140f,// 	ori	$r15,$r0,0x5
0x0014bdce,// 	and	$r14,$r14,$r15
0x0015bdef,// 	xor	$r15,$r15,$r15
0x5c0039cf,// 	bne	$r14,$r15,56(0x38) # 1c068ce0 <inst_error>
0x1401574d,// 	lu12i.w	$r13,2746(0xaba)
0x03affdad,// 	ori	$r13,$r13,0xbff
0x2100028d,// 	sc.w	$r13,$r20,0
0x0015b18c,// 	xor	$r12,$r12,$r12
0x5c0025ac,// 	bne	$r13,$r12,36(0x24) # 1c068ce0 <inst_error>
0x0401800e,// 	csrrd	$r14,0x60
0x0380040f,// 	ori	$r15,$r0,0x1
0x0014bdce,// 	and	$r14,$r14,$r15
0x0015bdef,// 	xor	$r15,$r15,$r15
0x5c0011cf,// 	bne	$r14,$r15,16(0x10) # 1c068ce0 <inst_error>
0x2880028d,// 	ld.w	$r13,$r20,0
0x5c000a6d,// 	bne	$r19,$r13,8(0x8) # 1c068ce0 <inst_error>
0x0280075a,// 	addi.w	$r26,$r26,1(0x1)


};

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = 0x1c000000;

  /* The zero register is always 0. */
  cpu.gpr[0]._32 = 0;
}


void init_isa() {
  init_csr();

  CRMD->plv  = 0;
  CRMD->ie   = 0;
  CRMD->da   = 1;
  CRMD->pg   = 0;
  CRMD->datf = 0;
  CRMD->datm = 0;
  ECFG->lie  = 0;
  ESTAT->is_01 = 0;
  TCFG->en   = 0;
  LLBCTL->klo = 0;
  DMW0->plv0 = 0;
  DMW0->plv3 = 0;
  DMW1->plv0 = 0;
  DMW1->plv3 = 0;

  cpu.ll_bit = 0;
  cpu.inst_idle = 0;


  /* Load built-in image. */
  memcpy(guest_to_host(0x1c000000), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();
// #ifndef __ICS_EXPORT
//   void init_mmu();
//   init_mmu();
// #endif
}