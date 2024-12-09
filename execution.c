
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

        // Séparation de la commande en arguments
        char *input_copy = strdup(command); // Copie de la commande pour éviter de modifier l'originale
        if (!input_copy) {
            perror("strdup error");
            exit(EXIT_FAILURE);
        }

        // Tokenisation de la chaîne en mots (séparés par des espaces)
        char *token = strtok(input_copy, " ");
        char *argv[256]; // Limité à 256 arguments
        int argc = 0;
         while (token != NULL && argc < 255) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL; // Terminaison du tableau

        // Exécuter la commande
        execvp(argv[0], argv);

        // Si execvp échoue
        perror("Command execution failed");
        free(input_copy);
        exit(EXIT_FAILURE);
        
    } else {
        
        // Processus parent
        waitpid(pid, status, 0); // Attend la fin du processus enfant et récupère le statut
        clock_gettime(CLOCK_MONOTONIC, &end);

                //calcul du temps écoulé en millisecondes
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