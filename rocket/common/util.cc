#include "rocket/common/util.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>


namespace rocket{

    static int g_pid = 0;

    static thread_local int g_thread_id = 0;

    pid_t getPid(){                                // 获取进程
        if(g_pid != 0){
            return g_pid;
        }

        return g_pid;
    }


    pid_t getThread_id(){                         // 获取线程
        if(g_thread_id != 0){
            return g_thread_id;
        }

        return syscall(SYS_gettid);
    }


}