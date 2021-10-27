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