#include "kernel/types.h"
#include "user/user.h"

int main(){
	char buf[512];
	char* p = buf;
	while(read(0, p++, 1) != 0);
	printf("%s\n", buf);
	exit(0);
}
