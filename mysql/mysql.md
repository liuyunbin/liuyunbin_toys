
## 为什么使用数据库
* 数据持久化
* 效率

## 安装及初始化
#### 1. 安装软件

    apt install mysql-server

#### 2. 初始化: 配置密码强度要求, 禁止 root 远程登录, 删除匿名用户,

    mysql_secure_installation      # 配置密码强度要求
                                   # 禁止 root 远程登录
                                   # 删除匿名用户
                                   # 删除测试数据库


```
                                   #
systemctl enable     mysql.service # 开机自动启动
systemctl start      mysql.service # 启动服务
systemctl is-active  mysql.service # 查看是否已启动
systemctl is-enabled mysql.service # 查看是否开机自动启动
                                   #
```

## 使用 utf8mb4 --- 8.0 的版本不需要修改了
```
mysql -e "show variables like 'character%';" # 1. 查看字符集
mysql -e "show variables like 'collation_%'" #
mysql --help --verbose 2> /dev/null | grep -A1 'Default options'
                                             # 2. 查找配置文件
default-character-set = utf8mb4              # 3. 修改对应的服务端和客户端配置
systemctl restart mysql                      # 4. 重启
mysql -e "show variables like 'character%';" # 5. 再次查看字符集
```

DDL(数据定义语言): CREATE DROP   ALTER
DML(数据操作语言): INSERT UPDATE SELECT DELETE
DCL(数据控制语言): GRANT  REVOKE COMMIT ROLLBACK SAVEPOINT

## 用户管理
```
select user,host from mysql.user;                        # 1. 查看用户
create user 'root'@'localhost' identified by 'password'; # 2. 创建用户
grant    all on *.* to 'root'@'localhost';               # 3. 赋予所有权限
grant select on *.* to 'root'@'localhost';               # 3. 赋予查询权限
show grants for root@'localhost';                        # 4. 查看权限
revoke select on *.* from 'root'@'localhost';            # 5. 回收查询权限
drop user 'root'@'localhost';                            # 6. 删除用户
```

## 修改密码
ALTER USER 'root'@'localhost' IDENTIFIED BY 'new_password';


set password for 'tom'@'localhost' = password('123');
mysqladmin -u root -p password “123456”;

## 忘记密码
sudo systemctl stop mariadb
sudo mysqld_safe --skip-grant-tables & ---- 跳过权限判断启动
mysql -u root
set password for 'root'@'localhost' = password('123'); --- 修改密码
flush privileges;
sudo systemctl start mariadb


## 视图
* 相当于是一张虚拟表
* 不存储数据
* 一般只用于查询
* 控制访问的内容, 安全
* 简化查询语言
* 具有隔离性

## 约束
```
* NOT NULL
* UNIQUE ------------ 唯一键
    * 整个表中是唯一的, 但 NULL 可以多个
    * 可以有多个 unique
    * 可以对多个列同时创建
    * 创建索引
* PRIMARY KEY ------- 主键
    * 唯一键 + 非空
* AUTO_INCREMENT ---- 自动递增
    * 一般在主键或唯一键
    * 最多有一列
    * 整形
* FOREIGN KEY ------- 外键
    * 从表的外键必须是主表的主键或唯一键
    * 先创建主表, 再创建从表
    * 先删除从表或外键, 再删除主表
    * 外键可以多个
    * 外键会自动创建索引
DEFAULT ------------ 默认值
```



[CONSTRAINT 约束名] UNIQUE(字段名) ---------------------------- 创建唯一键
[CONSTRAINT 约束名] PRIMARY KEY(字段名) ----------------------- 创建主键
[CONSTRAINT 约束名] FOREIGN KEY(从表的某个字段) references 主表名(被参考字段) ON UPDATE CASCADE ON DELETE RESTRICT
                                            ------------------- 创建外键, 同步更新, 删除严格

ALTER TABLE 表名称 ADD [CONSTRAINT 约束名] UNIQUE(字段名) ----------- 更改唯一键
ALTER TABLE 表名称 ADD [CONSTRAINT 约束名] PRIMARY KEY(字段列表) ---- 更改主键
ALTER TABLE 从表名 ADD [CONSTRAINT 约束名] -------------------------- 修改外键

ALTER TABLE 表名称 DROP INDEX 约束名或字段名 ------------------- 删除唯一键
ALTER TABLE 表名称 DROP PRIMARY KEY; --------------------------- 删除主键
ALTER TABLE 从表名 DROP FOREIGN KEY 外键约束名; ---------------- 删除外键


## 库
```
show databases;            # 查看数据库
show tables;               # 查看所有的表
show tables from ...;      # 查看某一库中所有的表
show create database  ...; # 查看数据库的创建信息
show create table ...;     # 查看表的创建信息

create database  ...;           # 创建数据库
create table ... (...);         # 创建表
create table ... as select ...; # 创建表

alter database  ...; # 修改数据库

alter table 表名称 add    [column]   列名称 列属性 [first | after 旧名称]; # 增加列
alter table 表名称 modify [column]   列名称 列属性 [first | after 旧名称]; # 修改列属性
alter table 表名称 change [column] 旧列名称 新列名称 列属性;               # 修改列名称
alter table 表名称 drop   [column]   列名称;                               # 删除列

alter table 表名称 rename [to] 新表名称;                     # 重命名表名

rename table 旧表名 to 新表名称; # 重命名表名

alter table ... add primary key (col_list);
alter table ... add unique index_name (col_list);
alter table ... add index index_name (col_list);
alter table ... add fulltext index_name (col_list);

alter table tbl_name drop index index_name；
alter table tbl_name drop primary key;

drop database ...; # 删除数据库
drop table ...;    # 删除表

truncate table ...; # 清空表

use ...; # 使用数据库

SET autocommit = FALSE; # 取消自动提交
ROLLBACK;               # 回滚





## 数据类型
int --------------- 整形
bigint unsigned --- 大整形
decimal(m,d) ------ 定点数
datetime ---------- 日期和时间
timestamp --------- 时间戳
char(m) ----------- 固定长度
varchar(m) -------- 可变长度, 5.0 之后 m 为字符数

## 创建表

drop index index_name on tbl_name;
create unique index uniq_idx_firstname on actor (`first_name`);
create        index idx_lastname on actor (`last_name`);


insert into ...
insert ignore into ...
replace into ...

create table ...()

drop table ...

source ...

DISTINCT ----- 放在所有列开头

NULL 参与的所有结果都为 NULL

desc ...

round -- 不一定是直观 的四舍五入


DB: 数据库 Database
DBMS: 数据库管理系统 Database Management System
SQL: 结构化查询语言 Structured Query Language

RDBMS: 关系型数据库
* 将复杂的关系转化为二元的关系, 表格
* 表之间通过外键来关联

E-R(entity-relationship 实体-联系)模型中有三个主要概念是 实体集 属性集 联系集
一个实体集(class)   == 一个表(table)
一个实体(instance)  == 一行(row), 一条记录(record)
一个属性(attribute) == 一列(column), 一个字段(field)


表之间的关系
一对一: 用的不多, 可以使用一张表, 但会冗余
一对多
多对多
自引用

外键: 是主键
主表
从表

单引号: 字符串 日期
双引号: 别名
反引用: 与关键字冲突时, 使用

库名 表名 表别名 字段名 字段别名 小写, 其他建议大写

## 其他
mysql -D <库名> -h <域名> -u <用户名> -p<密码>  # 登录
myqsl -D testdb < 1.sql                         # 从文件导入
mysqldump database_name table_name > 1.sql      # 导出到文件
select .. into outfile .. fields terminated by ',' optionally enclosed by '"' lines terminated by '\n' from ..
                                                # 保存数据到文件

mysql_install_db --user=mysql --ldata=/var/lib/mysql # 添加用户 mysql 使mysqld 可以使用 systemctl 启动

set global max_allowed_packet=64*1024*1024 # 设置插入的上限

desc ......;             # 查看表结构
delete   table 表名称;   # 删除表内数据, 表结构保留
truncate table 表名称;   # 删除表内数据, 表结构保留

auto_increment

primary key: 主键, 唯一, 不能为空, 只能有一个主键, 加索引
unique  index: 唯一, 能有多个, 加索引
foreign index: 外键, 加索引
        index: 普通索引

## SELECT
书写: SELECT -> DISTINCT -> FROM -> WHERE -> GROUP BY -> HAVING -> ORDER BY -> LIMIT
执行: FROM -> WHERE -> GROUP BY(此后可以使用聚合) -> HAVING -> SELECT -> DISTINCT -> ORDER BY -> LIMIT


LEAST
GREATEST
BETWEEN ... AND ... --- [ ]
ISNULL
IS NULL
IS NOT NULL
IN
NOT IN
LIKE
REGEXP
RLIKE

ORDER BY ... ASC | DESC
LIMIT 偏移量, 行数
LIMIT 行数

update table_name set ...=... where ...

insert into table_name () values ();

delete from table_name where ...

and or not
in, not in,
is null, is not null, <=>(相等或都为null)
between ... and ...,
like(%表示任意字符),
regexp, rlike

order by .... DESC

UNION --------- # 合并, 去重 ---- 效率低
UNION ALL ----- # 合并, 不去重 -- 效率高

INNER JOIN ... ON ... # 内连接
LEFT  JOIN ... ON ... # 左连接
RIGHT JOIN ... ON ... # 右连接

NATURAL JOIN ... # 所有相同字段等值连接
JION ... USING(...) ... # 指定字段等值连接

current_timestamp()
current_date()
now()

trigger 触发器

create index 索引名称  表名(字段名称)            # 创建索引
alter table 表名称 add  index 索引名称(字段名称) # 创建索引
drop index 索引名称 on 表名                      # 删除索引


# SELECT
## 书写
SELECT DISTINCT ...
FROM ...
WHERE ...
GROUP BY ...
HAVING ...
ORDER BY ...
LIMIT ...

## 执行
FROM -> WHERE -> GROUP BY(此后可以使用聚合) -> HAVING -> SELECT -> DISTINCT -> ORDER BY -> LIMIT

## 运算符
DISTINCT -------------- 后续所有的列都去重
LEAST ----------------- 最小
GREATEST -------------- 最大
BETWEEN ... AND ... --- 范围 [ ]
ISNULL ---------------- 是 NULL
IS NULL --------------- 是 NULL
IS NOT NULL ----------- 不是 NULL
IN -------------------- 属于集合
NOT IN ---------------- 不属于集合
LIKE ------------------ % 任意多个字符, _ 任意一个字符
REGEXP ---------------- 正则表达式
RLIKE ----------------- 正则表达式

ORDER BY ... ASC | DESC
LIMIT 偏移量, 行数
LIMIT 行数


update table_name set ... where ...

insert into table_name (...) values (...);
insert into table_name (...) select ... ;

delete from table_name where ...

UNION --------- # 合并, 去重
UNION ALL ----- # 合并, 不去重

INNER JOIN ... ON ... # 内连接
LEFT  JOIN ... ON ... # 左连接
RIGHT JOIN ... ON ... # 右连接
