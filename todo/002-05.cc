
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "log.h"

void handle_signal(int sig, siginfo_t* sig_info, void*) {
    log("捕获信号 SIGCHLD 来自: ", sig_info->si_pid);
}

int main() {
    log();
    log("计算机操作系统-僵尸进程");
    log("预防僵尸进程的产生: 设置 SIGCHLD 选项为 SA_NOCLDWAIT");
    log();

    log("设置 SIGCHLD 的信号选项: SA_NOCLDWAIT");
    struct sigaction act;
    act.sa_sigaction = handle_signal;
    act.sa_flags     = SA_SIGINFO | SA_NOCLDWAIT;
    sigemptyset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

    log("阻塞信号 SIGCHLD");
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    std::string cmd = "ps -o pid,comm,state -p ";

    for (int i = 1; i <= 5; ++i) {
        pid_t fd = fork();
        if (fd == 0) {
            // 子进程
            log("子进程启动后退出: ", getpid());
            exit(-1);
        } else {
            // 父进程
            cmd += std::to_string(fd) + ",";
            sleep(1);
        }
    }

    cmd.pop_back();  // 删除多余的逗号

    log("解除信号 SIGCHLD 的阻塞");
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    sleep(1);
    log("子进程的状态");
    system(cmd.data());

    log();
    log("主进程正常退出");
    log();
    return 0;
}