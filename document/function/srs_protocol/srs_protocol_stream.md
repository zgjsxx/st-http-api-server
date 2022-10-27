# SrsFastStream
一个buffer

## srs_error_t grow(ISrsReader* reader, int required_size)
使用reader去读取至少required_size的内容去填冲buffer， 读取过程是循环进行的，直到大小达到required_size。 实际上我们读取的内容是可能大于required_size的