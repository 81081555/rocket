#ifndef ROCKET_COMMON_LOG_H
#define ROCKET_COMMON_LOG_H


#include <string>
#include <queue>
#include <iostream>
#include <memory>

namespace rocket{

    // c格式化字符串
    template<typename... Args>  // args 可变参数长度

    std :: string formatString(const char* str, Args&&... args){          // 打印日志（log.cc）时只需要调用formatestring
            int size = snprintf(nullptr, 0, str, args...);       // 用snprintf这份函数来获取格式化字符串后的size

            std :: string result;
            if(size > 0){
                result.resize(size);      // 这个变量的空间设置为这个size
                snprintf(&result[0], size + 1, str, args...);          // 然后把格式后整个字符串输出到result[0]上
            }

            return result;
    }



    // 创建 -> 格式化 —> 将日志消息push进全局Logger -> 调用GetGlobalLogger打印日志
#define DEBUGLOG(str, ...)\
    std :: string msg = (new rocket :: LogEvent(rocket :: LogLevel :: Debug) -> toString()) + rocket :: formatString(str, ##_VA_ARGS_); \
    rocket :: Logger :: GetGlobalLogger() -> pushLog(msg); \
    rocket :: Logger :: GetGlobalLogger -> log(); \




    enum LogLevel{
        Debug = 1,
        Info = 2,
        Error = 3
    };





  class Logger{
            public:
                typedef std :: shared_ptr <Logger> s_ptr;
                void pushLog(const std :: string& msg);

                void log();

            public:
                static Logger* GetGlobalLogger();


            private:
                LogLevel m_set_level;

                std :: queue <std ::string> m_buffer;

        };




    std:: string LogLevelToString(LogLevel level);



    class LogEvent{
        public:
            std :: string getFilename() const{
                return m_file_name;
            }

            LogLevel getLogLevel () const{
                return m_level;
            }

            std :: string toString();

        private:
        std :: string m_file_name;    // 文件名 
        int32_t m_file_line;    //行号
        int32_t m_pid;                    // 进程号
        int32_t m_thread_id;                 // 线程号

        LogLevel m_level;          // 日志级别


    };


    

}





#endif