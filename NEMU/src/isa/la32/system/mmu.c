#include <isa.h>
#include <memory/paddr.h>
#include <memory/vaddr.h>

/* do nothing for now.. just for pass compiler */


paddr_t isa_mmu_translate(vaddr_t vaddr, int len, int type) {
  return vaddr;        
}