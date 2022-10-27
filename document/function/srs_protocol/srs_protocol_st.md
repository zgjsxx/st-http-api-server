# srs_protocol_st'

## global function

### srs_thread_yield()
将CPU的控制权让出，运行其他协程

### srs_thread_interrupt()
中断当前的协程，被中断的协程不能运行， 除非对其进行状态恢复。
和yield不同的是，yield只是暂时将cpu的使用权让出， 后续如果切回来。还可以继续运行。 


## SrsStSocket

### srs_error_t read_fully(void* buf, size_t size, ssize_t* nread)
使用st_read_fully函数去读取buffer
该函数会尽力去填满大小为size的buffer

```cpp
#include <st.h>

ssize_t st_read_fully(st_netfd_t fd, void *buf, size_t nbyte,
                      st_utime_t timeout);
```
当读取成功时，返回值为正数，并且通常情况下其值等于nbyte，如果返回值小于nbyte，意味着网络连接断开或者读取到文件的末尾。
