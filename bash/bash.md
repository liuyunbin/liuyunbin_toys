
${v:-w}              # v 不为空, 返回 $v, 否则, 返回 w
${v:=w}              # v 不为空, 返回 $v, 否则, 令 v=w, 返回 w
${v:+w}              # v 不为空, 返回  w, 否则, 返回空
${v:?w}              # v 不为空, 返回 $v, 否则, 输出 w, 退出
${#val}              # 输出字符串的长度
${val:起始位置:长度} # 获取子串
lyb=123
lyb=$lyb+123         # 字符串连接, lyb 将变成 123+123
lyb=123.456.txt
lyb=${lyb%.*}        # 后缀非贪婪匹配, lyb 为 123.456
lyb=${lyb%%.*}       # 后缀  贪婪匹配, lyb 为 123
lyb=${lyb#*.}        # 前缀非贪婪匹配, lyb 为 456.txt
lyb=${lyb##*.}       # 前缀  贪婪匹配, lyb 为 txt
lyb=${lyb/*./str}    # 全文  贪婪匹配, lyb 为 strtxt, 匹配一次
lyb=${lyb//*./str}   # 全文  贪婪匹配, lyb 为 strtxt, 匹配多次
lyb=${lyb^^}         # 变为大写
lyb=${lyb,,}         # 变为小写

## 括号 -- 只列举常用的情况
* 使用 [[ ... ]] 测试
    * [[     -z "$lyb"   ]] # 判断是否空字符串
    * [[     -n "$lyb"   ]] # 判断是否不是空字符串
    * [[ !   -n "$lyb"   ]] # 非操作
    * [[ "111" =~ 1{1,3} ]] # 右侧使用 扩展的正则表达式匹配
    * [[ "111" == 1*     ]] # 右侧使用 通配符
* cat <(ls)                 # 将命令或函数的输出作为文件

函数内建议使用 local 局部变量, 声明和使用放到不同的行

## 常用命令
!!    # 上一条命令
!l    # 执行最近使用的以 l 打头的命令
!l:p  # 输出最近使用的以 l 打头的命令
!num  # 执行历史命令列表的第 num 条命令
!$    # 上一条命令的最后一个参数
!*    # 上一条命令的所有参数
^1^2  # 将前一条命令中的 1 变成 2

read name     # 读取, 如果参数值小于字段数, 多余的值放入最后一个字段

## 常用快捷键
Ctrl+A      # 将光标移到行首
Ctrl+B      # 将光标向左移动一个字符
Ctrl+C      # 向前台进程组发送 SIGINT, 默认终止进程
Ctrl+D      # 删除光标前的字符 或 产生 EOF 或 退出终端
Ctrl+E      # 将光标移到行尾
Ctrl+F      # 将光标向右移动一个字符
Ctrl+G      # 响铃
Ctrl+H      # 删除光标前的一个字符
Ctrl+I      # 相当于TAB
Ctrl+J      # 相当于回车
Ctrl+K      # 删除光标处到行尾的字符
Ctrl+L      # 清屏
Ctrl+M      # 相当于回车
Ctrl+N      # 查看历史命令中的下一条命令
Ctrl+O      # 类似回车，但是会显示下一行历史
Ctrl+P      # 查看历史命令中的上一条命令
Ctrl+Q      # 解锁终端
Ctrl+R      # 历史命令反向搜索, 使用 Ctrl+G 退出搜索
Ctrl+S      # 锁定终端 -- TODO 历史命令正向搜索, 使用 Ctrl+G 退出搜索
Ctrl+T      # 交换前后两个字符
Ctrl+U      # 删除光标处到行首的字符
Ctrl+V      # 输入控制字符
Ctrl+W      # 删除光标左边的一个单词
Ctrl+X      #   TODO-列出可能的补全 ?
Ctrl+Y      # 粘贴被删除的字符
Ctrl+Z      # 前台运行的程序 --> 后台暂停
Ctrl+/      # 撤销之前的操作
Ctrl+\      # 产生 SIGQUIT, 默认杀死进程, 并生成 core 文件
Ctrl+xx     # 光标和行首来回切换

Esc+B              # 移动到当前单词的开头(左边)
Esc+F              # 移动到当前单词的结尾(右边)
Esc+.              # 获取上一条命令的最后的部分

Alt+B              # 向后（左边）移动一个单词
Alt+C              # 光标处字符转为大写
Alt+D              # 删除光标后（右边）一个单词
Alt+F              # 向前（右边）移动一个单词
Alt+L              # 光标处到行尾转为小写
Alt+R              # 取消变更
Alt+T              # 交换光标两侧的单词
Alt+U              # 光标处到行尾转为大写
Alt+BACKSPACE      # 删除光标前面一个单词，类似 Ctrl+W，但不影响剪贴板
Alt+.              # 使用上条命令的最后一个单词


bc <<< "scale=2; 10/2" # 使用两位小数,   输出: 5.00
bc <<< "ibase=2;  100" # 输入使用二进制, 输出: 4
bc <<< "obase=2;   10" # 输出使用二进制, 输出: 1010

dd if=/dev/zero bs=1M count=1000 | nc 127.0.0.1 9999 # 测速-客户端

iconv -f gbk -t utf-8 1.txt -o 1.txt

uptime -s # 列出系统启动时间

wget www.google.com
wget www.google.com -O 1.html                 # 指定目标文件名称
wget www.google.com -o 1.log                  # 指定日志文件
wget www.google.com -c                        # 断点续传
wget www.google.com -t 3                      # 指定重试的次数, 0 不停的尝试
wget www.google.com --limit-rate 10k          # 限速
wget www.google.com --quota 100M              # 限制最大下载量
wget www.google.com --mirror --convert-links  # 镜像下载, 递归, 并转换为本地 url
wget www.google.com --user ... --password ... # 指定用户名和密码

curl www.google.com
curl www.google.com -o 1.html                   # 指定目标文件名称
curl www.google.com --silent                    # 不显示进度信息
curl www.google.com -C -                        # 断点续传
curl www.google.com --referer http://google.com # 指定跳转前的界面
curl www.google.com --cookie ...                # 指定 cookie
curl www.google.com --user-agent "Mozilla/5.0"  # 设置浏览器信息
curl www.google.com -H ...                      # 指定其他header
curl www.google.com --limit-rate 20k            # 限速
curl www.google.com --max-filesize 100M         # 设置最大大小
curl www.google.com -u user:pass                # 设置用户名和密码
curl www.google.com --head                      # 只打印响应头部
curl 127.0.0.1/test -X POST -H "Content-Type: application/json" -d '{}" # 发送 POST 请求, 数据为 JSON

docker run ubuntu:15.10 -d --name "lyb"           # 启动 docker, 给起一个名字
docker run ubuntu:15.10 -d --net=host             # 主机和 docker 共享 IP 和 端口号
docker run ubuntu:15.10 -d -P                     # docke 内使用随机端口映射主机端口
docker run ubuntu:15.10 -d -p 2000:3000           # 本机:2000 绑定 docker:3000
docker run ubuntu:15.10 -d -v /home/123:/home/456 # 本机:/home/123 绑定 docker:/home/456

docker port     容器ID     # 查看端口号映射
docker ps                  # 列出当前运行的容器
docker ps -a               # 列出所有容器
docker start    容器ID     # 启动容器
docker stop     容器ID     # 停止容器
docker restart  容器ID     # 重新启动容器
docker rm -f    容器ID     # 删除容器
docker exec     容器ID ls  # 对于在后台运行的容器, 执行命令

redis flushdb # 清空数据
redis -c ...  # 集群时需要使用 -c 启动, 否则查不到数据

systemctl -a                 # 查看所有启动的服务
systemctl start      nginx   # 启动 nginx
systemctl stop       nginx   # 停止 nginx
systemctl restart    nginx   # 重启 nginx
systemctl status     nginx   # 查看 nginx 状态
systemctl enable     nginx   # 开机自动启动 nginx
systemctl disable    nginx   # 开机禁止启动 nginx
systemctl is-active  nginx   # 查看 nginx 是否启动成功
systemctl is-failed  nginx   # 查看 nginx 是否启动失败
systemctl is-enabled nginx   # 查看 nginx 是否开机启动

                                        # 注意, 有不同版本的 nc, 参数不一定相同
nc -l             8080                  # 服务端(tcp), 接收单个连接
nc -lk            8080                  # 服务端(tcp), 接收多个连接
nc -lv            8080                  # 服务端(tcp), 显示连接信息
nc -lu            8080                  # 服务端(udp)
nc      127.0.0.1 8080                  # 客户端(tcp)
nc -n   127.0.0.1 8080                  # 客户端(tcp), 不进行域名解析, 节省时间
nc -N   127.0.0.1 8080                  # 客户端(tcp), 收到 EOF 后, 退出(有的版本不需要此参数, 会自动退出)
nc -w 3 127.0.0.1 8080                  # 客户端(tcp), 设置超时时间
nc -vz  127.0.0.1 8080                  # 客户端(tcp), 不发送信息, 只显示连接信息(测试单个端口)
nc -vz  127.0.0.1 8080-8090             # 客户端(tcp), 不发送信息, 只显示连接信息(测试多个端口)
nc -u   127.0.0.1 8080                  # 客户端(udp)
nc -lk            8080 | pv > /dev/null # 测速-服务端, 注意重定向, 否则会受限于终端的写速率
nc      127.0.0.1 8080      < /dev/zero # 测试-客户端

nmap             127.0.0.1 # 主机发现 -> 端口扫描, 默认扫描 1000 个端口
nmap -p  80      127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80-85   127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80,8080 127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -Pn         127.0.0.1 # 跳过主机发现, 直接端口扫描
nmap -sn         127.0.0.1 # 主机发现

                              # 使用 iperf 测试的时候需要关掉防火墙: sudo systemctl stop firewalld
iperf -s                      # 服务器(TCP), 端口号为 5001
iperf -s -p 8080              # 服务器(TCP), 端口号为 8080
iperf -s -f MB                # 服务器(TCP), 端口号为 5001, 设置输出的单位
iperf -s -i 10                # 服务器(TCP), 端口号为 5001, 设置报告的时间间隔为 10s
iperf -s -D                   # 服务器(TCP), 端口号为 5001, 服务器在后台启动
iperf -s -1                   # 服务器(TCP), 端口号为 5001, 只接受一个客户端
iperf -s -N                   # 服务器(TCP), 端口号为 5001, 使用 TCP nodelay 算法
iperf -s -u                   # 服务器(UDP), 端口号为 5001
iperf -c 127.0.0.1            # 客户端(TCP), 服务器端口号为 5001
iperf -c 127.0.0.1 -p 8080    # 客户端(TCP), 服务器端口号为 8080
iperf -c 127.0.0.1 -i 1       # 客户端(TCP), 服务器端口号为 5001, 设置报告的时间间隔为 1s
iperf -c 127.0.0.1 -t 10      # 客户端(TCP), 服务器端口号为 5001, 设置测试时间为 10s
iperf -c 127.0.0.1 -f MB      # 客户端(TCP), 服务器端口号为 5001, 设置输出的单位
iperf -c 127.0.0.1 -b 100M    # 客户端(TCP), 服务器端口号为 5001, 设置发送速率
iperf -c 127.0.0.1 -n 100M    # 客户端(TCP), 服务器端口号为 5001, 设置测试的数据的大小
iperf -c 127.0.0.1 -k 100M    # 客户端(TCP), 服务器端口号为 5001, 设置测试的数据包的数量
iperf -c 127.0.0.1 -R         # 客户端(TCP), 服务器端口号为 5001, 反向测试, 服务端连客户端
iperf -c 127.0.0.1         -d # 客户端(TCP), 客户端连服务端的同时, 服务端同时连客户端, 端口号为 5001
iperf -c 127.0.0.1 -L 9090 -d # 客户端(TCP), 客户端连服务端的同时, 服务端同时连客户端, 端口号为 9090
iperf -c 127.0.0.1         -r # 客户端(TCP), 客户端连服务端结束后, 服务端连回客户端,   端口号为 5001
iperf -c 127.0.0.1 -L 9090 -r # 客户端(TCP), 客户端连服务端结束后, 服务端连回客户端,   端口号为 9090
iperf -c 127.0.0.1 -P 30      # 客户端(TCP), 客户端线程数为 30
iperf -c 127.0.0.1 -u         # 客户端(UDP)

firewall-cmd --list-ports                      # 查看所有打开的端口
firewall-cmd --list-services                   # 查看所有打开的服务
firewall-cmd --get-services                    # 查看所有的服务
firewall-cmd --reload                          # 重新加载配置
firewall-cmd --complete-reload                 # 重启服务
firewall-cmd --permanent --add-service=http    # 添加服务, 永久生效, 需要重新加载配置
firewall-cmd             --remove-service=http # 移除服务
firewall-cmd --permanent --add-port=80/tcp     # 添加端口, 永久生效, 需要重新加载配置
firewall-cmd             --remove-port=80/tcp  # 移除端口
firewall-cmd             --query-masquerade    # 检查是否允许伪装IP
firewall-cmd --permanent   --add-masquerade    # 允许防火墙伪装IP, 永久生效, 需要重新加载配置
firewall-cmd            --remove-masquerade    # 禁止防火墙伪装IP
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                               # 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080 --permanent
                                               # 端口转发, 永久生效, 需要重新加载配置
firewall-cmd --runtime-to-permanent            # 将当前防火墙的规则永久保存

ps -o pmem,rsz,vsz           # 内存百分比,内存,内存(含交换分区)
ps -o pcpu,c,bsdtime,cputime # cpu: 百分比,百分比整数,user+system,system
ps -o lstart,etime,etimes    # 启动时间,运行时间,运行时间(秒), 无法对 etimes 进行排序

top     # 第一行 系统时间 运行时间 用户数 平均负载
        # 第二行 进程总结
        # 第三行 CPU 总结
        # 第四行 物理内存总结
        # 第五行 虚拟内存总结
        # 交互命令
        #   空格 或 回车 刷新
        #   l 切换负载的显示
        #   t 切换任务的显示
        #   m 切换内存的显示
        #   f 选择展示的字段
        #   R 反向排序
        #   c 显示命令名称 或 完整命令行
        #   i 显示空闲任务
        #   u 显示特定用户的进程
        #   k 结束任务
        #   h 帮助
        #   L 搜索字符串
        #   H 显示线程
        #   0 不显示统计值为 0 的项
        #   1   显示所有的cpu信息
        #   < 排序字段左移
        #   > 排序字段右移
        #   M 内存排序   --- 常用
        #   P CPU 排序   --- 常用
        #   T 时间排序   --- 常用
top -n 1   # 刷新次数
top -b     # 方便写入文件
top -c     # 显示完整命令行
top -p ... # 指定 PID
top -u lyb # 指定用户

unzip    1.zip -d ... # 解压缩到指定目录
unzip -j 1.zip        # 解压时, 文件都移到顶层路径
unzip -o 1.zip        # 解压时, 直接覆盖重复的文件, 不提醒
unzip -n 1.zip        # 解压时,   不覆盖重复的文件
unzip -l 1.zip        # 列出 1.zip 的目录结构, 简单
unzip -v 1.zip        # 列出 1.zip 的目录结构, 详细点

unrar    v 1.rar          # 列出压缩包信息, 详细
unrar    l 1.rar          # 列出压缩包信息, 简易
unrar    l 1.rar ...      # 列出压缩包内的指定文件或目录
unrar    e 1.rar ...      # 解压缩到指定路径, 忽略压缩包内的路径
unrar    x 1.rar ...      # 解压缩到指定路径, 使用完整的压缩包路径
unrar    x 1.rar ... ...  # 解压缩到指定路径, 使用完整的压缩包路径, 只解压部分文件

tcpdump -nn -i any host 127.0.0.1 and port 9999 -w 1.pcap

passwd -stdin     # 修改 root 密码, 从标准输入读取

sudo -u USERNAME COMMAND                      # 指定用户执行命令
sudo -S date -s "20210722 10:10:10" <<< "123" # 脚本中免密码使用

ntpdate -s time-b.nist.gov # 使用时间服务器更新时间
