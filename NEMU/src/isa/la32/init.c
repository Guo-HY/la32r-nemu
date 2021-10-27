#include <isa.h>
#include <memory/paddr.h>

/*** if no .bin is given, nemu will run instructions in img[] *** --from a developer of NEMU 
 *   but when you do it, one assertion will cause <core dumped>
 */


//load some inst for test
static const uint32_t img [] = {
  0x1562b1ac, 	//  lu12i.w	$r12,-322163(0xb158d)
  0x0292058c, 	//  addi.w	$r12,$r12,1153(0x481)
  0x1400000b, 	//  lu12i.w	$r11,0
  0x0292016b, 	//  addi.w	$r11,$r11,1152(0x480)
  0x0373418a, 	//  andi	  $r10,$r12,0xcd0
  0x80000000    //  nemu_trap
};

static void restart() {
  /* Set the initial program counter. */
  cpu.pc = 0x1c000000;

  /* The zero register is always 0. */
  cpu.gpr[0]._32 = 0;
}


void init_isa() {
  /* Load built-in image. */
  memcpy(guest_to_host(0x1c000000), img, sizeof(img));

  /* Initialize this virtual computer system. */
  restart();
// #ifndef __ICS_EXPORT
//   void init_mmu();
//   init_mmu();
// #endif
}