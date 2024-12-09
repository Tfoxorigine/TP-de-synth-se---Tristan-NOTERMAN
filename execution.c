
#include "execution.h"
#include "prompt.h"
#include <sys/types.h>
#include <sys/wait.h>   // pour waitpid
#include <unistd.h>     // pour fork, execvp
#include <stdlib.h>     // pour exit, malloc, free
#include <stdio.h>      // pour perror
#include <string.h>     // pour strdup
#include "return42.h"
#include <time.h>

// zwécutz une commande utilisateur
void execute_command(const char *command, int *status) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start); // Temps de début

// commandes internes 
    if (strcmp(command, "return42") == 0) {
        // Gérer la commande "return42"
        return42(); // 
        return; // on ne doit jamais atteindre cette ligne
    }

    pid_t pid = fork(); // Crée un processus enfant
    if (pid == -1) {
        // si rrreur lors du fork
        perror("Fork error");
        *status = -1;
        return;
    }
    if (pid == 0) {
        // Processus enfant
        char *argv[] = {strdup(command), NULL}; //Alloue une nouvelle chaîne de caractères en mémoire et copie le contenu de command dans cette chaîne
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
        clock_gettime(CLOCK_MONOTONIC, &end);

                // Calcul du temps écoulé en millisecondes
        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        long elapsed_ms = seconds * 1000 + nanoseconds / 1000000;

              // Mettre à jour la variable `status` pour inclure le temps d'exécution
        printf("[Execution Time: %ldms]\n", elapsed_ms);

        // Mise à jour du prompt avec le temps d'exécution
        if (WIFEXITED(*status)) {
            printf("enseash [exit:%d|%ldms] %% ", WEXITSTATUS(*status), elapsed_ms);
        } else if (WIFSIGNALED(*status)) {
            printf("enseash [sign:%d|%ldms] %% ", WTERMSIG(*status), elapsed_ms);
        }


    }
}