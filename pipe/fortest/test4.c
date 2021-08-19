#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>

char *cat = "/usr/bin/cat";
char *catcmds[] = {"/usr/bin/cat", (void *)NULL};

char *echo = "/usr/bin/echo";
char *echocmds[] = {"/usr/bin/echo", "hello", (void *)NULL};

// child : fd 1은 open된 아웃풋으로
// parent : fd 0은 pipe[0]으로

int main(int argc, char *argv[], char *envp[]){
	int pipe0[2];
	int pipe1[2];
	int pipe2[2];
	int stat;



	pipe(pipe0);
	pipe(pipe1);
	int fd;
	fd = fork();
	if (fd == 0){ // child
	// 공통

		// 기본 input, output 셋팅
		///////////////////////
		close(pipe0[1]);

		// if (첫번째 커맨드)
			close(pipe0[0]);
		// else
		// 	dup2(pipe0[0], 0);

		close(pipe1[0]);
		dup2(pipe1[1], 1);
		////////////////////////

	// // input redirection
	// 	int inputfd;
	// 	if ((inputfd = open("/home/chanhlee/goinfre/minishell_coop/pipe/fortest/test.c", O_RDONLY)) < 0){
	// 		dprintf(2, "open rd fail\n");
	// 		return (0);
	// 	}
	// 	dup2(inputfd, 0); // openfd로 fd==0이 향하게

	// output redirectio
		int outputfd;
		if ((outputfd = open("/home/chanhlee/goinfre/minishell_coop/pipe/fortest/output4",\
		O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR)) < 0){
			dprintf(2, "open out fail\n");
			return (0);
		}
		dup2(outputfd, 1); // 자동으로 기존 pipe의 fd는 close되는 효과


		execve(cat, catcmds, envp);
		dprintf(2, "execve fail1\n");
	}else{
		close(pipe0[0]);
		close(pipe0[1]);
		waitpid(fd, &stat, 0);
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		execve(cat, catcmds, envp);
		dprintf(2, "execve fail2\n");
	}
}
