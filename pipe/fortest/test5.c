#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *cat = "/usr/bin/cat";
char *catcmds[] = {"/usr/bin/cat", (void *)NULL};

char *echo = "/usr/bin/echo";
char *echocmds[] = {"/usr/bin/echo", "hello", (void *)NULL};



void	copy_pipe_fd(int a[], int b[]){
	a[0] = b[0];
	a[1] = b[1];
}

// 모든 커맨드가 cat, 리디렉션 없고 파이프만

int main(int argc, char *argv[], char *envp[]){
	int pipe0[2];
	int pipe1[2];
	int pipe2[2];
	int stat;

	int	last = 4; // 커맨드 갯수
	int idx = 0;

	while (idx < last){
		if (idx == last){
			break ;
		}
		pipe(pipe1);
		int fd;
		fd = fork();
		if (fd == 0){ // child
		// 공통

			// 기본 input, output 셋팅
			///////////////////////
			if (idx != 0){
				close(pipe0[1]);
				dup2(pipe0[0], 0);
			}

			close(pipe1[0]);
			if (idx == last - 1){
				close(pipe1[1]);
			}else{
				dup2(pipe1[1], 1);
			}
			////////////////////////


			execve(cat, catcmds, envp);
			dprintf(2, "execve fail1\n");
			return (0);
		}
		if (idx != 0){
			close(pipe0[0]);
			close(pipe0[1]);
		}
		copy_pipe_fd(pipe0, pipe1);
		waitpid(fd, &stat, 0);
		++idx;
	}
}
