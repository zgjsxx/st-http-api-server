# state-thread(st)
reference from http://state-threads.sourceforge.net/docs/reference.html

## st_thread_create()
通过st_thread_create创建的协程并不会立即被调用，直到主线程中遇到阻塞时,才会切出执行创建好的协程。

例如下面的程序，
使用st_thread_create创建func协程后，func并不会立即执行， 直到等到count=5的时候调用st_usleep的时候， CPU控制权切出，才开始进行调度执行func函数。
```cpp
void demo(){
    st_thread_create(func, arg, 1, stack_size))
    int count = 0;
    while(1)
    {
        count++;
        sleep(1);
        if(count == 5)
        {
            st_usleep(1000*1000);
        }
    }
}

```