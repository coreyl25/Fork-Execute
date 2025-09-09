#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2];

    if (pipe(fd) == -1) { 
        perror("pipe"); 
        exit(1); 
    }

    // Fork first child for 'ls'
    pid_t pid1 = fork();
    if (pid1 < 0) { 
        perror("fork"); 
        exit(1); 
    }

    if (pid1 == 0) {
        // First child: ls
        close(fd[0]);  // close read end
        dup2(fd[1], STDOUT_FILENO);  // redirect stdout to pipe
        close(fd[1]);

        execlp("ls", "ls", (char *)NULL);
        perror("execlp ls");
        _exit(1);
    }

    // Fork second child for 'grep'
    pid_t pid2 = fork();
    if (pid2 < 0) { 
        perror("fork"); 
        exit(1); 
    }

    if (pid2 == 0) {
        // Second child: grep
        close(fd[1]);  // close write end
        dup2(fd[0], STDIN_FILENO);  // redirect stdin to pipe
        close(fd[0]);

        execlp("grep", "grep", "demo", (char *)NULL);
        perror("execlp grep");
        _exit(1);
    }

    // Parent: close both ends and wait for children
    close(fd[0]);
    close(fd[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}
