# Sokoban
Vous trouverez ici les fichiers de base pour le TP noté concernant le jeu du Sokoban
Les consignes et l'énoncé se trouve à cette address [TP Sokoban](https://techdevprintemps2022.pages.unistra.fr/TP_TechDevEnonce/)

## Étudiants
**Efe ERKEN**

Année : L2S3 Automne 2022

Groupes : TD2-TP4

## Problèmes rencontrés
Voici vous pouvez trouver les problèmes que j'ai eu lors du developpement et comment je les ai résolu (ou pas).

### Superposition joueur-objectif
Dans la première version v1.0.0 où on devait juste gérer le mouvement du joueur dans le vide et sur les objectifs, j'étais bloqué car j'arrivait pas à passer le joueur sur les objectifs. Ceci étais dû au fait que mon implémentation de départ étais problématique. Pour bouger le joueur dans le sens voulu, j'échangais la case dans le sens voulu et la case où se situait le joueur. Cette méthode ne marchait bien que quand la case dans le sens voulu étais vide. Si elle étais un objectif, cela revenait à modifier l'emplacement de l'objectif. J'ai du repenser mon approche.

J'ai passé à une méthode conditionnel où en fonction des cases concernées, je modifie manuellement ces cases. J'ai du étendre les représentations des cases dans la structure de jeu pour représenter la superposition du joueur avec un objectif. Grâce à cela, j'ai pu gérer le mouvement sans bouger les emplacements des objectifs et sans utiliser d'autres champs de données dans la structure de jeu pour stocker les positions de chaque objectif.

## Versions gcc/clang
J'ai utilisé comme compilateur GNU gcc et Apple clang. J'ai utilisé gcc lorsque je travaillait sur les machines de l'UFR et lorsque je travaillait depuis chez moi, j'ai utilisé Apple clang.

J'ai fait attention à tester mon programme sur les machines de l'UFR pour vérifier les erreurs avant de rendre sur Moodle.

Ci-dessous sont les versions des compilateurs que j'ai utilisé.

```
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0

Apple clang version 14.0.0 (clang-1400.0.29.102)
```

## Dépôt Git
Le dépôt git de ce projet suit une structure clair et détérminée proposé par Vincent Driessen à son poste [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).

Du coup ne soyez pas surpris par le fait que `branch main` n'a presque pas de commit. Tout le developpement se passe sur le `branch develop`. Avant chaque version, tout est préparé et assuré fonctionnel pour être inauguré au `branch main` qui n'a que des versions stables et complètes.
