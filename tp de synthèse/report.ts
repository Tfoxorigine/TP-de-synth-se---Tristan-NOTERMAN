const report = `
# Compte-Rendu

## Structure des Fichiers
# main.c : Contient la boucle principale et gère le flux général du shell.
# prompt.c : Contient les fonctions liées à l'affichage et à la récupération des commandes utilisateur.
# execution.c : Gère l'exécution des commandes utilisateur.

# Nous utilisons STDOUT_FILENO, qui est une constante définie dans <unistd.h> et représente la sortie standard (habituellement le terminal)

## Code
\`\`\`c
#include <stdio.h>
// (Include your code snippets here)
\`\`\`
`;

// Utilisation de la fonction native Deno.writeTextFile pour écrire dans un fichier
await Deno.writeTextFile("README.md", report);

console.log("Report generated as README.md");
