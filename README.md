# LinuxMonitor
## 模块介绍
### docker
基础环境搭建，基于Ubuntu18.04镜像安装了Qt5,gRPC，protobuf以及相关依赖
### display
Qt展示模块，客户端模块
### proto
protobuf源文件，基础的序列化数据结构
### rpc_manage
rpc服务以及提供用户调用的stub
### monitor
运行在服务端，用于读取伪目录`/proc`下的各种信息

## 安装

创建docker环境

```bash
cd /path/LinuxMonitor/docker/build				
docker build --network host -f ./dockfile -t linux:monitor .	 
```

启动并进入容器

```bash
cd ../scripts
./monitor_docker_run.sh
./monitor_docker_into.sh
```

构建工程

```bash
cd /work
mkdir build && cd build
cmake ..
make -j8
```

## 使用

客户端和服务端可以分开使用，客户端和服务端的公用模块式proto以及rpc_manage

其中monitor是服务端需要使用的，display则是客户端使用的

如果分开使用服务端和客户端，客户端的dockerfile可以去除Qt的安装来减少镜像大小。

以下示例为监控本地：

终端一

```bash
cd /path/LinuxMonitor
./docker/scripts/monitor_docker_into.sh	# 如果已经在容器中，不需要执行该步骤
./build/rpc_manager/server/server localhost:50051	# 启动gRPC服务监听本地50051端口
```

终端二

```bash
cd /path/LinuxMonitor
./docker/scripts/monitor_docker_into.sh	# 如果已经在容器中，不需要执行该步骤
./build/monitor/src/monitor localhost:50051		# 启动服务器monitor设置服务端通信端口
```

终端三

```bash
cd /path/LinuxMonitor
./docker/scripts/monitor_docker_into.sh	# 如果已经在容器中，不需要执行该步骤
./build/display/display localhost:50051		# 启动客户端，通过50051端口通信
```

