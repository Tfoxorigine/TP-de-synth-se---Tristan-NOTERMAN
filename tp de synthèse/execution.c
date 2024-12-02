#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "execution.h"

// zwécutz une commande utilisateur
void execute_command(const char *command) {
    if (strcmp(command, "fortune") == 0) {
        // si la commande est "fortune", affiche un message inspirant
        write(STDOUT_FILENO, "Today is what happened to yesterday.\n", 37);
        write(STDOUT_FILENO, "Sun Dec 13 13:19:40 CET 2020\n", 30);
    } else {
        // si la commande est inconnue, affiche un message d'erreur
        write(STDOUT_FILENO, "Command not found.\n", 20);
    }
}