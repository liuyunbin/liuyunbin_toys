
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void log(const std::string& msg = "") {
    std::cout << "进程(" << getpid() << "): " << msg << std::endl;
}

void log(pid_t pid) {
    std::string msg = "进程 " + std::to_string(pid);
    msg += " 进程组 " + std::to_string(getpgid(pid));
    msg += " 会话 " + std::to_string(getsid(pid));
    log(msg);
}

void test(pid_t pid, pid_t pgid) {
    log(pid);
    std::string msg = "修改进程组 ";
    msg += std::to_string(getpgid(pid));
    msg += " => ";
    msg += std::to_string(pgid);
    if (setpgid(pid, pgid) < 0) {
        msg += ": ";
        msg += strerror(errno);
    }
    log(msg);
    log(pid);
}

int main() {
    log("测试新建孙进程对应的进程组");
    log();

    int pipefd[2];
    pipe(pipefd);
    pid_t child = fork();
    if (child == 0) {
        pid_t grandchild = fork();

        if (grandchild == 0) {
            // 测试的孙进程
            close(pipefd[0]);
            close(pipefd[1]);
            for (;;)
                ;
        } else {
            // 测试的子进程
            close(pipefd[0]);
            std::string str = std::to_string(grandchild);
            write(pipefd[1], str.data(), str.size());
            close(pipefd[1]);
            for (;;)
                ;
        }
    } else {
        // 测试的父进程
        close(pipefd[1]);

        char ch;
        std::string str;

        while (read(pipefd[0], &ch, 1) > 0) str.push_back(ch);
        pid_t grandchild = atoi(str.data());

        log("进程关系");
        std::string cmd = "ps -o pid,ppid,comm -C a.out";
        system(cmd.data());
        log("修改孙进程(" + str + ")的进程组");
        test(grandchild, grandchild);

        kill(child, SIGKILL);
        kill(grandchild, SIGKILL);
    }

    log();
    log("主进程退出");

    return 0;
}