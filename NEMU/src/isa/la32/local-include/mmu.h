#ifndef __MMU_H__
#define __MMU_H__

#define TLB_SRCH   1
#define TLB_RD     2
#define TLB_WR     3
#define TLB_FILL   4
#define TLB_INVTLB 5

void init_mmu();
void tlbwr();
void tlbfill(uint32_t idx);
int tlbsrch();
void tlbrd();
void invtlb(uint32_t op, uint32_t asid, uint32_t va);

uint32_t tlbfill_index_diff; // tlbfill index from dut when run difftest

#pragma pack(8)
typedef union {
  struct {
    uint32_t E    : 1;
    uint32_t ASID : 10;
    uint32_t G    : 1;
    uint32_t PS   : 6;
    uint32_t VPPN : 19;
    uint32_t      : 27;    
  };
  uint64_t val;
} EntryHi;
#pragma pack()

typedef union {
  struct {
    uint32_t V     : 1;
    uint32_t D     : 1;
    uint32_t MAT   : 2;
    uint32_t PLV   : 2;
    uint32_t PPN   : 24;
    uint32_t pad0  : 2;
  };
  uint32_t val;  
} EntryLo;

struct tlb_struct{
  EntryHi hi;
  EntryLo lo[2];
} ;

struct tlb_struct tlb [CONFIG_TLB_ENTRIES];

#endif