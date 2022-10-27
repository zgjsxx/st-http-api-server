
## jmeter 命令

``` jmeter -n -t testfile.jmx -l testresults.jtl(不能已存在同名jtl) -e -o report(必须是个空目录)

ps:针对已经通过命令行生成了jtl文件，想解析成html可通过：
jmeter -g testresults.jtl -e -o report(必须是个空目录)
```

## jmeter 测试srs http api 遇到的问题
测试其他http 框架时没有遇到这个问题， 因为他们保持了keep-alive连接

使用jmeter 测试srs http api时， 由于srs response带了 Connection:close， 这会导致客户端关闭连接，客户端关闭连接时候会产生TIME_WAIT， 由于并发量较大， 会导致很快端口就被用光， 导致后续的请求都陆续失败。