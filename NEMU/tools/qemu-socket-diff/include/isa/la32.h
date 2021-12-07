#ifndef __LA32_H__
#define __LA32_H__

#define _str(x) # x
#define str(x) _str(x)

#define ISA_QEMU_BIN "qemu-system-loongson32"
/*
                      "-serial", "stdio",\
                      "-monitor", "tcp::1234,server,nowait",\
                      "-kernel", "../func/main.elf",
*/
#define ISA_QEMU_ARGS "-M", "ls3a5k32",\
                      "-d", "single,cpu",\
                      "-D", "single.log",\
                      "-m", "4096",\
                      "-fsdev", "local,security_model=mapped,id=fsdev0,path=./",\
                      "-device", "virtio-9p-pci,id=fs0,fsdev=fsdev0,mount_tag=hostshare,bus=ls7a.0",\
                      "-smp", "1",\
                      
union isa_gdb_regs {
  struct {
    uint32_t gpr[32];
    uint32_t pc;
  };
  struct {
    uint32_t array[77];
  };
};

#endif
