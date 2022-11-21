# Sokoban
Vous trouverez ici les fichiers de base pour le TP noté concernant le jeu du Sokoban
Les consignes et l'énoncé se trouve à cette address [TP Sokoban](https://techdevprintemps2022.pages.unistra.fr/TP_TechDevEnonce/)

Sokoban est un jeu vidéo de réflexion inventé au Japon. Le joueur doit ranger des caisses sur des cases cibles. Il peut se déplacer dans les quatre directions, et pousser (mais pas tirer) une seule caisse à la fois. Une fois toutes les caisses rangées (c'est parfois un vrai casse-tête), le niveau est réussi et le joueur passe au niveau suivant. [Article Wikipedia](https://fr.wikipedia.org/wiki/Sokoban)

<!-- Pour la compatibilité de GitLab et de Doxygen en même temps j'ai du utiliser cette ligne de html pour attacher une image -->
<img src="images/sokobanCLIv0.2.1.gif">

J'étais inspiré par ces dépôts git :

* [TD1 - Criblage](https://gitlab.com/qgoestch/td1-criblage)
* [doxygen-exemple-bidon](https://git.unistra.fr/max.schmitt/doxygen-exemple-bidon)
* [Generic-Makefile](https://github.com/Leandros/Generic-Makefile/blob/master/Makefile)

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

## Commandes d'utilisation

### Comment compiler ?
D'abord téléchargez le projet sur votre machine avec une des commandes qui suivent :

```
git clone https://git.unistra.fr/erken/sokoban.git
```
ou
```
git clone git@git.unistra.fr:erken/sokoban.git
```

Une fois cela est fait, rendez vous dans la répértoire du projet et compilez.
```
cd sokoban/

make
```

Désormais vous pouvez executer le jeu tant que vous etes dans la répértoire de celui-ci.
```
./sokoban
```

### Génération de la documentation
Pour générer la documentation pour votre copie du programme, utilisez la commande suivante et jeter un oeil au fichier `doc/doxygen/html/index.html` dans votre navigateur de web préféré.
```
make doc
```

### Génération d'une archive redistribuable
Pour archiver le projet avec tous les fichiers nécessaires pour compiler et générer la documentation dans format `tar.gz` pour redistribuer utilisez la commande suivante :
```
make archive
```

### Comment nettoyer ?
Pour nettoyer le répértoire du projet pour repartir à zéro il existe plusieurs commandes utiles.

Effacer les fichiers de compilation (*.o, *.d, executable finale). Cela est à faire surtout si vous changez les options de gcc (comme ajouter -g pour débogguer) ou si vous passez à l'executable test avec la commande `make test`.
```
make clean
```

Effacer la documentation et ses répértoires
```
make cleandoc
```

Effacer l'archive
```
make cleanarchive
```

Cela est une commande qui regroupe tous ce qui vient avant. Elle efface tous les fichiers et répértoires de compilation, de documentation et d'archive.
```
make cleanall
```

## Dépôt Git
Le dépôt git de [ce projet](https://git.unistra.fr/erken/sokoban) suit une structure clair et détérminée proposé par Vincent Driessen à son poste [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).

Du coup ne soyez pas surpris par le fait que `branch main` n'a presque pas de commit. Tout le developpement se passe sur le `branch develop`. Avant chaque version, tout est préparé et assuré fonctionnel pour être inauguré au `branch main` qui n'a que des versions stables et complètes.

### Légende emoji
La signification des emojis utilisé dans les descriptions des commits git.

Emoji | Signification
:-|:-
✨ NEW | Nouveau fichier ou fonctionnalité
🔧 UPDATE | Mise à jour d'une partie de programme
🔨 CONFIG | Manipulation des fichiers de configuration comme makefile ou doxyfile
♻️ REFACTOR | Réécriture d'une partie du programme
🐛 BUGFIX | Une correction de bogue
🔥 DELETION | Suppression d'un fichier ou d'une fonctionnalité
📝 DOC | Manipulation de la documentation
🎉 EPOCH | Le début du projet
🚀 RELEASE | Une nouvelle version du programme
