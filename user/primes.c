#include "kernel/types.h"
#include "user/user.h"

void process(int p[]){	
	int p1[2];
	pipe(p1);

	int nxt, prime = -1, num = 0;
	while(read(p[0], &nxt, 4) > 0){
		if(prime == -1){
			prime = nxt;
			printf("prime %d\n", prime);
		}else if(nxt % prime != 0){
			write(p1[1], &nxt, 4);
			num++;
		}
	}
	close(p[0]);
	close(p1[1]);

	if(num > 0){
		if(fork() > 0){
			wait(0);
		}else{
			process(p1);
		}
	}
}

int main(){
	int p[2];
	pipe(p);

	int i = 2;
	for(; i <= 35; i++){
		write(p[1], &i, 4);
	}
	close(p[1]);

	process(p);
	exit(0);
}
