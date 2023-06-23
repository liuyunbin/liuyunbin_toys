
#include "log.h"

jmp_buf buf;

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 ", sig_info->si_pid, " 的信号 SIGABRT");
    longjmp(buf, 1);
}

int main() {
    log();
    log("操作系统-信号");
    log("测试信号 SIGABRT 处理为 捕获信号不返回");
    log();

    log("设置 SIGABRT 处理为 捕获信号不返回");
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_sigaction = handle_signal;
    act.sa_flags     = SA_SIGINFO;
    sigaction(SIGABRT, &act, NULL);

    if (setjmp(buf) == 0) {
        log("调用 abort()");
        abort();
    }

    log();
    log("主进程正常退出");
    log();
    return 0;
}