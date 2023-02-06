# Kafka高级

what why how    use Kafka

## 3:基础开发及消费者提交维护offset不同粒度方式

```
API操作:
一个生产者
一个消费者

idea创建一个新的项目 -- maven -- maven本地仓库配置 -- 加依赖

Kafka不会加工数据,双方需要约定编解码方式
可以使用ZeroCopy(sendfile)实现快速消费

消费者开始消费,如果没有找到offset的位置:默认latest、earliest、none

offset自动提交:
	开启true #自动提交是异步提交 容易造成丢数据&&重复消费,默认提交间隔5s ！！！

kafka-consumer-groups.sh --bootstrap-server node02:9092 --list
kafka-consumer-groups.sh --bootstrap-server node02:9092 --describe --group groupName
CURRENT-OFFSET  LOG-END-OFFSET #两个数据

```

### 消费者提交维护offset方式 ！！！

```
演示一
1 offset自动提交开启
2 使用 latest 配置,consumer拉取数据
3 创建一个 consumer 组 XX001
CURRENT-OFFSET  LOG-END-OFFSET #观察两个数据变化

演示二
1 offset自动提交关闭  
2 使用 earliest 配置,consumer拉取数据
3 创建一个 consumer 组 XX002
CURRENT-OFFSET 显示为空


演示三
1 offset自动提交开启
2 自动提交延时设置成 15s
3 使用 earliest 配置,consumer拉取数据
4 创建一个 consumer 组 XX003

结论
一个运行的consumer,那么自己会维护自己消费进度
一旦自动提交开启了,但是是异步的
1 还没到时间,挂了,没提交,重启一个consumer,参照offset的时候,会重复消费
2 一个批次的数据还没写数据库成功,但是这个批次的offset被异步提交了,挂了,重启一个consumer,参照offset的时候,会丢失数据

```



```
Kafka的 consumer 会动态负载均衡
	1 只有一个 consumer 消费数据 
	2 两个 consumer 消费数据

idea设置可以多个 consumer 同时运行
默认hash进行分区

如果有两个分区,只有一个 consumer,是一个拉取一个分区的数据,还是一次拉取两个分区的数据？？？
	1 offset自动提交开启
	2 使用 earliest 配置
	3 创建一个 consumer 组 XX004
	4 #注释掉延时
	5 只启动一个consumer,producer数据打入两个分区中

如果offset 手动提交,关闭自动提交；并且可以设置offset持久化的位置。#暂不考虑持久化位置
offset提交粒度:
	1 每消息进度同步提交
	2 按分区粒度同步提交
	3 按当前poll的批次同步提交
思考:如果在多个线程下
	1 以上1,3的方式不用多线程
	2 以上2的方式最容易想到多线程方式处理,有没有问题？？？
		没有问题,

常识:
每poll一次,用一个语义:一个job启动
一次job用多线程并行处理分区
且job应该被控制是串行的
以上的知识点,是大数据思想

如果是按分区方式消费
拿到了分区的数据集
期望的是先对数据整体加工
小问题会出现？  怎么知道最后一条消息的offset ？！！！
Kafka很傻,不关心拿走了多少,需要告诉正确的最后一条消息的offset

```



## 4:kafka进阶,ISR,OSR,AR,LW,HW,LEO,ACK原理理论

```
纯理论:分布式 

zookeeper可以查看创建的Kafka信息:
get /kafka/brokers/topics/{topicName}/partitions/0/state
ISR:同步过程种可用的节点数

##############################################################
单机:
单机 broker 如何维护分区的数据 ？？？
	1 Kafka数据保存:磁盘,以文件方式保存数据
	2 Kafka broker的数据先写入 pagecache
	3 pagecache 的数据需要 flush,才会持久化到磁盘 #这个过程可能丢数据
	4 我们应该把单机的持久化可靠性转向,集群多机方式 ！！！

基于timestamp(producer以生产时间为主) 的index 找到 offset,在找到对应的 data位置
consumer 拉取数据:数据不需要加工,kernel 可以直接通过sendfile 发送数据到 consumer
Kafka对数据只是发送,没有加工的过程！！！

acks参数 #producer 生产数据！！！
    0:消息发出即可,可能丢数据
    默认1:pagecache收到数据后,回复确认
    -1:面向分布式,所有的分区副本都要同步

##############################################################
分布式:
分区可靠性 要解决一个问题,伴随着引入更多的问题(数据一致性)

1 强一致性,所有节点必须全部存活,一致性破坏可用性
2-1 最终一致性,过半通过,最常用的分布一致性解决方案
2-2 ISR(in-sync replicas)连通性&活跃性
	OSR(outof-sync replicas)超过阈值时间,没有“心跳”
	AR(Assigned replicas)面向分区的副本集合,创建topic的时候你给出了分区的副本数,那么controller在创建的时候就已经分配了broker 和分区的对应关系,并得到了该分区的broker集合
	AR = ISR + OSR
	
acks为 -1 的时候,ISR集合种,多个broker的消息进度是一致的

```



```
acks为 1 的时候
LogEndOffset(LEO):producer 生产到的位置
High Watermark HW高水位:consumer 可以消费到的位置

以HW 对外暴露可消费数据

0 另外一个trade off:不要强调磁盘的可靠性,转向异地多机的同步
1 如果拿磁盘做持久化,在做trade off:优先pagecache 或者绝对磁盘
2 在多机集群分布式的时候trade off:强一致,最终一致性(过半,ISR)

*redis:宁可用HA,不要刻意追求AOF准确性
像Kafka,我们追求ack -1,不要太追求磁盘的可靠性
还有trade off,就是在HA场景下, 如果有实例异常退出,是否需要立刻尝试重启

Low Watermark LW:Kafka保存数据是有时间限制的

```



## 5:观察验证ISR弹性,时间戳索引,自定义offset消费

```
主要内容:
1 索引 
2 生产者,数据可靠性 
3 时间戳,自定义消费数据 --> 本质:seek
```

### 索引 

```
启动Kafka集群,清空之前的数据
Kafka的config 文件夹内,查看配置文件 
vim server.properties
log.dirs=/var/kafka_data

cd /var/kafka_data #创建topic后会有对应分区的文件生成
kafka-topics.sh --zookeeper node02:2181,node03:2181/kafka --create --topic msb-items --partitions 2 --replications-factor 3
kafka-topics.sh --zookeeper node02:2181,node03:2181/kafka --describe --topic msb-items

cd /var/kafka_data/msb-items-0
.log #存放数据 
.index #偏移量offset的索引 
.timeindex #offset索引的二级索引,拿timestamp 找 offset 再找到数据具体位置
.index .timeindex空文件,但是大小是10M FD是mem类型
.log FD是普通IO

lsof -Pnp {KafkaPID} #yum install -y lsof 查看进程

cd /var/kafka_data/msb-items-0
kafka-dump-log.sh --files 00...00.log
kafka-dump-log.sh --files 00...00.index
kafka-dump-log.sh --files 00...00.timeindex

*log使用普通IO的形式目的是通用性,数据存入磁盘的可靠性级别
app层级:
调用了IO的write,但是这个时候只到达了内核,性能快,但是丢数据
只有NIO的filechannel,调用了write()+force(),才真的写到磁盘,性能极低
1 每条都force
2 只是write 基于内核刷写机制,靠脏页


```



### 生产者,数据可靠性 

```
演示 生产者ack -1:
	0分区,三个节点,一主node03,两从node02, node01
	修改其中一个从节点路由条目,造成从节点超时未返回同步完成信息
	node02目标地址是node03的,修改成指向其他位置 127.0.0.1
	node02:route add -host {node03IP} gw 127.0.0.1 #linux没有开启数据转发功能 IP forward
			route del -host {node03IP} #删除路由条目
			ping {node03IP} #查看一下路由修改结果是否生效
/var/kafka_data/msb-items-0 #文件大小增加
kafka-topics.sh --zookeeper node02:2181,node03:2181/kafka --describe --topic msb-items
#查看分区情况,超时ISR会有节点变动

为什么分区1 不受影响？？？
因为 node02 到分区1 leader node01的通信不受影响

*ISR超时时间默认10秒
```



### 时间戳,自定义消费数据

```
消费者消费数据

演示:
	1 offset自动提交开启
	2 使用 earliest 配置
	3 创建一个 consumer 组 OOXX
消费一段数据后查看Kafka OOXX组情况
kafka-consumer-groups.sh --bootstrap-server node02:9092,node03:9092 --list 
kafka-consumer-groups.sh --bootstrap-server node02:9092,node03:9092 --describe --group OOXX

可以设置根据时间点,开始消费

kafka-dump-log.sh --files 00...00.timeindex


*本质:seek
```



## 6:kafka之producer的参数,源码,原理剖析

```
写代码主要是在 producer 配置上下功夫

源码:
public KafkaProducer(Properties properties) {} #开始  KafkaProducer线程安全
分区器
private final Sender sender;
key和value序列化
private final ThreadioThread; ...

this.accumulator   
new BufferPool

RecordAccumulator Buffer配置 默认32MB
batch 大小:默认16KB
```



```
ioThread : Sender 的 run()

nio select

run --> running --> run --> dosend

```



## 7:kafka 源码分析producer及通信原理

```
数据发送之前需要先更新元数据:waitOnMetadata

推送数据,需要找到cluster对应的topic 分区等信息


sender 中 NetworkClient 的 poll()
poll()
	1 maybeupdate:
		initiateConnect(node) 第一轮循环,做了连接  
		sendinternalMetadataRequest() 第二轮循环 发送metadata请求
	2 poll --> nioSelector:select() 
	3 handler --> handlerCompleteReceives() --> metadata.updata(cluster)
		

```



```
服务器 1 如何更好的接受管理这么多的连接
以及 2 完成请求和响应的正确匹配 (两个核心问题)


需求:顺序性
1 前置 socket里存在顺序性,由发送方维护
2 推送方,在架构上整体设计约束的

```



## 8:kafka 源码分析broker网络层通信原理

```
broker




```



# 附录:



```
官网:https://kafka.apache.org/


```

