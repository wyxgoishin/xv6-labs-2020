#include "kernel/types.h"
#include "user/user.h"

int get_digit(int x){
	int digit = 1;
	while(x >= 10){
		digit++;
		x /= 10;
	}
	return digit;
}

char* integer2String(int num){
	int digit = get_digit(num);
	char* snum = (char*)malloc(sizeof(char) * digit);
	int i = 0;
	for(; i < digit; i++){
		*(snum + digit - i - 1) = num % 10 + '0';
		num /= 10;
	}
	return snum;
}

int main(){
	int p[2];
	pipe(p);
	char* sentByte = "b";
	
	write(p[1], sentByte, 1);

	if(fork() == 0){
		char ca[1];
		read(p[0], ca, 1);

		char* spid = integer2String(getpid());
		write(1, spid, strlen(spid));
		write(1, ": received ping\n", 16);
		write(p[0], sentByte, 1);
		exit(0);
	}else{
		wait(0);
		
		char ca[1];
		read(p[1], ca, 1);
		char* spid = integer2String(getpid());
		write(1, spid, strlen(spid));
		write(1, ": received pong\n", 16);
	}
	exit(0);
}
