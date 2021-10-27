#ifndef __INTR_H__
#define __INTR_H__

#include <cpu/decode.h>

/* interupt related codes havent been added, but add this func to pass compiler  */

word_t raise_intr(word_t NO, vaddr_t ret_addr);

#endif