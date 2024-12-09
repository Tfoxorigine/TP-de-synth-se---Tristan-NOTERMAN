#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "prompt.h"

void display_welcome_message() {     // contient les messages de bienvenue
    write(STDOUT_FILENO, "Bienvenue dans le Shell ENSEA.\n", 31);
    write(STDOUT_FILENO, "Pour quitter, tapez 'exit'.\n", 28);
}

char* get_prompt_input(int status) {    // permet d'affiche un prompt et lit la commande utilisateur
    // préparation du prompt avec le statut précédent
    char prompt[64];
    if (WIFEXITED(status)) {
        // si le processus se terminé normalement, affiche le code de retour
        
        snprintf(prompt, sizeof(prompt), "enseash [exit:%d] %% ", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        // si le processus s'est terminé à cause d'un signal, affiche le numéro du signal
        snprintf(prompt, sizeof(prompt), "enseash [sign:%d] %% ", WTERMSIG(status));
    } else {
        // si aucun statut n'est disponible (par exemple typiquement : la première commande)
        snprintf(prompt, sizeof(prompt), "enseash %% ");
    }


    write(STDOUT_FILENO, prompt, strlen(prompt)); // on utilise strlen au lieu de sizeof sinon on a des caractères bizarres
    // affichage du prompt dans le terminal 

    char *input = calloc(1024, sizeof(char));   // on alloue 1024 octets (1 Ko) qu'on initialise à 0 pour stocker l'entrée utilisateur
    if (!input) {        // si problème d'allocation on affiche un message d'erreur et quitte le programme
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes = read(STDIN_FILENO, input, 1024);   // lit les données saisies par l'utilisateur (sur l'entrée standard, ici le clavier) et les stocke dans le buffer input
    // STDOUT_FILENO représente le terminal comme sortie
    if (bytes <= 0) {
        free(input);     //Libère la mémoire précédemment allouée avec calloc.
        return NULL;
    }

    input[bytes - 1] = '\0'; // on remplace '\n' par '\0'
    return input;
}
