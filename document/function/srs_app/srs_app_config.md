# srs_app_config

## SrsConfigBuffer类

### srs_error_t fullfill(const char* name)
根据文件名读取文件， 并且将文件内容全部加载到缓存中

### bool empty()
判断buffer是否还有空间

## SrsConfDirective类
成员
int         conf_line

std::string name

std::vector<std::string> args;

std::vector<SrsConfDirective*> directives;

可以从测试用例去理解作用：

```cpp
VOID TEST(ConfigDirectiveTest, ParseSingleComplexDirs)
{
    srs_error_t err;
    
    MockSrsConfigBuffer buf("dir0 arg0;dir1 {dir2 arg2;}");
    SrsConfDirective conf;
    HELPER_ASSERT_SUCCESS(conf.parse(&buf));
    EXPECT_EQ(0, (int)conf.name.length());
    EXPECT_EQ(0, (int)conf.args.size());
    EXPECT_EQ(2, (int)conf.directives.size());

    SrsConfDirective& dir0 = *conf.directives.at(0);
    EXPECT_STREQ("dir0", dir0.name.c_str());
    EXPECT_EQ(1, (int)dir0.args.size());
    EXPECT_STREQ("arg0", dir0.arg0().c_str());
    EXPECT_EQ(0, (int)dir0.directives.size());

    SrsConfDirective& dir1 = *conf.directives.at(1);
    EXPECT_STREQ("dir1", dir1.name.c_str());
    EXPECT_EQ(0, (int)dir1.args.size());
    EXPECT_EQ(1, (int)dir1.directives.size());

    SrsConfDirective& dir2 = *dir1.directives.at(0);
    EXPECT_STREQ("dir2", dir2.name.c_str());
    EXPECT_EQ(1, (int)dir2.args.size());
    EXPECT_STREQ("arg2", dir2.arg0().c_str());
    EXPECT_EQ(0, (int)dir2.directives.size());
}
```
conf对象的name和size都是空的，conf的成员的vector中存储着所有的directive， 其还是directive长度为2

第一个孩子directive 就是dir0 arg0,其name = dir0， arg0 = arg0, 其孩子directive为空

第二个孩子directive 就是dir1 {dir2 arg2;}， 其name = dir1， 其arg0为空， 它还有一个孩子节点， name = dir2， arg0=arg2


### SrsConfDirective* get(string _name)
从vector中遍历所有的SrsConfDirective， 找到第一个name与传入参数name相同的SrsConfDirective

### SrsConfDirective* at(int index)
使用index下标从vector中读取SrsConfDirective

### string SrsConfDirective::arg0()
获取第一个参数

### string SrsConfDirective::arg1()
获取第二个参数

### string SrsConfDirective::arg2()
获取第三个参数

### string SrsConfDirective::arg3()
获取第四个参数