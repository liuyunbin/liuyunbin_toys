
#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获来自 " + std::to_string(sig_info->si_pid) + " 的信号 " + m[sig]);
}

int main() {
    log();
    log("操作系统-信号-优先级");
    log();

    log("注册所有的信号处理");
    struct sigaction act;
    act.sa_sigaction = handle_signal;

    log("设置信号处理过程中阻塞所有信号");
    sigfillset(&act.sa_mask);
    act.sa_flags = SA_RESTART | SA_SIGINFO;
    for (auto key : m) {
        sigaction(key.first, &act, NULL);
    }

    log("阻塞所有信号");
    sigset_t mask;
    sigfillset(&mask);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    log("发送除 " + m[SIGKILL] + " 和 " + m[SIGSTOP] + " 外的所有信号");

    for (auto key : m)
        if (key.first != SIGKILL && key.first != SIGSTOP)
            kill(getpid(), key.first);

    log("解除信号阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);

    sleep(1);

    log();
    log("主进程正常退出");
    log();
    return 0;
}