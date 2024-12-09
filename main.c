#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "prompt.h"
#include "execution.h"

// on essaie de garder le programme principal court et succint

int main() {
    int status = 0;
    display_welcome_message();   // message d'accuei sur le terminal

    // Boucle principale du shell
    while (1) {
        char *input = get_prompt_input(status);
        if (input == NULL || strcmp(input, "exit") == 0) {
            free(input);
            break; // Ctrl+D détecté
        }

        if (input[0] == '\0') {
            free(input);
            continue; // Ignore les entrées vides
        }
        execute_command(input, &status);
        free(input);
    }

    printf("Bye bye...\n");
    return 0;
}

