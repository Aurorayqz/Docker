# Simple Docker

## 项目介绍
 - Docker 的本质是使用 LXC 实现类似虚拟机的功能，进而节省的硬件资源提供给用户更多的计算资源。本项目将 C++ 与 Linux 的 Namespace 及 Control Group 技术相结合，实现一个简易 Docker 容器。
## Linux 相关
- Namespace
- Control Group
## Linux 系统调用
- clone()
- chdir()
- chroot()
- sethostname()
- mount()
- execv()
- ……
## C++相关
- namespace
- lambda expression
- C/C++ 混合编译
## 实现效果
- 独立的主机名
- 独立的文件系统
- 独立的进程系统
- 网络访问的支持
- 容器资源的限制
