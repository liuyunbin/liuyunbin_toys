
yum install epel-release # 安装软件源 epel -- 常用
yum check-update         # 更新软件源      -- 常用
                         # 软件源: /etc/yum.repos.d/
                         # * [...]           -- 源的名字
                         # * name=...        -- 源的描述
                         # * baseurl=file:// --	源的路径, file:// 表示本地仓库
                         # * enabled=...	 --	是否启用该仓库, 1-启用, 0-不启用
                         # * gpgcheck=...	 -- 是否不用校验软件包的签名, 0-不校验, 1-校验
                         # * gpgkey=...      -- 上个选项对应的 key 值
yum clean all            # 清空软件源缓存
yum makecache            # 新建软件源缓存
yum repolist             # 查看软件源(可达的)

yum update package_name  # 更新某个软件包           -- 常用
yum update               # 更新所有软件包           -- 常用
yum remove  package_name # 卸载软件                 -- 常用

yum list installed       # 列出已安装的软件
yum list vim             # 列出某软件包的详细信息
yum list updates         # 列出可用更新
yum provides vim         # 查看软件属于哪个软件包
yum provides /etc/vimrc  # 查看文件由哪个软件使用

TODO: 软件源的建立, 清除