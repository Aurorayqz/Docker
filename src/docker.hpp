//
// docker.hpp
// cpp_docker
//
#include <sys/wait.h>   // waitpid
#include <sys/mount.h>  // mount
#include <fcntl.h>      // open
#include <unistd.h>     // execv, sethostname, chroot, fchdir
#include <sched.h>      // clone

// C 标准库
#include <cstring>

// C++ 标准库
#include <string>       // std::string

#define STACK_SIZE (512 * 512) // 定义子进程空间大小

namespace docker {
	
	typedef int proc_statu;
	proc_statu proc_err  = -1;
	proc_statu proc_exit = 0;
	proc_statu proc_wait = 1;

	typedef struct container_config
	{
		std::string host_name;
		std::string root_dir;
	}container_config; 

	class container
	{
	private:
		// 可读性增强
		typedef int process_pid;

		// 子进程栈
		char child_stack[STACK_SIZE];

		// 容器配置
		container_config config;

	public:
		container(container_config &config){
			this->config=config
		}
		
		void start(){
			auto setup = [](void *)
		}		
	};
}