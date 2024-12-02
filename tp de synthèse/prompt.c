#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "prompt.h"

void display_welcome_message() {     // contient les messages de bienvenue
    write(STDOUT_FILENO, "Bienvenue dans le Shell ENSEA.\n", 31);
    write(STDOUT_FILENO, "Pour quitter, tapez 'exit'.\n", 28);
}

char* get_prompt_input() {     // affiche un prompt et lit la commande utilisateur
    static const char prompt[] = "enseash % ";    // décla de la chaîne de caractères constante pour le prompt comme dans un terminal
    write(STDOUT_FILENO, prompt, sizeof(prompt)-1);    // affichage du prompt dans le terminal 

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

    input[bytes - 1] = '\0'; // remplacer '\n' par '\0'
    return input;
}
