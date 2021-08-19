#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

char *cat = "/usr/bin/cat";
char *catcmds[] = {"/usr/bin/cat", (void *)NULL};

char *echo = "/usr/bin/echo";
char *echocmds[] = {"/usr/bin/echo", "hello", (void *)NULL};


// 자식 : fd 1은 pipe1[1]로 fd 0은 open된 fd로
// 부모 : fd 0은 pipe1[0]으로

int main(int argc, char *argv[], char *envp[]){
	int pipe1[2];
	int pipe2[2];
	int pipe3[2];
	int stat;



	pipe(pipe1);
	pipe(pipe2);
	int fd;
	fd = fork();
	if (fd == 0){ // child
	// 공통
		close(pipe1[0]);
		dup2(pipe1[1], 1);
	// input redirection
		int openfd;
		if ((openfd = open("/home/chanhlee/goinfre/minishell_coop/pipe/fortest/test.c", O_RDONLY)) < 0){
			dprintf(2, "open rd fail\n");
			return (0);
		}
		dup2(openfd, 0); // openfd로 fd==0이 향하게
	// output redirectio



		execve(echo, echocmds, envp);
		dprintf(2, "execve fail1\n");
	}else{
		waitpid(fd, &stat, 0);
		close(pipe1[1]);
		dup2(pipe1[0], 0);
		execve(cat, catcmds, envp);
		dprintf(2, "execve fail2\n");
	}
}