## 安装方法
**从github下载gperftools源码并解压**
```
wget https://github.com/gperftools/gperftools/archive/gperftools-2.7.tar.gz
tar xvf gperftools-2.7.tar.gz
```
**解压文件夹改名**
```
mv gperftools-gperftools-2.7 gperftools-2.7
cd gperftools-2.7
./autogen.sh
./configure
make -j8
```
**安装到系统文件夹**
```
sudo make install
```

注意：在64位操作系统下需要libunwind支持，如果没有安装libunwind，还要先编译安装libunwind。
```
yum install libunwind-devel
```


## 静态连接profiler
有的时候我们需要静态连接profiler库(比如在嵌入式系统下做性能分析).根据gperftools的官方说明：README，静态连接profiler不能使用profiler.a静态库，要用libtcmalloc_and_profiler.a替代。

```
EVERYTHING IN ONE
-----------------
If you want the CPU profiler, heap profiler, and heap leak-checker to
all be available for your application, you can do:
   gcc -o myapp ... -lprofiler -ltcmalloc

However, if you have a reason to use the static versions of the
library, this two-library linking won't work:
   gcc -o myapp ... /usr/lib/libprofiler.a /usr/lib/libtcmalloc.a  # errors!

Instead, use the special libtcmalloc_and_profiler library, which we
make for just this purpose:
   gcc -o myapp ... /usr/lib/libtcmalloc_and_profiler.a
```

## 关于采样次数
CPU profiler是基于采样工作的。所以采样次数影响着性能报告的准确性。
如果采样次数过少，则你会发现同样的程序同样的数据，每次输出的性能报告中的热点都不一样。
所以在我的实际应用中，通过循环运行测试程序函数，大幅度提高采样次数。这样才能获得一个稳定的准确的性能报告。