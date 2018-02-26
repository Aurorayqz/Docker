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

		void start_bash(){
			// 将 C++ std::string 安全的转换为 C 风格的字符串 char *
    		// 从 C++14 开始, C++编译器将禁止这种写法 `char *str = "test";`
    		std::string bash="/bin/bash";
    		char *c_bash=new char[bash.length()+1];
    		strcpy(c_bash, bash.c_str());

    		char* const child_args[]={c_bash,NULL};
    		execv(child_args[0], child_args); // 在子进程中执行 /bin/bash
    		delete []c_bash;
		}

		// 设置容器主机名
		void set_hostname(){
			sethostname(this->config.host_name.c_str(), this->config.host_name.length());
		}

		// 设置根目录
		void set_rootdir(){
			// chdir 系统调用, 切换到某个目录下
			chdir(this->config.root_dir.c_str());

			// chrrot 系统调用, 设置根目录, 因为刚才已经切换过当前目录
    		// 故直接使用当前目录作为根目录即可
    		chroot(".");
    		printf("hello world\n");
		}

		// 设置独立的进程空间
		void set_procsys() {
		    // 挂载 proc 文件系统
		    mount("none", "/proc", "proc", 0, nullptr);
		    mount("none", "/sys", "sysfs", 0, nullptr);
		}

	public:
		container(container_config &config){
			this->config=config;
		}
		
		void start(){
			auto setup = [](void *args) -> int{
				// 对容器进行相关配置
        		auto _this=reinterpret_cast<container *>(args);

        		_this->set_hostname();
        		_this->set_rootdir();
        		_this->set_procsys();
        		_this->start_bash();

        		return proc_wait;
			};
			process_pid child_pid=clone(setup,child_stack+STACK_SIZE,
				CLONE_NEWUTS|	// UTS   namespace
				CLONE_NEWNS|	// Mount namespace
				CLONE_NEWPID| // PID   namespace
				SIGCHLD,		// 子进程退出时会发出信号给父进程
				this);
			waitpid(child_pid, nullptr, 0);
		}		
	};
}