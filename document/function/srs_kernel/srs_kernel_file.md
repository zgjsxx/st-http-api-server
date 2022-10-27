# srs_kernel_file

## SrsFileReader类

### SrsFileReader()
该函数初始化fd为-1。

### open()
该函数使用系统的open函数打开文件句柄。

### close()
该函数使用系统的close函数关闭文件句柄。

### is_open()
该函数判断文件句柄是否打开。

### tellg()
该函数返回文件指针的当前位置。

### void skip(int64_t size)
该函数从文件指针的当前位置向后移动size的大小。

### int64_t seek2(int64_t offset)
该函数用于设置文件指针的位置为offset。

### srs_error_t read(void* buf, size_t count, ssize_t* pnread)
该函数用于从缓冲区buf中读取大小为count的内容， 实际读取的大小为*pnread。

### srs_error_t lseek(off_t offset, int whence, off_t* seeked);
该函数用于设置文件指针的位置：
如果whence是SEEK_SET，那么文件指针位置是offset。
如果whence是SEEK_CUR, 那么文件指针位置是当前位置+offset。
如果whence是SEEK_END，那么文件指针位置是文件末尾+offset。
*seeked代表调整后文件指针的位置。

