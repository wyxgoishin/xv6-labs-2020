#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]){
	char *message;
	if(argc <= 1){
		message = "error\n";
	}else{
		message = "(nothing happens for a little while)\n";
	}

	write(1, message, strlen(message));
	if(argc >= 2){
		sleep(atoi(argv[1]));
	}
	exit(0);
}
