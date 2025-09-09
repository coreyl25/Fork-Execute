# Fork-Execute
OS Lab — Processes & fork() in C
This repository contains solutions for the Operating Systems lab on Unix processes, fork() system calls, and process management.
Building and Running
Use CMake 
mkdir -p build && cd build
cmake ..
cmake --build .

# Run demos
./fork_demo
./exec_demo
./pipe_demo
./pipeline_demo
./zombie_demo
Important Notes
Zombie Processes
Child processes become zombies when they exit before parent calls wait()
Run ps -l while zombie_demo is sleeping to see Z state entries
Always call wait() or waitpid() to clean up child processes
Error Handling
Always check return values of fork(), pipe(), exec functions
Use perror() for system call error messages
Child processes should use _exit() instead of exit() after fork
Testing
Run each program and observe:
Process IDs and parent-child relationships
Exit status handling and reporting
Concurrent execution and synchronization
Pipe communication and data flow
Zombie process creation and cleanup
Environment
Tested on Ubuntu VM and GitHub Codespaces
Requires standard POSIX environment with gcc/clang, make, cmake
Uses common Unix utilities: ls, wc, echo

