
#include "log.h"

int main() {
    log("测试不可被信号打断的休眠(指被捕获的信号) 对 SIGSTOP 的处理");
    log();
    pid_t fd = fork();
    std::string cmd = "ps -o pid,state,comm -p " + std::to_string(fd);
    if (fd == 0) {
        if (vfork() == 0) {
            log("子进程启动");
            log("子进程休眠10秒");
            sleep(10);
            log("子进程休眠完成");
            log("子进程退出");
            exit(-1);
        }
        log("父进程休眠1s");
        sleep(1);
        log("父进程退出");
        exit(-1);
    } else {
        sleep(1);
        log("子进程状态");
        system(cmd.data());
        log("发送信号 SIGSTOP");
        kill(fd, SIGSTOP);
        log("子进程状态");
        system(cmd.data());
        log("发送信号 SIGCONT");
        kill(fd, SIGCONT);
        log("子进程状态");
        system(cmd.data());
        wait(NULL);
    }

    log();
    log("主进程正常退出");

    return 0;
}
