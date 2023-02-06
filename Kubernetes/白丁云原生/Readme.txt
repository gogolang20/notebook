#-----------------------------------------#-----------------------------------------#
#-----------------------------------------#-----------------------------------------#
client源码结构:
client-go 与k8s的 api-server 通信 !!!

discovery -- 用于发现 api-server 支持的 API
dynamic -- 可以操作任意的 API 对象,包括自定义的
informers -- 包含所有类资源的 informer, 便于操作k8s 的资源对象
kubernetes -- 包含所有访问 k8s API是clientset
lister -- 读取缓存中 k8s 资源对象的信息
plugin/pkg/client/auth -- 包含所有可选的认证插件
tools -- 工具
transport -- 创建 连接 认证的逻辑,被上层的 clientset使用


#-----------------------------------------#-----------------------------------------#
项目需求
#-----------------------------------------#-----------------------------------------#
1 新增service时
	自定义conroller 会根据 annotation,创建ingress资源对象
2 删除service时
	删除ingress资源对象
3 更新service时
	包含指定的annotation,检查ingress资源对象是否存在,不存在则创建,存在则忽略
	不包含指定的annotation,检查ingress资源对象是否存在,存在则删除,不存在则忽略
#隐藏需求
当ingress被删除的时候,通过ingress找到对应的service,通过service的
annotation 决定ingress是否重建。


#-----------------------------#-----------------------------#
11-4 test and bug fix
#-----------------------------#-----------------------------#
视频安装ingress方式
kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/controller-v1.2.0/deploy/static/provider/cloud/deploy.yaml

minikube 安装 ingress:
	minikube addons enable ingress


k get po -n ingress-nginx // ingress-nginx-controller
k get pod // need nginx
k get svc // need nginx service 
k get ingress
k edit svc nginx // check annotations 

Round 1
Start main.go
k edit svc nginx --> delete annotations  `ingress/http: "true"`
k get ingress // should be delete
# Fix OwnerReference

Round 2
k get ingress // not exist
k get svc // nginx exist
k edit svc nginx --> add annotations  `ingress/http: "true"`
k get ingress // should be create
k get ingress -o yaml // uid should equal to service uid
K get svc nginx -o yaml // check uid

k edit svc nginx --> delete annotations  `ingress/http: "true"` // should delete ingress
k get ingress // should be delete

Round 3
k edit svc nginx --> add annotations  `ingress/http: "true"` again
k get ingress // created again
k delete ingress nginx // delete ingress should be recreated
k get ingress -o yaml

Round 4
k get svc
k get ingress
k delete svc nginx // should delete ingress
k get ingress // check delete or not
k get pods // check nginx pods
k expose pods nginx --port=80 
k edit svc nginx --> add annotations  `ingress/http: "true"`
k get ingress // should be create

Round 5 
k expose pods nginx --port=80 
k edit svc nginx --> add annotations  `ingress/http: "true"`
k get ingress // should be create
k get svc -n ingress-nginx
minikube ssh
ip a
Firefox: minikube_eth1_IP:{ingress-nginx}svc_port
Fix IngressClassName at code, and use domain name example.com:port
vim /etc/hosts
	IP example.com


#-----------------------------#-----------------------------#
11-5 Deploy
#-----------------------------#-----------------------------#
minikube ssh
pwd // /home/docker
mkdir client-go
mikubue mount ../operator:/home/docker/client-go # coding Dir mount to minikube Dir
docker build -t golang20/ingress-manager:1.0.0 .
docker push golang20/ingress-manager:1.0.0

kubectl create deployment ingress-manager --image golang20/ingress-manager:1.0.0 --dry-run=client -o yaml > manifests/ingress-manager.yaml
kubectl apply -f manifests/ingress-manager.yaml (error)
kubectl create serviceaccount ingress-manager-sa --dry-run=client -o yaml > manifests/ingress-manager-sa.yaml (deployment add this sa)
kubectl create role ingress-manager-role --resource=ingress,service --berb list,watch,create,update,delete --dry-run=client -o yaml > manifests/ingress-manager-role.yaml
(services delete create,update,delete in ingress-manager-role.yaml)


网址: https://github.com/kubernetes/code-generator
git clone https://github.com/kubernetes/code-generator.git
git checkout v{k8s version}
go install ./cmd/{client-gen,deepcopy-gen,informer-gen,lister-gen}

