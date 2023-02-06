# K8S介绍

```
Kubernetes 的职责
    自动化容器的部署和复制
    随时扩展或收缩容器规模
    容器分组 Group,并且提供容器间的负载均衡
    实时监控,即时故障发现,自动替换

Kubernetes 基本概念
    Pod 
        Kubernetes控制的最小单元
        一个POD就是一个进程
        每个POD都有独立的虚拟IP
        可以包含多个"Container"
    Pause容器:提供一个共享的网络空间 和挂载数据卷

    Label:标签
    Replication Controller:在主节点上,对Pod数量监控
    Service:不同主机 Pod与Pod之间通信
    Kubernetes Master 主节点
    Node
```

# K8S集群搭建

### 环境准备

```
Kubernetes 安装:完成后就带有 kubectl kubeproxy
    使用 kubeadmin 通过离线镜像安装
    二进制包的形式进行安装 kubeasz GitHub(三方不推荐)

演示安装 1.14版本

Centos7 主机规划
192.168.245.154  master
192.168.245.155  node1
192.168.245.156  node2

安装设置！！！
1. 设置主机名与时区
timedatectl set-timezone Asia/Shanghai  #都要执行
hostnamectl set-hostname master   #154 执行
hostnamectl set-hostname node1    #155 执行
hostnamectl set-hostname node2    #156 执行

2. 添加hosts网络主机配置,三台虚拟机都要设置
vim /etc/hosts
192.168.245.154 master
192.168.245.155 node1
192.168.245.156 node2

3. 关闭防火墙,三台虚拟机都要设置,生产环境跳过这一步
sed -i 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config
setenforce 0
systemctl disable firewalld
systemctl stop firewalld
```

### 安装Kubeadm快速部署工具

```
安装Kubeadmin加载K8S镜像！！！
1. 将镜像包上传至服务器 每个节点！！！
mkdir /usr/local/k8s-install
cd /usr/local/k8s-install
XFTP上传安装文件

2. 在每个Centos上安装Docker
tar -zxvf docker-ce-18.09.tar.gz
cd docker 
yum localinstall -y *.rpm
systemctl start docker
systemctl enable docker

3. 确保从cgroups均在同一个从groupfs
#cgroups是control groups的简称,它为Linux内核提供了一种任务聚集和划分的机制,通过一组参数集合将一些任务组织成一个或多个子系统。   
#cgroups是实现IaaS虚拟化(kvm、lxc等),PaaS容器沙箱(Docker等)的资源管理控制部分的底层基础。
#子系统是根据cgroup对任务的划分功能将任务按照一种指定的属性划分成的一个组,主要用来实现资源的控制。
#在cgroup中,划分成的任务组以层次结构的形式组织,多个子系统形成一个数据结构中类似多根树的结构。cgroup包含了多个孤立的子系统,每一个子系统代表单一的资源

docker info | grep cgroup 

如果不是groupfs,执行下列语句
cat << EOF > /etc/docker/daemon.json
{
  "exec-opts": ["native.cgroupdriver=cgroupfs"]
}
EOF
systemctl daemon-reload && systemctl restart docker

4. 安装kubeadm
# kubeadm是集群部署工
cd /usr/local/k8s-install/kubernetes-1.14
tar -zxvf kube114-rpm.tar.gz
cd kube114-rpm
yum localinstall -y *.rpm

5. 关闭交换区
swapoff -a
vim /etc/fstab 
#swap一行注释

6. 配置网桥
cat <<EOF >  /etc/sysctl.d/k8s.conf
net.bridge.bridge-nf-call-ip6tables = 1
net.bridge.bridge-nf-call-iptables = 1
EOF
sysctl --system


7. 通过镜像安装k8s
cd /usr/local/k8s-install/kubernetes-1.14
docker load -i k8s-114-images.tar.gz
docker load -i flannel-dashboard.tar.gz
```

### 利用Kubeadm构建集群

```shell
1. master主服务器配置
kubeadm init --kubernetes-version=v1.14.1 --pod-network-cidr=10.244.0.0/16
#--pod-network-cidr=10.244.0.0/16 虚拟IP地址边界

mkdir -p $HOME/.kube
sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
sudo chown $(id -u):$(id -g) $HOME/.kube/config
# kubeadm init 生成的信息
# /etc/kubernetes/admin.conf 配置信息 

kubectl get nodes
#查看存在问题的pod
kubectl get pod --all-namespaces
#设置全局变量
#安装flannel网络组件
#多个Pod之间通信
cd /usr/local/k8s-install/kubernetes-1.14
kubectl create -f kube-flannel.yml

2. 加入NODE节点 (命令是master 节点kubeadm init 命令生成的信息)
kubeadm join 192.168.245.154:6443 --token u98xrh.o6duejol2n9a6i6l \
    --discovery-token-ca-cert-hash sha256:eec03e0fb324774d65031d5af86df5b2878904bbee9032d23c4d99f248493558


如果忘记
在master 上执行kubeadm token list 查看
在node上复制token,并执行 加入master集群
kubeadm join 192.168.245.154:6443 --token u98xrh.o6duejol2n9a6i6l --discovery-token-unsafe-skip-ca-verification
在node上运行！！！
kubeadm join 192.168.245.154:6443 --token u98xrh.o6duejol2n9a6i6l \
    --discovery-token-ca-cert-hash sha256:eec03e0fb324774d65031d5af86df5b2878904bbee9032d23c4d99f248493558

kubectl get nodes

3. Master开启仪表盘
cd /usr/local/k8s-install/kubernetes-1.14
kubectl apply -f kubernetes-dashboard.yaml #创建仪表盘
kubectl apply -f admin-role.yaml
kubectl apply -f kubernetes-dashboard-admin.rbac.yaml #角色访问权限
kubectl -n kube-system get svc #获取系统命名空间
http://192.168.245.154:32000 访问 .yaml配置跳过了用户名密码选项
```

### 重新启动服务

```
kubeadm 是kubernetes集群快速构建工具
kubelet 运行在所有节点上,负责启动POD和容器,以系统服务形式出现
kubectl 是kubernetes命令行工具,提供指令

启动节点命令
systemctl start kubelet
systemctl enable kubelet
```

### Dashboard部署Tomcat集群

```
需要docker配置阿里镜像加速

http://192.168.245.154:32000 进入页面
工作负载 --> 创建 --> 创建应用
    应用名称:my-tomcat
    容器镜像:tomcat:latest
    容器组个数:2
    服务:外部 #是否对外暴露端口 POD端口 容器内部端口
    8000  8080  tcp
--> 部署
点击 概况 --> 查看对应节点日志信息

如何访问？？？
概况 --> 副本集 --> 服务 
node访问对应的生成端口
http://192.168.245.155:31909/ #示例

docker exec -it e66fc7361e94 /bin/bash
rm -rf webapps
mv webapps.dist webapps #需要修改容器内部的内容才可以正常访问tomcat
```

### Deployment脚本部署Tomcat集群

```shell
kubenetes支持yml格式的部署脚本
kubectl create -f 部署yml文件 #创建部署
kubectl apply -f 部署yml文件 #更新部署配置
kubectl get pod -o wide #查看已部署pod
kubectl describe pod pod名称 #查看Pod详细信息
kubectl logs [-f] pod名称 #查看pod输出日志 -f是否实时更新
```

```shell
cd /usr/local
mkdir k8s
cd k8s
mkdir tomcat-deploy
cd tomcat-deploy
vim tomcat-deploy.yml
#配置内容
apiVersion: extensions/v1beta1 #版本标签
kind: Deployment  #部署
metadata:  #元数据
  name: tomcat-deploy
spec: #设置详细内容
  replicas: 2
  template:
    metadata:
      labels:
        app: tomcat-cluster #Pod名称
    spec:
      containers:
      - name: tomcat-cluster #当前创建容器的名字,通常和上面的app保持一致
        image: tomcat:latest
        ports:
        - containerPort: 8080 #容器内部对外暴露的端口

kubectl create -f ./tomcat-deploy.yml #当前目录继续执行
kubectl get deployment
kubectl describe pod tomcat-deploy-5fd4fc7ddb-ffb2f
```

### 外部访问Tomcat集群(NodePort方式)

```shell
cd /usr/local/k8s
mkdir tomcat-service
cd tomcat-service
vim tomcat-service.yml
#配置信息
apiVersion: v1
kind: Service
metadata:
  name: tomcat-service
  labels:
    app: tomcat-service #后期选择pod时使用的
spec:
  type: NodePort #设置节点端口与内部tomcat映射
  selector:
    app: tomcat-cluster #之前设置的label
  ports:
  - port: 8000 #service接收的端口
    targetPort: 8080 #容器内部对外暴露的端口
    nodePort: 32500  #每个node对外暴露的端口

kubectl create -f ./tomcat-service.yml #当前目继续执行
kubectl get service 
kubectl describe service tomcat-service #查看服务信息
```

### 基于NFS实现集群文件共享

```
Network File System 文件传输协议
NFS主要时采用 远程过程调用RPC机制实现文件传输
yum install -y nfs-utils rpcbind # master安装
```

```shell
将master 设定成文件共享服务器
cd /usr/local
mkdir data
cd data
mkdir www-data #f放置共享信息
cd www-data

vim /etc/exports
#配置信息
/usr/local/data/www-data 192.168.245.154/24(rw,sync) #可读可写 同步写入

#启动服务
systemctl start nfs.service
systemctl start rpcbind.service
systemctl enable  nfs.service
systemctl enable  rpcbind.service

exportfs
配置成功提示:
/usr/local/data/www-data
        192.168.245.154/24
```

```shell
node节点配置:
yum install -y nfs-utils
systemctl enable  nfs.service

showmount -e 192.168.245.154 #查看共享的文件夹
mount 192.168.245.154:/usr/local/data/www-data /mnt #挂载到本机的对应目录

演示！！！
master的/usr/local/data/www-data路径
vim test.txt 
    this is test 
node:
cd /mnt #可以访问到挂载的文件,获取信息
```

### 部署配置挂载点

```shell
如何在pod中与之前设置的 /mnt映射,需要修改部署脚本

master节点
kubectl get deploymen
kubectl delete deployment tomcat-deploy #删除之前的部署,对应pod也会删除
kubectl get pod 
kubectl get service 
kubectl delete service tomcat-service #删除对应的服务

cd /usr/local/k8s/tomcat-deploy
vim tomcat-deploy.yml
#修改后的配置项
apiVersion: extensions/v1beta1
kind: Deployment
metadata:
  name: tomcat-deploy
spec:
  replicas: 2
  template:
    metadata:
      labels:
        app: tomcat-cluster
    spec:
      volumes:
      - name: web-app
        hostPath:
          path: /mnt
      containers:
      - name: tomcat-cluster
        image: tomcat:latest
        ports:
        - containerPort: 8080
        volumeMounts:
        - name: web-app
          mountPath: /usr/local/tomcat/webapps
kubectl create -f  tomcat-deploy.yml
kubectl get deployment
kubectl get pod -o wide

如何验证文件是否已经挂载
方法一
node节点
docker exec -it 9ed2ddfc7b4a /bin/bash
cd webapps
cat test.txt #查看挂载信息

master节点修改挂载文件
vim /usr/local/data/www-data/test.txt
容器内部挂载内容同步修改

方法二
master节点
kubectl get pod -o wide
kubectl exec -it tomcat-deploy-6678dccdc9-6f7nb /bin/bash
cd webapps
```

两步实现:

首先通过nfs在每个节点上形成挂载点

然后被部署的容器通过 .yml的脚本设置目录与容器内部哪个目录对应

### 利用Rinted对外提供Service负载均衡支持

```shell
Service提供负载均衡实现

cd /usr/local/k8s/tomcat-service
kubectl get service #如果有,就先删除之前的服务,重新编辑
vim tomcat-service.yml
#注释两行,其他不变
apiVersion: v1
kind: Service
metadata:
  name: tomcat-service
  labels:
    app: tomcat-service
spec:
#  type: NodePort 
  selector:
    app: tomcat-cluster
  ports:
  - port: 8000
    targetPort: 8080
#    nodePort: 32500

kubectl create -f tomcat-service.yml #重新创建服务
kubectl get service #获取到IP:10.97.83.208
kubectl describe service tomcat-service #查看service IP端口信息
curl 10.97.83.208:8000 #访问404
```

```shell
cd /usr/local/data/www-data
mkdir test
cd test
vim index.jsp
    <%=request.getLocalAddr()%> #请求IP
curl 10.97.83.208:8000/test/index.jsp #显示负载,请求回的IP不同,随机分配
```

```shell
端口转发工具-Rinetd
Rinetd时Linux操作系统中为重定向传输控制协议工具
可将源IP端口数据转发至目标IP端口
在k8s中用于将service服务对外暴露

master安装:
cd /usr/local
上传压缩包
tar -zxvf rinetd.tar.gz
cd /usr/local/rinetd
sed -i  's/65536/65535/g' rinetd.c
mkdir -p /usr/man/ #软件要求动创建
make && make install #编译安装

vim /etc/rinetd.conf
0.0.0.0 8000 10.97.83.208 8000 
#kubectl get service 获取IP
#0.0.0.0 代表所有IP

rinetd -c /etc/rinetd.conf
netstat -tulpn #验证8000端口
192.168.245.154:8000
http://192.168.245.154:8000/test/index.jsp #正常访问到信息
```

### 更新集群配置与资源限定

```
更新集群配置
kubectl apply -f yml文件路径

删除部署deployment | 服务service
kubectl delete deployment|service 部署|服务名称
```

```shell
资源限定(resources:requests 基本需要 limits 最大资源)

cd /usr/local/k8s/tomcat-deploy
vim tomcat-deploy.yml
#配置选项
apiVersion: extensions/v1beta1
kind: Deployment
metadata:
  name: tomcat-deploy
spec:
  replicas: 3 #修改数量
  template:
    metadata:
      labels:
        app: tomcat-cluster
    spec:
      volumes:
      - name: web-app
        hostPath:
          path: /mnt
      containers:
      - name: tomcat-cluster
        image: tomcat:latest
        resources: #限定资源
          requests:
            cpu: 0.5
            memory: 200Mi
          limits:
            cpu: 1
            memory: 512Mi
        ports:
        - containerPort: 8080
        volumeMounts:
        - name: web-app
          mountPath: /usr/local/tomcat/webapps

kubectl get deployment
kubectl apply -f tomcat-deploy.yml
#k8s默认分配到负载最低的机器上
```

### 贝亲商城K8S实战-构建NFS文件共享

```shell
上次资料到master节点

vim /etc/exports
    /usr/local/beiqin/dist 192.168.245.154/24(rw,sync)
    /usr/local/beiqin/sql 192.168.245.154/24(rw,sync)
systemctl restart nfs.service
systemctl restart rpcbind.service
exportfs #验证
```

```shell
node操作设置挂载点

mkdir /usr/local/beiqin-dist
mkdir /usr/local/beiqin-sql
systemctl restart nfs.service

mount 192.168.245.154:/usr/local/beiqin/dist  /usr/local/beiqin-dist
mount 192.168.245.154:/usr/local/beiqin/sql  /usr/local/beiqin-sql

ls /usr/local/beiqin-dist #出现master上传的文件
ls /usr/local/beiqin-sql 
```

### 贝亲商城K8S实战-部署并初始数据库

```shell
master节点操作

cd /usr/local/beiqin
vim beiqin-db-deploy.yml
#配置文件
apiVersion: apps/v1beta1
apiVersion: apps/v1beta1
kind: Deployment
metadata:
  name: beiqin-db-deploy
spec:
  replicas: 1
  template:
    metadata:
      labels:
        app: beiqin-db-deploy
    spec:
      volumes:
      - name: beiqin-db-volume
        hostPath:
          path: /usr/local/beiqin-sql
      containers:
      - name: beiqin-db-deploy
        image: mysql:5.7
        ports:
        - containerPort: 3306
        env:
        - name: MYSQL_ROOT_PASSWORD
          value: "root"
        volumeMounts:
        - name: beiqin-db-volume
          mountPath: /docker-entrypoint-initdb.d

kubectl create -f beiqin-db-deploy.yml #创建
kubectl exec -it beiqin-db-deploy-c7785f9d4-tp5pd /bin/bash
    mysql -uroot -proot #密码也是root
    use beiqin
    show tables;
    select count(*) from t_goods; #验证完成


vim beiqin-db-service.yml
#服务配置信息
apiVersion: v1
kind: Service
metadata:
  name: beiqin-db-service
  labels:
    app: beiqin-db-service
spec:
  selector:
    app: beiqin-db-deploy
  ports:
  - port: 3310 #服务对外暴露端口
    targetPort: 3306 #容器暴露端口

kubectl create -f  beiqin-db-service.yml #创建
kubectl get svc #kubectl get service 简写
kubectl describe service beiqin-db-service #查看服务详情
```

### 贝亲商城K8S实战-部署Web应用

```
master节点操作

cd /usr/local/beiqin
vim beiqin-app-deploy.yml
#配置文件
apiVersion: apps/v1beta1
kind: Deployment
metadata:
  name: beiqin-app-deploy
spec:
  replicas: 2
  template:
    metadata:
      labels:
        app: beiqin-app-deploy
    spec:
      volumes:
      - name : beqin-app-volume
        hostPath:
          path: /usr/local/beiqin-dist #宿主机目录
      containers:
      - name: beiqin-app-deploy
        image: openjdk:8u222-jre
        command: ["/bin/sh"]
        args: ["-c","cd /usr/local/beiqin-dist;java -jar beiqin-app.jar"]
        volumeMounts:
        - name: beqin-app-volume
          mountPath: /usr/local/beiqin-dist #容器内的目录


kubectl create -f  beiqin-app-deploy.yml
kubectl logs -f beiqin-app-deploy-596fd7c4dd-lsxgt

cd /usr/local/beiqin/dist
vim application.yml #查看配置信息,使用service名称代替IP地址


curl 10.244.1.8:80/goods?gid=1788 #利用pod IP 请求回信息


#配置service

cd /usr/local/beiqin
vim beiqin-app-service.yml
#配置信息
apiVersion: v1
kind: Service
metadata:
  name: beiqin-app-service
  labels:
    app: beiqin-app-service
spec:
  selector:
    app: beiqin-app-deploy
  ports:
  - port: 80
    targetPort: 80

kubectl create -f beiqin-app-service.yml
kubectl describe service beiqin-app-service #获取IP 10.111.33.194

curl 10.111.33.194/goods?gid=1788 #宿主机内部访问
```

```
master设置端口转发
vim /etc/rinetd.conf
    0.0.0.0 80 10.111.33.194 80

rinetd -c /etc/rinetd.conf

192.168.245.154/goods?gid=1788 #外部浏览器可以访问
```

# Kubernetes

# 附录

```

```
