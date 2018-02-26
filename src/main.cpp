//
// main.cpp
// cpp_docker
//

#include "docker.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
	std::cout<<"...start container"<<std::endl;
	docker::container_config config;

    // 配置容器
    // ...
    config.host_name="aurorayqz_docker";
    config.root_dir="..";

    // 配置网络参数
    config.ip = "192.168.0.100"; 		// 容器 IP
    config.bridge_name = "docker0";     // 宿主机网桥
    config.bridge_ip   = "192.168.0.1"; // 宿主机网桥 IP

    

    docker::container container(config);// 根据 config 构造容器
    container.start();// 启动容器
    std::cout<<"stop container..."<<std::endl;

	return 0;
}