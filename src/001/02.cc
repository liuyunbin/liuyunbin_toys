
#include "log.h"

int main() {
    log("测试僵尸进程");
    log("测试父进程未正确处理子进程退出的状态信息");
    log();

    log("设置 SIGCHLD 处理为: 调用 waitpid() 一次");
    set_signal(handle_signal_2);

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
            log("第 " + std::to_string(i) + " 个子进程启动后退出");
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
    log("此时, 子进程的状态");
    system(cmd.data());

    log();
    log("主进程退出");

    return 0;
}