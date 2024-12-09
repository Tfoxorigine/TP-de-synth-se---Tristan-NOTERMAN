
#include "execution.h"
#include "prompt.h"
#include <sys/types.h>
#include <sys/wait.h>   // pour waitpid
#include <unistd.h>     // pour fork, execvp
#include <stdlib.h>     // pour exit, malloc, free
#include <stdio.h>      // pour perror
#include <string.h>     // pour strdup

// zwécutz une commande utilisateur
void execute_command(const char *command, int *status) {
    pid_t pid = fork(); // Crée un processus enfant
    if (pid == -1) {
        // si rrreur lors du fork
        perror("Fork error");
        *status = -1;
        return;
    }
    if (pid == 0) {
        // Processus enfant
        char *argv[] = {strdup(command), NULL};
        if (!argv[0] || strlen(argv[0]) == 0) {
            perror("Invalid command");
            free(argv[0]);
            *status = 1;
            return;
        }
        execvp(argv[0], argv); // exécute la commande
        // Si execvp échoue, affiche un message et quitte
        perror("Command execution failed");
        free(argv[0]);
        exit(EXIT_FAILURE);
    } else {
        // Processus parent
        waitpid(pid, status, 0); // Attend la fin du processus enfant et récupère le statut
    }
}