#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

void shell_loop();
char *read_input();
char **parse_input(char *input);
int execute_command(char **args);
int shell_cd(char **args);
int shell_exit(char **args);

// Built-in command names and functions
char *builtin_str[] = { "cd", "exit" };
int (*builtin_func[]) (char **) = { &shell_cd, &shell_exit };
int num_builtins() { return sizeof(builtin_str) / sizeof(char *); }

int main() {
    shell_loop();
    return 0;
}

void shell_loop() {
    char *input;
    char **args;
    int status;

    do {
        printf("mybash> ");
        input = read_input();
        args = parse_input(input);
        status = execute_command(args);

        free(input);
        free(args);
    } while (status);
}

char *read_input() {
    char *buffer = malloc(MAX_INPUT);
    if (!buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (fgets(buffer, MAX_INPUT, stdin) == NULL) {
        free(buffer);
        exit(EXIT_SUCCESS); // Handle Ctrl+D
    }

    // Remove newline character
    buffer[strcspn(buffer, "\n")] = '\0';
    return buffer;
}

char **parse_input(char *input) {
    char **args = malloc(MAX_ARGS * sizeof(char *));
    char *token;
    int position = 0;

    if (!args) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    token = strtok(input, " ");
    while (token != NULL) {
        args[position++] = token;
        token = strtok(NULL, " ");
    }
    args[position] = NULL;
    return args;
}

int execute_command(char **args) {
    if (args[0] == NULL) {
        return 1; // Empty command
    }

    for (int i = 0; i < num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0) {
            return (*builtin_func[i])(args);
        }
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(args[0], args) == -1) {
            perror("mybash");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork");
    } else {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    }
    return 1;
}

int shell_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "mybash: expected argument to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("mybash");
        }
    }
    return 1;
}

int shell_exit(char **args) {
    return 0;
}