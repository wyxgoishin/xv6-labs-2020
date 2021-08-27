#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

static char *cur = ".";
static char *parent = "..";

char* fmtname(char *path){
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void find(char *path, char *pattern){
	char buf[64], *p;
	int fd;
	struct dirent de;
	struct stat st;
	
	if((fd = open(path, 0)) < 0){
   		fprintf(2, "find: cannot open %s\n", path);
    	return;
  	}

  	if(fstat(fd, &st) < 0){
    	fprintf(2, "find: cannot stat %s\n", path);
    	close(fd);
    	return;
  	}
	
	if(st.type == T_FILE && strcmp(fmtname(path), pattern) == 0){
		printf("%s\n", path);
	}

	if(st.type == T_DIR){
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)){
			printf("find: path too long\n");
		}
		strcpy(buf, path);
		p = buf + strlen(buf);
		*p++ = '/';
		while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0 || strcmp(de.name, cur) == 0 || strcmp(de.name, parent) == 0){
				continue;
			}
			memmove(p, de.name, DIRSIZ);
			p[DIRSIZ] = 0;
			if(stat(buf, &st) < 0){
        		printf("find: cannot stat %s\n", buf);
       		 	continue;
     		}
			if(strcmp(de.name, pattern) == 0){
				printf("%s\n", buf);
			}
			if(st.type == T_DIR){
				find(buf, pattern);
			}	
		}
	}
	close(fd);	
}

int main(int argc, char *argv[]){
	if(argc >= 3){
		find(argv[1], argv[2]);
	}
	exit(0);
}
