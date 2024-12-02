#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "prompt.h"
#include "execution.h"

int main() {
    display_welcome_message();   // message d'accuei sur le terminal

    // Boucle principale du shell
    while (1) {
        char *input = get_prompt_input();
        if (input == NULL || strcmp(input, "exit") == 0) {
            free(input);
            break; // Ctrl+D détecté
        }
        execute_command(input);
        free(input);
    }

    printf("Bye bye...\n");
    return 0;
}

