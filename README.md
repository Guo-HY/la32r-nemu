# **基于NEMU实现的LoongArch32-primary模拟器**
## **介绍与概况**
本项目基于目前已经开源的 `NEMU` 模拟器，向其中移植龙芯架构32位精简版，即 `LoongArch32-primary`(以下简称为 `LA32`)。

为了向 `LA32` 的开发者、学习者、爱好者、<s>靠它毕业者</s>提供一个类似于 ysyx 项目中的 `difftest` 环境，我产生了向 `NEMU` 中移植 `LA32` ，之后复用 `difftest` 框架的想法。于是该项目诞生了。<s>为了让更多的朋友帮忙找bug</s>为了向更多的朋友分享，在与汪老师沟通后，我们选择开源本项目。

目前 `NEMU` 本体有两个organizations可以选择：
```
git clone https://github.com/OpenXiangShan/NEMU.git
git clone https://github.com/OSCPU/nemu.git
```
前者是上游，但本项目目前是基于后者来进行移植的，将来会切换到前者。

## **实现规模**
本项目按照《龙芯架构32位精简版参考手册》实现，目前已经实现了：
* 除浮点指令之外的全部指令
* 除时钟中断、硬件中断、浮点例外之外的全部中断例外支持
* 全部的 `CSR` 寄存器
* 项数可配置的 `TLB MMU`
* 向 `difftest` 框架提供的各 `API`

目前尚未实现、无法实现以及不打算实现的内容：
* `Cache`：不打算实现
* 计时器和定时器：`NEMU` 无法模拟时钟周期，故无法实现
* 各种外设（包括串口）：尚未实现。本项目的最终目的是为了实现 `difftest` ，故外设支持的优先级靠后
* 配套的 `AM` （裸机运行时环境）：尚未实现。理由同上

### **一些特殊实现的说明**
* 由于没有实现缓存，故与缓存相关的指令：`IBAR DBAR PRELD CACOP` 均实现为了 `NOP`，但是 `CACOP` 指令会触发与之相关的指令特权等级错例外（`IPE`）。
* 与计时器和定时器相关的指令 `RDCNTV{L/H}.W、RDCNTID` 以及读 `TVAL` 寄存器的 `CSR` 指令，是需要从CPU端获取数据的。在单独运行 `NEMU` 的时候，都会读到 0 或者不确定的值。
* `IDLE` 指令实现为了自己跳转到自己，单独运行 `NEMU` 的时候不会产生时钟中断和硬件中断，所以会陷入死循环。
* 实现了两条只对 NEMU 可见的指令：`nemu_trap: 0x80000000`， `print_led: 0xc0000000`。前一条指令用于让 `NEMU` 停止执行，在没有运行时环境支持进程正常退出的情况下，需要在运行的程序中手动编入这条指令来让 `NEMU` 停止工作；后一条指令在运行 `chiplab` 中提供的测试 func 时有用，效果是打印寄存器 `R12` 中的值，即模仿龙芯杯比赛中，试验箱上数码管显示的结果，形如 `XX0000XX`，最左边一字节显示当前的测试点编号，最右边一字节显示当前通过的测试点数目，最左一字节和最右一字节不同的时候就意味着有测试点没有通过。
* 时钟中断、硬件中断信号均需要从CPU端获取，单独运行 `NEMU` 的时候，都不会触发。
* `CSR` 寄存器 `CPUID` 不能写入，读出永远为 0 。

## **编译运行**
1、首先需要安装依赖。由于本项目是从 ysyx 项目中的 NEMU 移植而来，所以请按照 ysyx 的标准安装依赖：
https://github.com/OpenXiangShan/xs-env/blob/master/setup-tools.sh

2、完成依赖安装之后，需要设置环境变量：`export NEMU_HOME=...`，设置为 `NEMU` 主目录。

3、进入 `NEMU` 主目录之后，可以进行编译，输入以下命令完成一次编译：
```shell
make la32-primary_defconfig   // 导入配置文件
make
```
（当然也可以使用 `make menuconfig` 进入图形化界面手动配置，但是不推荐，一方面是不好用，一方面是已经准备好了配置文件，一方面是很多配置组合并没有测试过）

在编译过程中，你应该会看到四处 `WARNING`:

第一二处 be like
```
warning: ‘vaddr_write_cross_page’ defined but not used
warning: ‘vaddr_read_cross_page’ defined but not used
```
这两个函数是用来处理 `riscv` 中，16bit 压缩指令可能导致的跨页读写问题。`LA32` 中不存在这个问题，忽略之。

第三四处 be like
```shell
resource/softfloat/repo/source/8086-SSE/specialize.h:158:35: warning: large integer implicitly truncated to unsigned type
resource/softfloat/repo/source/8086-SSE/specialize.h:158:35: warning: large integer implicitly truncated to unsigned type
```
这是软件模拟浮点运算的相关代码，浮点指令没有实现，不用管。（并不明白为啥这里会报警告）

如果你没有再看到其他报错，那么 `NEMU` 的可执行文件 `la32-nemu-interpreter` 就已经在 `.build` 之中喇。
## **加载程序并运行**
`NEMU` 有两种方法加载程序，第一种，是将程序的 `.bin` 文件作为参数，在运行程序时传入，如：
```
./la32-nemu-interpreter ../../../coremark.bin
```
第二种方式是运行程序时不附带任何参数，这时候 `NEMU` 会将 `NEMU/src/isa/la32/init.c` 中的 `img` 数组中的内容拷贝到 `RESET_PC` 开始执行。可以手动将一些指令编入 `img` 数组中，这在调试的时候非常方便。

### **NEMU部分命令的使用说明**

运行了程序之后就会进入 `NEMU` 命令行，输入 `help` 即可查看可使用的命令。注意 `attach detach save load` 这四个命令没有测试过。

`tlb` 命令和 `b` 命令是我自己加的（没错， `NEMU` 甚至没有自带断点功能），使用说明如下：

* 指令：`tlb`
* 效果：打印当前一共支持多少个 TLB 表项，即 `CONFIG_TLB_ENTRIES`
* 指令：`tlb NUM`
* 效果：`NUM` 范围为 `[0,CONFIG_TLB_ENTRIES]`，当 `NUM` 不等于 `CONFIG_TLB_ENTRIES` 时，`NUM` 作为 `index` ，打印 `tlb[NUM]`；当 `NUM` 等于 `CONFIG_TLB_ENTRIES` 时，会依次打印所有 `TLB` 表项。
* 指令：`b PC`
* 效果：在 `PC` 处设置一个**一次性**的断点，之后 `NEMU` 会自动开始执行，直到下一条指令在 `PC` 时暂停，期间会打印执行过的指令。

还有一个奇怪的 `watchpoint` 命令：
* 指令： `w expression`
* 注意一定是跟一个表达式，可以用来观察每个寄存器的值何时变化，寄存器名称前要加 `$`，如 `$pc==0x1c000000 $sp!=0x0` 在**表达式的值**变化的时候，`NEMU` 会打印变化处的 `PC`,按理说应该在变化处暂停下来，但是很多时候并不能准确地暂停在表达式值变化处。
* <s>ysyx 那边负责维护 `NEMU` 的学长表示他也没怎么用过这个功能。</s>

如果你想实现更多的 `NEMU` 命令，可以在 `NEMU/src/monitor/ui.c` 中自行修改。

### **关于自制workload的说明**

如果你想在 `NEMU` 上运行自己编写的程序，需要注意以下几点：
* 没有输出。`NEMU` 尚未实现配套的 `AM` 以及串口支持。
* 数据段一定要放在代码段后面，这一点可能需要自行修改链接脚本。

我使用的 `workload` 都来自于龙芯的 `chiplab` 仓库：https://gitee.com/loongson-edu/chiplab

如果你也想利用龙芯的 `chiplab` 仓库里的 `func`，这里做出如下说明：
* 龙芯的 `chiplab` 仓库于 `2021.12.3` 进行了更新，请使用最新的仓库。
* `chiplab/software/func` 中的 `lab16` 测试实现为 `nop` 的指令，没有在 `NEMU` 上运行的必要。建议运行 `lab16` 及之前的功能测试。
* `chiplab/software/func` 中的功能测试都是用汇编写的，不存在数据段。但是要注意，`NEMU` 来模拟 `IDLE_1s` 会很慢，请注释掉。另外，涉及到 `NEMU` 没有实现的功能的测试项，也建议注释掉（如 `IDLE` 指令测试，时钟中断测试等）
* 对于其他C程序，如 `coremark`，为了将数据段放在代码段后面，请将 `chiplab/toolchains/system_newlib/pmon.ld` 的第81行   `. = 0x1000;`    注释掉，并且在产生 `.bin` 文件时, `objcopy` 所有的 `section`。

也可以直接使用本项目编译好的 `main_lab14.bin`，注意它去掉了 `n49_ti_ex_test n58_ti_ex_idle_test n59_rdcnt_test` 这三项。

### **“对Hit xxx Trap”的说明** 
在执行了 `nemu_trap: 0x80000000` 这条指令之后，`NEMU` 会判断当前保存返回值的 `a0` 寄存器内容是否为 0 ，是则显示 `HIT GOOD TRAP` 否则显示 `HIT BAD TRAP`。由于尚未实现配套的 `AM` ，`NEMU` 执行程序时大概率都会显示 `HIT BAD TRAP`，但这不代表一定错误地执行了程序。

## **对配置文件的说明**
与 `LA32` 相关的配置文件有两个：`la32-primary_defconfig` 和 `la32-primary-ref_defconfig`， 位于 `NEMU/configs` 中。前者用于编译产生可执行文件，后者用于编译产生动态链接库。请不要随意修改两者的内容。

如果你需要配置 `TLB` 表项的数目，可以在配置文件中找到并修改 `CONFIG_TLB_ENTRIES` 一项。如果超过32项，就需要再修改 `CSR` 寄存器 `TLBIDX` 的 `index` 位域的宽度以及 `TLBIDX_W_MASK` 了。

## **加载程序并运行**

### **编译difftest**
由于`NEMU`目录下的Makefile存在未知的问题，此处我们需要手动编译difftest源码生成动态链接库。Makefile第112行打印了difftest源码所在的目录，复制该目录。在`NEMU`目录下执行
```shell
make 上一步复制的目录
```
执行后该目录下会生成./build/la32-qemu-so

### **修改config并链接运行**
需要修改的部分如下：
```
CONFIG_DIFFTEST=y
CONFIG_DIFFTEST_REF_PATH="tools/qemu-socket-diff"
CONFIG_DIFFTEST_REF_NAME="qemu"
```
请注意，直接修改.config或使用Makefile修改均可能造成修改不生效，建议使用`make menuconfig`进行修改。修改后执行
```shell
make
```
检查生成了可执行文件/build/la32-nemu-interpreter，随后执行。注意需使用-d链接上一步生成的动态链接库。
```shell
 ./build/la32-nemu-interpreter -d ./tools/qemu-socket-diff/build/la32-qemu-so ../func/main.bin
```

### **注意事项**
1. 请在环境变量中添加qemu-system-loognson32
2. ./tools/qemu-socket-diff/include/isa/la32.h中描述了启动qemu的参数，用户可以根据需求自行更改
3. qemu执行后会生成single.log，记录每条指令执行后的体系结构状态，若程序卡死请尽快强制退出，否则程序会持续向single.log输出造成其占用过多空间

## **《龙芯架构32位精简版参考手册》中写得不清楚的地方**
**本节内容仅为个人理解，对指令集的最终解释归龙芯中科所有！**
* `P51 6.1.1 中断类型`，描述为一共有 12 个中断，但是 `ESTAT.IS` 域有13位，并没有说明差一个差在哪，哪一位是不用的。对比了完整手册，实际上 `ESTAT.IS[10]` 是性能监测计数溢出中断，在 `LA32` 精简版中是没有这个中断的，应当始终为0。
* 只有在用到 `TLB` 进行地址翻译的时候，才会触发虚地址最高位为 1 的地址错例外 `ADE`。
* 手册中规定，物理地址最大可实现为 36 位，因此才会出现 `PPN` 在 `CSR` 寄存器中是24位，在 `TLB` 表项中是20位的问题。`NEMU` 实现位32位物理地址，故 `PPN` 在 `CSR` 寄存器中高4位是0。
* 对于 `TLBRD` 指令读出无效 `TLB` 表项的情况，手册中的描述是：“建议不更新 `CSR` 寄存器或全置为0”，本项目选择了不更新的实现。
* 手册中说 `syscall` `break` 指令编码时可以编一个参数进去，但并没有说这个参数怎么传递。实际上完全可以忽视这个参数不管。
## 其他
* 《龙芯架构32位精简版参考手册》可以从龙芯官网下载。https://www.loongson.cn/FileShow
* `LA32` 相关工具链可以在这里下载：http://114.242.206.180:24989/nextcloud/index.php/s/7xXTPkWg6Jn5KLW
* 目前 `NEMU` 在打印指令的操作数时会有一些不准确、操作数顺序与汇编文件不一样的情况，这是打印的问题，暂时懒得改。
* 目前 `NEMU` 打印的 `PC` 几乎都是 “下一条待执行的指令的 `PC`”，而不是 “本条已执行的指令的 `PC`”，相信聪明的你一定可以理解。
* 目前 `NEMU` 的基本功能正确，在不实现 `RDCNTV{L/H}.W、RDCNTID` 指令的情况下可以正确执行 `coremark` 。但 `NEMU` 尚未经过充分的随机指令测试，如果你发现了 bug 或者其他问题，请提出 Issue 或者联系我： wangweitong18@mails.ucas.ac.cn
* 由于 ysyx 的 `NEMU` 项目本身并没有任何的开源许可证，在与 ysyx 的王华强学长交流后，本项目只开源与 `LA32` 实现相关的源代码，其他架构的代码不包含在本项目中，但也请**不要删除** `NEMU/src/isa` 下的其他文件夹。
* 目前本项目和开源仓库仅由我一个人开发管理，这也是我正式开源并管理的第一个仓库，不当之处还请各位不吝赐教，谢谢大家看到这里。
