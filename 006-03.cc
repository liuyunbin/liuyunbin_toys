
#include "log.h"

void test(pid_t pid, pid_t pgid) {
    log();

    std::string msg;

    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);

    msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid));
    msg += " => ";
    msg += std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);

    msg.clear();
    msg += "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);

    log();
}

int main() {
    log();
    log("测试新建子进程对应的进程组(子进程属于不同的会话)");
    log();

    pid_t child = fork();
    if (child == 0) {
        log("子进程新建会话");
        setsid();
        for (;;)
            ;
    }
    sleep(1);
    log("父进程会话: " + std::to_string(getsid(getpid())));
    log("子进程会话: " + std::to_string(getsid(child)));
    log("新建子进程(" + std::to_string(child) + ")的进程组");
    test(child, child);
    kill(child, SIGKILL);

    sleep(1);
    log("主进程退出");
    log();

    return 0;
}
