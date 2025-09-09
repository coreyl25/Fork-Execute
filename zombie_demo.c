#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    printf("Run './zombie_demo' in shell and 'ps -l' in another terminal to see zombie state entries.\n");
    printf("Then modify program to wait() quickly to avoid zombies.\n\n");

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child exits immediately - will become zombie until parent waits
        printf("[child] PID=%d, PPID=%d - exiting immediately\n", getpid(), getppid());
        _exit(0);
    } else {
        // Parent sleeps for 10 seconds - child becomes zombie during this time
        printf("[parent] child PID=%d created, sleeping 10 seconds...\n", pid);
        printf("Check 'ps -l' output in another terminal for zombie (Z state)\n");
        
        sleep(10);  // Child is zombie during this time
        
        // Now wait for child
        int status;
        pid_t w = waitpid(pid, &status, 0);
        
        if (w == -1) {
            perror("waitpid");
            exit(1);
        }
        
        printf("[parent] cleaned up zombie child %d\n", w);
    }

    return 0;
}
