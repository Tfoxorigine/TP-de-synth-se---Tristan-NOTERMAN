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


# Question 4 : Affichage des informations d'exécution

Dans cette question, l'objectif est d'afficher des informations sur l'exécution de la commande précédemment entrée par l'utilisateur. Pour cela, le shell affiche un **code de retour**, par exemple :

- **`[exit:0]`** : Le programme s’est exécuté sans problème (via `exit()`) et a renvoyé un code de retour `0` indiquant une exécution réussie.
- **`[sign:9]`** : La commande a été interrompue par un signal, ici le signal numéro `9`, correspondant à **`SIGKILL`**.

---

## Fonctionnement du code de retour dans ce shell

Le **exit status**, ou code de retour, est une valeur numérique renvoyée par un processus lorsqu'il termine son exécution. Cette valeur permet au système et au processus parent de savoir si l'exécution s'est déroulée avec succès ou si une erreur est survenue.

### Exécution d'une commande par le processus enfant

Lorsqu'une commande est exécutée dans le shell, un **processus enfant** est généré via `fork()`.  
Ce processus enfant exécute la commande via `execvp()`. Si l'exécution réussit, le processus enfant se termine avec un **code de retour** selon la commande exécutée.

### Récupération du code de retour dans le processus parent

Le **processus parent** utilise `waitpid()` pour attendre la fin du processus enfant et récupérer son statut.  
La valeur renvoyée par `waitpid()` permet de savoir si le processus s'est terminé normalement ou s'il a été interrompu par un signal.


## Code
\`\`\`c
#include <stdio.h>
// (Include your code snippets here)
\`\`\`
`;

// Utilisation de la fonction native Deno.writeTextFile pour écrire dans un fichier
await Deno.writeTextFile("README.md", report);

console.log("Report generated as README.md");
