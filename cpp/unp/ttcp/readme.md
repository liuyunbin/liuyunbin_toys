
## 程序简介
使用 ttcp 的服务器和客户端，ttcp 用于测试 tcp 性能

## 协议说明
1. ttcp 客户端发送 8 的字节，前 4 个字节，表示发送消息的数量，后 4 个字节表示每条消息的大小
2. ttcp 服务器端接收 8 字节的数据，得到消息的数量和大小
3. ttcp 客户端首先发送每条消息的大小，然后发送整条消息
4. ttcp 服务器端首先接收消息的大小，然后接收整条消息，并向客户端返回消息的大小
5. ttcp 客户端接收服务器返回的消息大小，并确认是否有误
6. 重复 3 - 5，直到发送所有消息
7. ttcp 客户端打印 带宽，吞吐量，等等性能数据

