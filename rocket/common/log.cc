#include "rocket/common/log.h"
#include <sys/time.h>
#include "rocket/common/util.h"
#include <sstream>
#include <stdio.h>



namespace rocket{

static Logger* g_logger = nullptr;


Logger* Logger :: GetGlobalLogger(){
    if(g_logger){
        return g_logger;
    }

    return new Logger;
}

std :: string LogLevelToString(LogLevel level){
    switch(level){
        case Debug:
            return "Debug";

        case Info:
            return "Info";

        case Error:
            return "Error";
    
        default:
            return "UNKNOWN";
    }
}




std :: string LogEvent :: toString(){
    struct timeval now_time;

    gettimeofday(&now_time, nullptr);

    struct tm now_time_t;

    localtime_r(&(now_time.tv_sec), &now_time_t);

    char buf[128];
    strftime(&buf[0], 128, "%y-%m-%d %H:%M:%S", &now_time_t);;

    std :: string time_str(buf);   // 日期和时间

    int ms = now_time.tv_usec / 1000;      // 微秒乘以1000得到ms
    time_str = time_str + "." + std :: to_string(ms);



    // 进程，线程
    m_pid = getPid();
    m_thread_id = getThread_id();



    std :: stringstream ss;

    ss << "[" << LogLevelToString(m_level) << "]\t"
       << "[" << time_str << "]\t"
       << "[" << m_pid << m_thread_id << "]\t";

    return ss.str();
 
}


void Logger :: pushLog(const std :: string& msg){
    m_buffer.push(msg); 
 }


void Logger :: log(){
    while(!m_buffer.empty()){
        std :: string msg = m_buffer.front();
        m_buffer.pop();

        printf(msg.c_str());
    }
}



}