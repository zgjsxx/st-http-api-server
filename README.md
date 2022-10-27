# st http api server
An async http server relized with coroutine.

## how to make 
```shell
./configure
make
./objs/srs -c conf/srs.conf
```

## run utest
google test needs a gcc 7+ compiler

```shell
yum install centos-release-scl
yum install devtoolset-7-gcc*
```

temperaily enable
```shell
scl enable devtoolset-7 bash
```

permanent enable

```shell
mv /usr/bin/gcc /usr/bin/gcc-4.8.5
ln -s /opt/rh/devtoolset-8/root/bin/gcc /usr/bin/gcc
mv /usr/bin/g++ /usr/bin/g++-4.8.5
ln -s /opt/rh/devtoolset-8/root/bin/g++ /usr/bin/g++
gcc --version
g++ --version
```

```
./configure --utest=off
make utest
./objs/srs_utest
```

## run gcp 
```
./configure --with-gperf --with-gcp
or ./configure --gperf=on --gcp=on && make

# Or CTRL+C to stop GCP
killall -2 srs
./objs/pprof --text objs/srs gperf.srs.gcp*
```