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


# Question 5 : Mesure du Temps d'Exécution d'une Commande

Pour mesurer le temps d'exécution d'une commande dans un shell, on utilise la fonction `clock_gettime`. Cette fonction permet de récupérer le temps à deux moments différents pour calculer la durée d'exécution.

## Fonctionnement de `clock_gettime`

La fonction `clock_gettime` prend deux paramètres :

1. **`clk_id`** :  
   L'identifiant de l'horloge que l’on veut utiliser.  
   On choisit généralement `CLOCK_MONOTONIC`, qui permet de récupérer le temps écoulé depuis un instant arbitraire.

2. **"L'état du timer"** :  
   Cela fait référence aux variables `&start` ou `&end`, qui contiendront respectivement l'heure avant et après l'exécution de la commande.

   # Question 6 : 

## Exécution d’une commande complexe

On commence par séparer la commande en argument avec la fonction `strdup`.

La commande est découpée en tokens pour identifier les arguments et les opérateurs.  
Pour cela, on utilise la fonction `strtok`. Elle divise la chaîne en sous-chaînes basées sur un séparateur (ici, l'espace `" "`).

### Fonctionnement de `strtok`

`strtok` a besoin de deux paramètres :  

- **`str`** : La chaîne à découper. Lors du premier appel, on donne la chaîne de caractères en entier. Pour les appels suivants, il faut passer le paramètre à `NULL` pour continuer la découpe sur la même chaîne.
- **`delim`** : Une chaîne qui contient les caractères qui délimitent. Lorsque l’on rencontre l’un de ces paramètres, la chaîne est découpée à cet endroit.

Enfin, on exécute la commande avec `execvp`.

# Question 7

## Gestion des redirections de fichiers

La commande est parcourue pour détecter les symboles `<` et `>`.  
Si un symbole est trouvé, le fichier suivant est enregistré comme fichier d'entrée (`input_file`) ou de sortie (`output_file`).

### Séparation de la commande en tokens

Dans la question précédente, nous avons séparé la commande en tokens. On peut se servir de cette séparation pour spécifier que lorsqu’un token `<` ou `>` est détecté, le token suivant est traité comme le nom du fichier à rediriger.

### Fonction `dup2`

La fonction `dup2` permet de rediriger un descripteur de fichier vers un autre :

- Si un fichier d'entrée est spécifié avec `<`, le descripteur de fichier standard `STDIN_FILENO` est redirigé vers ce fichier.
- Si un fichier de sortie est spécifié avec `>`, le descripteur de fichier standard `STDOUT_FILENO` est redirigé vers ce fichier.

### Exécution de la commande

Juste après la gestion des redirections, la commande est exécutée avec `execvp`.

## Gestion des erreurs

- Si le fichier spécifié dans la redirection n'existe pas (pour `<`) ou ne peut pas être créé (pour `>`), le programme affiche un message d'erreur et quitte.
- Si `<` ou `>` est utilisé sans spécifier de fichier, une erreur est signalée.
- Si la commande exécutée par `execvp` échoue (par exemple, commande inexistante), un message d'erreur est affiché et le processus enfant termine avec un statut d'échec.



## Code
\`\`\`c
#include <stdio.h>
// (Include your code snippets here)
\`\`\`
`;

// Utilisation de la fonction native Deno.writeTextFile pour écrire dans un fichier
await Deno.writeTextFile("README.md", report);

console.log("Report generated as README.md");
