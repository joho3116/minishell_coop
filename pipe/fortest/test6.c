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



		// input redirection
			// if (input 리디렉션 있으면 다 확인할 때까지)
			int inputfd;
			char tmp1[] ="/home/chanhlee/goinfre/minishell_coop/pipe/fortest/test.c";
			// tmp1[55] = (idx % 10) + '0';
			if ((inputfd = open(tmp1, O_RDONLY)) < 0){
				dprintf(2, "open rd fail\n");
				return (0);
			}
			dup2(inputfd, 0); // openfd로 fd==0이 향하게
		////////////////////////////


		// output redirectio
			int outputfd;
			char tmp2[] ="/home/chanhlee/goinfre/minishell_coop/pipe/fortest/outputx";
			tmp2[57] = (idx % 10) + '0';
			if ((outputfd = open(tmp2, O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0){
				dprintf(2, "open out fail\n");
				return (0);
			}
			dup2(outputfd, 1); // 자동으로 기존 pipe의 fd는 close되는 효과
		///////////////////////



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
