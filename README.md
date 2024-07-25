# rocket


#### 日志模块开发
1.日志级别
2.打印到文件（支持日期命名，及日志滚动）
3.c格式化字符串
4.线程安全


类：
LogLevel:
Debug
Info
Error


LogEvent:
文件名，行号
MsgNo      ---(标志每个rpc请求)
Thread id  ---（线程号）
日期，时间（ms）
自定义消息



日志打印格式
[级别][日期 时间] \t [进程：线程号] \t [文件名：行号]
[Level][%y-%m-%d %H:%M.%s,%ms] \t [pid:thread_id] \t [file_name:line][%msg]

Logger 日志器（一个类）
1.提供打印日志的方法
2.设置日志输出的路径
