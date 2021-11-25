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

#endif