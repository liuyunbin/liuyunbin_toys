
# 编译
```
./install-dependency.sh
./build.sh
```

# 目录

* [操作系统-僵尸进程](./001-00.md)
* [操作系统-孤儿进程](./002-00.md)
* [操作系统-孤儿进程组](./003-00.md)
* [操作系统-信号](./004-00.md)
* [操作系统-进程](./005-00.md)
* [操作系统-进程组](./006-00.md)
* [操作系统-会话](./007-00.md)
* [操作系统-用户和组](./008-00.md)
* [操作系统-打包和压缩](./009-00.md)
* [操作系统-软件安装](./010-00.md)
* [操作系统-日期和时间](./011-00.md)
* [操作系统-正则表达式](./012-00.md)
* [操作系统-文件和文本](./013-00.md)
* [计算机组成原理-整数-浮点数-字符](./101-00.md)


# 计算机网络-内网穿透
指的是位于 NAT 之后的机器, 相互连接的问题(P2P)

## NAT 用途
* 子网机器 => NAT => 互联网或其他网络
* 可以解决 IPv4 地址短缺的问题(使用一个IP地址可以让子网内的用户都可以上网)
* 可以使得访问更安全(通过 NAT 过滤)

## NAT 类型
### 基础NAT(只修改 IP)(基本不用)
### NAPT(修改IP和端口号)
* 完全圆锥形NAT(Full cone NAT)
    1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
    2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
    3. 任何外网机器的任何端口号都可通过NAT(D:X1)向内网机器(A:X)发送数据(任意IP, 任意端口号)
* 受限圆锥形NAT(Address-Restricted cone NAT)
    1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
    2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
    3. 外网机器(B)的任何端口号都可通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 任意端口号)
* 端口受限圆锥形NAT(port-Restricted cone NAT)
    1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
    2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
    3. 外网机器(B:Y)才可以通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 同端口号)
* 对称NAT(Symmetric NAT)
    1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
    2. 那么, 内网机器(A:X)通过NAT(D:X2)发送数据给公网机器(B:Z), X1 != X2 (IP 相同, 端口号不同)
    3. 那么, 内网机器(A:X)通过NAT(D:X3)发送数据给公网机器(C:Y), X1 != X3 (IP 不同, 端口号相同)
    4. 那么, 内网机器(A:X)通过NAT(D:X4)发送数据给公网机器(C:Z), X1 != X4 (IP 不同, 端口号不同)
    5. 外网机器(B:Y)才可以通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 同端口号)
    6. 外网机器(B:Z)才可以通过NAT(D:X2)向内网机器(A:X)发送数据(同IP, 同端口号)
    7. 外网机器(C:Y)才可以通过NAT(D:X3)向内网机器(A:X)发送数据(同IP, 同端口号)
    8. 外网机器(C:Z)才可以通过NAT(D:X4)向内网机器(A:X)发送数据(同IP, 同端口号)

## 检测NAT的类型(需要公网机器(B:Y), 公网机器(C:Z))
0. 内网机器(A:X)给公网机器(B:Y)发送数据
1. 公网机器(B:Y)返回内网机器(A:X)的地址: D:X1
2. 如果 D == A && X1 == X, 则为公网 IP
3. 否则, 公网机器(C:Z)通过NAT(D:X1)给内网机器(A:X)发送消息(IP和端口号都不同)
4. 如果内网机器(A:X)可以收到消息，则为 完全圆锥形 NAT
5. 否则, 公网机器(B:Z)通过NAT(D:X1)给内网机器(A:X)发送消息(IP相同, 端口号不同)
6. 如果内网机器(A:X)可以收到消息，则为 受限圆锥形 NAT
7. 否则, 内网机器(A:X)给公网机器(C:Z)发送数据
8. 公网机器(C:Z)返回内网机器的地址: D:X2
9. 如果 X1 == X2, 则为 端口受限圆锥形 NAT, 否则为对称 NAT

## P2P 通信
### 通过公共机器直接通信(不受任何NAT类型的限制, 但效率比较低, 会给服务器造成很大的消耗)
* 内网机器(A)与公网机器器(C)相连
* 内网机器(B)与公网机器器(C)相连
* 内网机器(A)将数据发给公网机器(C), 公网机器(C)再将数据发送给内网机器(B)
* 内网机器(B)将数据发给公网机器(C), 公网机器(C)再将数据发送给内网机器(A)

### 机器(A:X)和机器(B:Y)都是公网IP
两个机器可以直接相连

### 机器(A:X)或机器(B:Y)只有一个是公网IP
* 假设, 机器(A:X)有公网IP
* 通过 机器(B:Y) => NAT(E:Q) => 机器(A:X) 发送数据, 因为机器(A:X)为公网IP
* 此时 机器(A:X) => NAT(E:Q) => 机器(B:Y) 也通了

### 机器(A:X)和机器(B:Y)位于不同 NAT, 有一个公网机器(C:Y)
1. 机器(A:X)或机器(B:Y)所属的 NAT 为完全锥形 NAT
    * 假定机器(A:X)所属的 NAT 为完全锥形 NAT
    * 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
    * 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
    * 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送数据NAT(D:P)
    * 通过 机器(B:Y) => NAT(E:R) => NAT(D:P) => 机器(A:X) 发送数据(完全锥形 NAT)
    * 此时 机器(A:X) => NAT(D:P) => NAT(E:R) => 机器(B:Y) 也通了
2. 机器(A:X)或机器(B:Y)所属的 NAT 为受限锥形 NAT
    * 假定机器(A:X)所属的 NAT 为受限锥形 NAT
    * 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
    * 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
    * 通过 公网机器(C:Z) => NAT(D:P) => 机器(A:X) 发送数据NAT(E:Q)
    * 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送数据NAT(D:P)
    * 通过 机器(A:X) => NAT(D:P) => NAT(E:Q) 发送数据, 会被丢弃
        * 因为NAT(E:Q) 不知道数据要发往哪里
        * 但 NAT(E) => NAT(D:P) => 机器(A:X) 这条路已经通了,
        * 此时, NAT(E)的任何端口号都通过 NAT(D:P)=>机器(A:X) 发送数据(受限锥形 NAT)
    * 通过 机器(B:Y) => NAT(E:R) => NAT(D:P) => 机器(A:X) 发送数据, 会成功,
        * 因为NAT(E) => NAT(D:P) => 机器(A:X) 是通的
    * 此时, 机器(A:X) => NAT(D:P) => NAT(E:R) => 机器(B:Y) 也通了
3. 机器(A:X)和机器(B:Y)所属的 NAT 均为端口受限锥形 NAT
    * 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
    * 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
    * 通过 公网机器(C:Z) => NAT(D:P) => 机器(A:X) 发送数据NAT(E:Q)
    * 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送数据NAT(D:P)
    * 通过 机器(A:X) => NAT(D:P) => NAT(E:Q) 发送数据, 会被丢弃
        * 因为NAT(E:Q) 不知道数据要发往哪里
        * 但 NAT(E:Q) => NAT(D:P) => 机器(A:X) 这条路已经通了(端口受限锥形 NAT)
    * 通过 机器(B:Y) => NAT(E:Q) => NAT(D:P) => 机器(A:X) 发送数据, 会成功,
        * 因为机器NAT(E:Q) => NAT(D:P) => 机器(A:X) 是通的
    * 此时, 机器(A:X) => NAT(D:P) => NAT(E:Q) => 机器(B:Y)  也通了
4. 机器(A:X)和机器(B:Y)所属的 NAT 均为对称 NAT
    * 无法穿透
    * 可以考虑通过公网机器发送数据
5. 机器(A:X)和机器(B:Y)所属的 NAT 一个为对称 NAT，一个为端口受限的 NAT
    * 无法穿透
    * 可以考虑通过公网机器发送数据


# 计算机网络
## 基础知识
```
硬盘: 1T = 1000G = 1000 * 1000 * 1000 * 1000B = ... / 1024 / 1024 /1024 GB = 931GB
网卡: 1000M = 1000Mbps = 125MB (网速也一样)

  带宽: 网速, 上限由网卡控制
吞吐量: 有效数据的速度, 速度小于带宽
  延时: 客户端发送数据到收到数据的时差

kmg(1000), KMG(1024), B(字节), b(位)

## 网络接口层(帧)(以太网)
### 为什么不能去掉MAC(48位, 一般无法改变)
1. 网络协议分层, 不同层实现不同的功能, 交换机会使用其传递数据
2. 直接使用IP其实也可以, 这个就是历史原因了

### 集线器: 无脑转发数据到所有出口(很少使用了)
* 机器收到不是自己的数据将丢弃

### 交换机: 将指定数据直接发送到目标机器
* 利用MAC地址表发送数据到指定机器, 找不到时, 将发送数据给所有机器
* 到达的数据需要知道目标的MAC地址
* 机器数量过大时, 会很难处理

### 通过MAC可以区分是单播还是(组播或广播)

## 网络层(数据包)
###为什么不能去掉IP(32位)
1. 为了划分子网, 方便路由, 传送数据到子网

* 主机号都为 0 表明网络地址
* 主机号都为 1 表明广播地址
* 互联网上只能使用公有IP
* 子网: 由 IP 和子网掩码(主机号都为0)确定
* 默认网关: 用于路由
* ARP: IP => MAC (ARP 缓存表)

### ICMP(不使用端口号, 和 TCP UDP IGMP处于同一级)
* 传输控制协议
* ping 实现

IGMP

1.0.0.0~126.255.255.255   -- a类
128.0.0.0~191.255.255.255 -- b类
192.0.0.0~223.255.255.255 -- c类
224.0.0.0~239.255.255.255 -- 组播地址
240.0.0.0~255.255.255.254 -- 保留
10.0.0.0/8                -- a类私有
172.16.0.0/12             -- b类私有
192.168.0.0/16            -- c类私有
127.0.0.0/8               -- 本机使用
224.0.0.0/24              -- 本网络组播
239.0.0.0/8               -- 私有组播

0.0.0.0                   -- 使用 DHCP 获取 IP 时, 填的源 IP
255.255.255.255           -- 使用 DHCP 获取 IP 时, 填的目标 IP

路由器: 将指定数据直接发送到目标(可能需要再次转发)
* 利用路由表发送数据到指定机器, 找不到将发送到路由器的默认网关
* 到达的数据需要知道目标的 IP 地址

单播(一般的网络服务都是单播)
1. 源IP和目标IP属于同一个子网时, 利用arp获取目标的MAC, 然后利用交换机发送数据到指定机器
2. 否则, 利用arp获取默认网关的MAC, 然后利用交换机发送数据到默认网关
3. 默认网关会修改源MAC, 然后再查找下一跳或指定机器

数据传输过程中, 原 IP 和目标 IP 一般不变, 除了, NAT 等

组播(IGMP 直播 电视)
1. 组播源注册: 服务器(组播源IP)向中介机构(RP)注册组播IP(2.2.2.2)
2. 客户端向中介机构(RP)申请加入组播IP: 生成基于中介机构(RP)的树(RPT), 同时获取组播源IP
3. 客户端向服务器(组播源IP)申请加入组播IP: 生成基于源的树(SPT), 废弃掉 RPT(SPT路径更优)
4. 服务器通过SPT, 向所有的注册组播IP的用户发送数据
    * 源IP和MAC填自己的数据
    * 目的IP为组播地址
    * 目的MAC为: 01:00:5e + 组播IP 地址低 23 bit(区分单播 组播 广播)
    * 由于目的IP为组播IP, 无法获取确切的MAC, 指定某一机器, 所以只能采用广播向所有机器发送数据
5. 客户端或者路由器通过接收到的数据的组播地址来确定是不是自己所需要的数据

广播(ARP, 使用DHCP申请IP地址时)
利用集线器发送所有数据到当前网络的所有机器

任播: 最近或最合适的客户

### 传输层(段)(TCP UDP)
端口号(16位)
* [0, 1024)      公认端口号, 需要 root 启动, 比如 80
* [1024, 32768)  注册端口, 可以自己注册一些常用服务
* [32768, 60990) 动态端口, 进程未指定端口号时, 将从这个范围内获取一个端口号
                 可通过文件 /proc/sys/net/ipv4/ip_local_port_range 获取
* [60990, 65535) 可能有特殊用途

TCP 有广播和组播一说吗?

TCP
* 三次握手
    1. 客户端将随机的序列号发送给服务端(SYN)(CLOSED -> SYN-SENT)
    2. 服务端收到数据后, 知道了客户端的序列号
       服务端将自己随机的序列号以及客户端序列号加一返回给客户端(SYN ACK)(LISTEN -> SYN-RCVD)
    3. 客户端收到数据后, 认为连接已经建立成功了
       客户端将服务端的序列号加一发送给服务端(ACK)(SYN-SENT -> ESTABLISHED)
       此时客户端就可以发送数据了
    4. 服务端收到数据后, 认为连接已经建立成功了, 可以发送数据了(SYN-RCVD -> ESTABLISHED)
* 四次挥手(服务端也可以先发起)
    1. 客户端发送 FIN(ESTABLISHED -> FIN-WAIT-1)
    2. 服务端收到 FIN(ESTABLISHED -> CLOSE-WAIT
       服务端向客户端发送确认
       客户端收到确认(FIN-WAIT-1 -> FIN-WAIT-2)
       此时, 客户端不能再向服务端发送数据, 但服务端可以向客户端发送数据
    3. 服务端发送 FIN(CLOSE-WAIT -> LAST-ACK)
    4. 客户端收到 FIN(FIN-WAIT-2 -> TIME-WAIT)
       向服务端发送确认
       等待 2MSL, 客户端(TIME-WAIT -> CLOSED)
       (为了处理服务端可能收不到确认的情况, 也为了让游离在外的包尽可能消亡)
       服务端收到确认(LAST-ACK -> CLOSED)
* 为什么需要序列号(32位):
    * 数据包需要被确认, 而包可能会被拆, 需要使用序列号来判断确认到哪个数据包了
    * 数据包可能会丢失, 需要使用序列号来判断需要重发哪个数据包
    * 数据包可能会重复, 需要使用序列号来丢弃重复的数据包
    * 数据包到达的时间, 顺序可能不同, 需要使用序列号排序
* 初始序列号为什么随机生成:
    * 随机序列号很难猜测, 为了避免其他人冒充对方报文, 或 伪造reset报文, 影响正常的使用
    * 为了避免旧数据影响新连接, 例如
        客户端连接服务端
        客户端向服务端发送一个数据包(由于网络问题, 数据包发了两次, 有游离包在网络中)
        客户端向服务端发送 reset, 立刻退出(没有经过正常的四次挥手)
        此时, 客户端使用相同的IP和端口号重新连服务端, 并成功
        此时, 游离的包到达服务端,
        如果初始话序列号相同, 此游离包  在服务端的接收窗口内, 会被误认为是新的数据包, 而返回确认
        如果初始话序列号不同, 此游离包不在服务端的接收窗口内, 会被丢弃(极大概率)
* 序列号回绕:
    初始化序列号每4微妙增长一个, 即, 每秒增长 250000 个, 循环一次需要 4 个多小时
    远大于数据包的最大分段的时间(MSL)(一般两分钟)
    所以不会对数据造成影响, 而发送的数据大小不受序列号的限制
* 所有有数据的报文都需要ack, 也可能会重传
* 报文类型
    *   SYN: 三次握手(需要确认, 可能会重传)
    *   FIN: 四次挥手(需要确认, 可能会重传)
    *  data: 数据报文(需要确认, 可能会重传)
    * reset: 重置(不需要确认,   不会重传)(发送重置后, 内核会销毁掉所有的连接信息, 对方的确认没意义)
    *   ACK: 确认(不需要确认,   不会重传)(如果确认的话就死循环了)(不包含数据)(下一个期望的序列号)
    *   ACK: 确认(  需要确认, 可能会重传)(如果确认的话就死循环了)(  包含数据)(下一个期望的序列号)
* SYN 和 FIN 为什么占一个序列号: 为了处理可能的重传
* reset 发送场景:
    * 客户端连接服务端, 而服务端的此端口没有被监听, 会返回 rst
    * 客户端连接服务端, 被防火墙连接(不一定, 可能收到 ICMP 错误)
    * 当接收缓冲区内还有数据, 但关闭了改 socket, 会向对方发送 rst
    * 向已关闭的 socket 发送数据, 对方会返回 rst
* 为什么需要三次握手:
    1. 一次握手: 客户端发送连接, 即认为连接成功, 服务端收到连接, 即认为连接成功
                 由于客户端无法知道服务端的序列号, 也就没有序列号这一说了,
                 TCP 的包不能拆分了(无法确认数据包的先后), 也就没有确认机制了(无法确认),
                 直接相当于 UDP 了
    2. 两次握手: 客户端发送连接
                 服务端收到连接, 并返回确认, 此时, 服务端认为连接成功了
                 客户端收到确认, 认为连接成功了
                 * 如果客户端的连接包丢失了, 由于无法收到确认包, 所以会重新发送连接包
                 * 如果服务端的确认包丢失了, 服务端感知不到这种情况,
                     由于客户端接收不到确认包, 所以客户端仍然会重新发送连接包
                 * 旧的连接包会影响服务端的使用, 例如,
                        客户端连接服务端(由于网络问题, 连接包发了两次, 有一个游离包在网络中)
                        服务端返回确认
                        客户端收到确认, 向服务端发送 reset, 立刻退出(没有经过正常的四次挥手)
                        此时, 游离的包到达服务端, 服务端认为是新的连接, 向客户端发送确认
                        客户端收到子虚乌有的确认直接丢弃了
                        (客户端可以考虑发送 reset 让服务端释放资源也成, 客户端不存在或不可达也还是有问题)
                        服务端直到发送数据, 才能知道连接不成功(不发送的话, 一直浪费)
    3. 三次握手: 客户端发送连接
                 服务端收到连接, 并返回确认
                 客户端收到确认, 并返回确认, 认为连接成功了
                 服务端收到确认, 认为连接成功了
                 * 如果客户端的连接包丢失了, 由于无法收到确认包, 所以会重新发送
                 * 如果服务端的确认包丢失了, 由于无法收到确认包, 所以会重新发送
                 * 旧的连接包不会影响服务端的使用, 例如,
                        客户端连接服务端(由于网络问题, 连接包发了两次, 有一个游离包在网络中)
                        服务端返回确认
                        客户端收到确认, 向服务端发送 reset, 立刻退出(没有经过正常的四次挥手)
                        此时, 游离的包到达服务端, 服务端认为是新的连接, 向客户端发送确认
                        客户端收到子虚乌有的确认直接丢弃了(客户端也可以考虑发送 reset)
                        服务端没收到确认消息, 会多次发送, 最终放弃, 释放资源
    4. 其实, 两次握手也能成功, 兼顾效率和可靠性, 选择三次握手(主要是网络出问题的情况)
      * 三次握手保证双方都知道对方是可收可发的(保证是可用的, 不一定是可靠的)


UDP

### 应用层(消息)(HTTP DNS SSH DHCP)
DHCP(广播, UDP)
1. 新机器(IP: 0.0.0.0)发送信息给当前网络(IP: 255.255.255.255)的所有机器(不会跨网关)
2. 包含 DHCP 服务器的机器发送新的 IP 给新机器(IP: 255.255.255.255)
3. 新机器(IP: 新IP)发送确认信息给 DHCP 服务器

### 浏览器输入 https://www.bing.com 后的行为
1. 解析 www.bing.com. 找到域名 bing.com. 查找对应 IP, 顺序查找,
    * DNS cache
    * 本地 host 文件
    * DNS 服务器(8.8.8.8, 找不到的话, 会递归查找, 直到根域名服务器)
2. 使用目标 IP 和端口号三次握手
3. TLS 商讨密钥的方案
4.

### 防火墙
包过滤防火墙: 过滤某些不必要的流量, 依靠 IP 端口号 协议类型(ICMP)
代理防火墙: http 代理
            socks 代理

真正的路由器应该只有路由的功能

### NAT(Network Address Translation)
主要目的是解决 IPv4 地址短缺的问题以及安全

分类
* 基础NAT: 只修改 IP
* NAPT: 修改IP和端口号
	1. 完全圆锥形NAT(Full cone NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
		3. 任何外网机器的任何端口号都可通过NAT(D:X1)向内网机器(A:X)发送数据(任意IP, 任意端口号)
	2. 受限圆锥形NAT(Address-Restricted cone NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
		3. 外网机器(B)的任何端口号都可通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 任意端口号)
	3. 端口受限圆锥形NAT(port-Restricted cone NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
		3. 外网机器(B:Y)才可以通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 同端口号)
	4. 对称NAT(Symmetric NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)通过NAT(D:X2)发送数据给公网机器(B:Z), X1 != X2 (IP 相同, 端口号不同)
		3. 那么, 内网机器(A:X)通过NAT(D:X3)发送数据给公网机器(C:Y), X1 != X3 (IP 不同, 端口号相同)
		4. 那么, 内网机器(A:X)通过NAT(D:X4)发送数据给公网机器(C:Z), X1 != X4 (IP 不同, 端口号不同)
		5. 外网机器(B:Y)可以通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 同端口号)
		6. 外网机器(B:Z)可以通过NAT(D:X2)向内网机器(A:X)发送数据(同IP, 同端口号)
		7. 外网机器(C:Y)可以通过NAT(D:X3)向内网机器(A:X)发送数据(同IP, 同端口号)
		8. 外网机器(C:Z)可以通过NAT(D:X4)向内网机器(A:X)发送数据(同IP, 同端口号)

检测NAT的类型
0. 内网机器(A:X)给公网机器(B:Y)发送数据
1. 公网机器(B:Y)返回内网机器(A:X)的地址: D:X1
2. 如果 D == A && X1 == X, 则为公网 IP
3. 否则, 公网机器(C:Z)通过NAT(D:X1)给内网机器(A:X)发送消息(IP和端口号都不同)
4. 如果内网机器(A:X)可以收到消息，则为 完全圆锥形 NAT，
5. 否则, 公网机器(B:Z)通过NAT(D:X1)给内网机器(A:X)发送消息(IP相同, 端口号不同)
6. 如果内网机器(A:X)可以收到消息，则为 受限圆锥形 NAT,
7. 否则, 内网机器(A:X)给公网机器(C:Z)发送数据
8. 公网机器(C:Z)返回内网机器的地址: D:X2
9. 如果 X1 == X2, 则为 端口受限圆锥形 NAT, 否则为对称 NAT

## p2p 通信
### 机器(A:X)和机器(B:Y)都是公网IP
两个机器可以直接相连

### 机器(A:X)或机器(B:Y)只有一个是公网IP
* 假设, 机器(A:X)有公网IP
* 通过 机器(B:Y) => NAT(E:Q) => 机器(A:X) 发送数据, 因为机器(A:X)为公网IP
* 此时 机器(A:X) => NAT(E:Q) => 机器(B:Y) 也通了

### 机器(A:X)和机器(B:Y)位于不同 NAT, 有一个公网机器(C:Y)
1. 机器(A:X)或机器(B:Y)所属的 NAT 为完全锥形 NAT
	* 假定机器(A:X)所属的 NAT 为完全锥形 NAT
	* 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
	* 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
	* 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送NAT(D:P)数据
	* 通过 机器(B:Y) => NAT(E:R) => NAT(D:P) => 机器(A:X) 发送数据(完全锥形 NAT)
	* 此时 机器(A:X) => NAT(D:P) => NAT(E:R) => 机器(B:Y) 也通了
2. 机器(A:X)或机器(B:Y)所属的 NAT 为受限锥形 NAT
	* 假定机器(A:X)所属的 NAT 为受限锥形 NAT
	* 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
	* 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
	* 通过 公网机器(C:Z) => NAT(D:P) => 机器(A:X) 发送NAT(E:Q)数据
	* 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送NAT(D:P)数据
	* 通过 机器(A:X) => NAT(D:P) => NAT(E:Q) => 机器(B:Y) 发送数据, 会失败
		* 因为机器(B:Y) => NAT(E:Q) => NAT(D:P) => 机器(A:X) 未发送过消息
		* 但 NAT(E) => NAT(D:P) => 机器(A:X) 这条路已经通了,
		* 此时, NAT(E)的任何端口号都通过 NAT(D:P)=>机器(A:X) 发送数据(受限锥形 NAT)
	* 通过 机器(B:Y) => NAT(E:R) => NAT(D:P) => 机器(A:X) 发送数据, 会成功,
		* 因为机器(A:X) => NAT(D:P) => NAT(E) 路是通的
	* 此时, 机器(A:X) => NAT(D:P) => NAT(E:R) => 机器(B:Y) 也通了
3. 机器(A:X)和机器(B:Y)所属的 NAT 均为端口受限锥形 NAT
	* 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
	* 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
	* 通过 公网机器(C:Z) => NAT(D:P) => 机器(A:X) 发送NAT(E:Q)数据
	* 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送NAT(D:P)数据
	* 通过 机器(A:X) => NAT(D:P) => NAT(E:Q) => 机器(B:Y) 发送数据, 会失败,
		* 因为机器(B:Y) => NAT(E:Q) => NAT(D:P) 未发送过消息
		* 但 NAT(E:Q) => NAT(D:P) => 机器(A:X) 这条路已经通了(端口受限锥形 NAT)
	* 通过 机器(B:Y) => NAT(E:Q) => NAT(D:P) => 机器(A:X) 发送数据, 会成功,
		* 因为机器NAT(E:Q) => NAT(D:P) => 机器(A:X) 是通的
	* 此时，机器(A:X) => NAT(D:P) => NAT(E:Q) => 机器(B:Y)  也通了
4. 机器(A:X)和机器(B:Y) 所属的 NAT 均为对称 NAT: 无法穿透
5. 机器(A:X)和机器(B:Y)所属的 NAT 一个为对称 NAT，一个为端口受限的 NAT: 无法穿透


p2p 通信(客户端(A)位于NAT(a)后, 客户端(B)位于NAT(b)后, 服务器(C)位于公网, 客户端(A)和客户端(B)要通信)
1. 通过服务器(c)直接通信:(不受任何NAT类型的限制, 但效率比较低, 会给服务器造成很大的消耗)(TCP)
	客户端(A)通过NAT(a)与服务器(C)相连
	客户端(B)通过NAT(b)与服务器(C)相连
	客户端(A)将数据发给服务器(C), 服务器(C)再将数据发送给客户端(B)
	客户端(B)将数据发给服务器(C), 服务器(C)再将数据发送给客户端(A)

UDP-打洞(客户端A位于局域网a, 客户端B位于局域网b, 服务器C位于公网, 客户端A和客户端B要通信)
1. 全锥形NAT

	假设, 内网机器(A:X), 公网机器(B:Y), 公网机器(C:Z)
如果内网机器(A:X)发送数据给公网机器(B:Y), 则映射的公网接口(D:X1)
如果内网机器(A:X)发送数据给公网机器(C:Z), 则映射的公网接口(D:X2)

## UDP hole punching
	### 方法
假设有两个客户 A:X B:Y 位于不同的 NAT 中，还有一个处于公网的服务器 C:Z

假设: X:x(私有) -> X1:x1(NAT) -> Y1:y1(公有)
此时, 如果, 新连接: X:x(私有) -> X2:x2(NAT) -> Y2:y2(公有)(X1 == X2)
1. 对于任何 Y1:y1 和 Y2:y2, X1:x1 都等于 X2:x2, 即: X:x 发向任何地址的数据都使用 NAT 的 X1:x1 (任何地址)
2. 如果 Y1 == Y2, 则 X1:x1 == X2:x2, 即: X:x 只有发往 Y1 的数据才使用 NAT 的 X1:x1 (IP 相同)
3. 如果 Y1:y1 == Y2:y2, 则 X1:x1 == X2:x2, 即: X:x 只有发往 Y1:y1 的数据才使用 NAT 的 X1:x1 (IP 和 端口号都相同)
此时, 如果, Y3:y3(私有) -> X1:x1(NAT) -> X:x(私有)
1. 对于任何 Y3:y3, 都可以发送成功(全锥形NAT)(任意)
2. 只要 Y3 == Y1, 就可以发送成功(受限圆锥形NAT)(IP相同)
3. 只有 Y3:y3 == Y1:y1, 才可以发送成功(端口受限圆锥形NAT)(IP和端口号都相同)
4.

链路层广播

MTU 最大传输单元 (链路层)

p2p

网络层:

traceroute: 查看数据包经过的路径

强主机模式: 数据包必须和对应网络接口对上
弱主机模式: 数据包和任一网络接口对上即可

## 常用命令
netstat  -- 已过时, 被 ss       替代
ifconfig -- 已过时, 被 ip addr  替代
route    -- 已过时, 被 ip route 替代

ip a                                 # 显示网卡信息
ip addr    show                      # 显示指定网卡信息
ip address show dev   lo             # 显示指定网卡信息
ip address add 192.268.1.10 dev eth0 # 添加 IP 地址
ip address del 192.268.1.10 dev eth0 # 删除 IP 地址

ip link set dev eth0 multicast on  # 启用组播
ip link set dev eth0 multicast off # 禁用组播
ip link set dev eth0 up            # 启用网卡
ip link set dev eth0 down          # 禁用网卡
ip link set dev eth0 arp       on  # 启用 arp 解析
ip link set dev eth0 arp       off # 禁用 arp 解析
ip link set dev eth0 mtu      1500 # 设置最大传输单元
ip link set dev eth0 address  ...  # 设置 MAC 地址

ip route       # 路由信息
ip route show  # 路由信息
ip route get   # 查看指定 IP 的路由信息
ip route add   # 添加路由
ip route chage # 修改路由
ip route flush # 清空路由信息

ip neighbour  # 查看 arp 协议

ip -s link         # 查看统计信息
ip -s link ls eth0 # 查看统计信息, 指定网卡

ip maddr  # 广播
ip rule   # 路由策略, 和网卡有关
ip tunnel # 隧道

firewall-cmd --list-ports                      # 查看所有打开的端口
firewall-cmd --list-services                   # 查看所有打开的服务
firewall-cmd --get-services                    # 查看所有的服务
firewall-cmd --reload                          # 重新加载配置
firewall-cmd --complete-reload                 # 重启服务
firewall-cmd             --add-service=http    # 添加服务
firewall-cmd --permanent --add-service=http    # 添加服务, 永久生效, 需要重新加载配置
firewall-cmd             --remove-service=http # 移除服务
firewall-cmd             --add-port=80/tcp     # 添加端口
firewall-cmd --permanent --add-port=80/tcp     # 添加端口, 永久生效, 需要重新加载配置
firewall-cmd             --remove-port=80/tcp  # 移除端口
firewall-cmd             --query-masquerade    # 检查是否允许伪装IP
firewall-cmd               --add-masquerade    # 允许防火墙伪装IP
firewall-cmd --permanent   --add-masquerade    # 允许防火墙伪装IP, 永久生效, 需要重新加载配置
firewall-cmd            --remove-masquerade    # 禁止防火墙伪装IP
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                               # 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080 --permanent
                                               # 端口转发, 永久生效, 需要重新加载配置
firewall-cmd --runtime-to-permanent            # 将当前防火墙的规则永久保存

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

lsof -i        :22 -sTCP:LISTEN -t # 监听端口号 22 的进程
lsof -i@1.2.3.4:22 -sTCP:LISTEN -t # 监听端口号 22 的进程, 指定 IP

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
dd if=/dev/zero bs=1M count=1000 | nc 127.0.0.1 9999 # 测速-客户端

nmap             127.0.0.1 # 主机发现 -> 端口扫描, 默认扫描 1000 个端口
nmap -p  80      127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80-85   127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -p  80,8080 127.0.0.1 # 主机发现 -> 端口扫描, 指定端口号
nmap -Pn         127.0.0.1 # 跳过主机发现, 直接端口扫描
nmap -sn         127.0.0.1 # 主机发现

ping      www.bing.com # 使用 ICMP ping 主机
ping -c 3 www.bing.com # 使用 ICMP ping 主机, 设置测试的次数
ping -i 3 www.bing.com # 使用 ICMP ping 主机, 设置间隔的秒数
ping -w 3 www.bing.com # 使用 ICMP ping 主机, 设置耗时的上限
ping -f   www.bing.com # 使用 ICMP ping 主机, 高速率极限测试, 需要 root 权限

ss       # 显示已连接的 UDP, TCP, unix domain sockets
ss -x    # unix domain sockets
ss -u    #          UDP
ss -t    # 已连接的 TCP
ss -tl   #   监听的 TCP
ss -ta   # 已连接和监听的 TCP
ss -tln  # 服务使用数字而不是名称
ss -tlnp # 列出监听的进程号, 需要root 权限
ss -s    # 显示统计
ss src   192.168.198.128:22  # 通过源  IP和端口号筛选信息
ss dst   192.168.198.1:51932 # 通过目的IP和端口号筛选信息
ss sport OP 22               # 通过源  端口号过滤数据
ss dport OP 22               # 通过目的端口号过滤数据
                             # OP 可以是空, >(gt) >=(ge) <(lt) <=(le) ==(eq) !=(ne), 注意转义

# 查询 域名 对应 的 IP
* nslookup baidu.com

curl -I ... # 只打印头部信息

## ssh
### 密钥登录
主目录权限不能是 777

### 常用命令
ssh -N -D A_PORT B_IP
            # 功能:
            #   动态端口转发
            #   将本地到 A_PORT 的请求转发到 B_IP
            #   使用 SOCKS5 协议
ssh -N -L A_PORT:C_IP:C_PORT B_IP
            # 功能:
            #   本地端口转发
            # 目标:
            #    A_IP:A_PORT --> C_IP:C_PORT
            # 现状:
            #    A_IP --> C_IP 失败
            #    B_IP --> C_IP 成功
            #    A_IP --> B_IP 成功
            #    B_IP --> A_IP 成功 或 失败都行
            # 实现:
            #   * 在 A_IP 机器上执行: ssh -N -L A_PORT:C_IP:C_PORT B_IP
            #   * 发往 A_IP 机器的端口号 A_PORT 的请求, 经由 B_IP 机器, 转发到 C_IP 机器的 C_PORT 端口
            #   * 即: A_IP:A_PORT --> B_IP --> C_IP:C_PORT
ssh -N -R A_PORT:C_IP:C_PORT A_IP
            # 功能:
            #   远程端口转发
            # 目标:
            #    A_IP:A_PORT --> C_IP:C_PORT
            # 现状:
            #    A_IP --> C_IP 失败
            #    B_IP --> C_IP 成功
            #    A_IP --> B_IP 成功 或 失败都行
            #    B_IP --> A_IP 成功
            # 实现:
            #   * 在 B_IP 机器上执行: ssh -N -R A_PORT:C_IP:C_PORT A_IP
            #   * 发往 A_IP 机器的端口号 A_PORT 的请求, 经由 B_IP 机器, 转发到 C_IP 机器的 C_PORT 端口
            #   * 即: A_IP:A_PORT --> B_IP --> C_IP:C_PORT
            #   * 如果要支持其他主机通过 A_IP 访问 C_IP, 需要在 A_IP 的 ssh 配置 GatewayPorts
ssh -N             # 不登录 shell, 只用于端口转发
ssh -p port        # 指定服务器端口号
ssh -f             # 在后台运行
ssh -t             # 开启交互式 shell
ssh -C             # 压缩数据
ssh -F             # 指定配置文件
ssh -q             # 不输出任何警告信息
ssh -l lyb 1.2.3.4
ssh        1.2.3.4
ssh    lyb@1.2.3.4
ssh -i ~/.ssh/id_rsa lyb # 指定私钥文件名

ssh-keygen -t rsa              # 指定密钥算法, 默认就是 rsa
ssh-keygen -b 1024             # 指定密钥的二进制位数
ssh-keygen -C username@host    # 指定注释
ssh-keygen -f lyb              # 指定密钥的文件
ssh-keygen -R username@host    # 将 username@host 的公钥移出 known_hosts 文件

ssh-copy-id -i ~/id_rsa username@host # 添加公钥到服务器中的 ~/.ssh/authorized_keys
                                      # -i 未指定时, 将使用 ~/.ssh/id_rsa.pub

#### ssh 客户端的常见配置: ~/.ssh/config, /etc/ssh/ssh_config, man ssh_config
Host *                          # 对所有机器都生效, 使用 通配符, 配置直到下一个 host
Host 123                        # 可以起一个别名
HostName 1.2.3.4                # 远程主机
Port 2222                       # 远程端口号
BindAddress 192.168.10.235      # 本地 IP
User lyb                        # 用户名
IdentityFile ~/.ssh/id.rsa      # 密钥文件
                                # 此时, 使用 ssh 123 相当于使用 ssh -p 2222 lyb@1.2.3.4
DynamicForward 1080             # 指定动态转发端口
LocalForward  1234 1.2.3.4:5678 # 指定本地端口转发
RemoteForward 1234 1.2.3.4:5678 # 指定远程端口转发

#### ssh 服务端的常见配置: /etc/ssh/sshd_config, man sshd_config
AllowTcpForwarding yes     # 是否允许端口转发, 默认允许
ListenAddress 1.2.3.4      # 监听地址
PasswordAuthentication     # 指定是否允许密码登录，默认值为 yes
Port 22                    # 监听端口号
GatewayPorts no            # 远程转发时, 是否允许其他主机使改端口号, 默认不允许

tcpdump 可选项 协议(tcp udp icmp ip arp) 源(src dst) 类型(host net port portrange) 值
* [S]: SYN(发起连接), [P]: push(发送), [F]:fin(结束), [R]: RST(重置), [.](确认或其他)
* ack 表示下一个要接收的 seq 号
* length 有效数据的长度
* win 接收窗口的大小
* 为避免shell干扰, 可将内容用引号包含
* and  or 可以组合多个条件

tcpdump -D                      # 列出可以 tcpdump 的网络接口
tcpdump -i eth0                 # 捕捉某一网络接口
tcpdump -i any                  # 捕捉所有网络接口
tcpdump -i any -c 20            # 捕捉所有网络接口, 限制包的数量
tcpdump -i any -n               # 捕捉所有网络接口, 使用IP和端口号, 而不是域名和服务名称
tcpdump -i any -w ...           # 捕捉所有网络接口, 将数据保存在文件中
tcpdump -i any -r ...           # 捕捉所有网络接口, 从文件中读取数据
tcpdump -i any -A               # 捕捉所有网络接口, 打印报文 ASCII
tcpdump -i any -x               # 捕捉所有网络接口, 打印包的头部, -xx -X -XX 类似
tcpdump -i any -e               # 捕捉所有网络接口, 输出包含数据链路层信息
tcpdump -i any -l               # 捕捉所有网络接口, 使用行缓存, 可用于管道
tcpdump -i any -N               # 捕捉所有网络接口, 不打印域名
tcpdump -i any -Q in            # 捕捉所有网络接口, 指定数据包的方向 in, out, inout
tcpdump -i any -q               # 捕捉所有网络接口, 简洁输出
tcpdump -i any -s ...           # 捕捉所有网络接口, 设置读取的报文长度,0 无限制
tcpdump -i any -S ...           # 捕捉所有网络接口, 使用绝对 seq
tcpdump -i any -v               # 捕捉所有网络接口, 显示详细信息, -vv -vvv 更详细
tcpdump -i any -t               # 捕捉所有网络接口, 不打印时间
tcpdump -i any -tt              # 捕捉所有网络接口, 发送(绝对时间), 确认(绝对时间)(时间戳)
tcpdump -i any -ttt             # 捕捉所有网络接口, 发送(相对时间), 确认(相对间隔)(时分秒 毫秒)
tcpdump -i any -tttt            # 捕捉所有网络接口, 发送(绝对时间), 确认(绝对时间)(年月日-时分秒)
tcpdump -i any -ttttt           # 捕捉所有网络接口, 发送(相对时间), 确认(相对时间)(时分秒 毫秒)
tcpdump -l                      # 使用行缓存, 可用于管道
tcpdump src  host 192.168.1.100 # 指定源地址 可以使用 /8 表明网络
tcpdump dst  host 192.168.1.100 # 指定目的地址
tcpdump      host 192.168.1.100 # 指定主机地址
tcpdump       net 192.168.1     # 指定网络地址, 也可以使用 /8 表示
tcpdump src  port 22            # 指定源端口号
tcpdump dst  port 22            # 指定目的端口号
tcpdump      port 22            # 指定端口号, 可使用服务名称
tcpdump not  port 22            # 排除端口号
tcpdump tcp                     # 指定协议
tcpdump "tcp[tcpflags] == tcp-syn" # 基于tcp的flag过滤
tcpdump less 32                 # 基于包大小过滤
tcpdump greater 64              # 基于包大小过滤
tcpdump ether   host  ...          # 基于 MAC 过滤
tcpdump gateway host ...          # 基于网关过滤
tcpdump ether broadcast      # 基于广播过滤
tcpdump ether multicast      # 基于多播过滤
tcpdump ip broadcast         # 基于广播过滤
tcpdump ip multicast         # 基于多播过滤



## 定期执行命令
crontab -l # 查询任务表
crontab -e # 编辑任务表
           # 格式为: 分钟 小时 日 月 星期 执行的程序
           # *     : 每分钟执行
           # 1-3   : 1 到 3分钟内执行
           # */3   : 每 3 分钟执行一次
           # 1-10/3: 1-10 分钟内, 每 3 分钟执行
           # 1,3,5 : 1,3,5 分钟执行
           # crontab 不会自动执行 .bashrc, 如果需要, 需要在脚本中手动执行
crontab -r # 删除任务表

## 系统
df   -Th    # 文件系统挂载情况
du   -sh .  # 目录整体大小
free -h     # 内存使用情况

ulimit              # 限制资源使用, 包括:
                    #   内存, 虚拟内存, CPU
                    #   进程数, 线程数
                    #   文件锁数, 文件描述符数, 写入文件大小
                    #   待处理的信号数
                    #   core 文件大小
                    # 也可指定是硬限制还是软限制
ulimit -a           # 列出资源的限制
ulimit -c unlimited # 允许 core 文件

uname -a # 全部信息
uname -m # x86_64 等
uname -r # 内核版本

uptime -s # 列出系统启动时间

rz          #  windows 向 虚拟机  发送数据
sz          #  虚拟机  向 windows 发送数据

systemctl start      nginx   # 启动 nginx
systemctl stop       nginx   # 停止 nginx
systemctl restart    nginx   # 重启 nginx
systemctl status     nginx   # 查看 nginx 状态
systemctl enable     nginx   # 开机自动启动 nginx
systemctl disable    nginx   # 开机禁止启动 nginx
systemctl is-active  nginx   # 查看 nginx 是否启动成功
systemctl is-failed  nginx   # 查看 nginx 是否启动失败
systemctl is-enabled nginx   # 查看 nginx 是否开机启动

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

## 网络
* [0, 1024)      公认端口号, 需要 root 启动, 比如 80
* [1024, 32768)  注册端口, 可以自己注册一些常用服务
* [32768, 60990) 动态端口, 进程未指定端口号时, 将从这个范围内获取一个端口号
                 可通过文件 /proc/sys/net/ipv4/ip_local_port_range 获取
* [60990, 65535)

netstat  -- 已过时, 被 ss       替代
ifconfig -- 已过时, 被 ip addr  替代
route    -- 已过时, 被 ip route 替代

ss       # 显示已连接的 UDP, TCP, unix domain sockets
ss -x    # unix domain sockets
ss -u    #          UDP
ss -t    # 已连接的 TCP
ss -tl   #   监听的 TCP
ss -ta   # 已连接和监听的 TCP
ss -tln  # 服务使用数字而不是名称
ss -tlnp # 列出监听的服务, 需要 root 权限
ss -s    # 显示统计
ss src   192.168.198.128:22  # 通过源  IP和端口号筛选信息
ss dst   192.168.198.1:51932 # 通过目的IP和端口号筛选信息
ss sport OP 22               # 通过源  端口号过滤数据
ss dport OP 22               # 通过目的端口号过滤数据
                             # OP 可以是空, >(gt) >=(ge) <(lt) <=(le) ==(eq) !=(ne), 注意转义

ip a                     # 显示网卡信息
ip addr    show          # 显示指定网卡信息
ip address show dev   lo # 显示指定网卡信息
ip address add 192.268.1.10 dev eth0 # 添加 IP 地址
ip address del 192.268.1.10 dev eth0 # 删除 IP 地址

ip link set dev eth0 multicast on  # 启用组播
ip link set dev eth0 multicast off # 禁用组播
ip link set dev eth0 up            # 启用网卡
ip link set dev eth0 down          # 禁用网卡
ip link set dev eth0 arp       on  # 启用 arp 解析
ip link set dev eth0 arp       off # 禁用 arp 解析
ip link set dev eth0 mtu      1500 # 设置最大传输单元
ip link set dev eth0 address  ...  # 设置 MAC 地址

ip route       # 路由信息
ip route show  # 路由信息
ip route get   # 查看指定 IP 的路由信息
ip route add   # 添加路由
ip route chage # 修改路由
ip route flush # 情况路由信息

ip neighbour  # 查看 arp 协议

ip -s link         # 查看统计信息
ip -s link ls eth0 # 查看统计信息, 指定网卡

ip maddr  # 广播
ip rule   # 路由策略, 和网卡有关
ip tunnel # 隧道

nc
                   # lsof -- sudo yum install lsof
lsof -iTCP         # 查看 TCP 信息
lsof -i :22        # 查看指定 端口号 的信息
lsof -i@1.2.3.4:22 # 查看是否连接到指定 IP 和 端口号上
lsof -p 1234       # 指定 进程号
lsof -d 0,1,2,3    # 指定 文件描述符
lsof -t            # 仅获取进程ID

# 查询 域名 对应 的 IP
* nslookup baidu.com

firewall-cmd --list-ports                       # 查看所有打开的端口
firewall-cmd --list-services                    # 查看所有打开的服务
firewall-cmd --get-services                     # 查看所有的服务
firewall-cmd --reload                           # 重新加载配置
firewall-cmd --complete-reload                  # 重启服务
firewall-cmd             --add-service=http     # 添加服务
firewall-cmd --permanent --add-service=http     # 添加服务, 永久生效, 需要重新加载配置
firewall-cmd             --remove-service=http  # 移除服务
firewall-cmd             --add-port=80/tcp      # 添加端口
firewall-cmd --permanent --add-port=80/tcp      # 添加端口, 永久生效, 需要重新加载配置
firewall-cmd             --remove-port=80/tcp   # 移除端口
firewall-cmd             --query-masquerade     # 检查是否允许伪装IP
firewall-cmd               --add-masquerade     # 允许防火墙伪装IP
firewall-cmd --permanent   --add-masquerade     # 允许防火墙伪装IP, 永久生效, 需要重新加载配置
firewall-cmd            --remove-masquerade     # 禁止防火墙伪装IP
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080
                                                # 端口转发, 0.0.0.0:80 --> 192.168.0.1:8080
firewall-cmd --add-forward-port=proto=80:proto=tcp:toaddr=192.168.0.1:toport=8080 --permanent
                                                # 端口转发, 永久生效, 需要重新加载配置
firewall-cmd --runtime-to-permanent             # 将当前防火墙的规则永久保存

curl -I ... # 只打印头部信息


防火墙:
包过滤防火墙: 过滤某些不必要的流量, 依靠 IP 端口号 协议类型(ICMP)
代理防火墙: http 代理
            socks 代理

真正的路由器应该只有路由的功能

# NAT
## NAT(Network Address Translation)
主要目的是解决 IPv4 地址短缺的问题

## 分类
* 基础NAT: 只修改 IP
* NAPT: 修改IP和端口号
	1. 完全圆锥形NAT(Full cone NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
		3. 任何外网机器的任何端口号都可通过NAT(D:X1)向内网机器(A:X)发送数据(任意IP, 任意端口号)
	2. 受限圆锥形NAT(Address-Restricted cone NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
		3. 外网机器(B)的任何端口号都可通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 任意端口号)
	3. 端口受限圆锥形NAT(port-Restricted cone NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)发往任何机器的任何端口号的数据都会通过NAT(D:X1)发送
		3. 外网机器(B:Y)才可以通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 同端口号)
	4. 对称NAT(Symmetric NAT)
		1. 如果内网机器(A:X)通过NAT(D:X1)发送数据给公网机器(B:Y)
		2. 那么, 内网机器(A:X)通过NAT(D:X2)发送数据给公网机器(B:Z), X1 != X2 (IP 相同, 端口号不同)
		3. 那么, 内网机器(A:X)通过NAT(D:X3)发送数据给公网机器(C:Y), X1 != X3 (IP 不同, 端口号相同)
		4. 那么, 内网机器(A:X)通过NAT(D:X4)发送数据给公网机器(C:Z), X1 != X4 (IP 不同, 端口号不同)
		5. 外网机器(B:Y)可以通过NAT(D:X1)向内网机器(A:X)发送数据(同IP, 同端口号)
		6. 外网机器(B:Z)可以通过NAT(D:X2)向内网机器(A:X)发送数据(同IP, 同端口号)
		7. 外网机器(C:Y)可以通过NAT(D:X3)向内网机器(A:X)发送数据(同IP, 同端口号)
		8. 外网机器(C:Z)可以通过NAT(D:X4)向内网机器(A:X)发送数据(同IP, 同端口号)

## 检测NAT的类型
0. 内网机器(A:X)给公网机器(B:Y)发送数据
1. 公网机器(B:Y)返回内网机器(A:X)的地址: D:X1
2. 如果 D == A && X1 == X, 则为公网 IP
3. 否则, 公网机器(C:Z)通过NAT(D:X1)给内网机器(A:X)发送消息(IP和端口号都不同)
4. 如果内网机器(A:X)可以收到消息，则为 完全圆锥形 NAT，
5. 否则, 公网机器(B:Z)通过NAT(D:X1)给内网机器(A:X)发送消息(IP相同, 端口号不同)
6. 如果内网机器(A:X)可以收到消息，则为 受限圆锥形 NAT，否则,
7. 内网机器(A:X)给公网机器(C:Z)发送数据
8. 公网机器(C:Z)返回内网机器的地址: D:X2
9. 如果 X1 == X2, 则为 端口受限圆锥形 NAT, 否则为对称 NAT

## p2p 通信
### 机器(A:X)和机器(B:Y)都是公网IP
两个机器可以直接相连

### 机器(A:X)或机器(B:Y)只有一个是公网IP
* 假设, 机器(A:X)有公网IP
* 由于, 机器(A:X)有公网IP, 所以机器(B:Y) => NAT(E:Q) => 机器(A:X) 可以发送数据
* 由于, 机器(B:Y) => NAT(E:Q) => 机器(A:X) 连接过, 所以, 机器(A:X) => NAT(E:Q) => 机器(B:Y) 也通了

### 机器(A:X)和机器(B:Y)位于不同 NAT, 有一个公网机器(C:Y)
1. 机器(A:X)或机器(B:Y)所属的 NAT 为完全锥形 NAT
	* 假定机器(A:X)所属的 NAT 为完全锥形 NAT
	* 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
	* 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
	* 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送NAT(D:P)数据
	* 此时 机器(B:Y) => NAT(E:R) => NAT(D:P) => 机器(A:X) 就通了(完全锥形 NAT)
	* 此时 机器(A:X) => NAT(D:P) => NAT(E:R) => 机器(B:Y) 也通了
2. 机器(A:X)或机器(B:Y)所属的 NAT 为受限锥形 NAT
	* 假定机器(A:X)所属的 NAT 为受限锥形 NAT
	* 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
	* 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
	* 通过 公网机器(C:Z) => NAT(D:P) => 机器(A:X) 发送NAT(E:Q)数据
	* 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送NAT(D:P)数据
	* 通过 机器(A:X) => NAT(D:P) => NAT(E:Q) => 机器(B:Y) 发送数据, 会失败
		* 因为机器(B:Y) => NAT(E:Q) => NAT(D:P) 未发送过消息
		* 但 NAT(E) => NAT(D:P) => 机器(A:X) 这条路已经通了,
		* 此时, NAT(E)的任何端口号都通过 NAT(D:P)=>机器(A:X) 发送数据(受限锥形 NAT)
	* 通过 机器(B:Y) => NAT(E:R) => NAT(D:P) => 机器(A:X) 发送数据, 会成功,
		* 因为机器(A:X) => NAT(D:P) => NAT(E) 路是通的
		* 此时, 机器(A:X) => NAT(D:P) => NAT(E:R) => 机器(B:Y) 也通了
3. 机器(A:X)和机器(B:Y)所属的 NAT 均为端口受限锥形 NAT
	* 通过 机器(A:X) => NAT(D:P) => 公网机器(C:Z) 发送数据
	* 通过 机器(B:Y) => NAT(E:Q) => 公网机器(C:Z) 发送数据
	* 通过 公网机器(C:Z) => NAT(D:P) => 机器(A:X) 发送NAT(E:Q)数据
	* 通过 公网机器(C:Z) => NAT(E:Q) => 机器(B:Y) 发送NAT(D:P)数据
	* 通过 机器(A:X) => NAT(D:P) => NAT(E:Q) => 机器(B:Y) 发送数据, 会失败,
		* 因为机器(B:Y) => NAT(E:Q) => NAT(D:P) 未发送过消息
		* 但 NAT(E:Q) => NAT(D:P) => 机器(A:X) 这条路已经通了(端口受限锥形 NAT)
	* 通过 机器(B:Y) => NAT(E:Q) => NAT(D:P) => 机器(A:X) 发送数据, 会成功,
		* 因为机器NAT(E:Q) => NAT(D:P) => 机器(A:X) 是通的
	* 此时，机器(A:X) => NAT(D:P) => NAT(E:Q) => 机器(B:Y)  也通了
4. 机器(A:X)和机器(B:Y) 所属的 NAT 均为对称 NAT: 无法穿透
5. 机器(A:X)和机器(B:Y)所属的 NAT 一个为对称 NAT，一个为端口受限的 NAT: 无法穿透


1. 客户 A:X 通过 D:P 多次发送数据给 C:Z
2. 客户 B:Y 通过 E:Q 多次发送数据给 C:Z
3. 服务器 C:Z 将 A:X 的映射的 D:P 多次发送给 B:Y
4. 服务器 C:Z 将 B:Y 的映射的 E:Q 多次发送给 A:X
5. 客户 A:X 多次发送数据给 E:Q
6. 在此之后，客户 B:Y   可以通过 E:Q --> D:P 给客户 A:X 发送消息
7. 在此之后，客户 A:X 也可以通过 D:P --> E:Q 给客户 B:Y 发送消息



p2p 通信(客户端(A)位于NAT(a)后, 客户端(B)位于NAT(b)后, 服务器(C)位于公网, 客户端(A)和客户端(B)要通信)
1. 通过服务器(c)直接通信:(不受任何NAT类型的限制, 但效率比较低, 会给服务器造成很大的消耗)(TCP)
	客户端(A)通过NAT(a)与服务器(C)相连
	客户端(B)通过NAT(b)与服务器(C)相连
	客户端(A)将数据发给服务器(C), 服务器(C)再将数据发送给客户端(B)
	客户端(B)将数据发给服务器(C), 服务器(C)再将数据发送给客户端(A)


UDP-打洞(客户端A位于局域网a, 客户端B位于局域网b, 服务器C位于公网, 客户端A和客户端B要通信)
1. 全锥形NAT

	假设, 内网机器(A:X), 公网机器(B:Y), 公网机器(C:Z)
如果内网机器(A:X)发送数据给公网机器(B:Y), 则映射的公网接口(D:X1)
如果内网机器(A:X)发送数据给公网机器(C:Z), 则映射的公网接口(D:X2)

## UDP hole punching
	### 方法
假设有两个客户 A:X B:Y 位于不同的 NAT 中，还有一个处于公网的服务器 C:Z


假设: X:x(私有) -> X1:x1(NAT) -> Y1:y1(公有)
此时, 如果, 新连接: X:x(私有) -> X2:x2(NAT) -> Y2:y2(公有)(X1 == X2)
1. 对于任何 Y1:y1 和 Y2:y2, X1:x1 都等于 X2:x2, 即: X:x 发向任何地址的数据都使用 NAT 的 X1:x1 (任何地址)
2. 如果 Y1 == Y2, 则 X1:x1 == X2:x2, 即: X:x 只有发往 Y1 的数据才使用 NAT 的 X1:x1 (IP 相同)
3. 如果 Y1:y1 == Y2:y2, 则 X1:x1 == X2:x2, 即: X:x 只有发往 Y1:y1 的数据才使用 NAT 的 X1:x1 (IP 和 端口号都相同)
此时, 如果, Y3:y3(私有) -> X1:x1(NAT) -> X:x(私有)
1. 对于任何 Y3:y3, 都可以发送成功(全锥形NAT)(任意)
2. 只要 Y3 == Y1, 就可以发送成功(受限圆锥形NAT)(IP相同)
3. 只有 Y3:y3 == Y1:y1, 才可以发送成功(端口受限圆锥形NAT)(IP和端口号都相同)
4.




链路层广播

MTU 最大传输单元 (链路层)

p2p

网络层:

traceroute: 查看数据包经过的路径

强主机模式: 数据包必须和对应网络接口对上
弱主机模式: 数据包和任一网络接口对上即可

DHCP:

```



# TODO

## 简介
* Bash 是 Linux 的默认 shell
* Bash 是脚本, 一门编程语言

## set 设置
```
set -o nounset  # 使用未初始化的变量报错, 同 -u
set -o errexit  # 只要发生错误就退出, 同 -e
set -o pipefail # 只要管道发生错误就退出
set -o errtrace # 函数报错时, 也处理 trap ERR, 同 set -E
set -o  xtrace  # 执行前打印命令, 同 -x
set -o verbose  # 读取前打印命令, 同 -v
set -o vi       # 使用 vi 快捷键
set -- ....     # 重新排列参数
```

建议使用: set -ueo pipefail

## 特殊字符 -- 要使用原字符必须转义
* 没引号包含
    * {} => 变量分割符 或 将语句封装成块
    * [] => 通配符 或 数字计算等等
    * () => 子shell
    * $  => 读取变量, 无值时默认忽略
    * !  => 一些快捷的方式获取命令或参数
    * ;  => 命令的分割符
    * #  => 注释
    * -  => 字符串以 - 开头表示是可选参数
    * -- => 后面的字符串都不是可选参数
    * '  => 单引号
    * "  => 双引号
    * &  => 后台运行
* 单引号包含:
    * '  => 单引号, 需要在字符串开头加上 $ 符号
* 双引号包含:
    * $  => 读取变量, 无值时默认忽略
    * !  => 一些快捷的方式获取命令或参数
    * "  => 双引号

## 特殊变量
```
$HOME  -- 主目录
$IPS   -- 默认分隔符, 默认为: " \t\n", 包含转义字符时, 需要在开头添加 $, IFS=$'\n'
$PATH  -- 命令路径
$PS1   -- 提示符
$PWD   -- 当前工作目录
$SHELL -- 当前 shell
$?     -- 上一命令执行是否成功
$$     -- shell ID
$_     -- 上一命令的最后一个参数
$!     -- 后台最后一个进程的进程 ID
$0     -- shell 名称
$-     -- shell 启动参数
```

## 字符串
```
v=...   #   解析变量和转义字符
v="..." #   解析变量和转义字符
v='...' # 不解析变量和转义字符
v="...
...
"       # 字符串跨行
v='...
...
'       # 字符串跨行

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
```

## 索引数组:
```
* v=(1 2 3)  # 初始化数组, 以空字符分割多个元素
* ${v[1]}    # 数组中指定元素的值
* ${v[-1]}   # 数组中最后一个元素的值
* ${v[@]}    # 数组中所有元素的值, "1" "2" "3"
* ${#v[@]}   # 数组中元素的个数
* ${!v[@]}   # 获取所有的 key
* v+=(1 2 3) # 添加数组元素
```

## 关联数组:
```
* declare -A v # 关联数组, map
* v[a]=a       # 赋值
* v[-1]=b      # 以 -1 作为 key
               # 其他同索引数组
```

## 模式扩展 -- 通配符
```
* ~       用户主目录
* ~lyb    用户 lyb 的主目录, 匹配失败的话, 不扩展
* ~+      当前目录
* ?       任意单个字符, 匹配失败的话, 不扩展
* *       任意多个字符, 匹配失败的话, 不扩展
* [123]   [1,3] 中任意一个, 匹配失败的话, 不扩展
* [1-5]   [1,5] 中任意一个, 匹配失败的话, 不扩展
* [!a]    非 a, 匹配失败的话, 不扩展
* [^a]    非 a, 匹配失败的话, 不扩展
* {1,2,3} [1,3] 匹配失败, 也会扩展
* {,1}    空 或 1, 匹配失败, 也会扩展
* {1..10}          匹配失败, 也会扩展
* {01..10}         匹配失败, 也会扩展(保证两位数)
* {1..10..3}       匹配失败, 也会扩展
```

## 模拟命令的标准输入
```
解释变量
cat << EOF
    $lyb
EOF

解释变量
cat << "EOF"
    $lyb
EOF

不解释变量
cat << 'EOF'
    $lyb
EOF

cat <<<  $lyb  #   解释变量
cat <<< "$lyb" #   解释变量
cat <<< '$lyb' # 不解释变量
```

## 括号 -- 只列举常用的情况
```
* 命令替换使用 $() 而不是反引号
    * (ls)         # 子shell执行命令, 输出到屏幕上
    * lyb=$(ls)    # 子shell执行命令, 存入变量
* 整数运算
    * (())         # 整数运算, 变量不需要加 $
    * lyb=$((...)) # 将结果存储在变量中
* 使用 [[ ... ]] 测试
    * [[ -z "$lyb" ]] # 判断是否空字符串
    * [[ -n "$lyb" ]] # 判断是否不是空字符串
    * [[ lyb =~ ^l ]] # 扩展的正则表达式匹配
    * [[ -a file   ]] # file 存在
    * [[ -e file   ]] # file 存在
    * [[ -f file   ]] # file 存在且普通文件
    * [[ -d file   ]] # file 存在且是目录
    * [[ -h file   ]] # file 存在且是符号链接
    * [[ -L file   ]] # file 存在且是符号链接
    * [[ -b file   ]] # file 存在且是  块文件
    * [[ -c file   ]] # file 存在且是字符文件
    * [[ -p file   ]] # file 存在且是一个命名管道
    * [[ -S file   ]] # file 存在且是一个网络 socket
    * [[ -s file   ]] # file 存在且其长度大于零
    * [[ -N file   ]] # file 存在且自上次读取后已被修改
    * [[ -r file   ]] # file 存在且可读
    * [[ -w file   ]] # file 存在且可写权
    * [[ -x file   ]] # file 存在且可执行
    * [[ -u file   ]] # file 存在且设置了 SUID
    * [[ -g file   ]] # file 存在且设置了 SGID
    * [[ -k file   ]] # file 存在且设置了 SBIT
    * [[ -O file   ]] # file 存在且属于有效的用户 ID
    * [[ -G file   ]] # file 存在且属于有效的组   ID
    * [[ -t fd     ]] # fd 是一个文件描述符，并且重定向到终端
    * [[ FILE1 -nt FILE2 ]] # FILE1 比 FILE2 的更新时间更近, 或者 FILE1 存在而 FILE2 不存在
    * [[ FILE1 -ot FILE2 ]] # FILE1 比 FILE2 的更新时间更旧, 或者 FILE2 存在而 FILE1 不存在
    * [[ FILE1 -ef FILE2 ]] # FILE1 和 FILE2 引用相同的设备和 inode 编号
* cat <(ls)           # 将命令或函数的输出作为文件
```

## 其他 bash 操作
```
bash file_name # 执行文件内的命令
bash -c "ls"   # 将字符串的内容交由 bash 执行, 字符串里可包含重定向和管道

echo -n "123"                # 不换行
echo -e "\e[1;33m lyb \e[0m" # 文本黄色 加粗
echo  $'123\''               # 单引号内存在单引号的情况
echo  $(cal)                 # 输出字符以空格区分
echo "$(cal)"                # 保留输出字符的分割符
echo ${!S*}                  # 列出所有包含 S 的变量

ls &> /dev/null # 重定向

!!    # 上一条命令
!l    # 执行最近使用的以 l 打头的命令
!l:p  # 输出最近使用的以 l 打头的命令
!num  # 执行历史命令列表的第 num 条命令
!$    # 上一条命令的最后一个参数
!*    # 上一条命令的所有参数
^1^2  # 将前一条命令中的 1 变成 2

bg %jobspec # 后台暂停 --> 后台运行, 有无 % 都成
fg %jobspec # 后台     --> 前台运行, 有无 % 都成

jobs          # 列出后台作业
jobs %jobspec # 作业号有无 % 都成
jobs -l       #   列出后台作业的 PID
jobs -p       # 只列出后台作业的 PID
jobs -n       # 只列出进程改变的作业
jobs -s       # 只列出停止的作业
jobs -r       # 只列出运行中的作业

read name     # 读取, 如果参数值小于字段数, 多余的值放入最后一个字段

sleep 30   # 前台运行
sleep 30 & # 后台运行

\command # 忽略别名

env          # 设置环境变量, 然后执行程序

getconf NAME_MAX / # 获取变量的值
getconf PATH_MAX /

history
```

## 脚本
```
$0 # 脚本名称
$1 # 第一个参数
$@ # 参数序列
$# # 参数个数

getopts # 处理参数, -- 表示可选参数的终止

exec &>> 1.log  # 脚本内重定向
exec ls         # 替换当前 shell, 执行后不再执行之后的命令
exec &>  1.txt  # 打开文件描述符, 然后继续执行之后的命令

trap ... ERR  # 发生错误退出时, 执行指定命令
trap ... EXIT # 任意情况退出时, 执行指定命令

flock    1.c ls # 设置文件互斥锁 执行命令, 设置锁失败, 等待
flock -n 1.c ls # 设置文件互斥锁 执行命令, 设置锁失败, 退出

脚本内使用, 保证脚本最多执行一次
[[ "$FLOCKER" != "$0" ]] && exec env FLOCKER="$0" flock -en "$0" "$0" "$@" || :

解释:
1. 第一次进入脚本, 由于变量未设置, 会执行 exec
2. 调用 exec, 使用 env 设置 变量名
3. 执行 flock, 重新执行这个脚本, 执行完脚本后会退出, 不会执行之后的命令
    * 使用脚本名作为 文件锁, 脚本名使用绝对路径, 所以不会重复
4. 第二次进入脚本, 由于变量已设置, 直接往下执行就可以了
5. 在此期间, 如果, 有其他脚本进入, 文件锁获取失败, 就直接退出了

if for while

函数

建议使用 local 局部变量, 声明和使用放到不同的行

```

测试文件: [test.sh](./test.sh)

## 常用快捷键
```
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

Ctrl+X Ctrl+X      # 连续按两次 Ctrl+X，光标在当前位置和行首来回跳转
Ctrl+X Ctrl+E      # 用你指定的编辑器，编辑当前命令
Ctrl+insert        # 复制命令行内容
shift+insert       # 粘贴命令行内容
```

## 相关命令
```
basename $(readlink -f $0) # 获取脚本的名称
dirname  $(readlink -f $0) # 获取脚本的目录

bc <<< "scale=2; 10/2" # 使用两位小数, 输出: 5.00
bc <<< "ibase=2;  100" # 输入使用二进制, 输出: 4
bc <<< "obase=2;   10" # 输出使用二进制, 输出: 1010

                  # 文件如果是符号链接, 将使用符号链接对应的文件
cat               # 输出 标准输入 的内容
cat          -    # 输出 标准输入 的内容
cat    1.txt      # 输出 1.txt 的内容, 文件支持多个
cat    1.txt -    # 输出 1.txt 和 标准输入 的内容
cat -n 1.txt      # 显示行号
cat -b 1.txt      # 显示行号, 行号不包括空行, 将覆盖参数 -n
cat -s 1.txt      # 去掉多余的连续的空行
cat -T 1.txt      # 显示 TAB
cat -E 1.txt      # 使用 $ 标明行结束的位置

tac               # 最后一行 => 第一行

chattr +i 1.c # 设置文件不可修改
chattr -i 1.c # 取消文件不可修改

chmod  755    1.c # 设置权限, 不足四位时, 补前缀 0
chmod  644 -R 1.c # 递归
chmod 4755    1.c # 设置 SUID(4)
chmod 2755    1.c # 设置 SGID(2)
chmod 1755    1.c # 设置 SBIT(1)

chown lyb:lyb 1.c # 修改文件所属的组和用户

column -t # 列对齐

                                                       # 文件如果是符号链接, 将使用符号链接对应的文件
comm                        1.c 2.c                    # 要求文件已排序, 以行比较
comm --check-order          1.c 2.c                    #   检测文件是否已排序
comm --nocheck-order        1.c 2.c                    # 不检测文件是否已排序
comm --output-delimiter=... 1.c 2.c                    # 指定列分割, 默认是 TAB
comm                        1.c 2.c       | tr -d '\t' # 全集
comm                        1.c 2.c -1 -2 | tr -d '\t' # 交集
comm                        1.c 2.c -3    | tr -d '\t' # B - A 和 A - B
comm                        1.c 2.c -1 -3              # B - A
comm                        1.c 2.c -2 -3              # A - B

cp    123 456      # 拷贝文件时, 使用符号链接所指向的文件
                   # 拷贝目录时, 目录中的符号链接将使用符号链接本身
                   # 456 只使用符号链接所指向的文件
cp -r 123 456      # 递归复制
cp -P 123 456      # 总是拷贝符号链接本身
cp -L 123 456      # 总是拷贝符号链接所指的文件
cp --parents a/b t # 全路径复制, 将生成 t/a/b

                                      # 文件如果是符号链接, 将使用符号链接对应的文件
cut                        -b 2   1.c # 按字节切割, 输出第 2 个字节
cut                        -c 2-  1.c # 按字符切割, 输出 [2, 末尾] 字符
cut                        -f 2-5 1.c # 按列切割,   输出 [2,5] 列
cut -d STR                 -f 2,5 1.c # 设置输入字段的分隔符, 默认为 TAB, 输出 第 2 列和第 5 列
cut -s                     -f  -5 1.c # 不输出不包含字段分隔符的列, 输出 [开头, 5] 的列
cut --output-delimiter=STR -f  -5 1.c # 设置输出的字段分隔符, 默认使用输入的字段分隔符

diff    1.txt 2.txt # 比较两个文件的不同
diff -u 1.txt 2.txt # 一体化输出, 比较两个文件的不同

dd if=/dev/zero of=junk.data bs=1M count=1

df   -Th                # 查看磁盘挂载情况

dos2unix 1.txt # \r\n (windows) => \n (Linux/iOS)
unix2doc 1.txt # \n (Linux/iOS) => \r\n (windows)

du                      # 列出目录大小
du -0                   # 输出以 \0 分割, 默认是换行符
du -a                   # 列出目录和文件大小
du -d 1                 # 最大目录深度
du -sh                  # 只列出整体使用大小
du --exclude="*.txt"    # 忽略指定文件, 支持通配符

file 1.txt # 查看换行符等

find . -name  lyb                     # 以文件名查找文件, 不包括路径, 可以使用通配符
find . -iname lyb                     # 同上, 忽略大小写
find . -path   "*/bash/*"             # 以全路径名查找文件, 可包括文件名, 可以使用通配符
find . -ipath  "*/bash/*"             # 同上, 忽略大小写
find . -regex ".*p+"                  # 同上, 使用正则表达式
find . -iregex ".*p+"                 # 同上, 忽略大小写
find . -maxdepth 5 –mindepth 2 -name lyb # 使用目录深度过滤
find . -L -name lyb                   # 是否跟着符号链接跳
find . -type  f                       # 以类型查找文件
find . -type f -atime -7              #     7天内访问过的文件
find . -type f -mtime  7              # 恰好7天前修改过的文件
find . -type f -ctime +7              #     7天前变化过的文件
find . -type f -newer file.txt        # 查找修改时间比 file.txt 新的文件
find . -type f -size +2G              # 以文件大小查找
find . -type f -perm 644              # 以权限查找
find . -type f -user lyb              # 以用户查找
find . -name '.git' -prune -o -type f # -prune 将前面匹配到的文件 或 目录 忽略掉
find . ! -type f -o   -name lyb       # ! 只否定最近的条件
find . \( -type f -and -name lyb \)   # 且, 多个条件必须同时成立
find . \( -type f -a   -name lyb \)   # 同上
find .    -type f      -name lyb      # 同上, 默认多个条件同时成立
find . \( -type f -or  -name lyb \)   # 或, 多个条件成立一个即可
find . \( -type f -o   -name lyb \)   # 同上

grep -v                   # 输出不匹配的内容
grep -c                   # 输出匹配的行的次数, 同一行只输出一次
grep -o                   # 只输出匹配的内容
grep -n                   # 输出匹配的行号
grep -l                   # 输出匹配的文件
grep -f                   # 从文件中读取匹配模式
grep -i                   # 忽略大小写
grep -h                   # 不输出文件名
grep -q                   # 静默输出
grep -A 5                 # 输出之前的行
grep -B 5                 # 输出之后的行
grep -C 5                 # 输出之前之后的行
grep -e .. -e ..          # 多个模式取或
grep -E ..                # 使用扩展的正则表达式, 同 egrep
grep -P ..                # 使用 perl 风格的正则表达式
grep -W ..                # 单词匹配
grep -X ..                # 行匹配
grep ... --inclue "*.c"   # 指定文件
grep ... --exclue "*.c"   # 忽略文件
grep ... --exclue-dir src # 忽略目录

less # 空格   : 下一页
     # ctrl+F : 下一页
     # b      : 上一页
     # ctrl+b : 上一页
     # 回车   : 下一行
     # =      : 当前行号
     # y      : 上一行

ln -s target symbolic_link_name # 创建符号链接

ls -a        # 列出当前目录中的元素, 包括隐藏的文件
ls -S        # 使用 文件大小 排序, 大 --> 小
ls -v        # 使用 版本号 排序
ls -X        # 使用 扩展名 排序
ls -d        # 只列出目录本身，而不列出目录内元素
ls -l        # 列出当前目录中的元素的详细信息
ls -h        # 使用人类可读的形式
ls -F        # 在目录后添加 /，在可执行文件后添加 *
ls -r        # 逆序
ls -R        # 递归
ls -1        # 在每一行列出文件名
ls -L        # 符号链接所指向的文件, 而不是符号链接本身
ls -I "*.sh" # 忽略文件, 使用通配符
ls -clt      # 使用 ctime 排序和展示, 新 -> 旧
ls -tl       # 使用 mtime 排序和展示, 新 -> 旧
ls -ult      # 使用 atime 排序和展示, 新 -> 旧

ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtu # 以 文件访问时间     排序, 不准确
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtc # 以 文件属性修改时间 排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrt  # 以 文件内容修改时间 排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrtd # 以 文件内容修改时间 排序, 只列出目录本身
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrS  # 以 文件大小         排序
ls --time-style='+%Y-%m-%d %H:%M:%S %z' -lhrv  # 以 文件名为版本号   排序

md5sum 1.txt # MD5 检验

mkdir    abc   # 创建目录
mkdir -p a/b/c # 递归创建目录, 目录已存在时不报错

mktemp         # 临时文件
mktemp -d      # 临时目录

more    # 空格   : 下一页
        # ctrl+F : 下一页
        # b      : 上一页
        # ctrl+b : 上一页
        # 回车   : 下一行
        # =      : 当前行号

mv a b # a 是符号链接时, 将使用符号链接本身
       # b 是指向文件  的符号链接时， 相当于 移到 b 本身
       # b 是指向目录  的符号链接时， 相当于 移到 b 最终所指向的目录下
       # b 是指向不存在的符号链接时， 相当于 重命名

patch     1.txt diff.pathc  # 恢复文件
patch -p1 1.txt diff.pathc  # 恢复文件, 忽略 diff.pathc 的第一个路径

readlink    1.c.link  # 读取符号链接
readlink -f 1.c.link  # 读取符号链接, 递归

rm -r  a    # 递归删除
rm -rf a    # 强行删除, 文件不存在时, 忽略

sort            # 排序
sort -b         # 忽略前置空白
sort -c         # 检查是否已排序
sort -d         # 字典序排序
sort -f         # 忽略大小写
sort -k 4       # 指定排序的列字段
sort -k 4.1,4.2 # 指定排序的列字段
sort -h         # 以 K, M, G 排序
sort -i         # 忽略不可打印字符
sort -m         # 合并排序过的文件
sort -n         # 以数字进行排序
sort -r         # 逆序
sort -t :       # 指定列的分割符
sort -u         # 重复项只输出一次
sort -V         # 以版本号排序
sort lyb -o lyb # 排序并存入原文件

               # 查看文件时间
stat       1.c # 列出 birth atime mtime ctime
stat -L    1.c # 符号链接所指向的文件, 而不是符号链接本身
stat -c %w 1.c # 列出 birth 人类可读形式
stat -c %W 1.c # 列出 birth 距离 Epoch 的秒数
stat -c %x 1.c # 列出 atime 人类可读形式
stat -c %X 1.c # 列出 atime 距离 Epoch 的秒数
stat -c %y 1.c # 列出 mtime 人类可读形式
stat -c %Y 1.c # 列出 mtime 距离 Epoch 的秒数
stat -c %z 1.c # 列出 ctime 人类可读形式
stat -c %Z 1.c # 列出 ctime 距离 Epoch 的秒数

tail -f * # 动态查看新增内容

tee    1.txt # 管道中把文件拷贝到文件
tee -a 1.txt # 管道中把文件添加到文件

                 # 修改文件时间
touch        1.c # 修改 atime mtime ctime
touch -a     1.c # 修改 atime
touch -c     1.c # 文件不存在时, 不创建文件
touch -h     1.c # 改变符号链接本身, 而不是所指向的文件
touch -m     1.c # 修改       mtime ctime
touch -r 2.c 1.c # 以 2.c 的时间修改 1.c
touch -d ... 1.c # 指定时间, 格式同 date
touch -t ... 1.c # 指定时间
                 # 依次是: 时区-年-月-日-时-分-秒

tr    'a-z' 'A-Z' # 小写转大写
tr -d 'a-z'       # 删除字符
tr -s ' '         # 压缩字符

tree -p "*.cc"       # 只显示  匹配到的文件
tree -I "*.cc"       # 只显示没匹配到的文件
tree -H . -o 1.html  # 指定目录生成 html 文件

uniq    # 删除重复的行
uniq -c # 输出统计的次数
uniq -d # 只输出重复的行, 重复的项只输出一次
uniq -D # 只输出重复的行, 重复的项输出多次
uniq -i # 忽略大小写
uniq -u # 只输出没重复的行

cat lyb | xargs -i vim {} # 以此编辑 lyb 中的每一个文件

wc    # 输出 换行符数 字符串数 字节数
wc -l #   行数
wc -w # 字符串数
wc -c # 字节数
wc -m # 字符数
```

