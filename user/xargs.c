#include "kernel/types.h"
#include "user/user.h"
#include "kernel/param.h"

int main(char argc, char* argv[]){
	char buf[64];
	int n;
	// 没有参数，读到什么输出什么（仿xargs默认功能）
	if(argc < 2){
		while((n = read(0, buf, sizeof buf)) > 0){
			write(1, buf, n);
		}
	}else{
		char* args[MAXARG];
		int numArg;
		for(int i = 1; i < argc; i++){
			args[i - 1] = argv[i];
		}
		numArg = argc - 1;
		char* p = buf;
		while(read(0, p, 1) > 0){
			if(*p == '\n'){
				*p = 0;
				if(fork() != 0){
					wait(0);
				}else{
					args[numArg] = buf;
					exec(args[0], args);
					exit(0);
				}
				p = buf;
			}else{
				p++;
			}
		}
	}
	exit(0);
}
