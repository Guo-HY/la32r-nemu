## 说明
可执行文件位于`./NEMU/build`中，如果需要重新编译，请在`./NEMU`下依次执行
```shell
make clean
make riscv64-xs_defconfig
make
```
其中`riscv64-xs_defconfig`是配置文件，里面的内容已经修改过，请忽略它的名字为什么是riscv64

源代码方面，大部分由我完成的源代码都位于`./NEMU/src/isa/la32`下，可以在`./NEMU/src/isa/la32/init.c`中修改`img`数组来手动编入指令

测试文件在`./func/inst`中，具体可读`./func/Readme_first.txt`，LA工具链可以在 http://114.242.206.180:24989/nextcloud/index.php/s/7xXTPkWg6Jn5KLW 中下载

## 更新说明
### 添加了例外、中断的支持
时钟中断和硬件中断除外，因为这两者必须从CPU端获取中断信号；TLB相关例外暂未实现。


### 添加了新指令 
添加了 `CSRRD CSRWR CSRXCHG SYSCALL BREAK ERTN IDLE LL.W SC.W` 指令，并经过了测试；指令 `IBAR DBAR CACOP PRELD` 实现为了 `nop`，但是对于 `CACOP` 指令，还是进行了特权态检查。
TLB 指令尚未实现。

### 添加了 CSR 寄存器
添加了 LA32 手册中的全部 CSR 寄存器，均可使用 CSR 指令进行读写（写入只写 R/W 位，其他位是0），但是计时器相关的 CSR 寄存器并没有真正使用，因为 NEMU 无法模拟 RTL 的时钟周期，这部分只有等到跟 CPU 联调的时候再实现了。

### 指令不存在
对于尚未实现的指令，现在的 NEMU 会直接进入指令不存在的例外处理环节，而不是抛出错误。

## 注意，目前的测试func本身不健全，甚至对于部分例外有与手册不同的解释，故大部分例外相关的func不能在这一版的NEMU上直接运行
