
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

        // Son sépare la commande en arguments
        char *input_copy = strdup(command); //copie de la commande pour éviter de modifier l'originale
        if (!input_copy) {
            perror("strdup error");
            exit(EXIT_FAILURE);
        }

        // on analyse la commande pour détecter les redirections
        char *input_file = NULL;
        char *output_file = NULL;

        

        // on sépare la chaîne en mots (séparés par des espaces)
        char *token = strtok(input_copy, " ");
        char *argv[256]; // limité de 256 arguments
        int argc = 0;

        while (token != NULL) {
            if (strcmp(token, "<") == 0) {
                token = strtok(NULL, " ");
                if (token) {
                    input_file = token;
                } else {
                    fprintf(stderr, "Error: Missing input file for redirection '<'\n");
                    free(input_copy);
                    exit(EXIT_FAILURE);
                }
            } else if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                if (token) {
                    output_file = token;
                 } else {
                    fprintf(stderr, "Error: Missing output file for redirection '>'\n");
                    free(input_copy);
                    exit(EXIT_FAILURE);
                }
            } else {
                argv[argc++] = token;
            }
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL; // Fin du tableau des arguments

        // Gestion des redirections
        if (input_file) {
            FILE *in = fopen(input_file, "r");
            if (!in) {
                perror("Input file open error");
                free(input_copy);
                exit(EXIT_FAILURE);
            }
            dup2(fileno(in), STDIN_FILENO);
            fclose(in);
        }

        if (output_file) {
            FILE *out = fopen(output_file, "w");
            if (!out) {
                perror("Output file open error");
                free(input_copy);
                exit(EXIT_FAILURE);
            }
            dup2(fileno(out), STDOUT_FILENO);
            fclose(out);
        }
        
        // Exécuter la commande
        execvp(argv[0], argv);

        // Si execvp échoue
        perror("Command execution failed");
        free(input_copy);
        exit(EXIT_FAILURE);

    } else {
        
        // Processus parent
        waitpid(pid, status, 0); // on attend la fin du processus enfant et on récupère le statut
        clock_gettime(CLOCK_MONOTONIC, &end);

                //calcul du temps écoulé en millisecondes
        long seconds = end.tv_sec - start.tv_sec;
        long nanoseconds = end.tv_nsec - start.tv_nsec;
        long elapsed_ms = seconds * 1000 + nanoseconds / 1000000;

              // mettre à jour la variable `status` pour inclure le temps d'exécution
        printf("[Execution Time: %ldms]\n", elapsed_ms);

        // mise à jour du prompt avec le temps d'exécution
        if (WIFEXITED(*status)) {
            printf("enseash [exit:%d|%ldms] %% ", WEXITSTATUS(*status), elapsed_ms);
        } else if (WIFSIGNALED(*status)) {
            printf("enseash [sign:%d|%ldms] %% ", WTERMSIG(*status), elapsed_ms);
        }


    }
}