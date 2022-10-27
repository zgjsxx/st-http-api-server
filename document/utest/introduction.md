# utest introduction

## 1.prepare then ut environment
upgrade gcc version

```shell
sudo yum install centos-release-scl
sudo yum install devtoolset-7
scl enable devtoolset-7 bash
```

set in bashrc：
```shell
source /opt/rh/devtoolset-7/enable
or
source scl_source enable devtoolset-7
```

## compile with UT and run UT
```
./configure --srt=on --utest=on --jobs=2
```

then run
```
./objs/srs_utest
```

