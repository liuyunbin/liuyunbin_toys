
#include "00.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

int main() {
    init();

    log();
    log("测试信号");
    log();

    log("注册所有信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO | SA_NOCLDSTOP | SA_NOCLDWAIT | SA_RESTART;
    for (auto key : m) sigaction(key.first, &act, NULL);

    log("主进程死循环");
    for (;;)
        ;

    log("主进程退出");
    log();

    return 0;
}
