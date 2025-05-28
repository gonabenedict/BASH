

 Custom Shell in C

A simple, yet powerful command-line shell implemented in C, designed to mimic basic functionalities of a Unix/Linux bash terminal. This project demonstrates proficiency in C programming, system calls, process management, and command parsing.



 🧑‍💻 About the Project

This shell program allows users to execute commands interactively from the terminal. It supports:

 Executing system commands with arguments.
 Built-in commands like `cd`, `exit`, and `help`.
 Handling multiple commands separated by semicolons.
 Background process execution using `&`.
 Basic input/output redirection (`>`, `<`).
 Signal handling for `Ctrl+C` (SIGINT) to safely terminate foreground processes.



 🔧 Key Features & Skills Demonstrated

Process Management: Using `fork()`, `execvp()`, and `waitpid()` to create and manage child processes.
Command Parsing: Tokenizing user input, handling arguments, and parsing special characters.
File I/O & Redirection: Implementing input/output redirection with `dup2()` and file descriptors.
Signal Handling:Managing asynchronous events with signal handlers.
Memory Management: Careful use of dynamic memory allocation (`malloc`, `free`) to avoid leaks.
error Handling: Robust checks for system call failures and invalid inputs.



what I Learned

This project deepened my understanding of:

 Low-level system programming in C.
 Interaction between user-level programs and OS kernel.
 Writing modular, maintainable C code.
 Debugging with `gdb` and memory analysis with `valgrind`.



