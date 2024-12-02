# Compte-Rendu

## Structure des Fichiers

- **`main.c`** : Contient la boucle principale et gère le flux général du shell.
- **`prompt.c`** : Contient les fonctions liées à l'affichage et à la récupération des commandes utilisateur.
- **`execution.c`** : Gère l'exécution des commandes utilisateur.

---

## Détails Techniques

- **`STDOUT_FILENO`** :
  - Une constante définie dans `<unistd.h>` qui représente la sortie standard (habituellement le terminal).

- **`calloc`** :
  - Alloue dynamiquement de la mémoire (ici 1024 octets) et initialise chaque octet à `0`.

- **`free`** :
  - Libère la mémoire précédemment allouée avec `calloc`. Cela évite les fuites de mémoire.

---





## Fonctionnement de la fonction `read`

- **Lecture des données** :  
  La fonction `read` lit les données saisies par l'utilisateur (sur l'entrée standard, ici le clavier) et les stocke dans le buffer, par exemple `input`.

- **Gestion de la fin de l'entrée** :  
  Si l'utilisateur presse **`<Ctrl+D>`**, la fonction `read` retourne `0`, indiquant la fin de l'entrée (**EOF**).

- **Appui sur "Entrée"** :  
  Si l'utilisateur appuie sur **Entrée**, la chaîne contiendra un caractère de nouvelle ligne (**`\n`**) à la fin.  
  Ce caractère est remplacé par **`\0`** pour que la chaîne soit correctement terminée.

---





## Code
\`\`\`c
#include <stdio.h>
// (Include your code snippets here)
\`\`\`
`;

// Utilisation de la fonction native Deno.writeTextFile pour écrire dans un fichier
await Deno.writeTextFile("README.md", report);

console.log("Report generated as README.md");
