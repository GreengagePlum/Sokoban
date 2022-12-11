# Sokoban
Vous trouverez ici les fichiers de base pour le TP noté concernant le jeu du Sokoban.
Les consignes et l'énoncé se trouvent à cette address [TP Sokoban](https://techdevprintemps2022.pages.unistra.fr/TP_TechDevEnonce/)

Sokoban est un jeu vidéo de réflexion inventé au Japon. Le joueur doit ranger des caisses sur des cases cibles. Il peut se déplacer dans les quatre directions, et pousser (mais pas tirer) une seule caisse à la fois. Une fois toutes les caisses rangées (c'est parfois un vrai casse-tête), le niveau est réussi et le joueur passe au niveau suivant. [Article Wikipédia](https://fr.wikipedia.org/wiki/Sokoban)

<!-- Pour la compatibilité de GitLab et de Doxygen en même temps j'ai du utiliser cette ligne de html pour attacher une image -->
<img src="images/sokobanCLIv0.2.2.gif">

Je me suis inspiré de ces dépôts git :

* [TD1 - Criblage](https://gitlab.com/qgoestch/td1-criblage)
* [doxygen-exemple-bidon](https://git.unistra.fr/max.schmitt/doxygen-exemple-bidon)
* [Generic-Makefile](https://github.com/Leandros/Generic-Makefile/blob/master/Makefile)

## Étudiants
**Efe ERKEN**

Année : L2S3 Automne 2022

Groupes : TD2-TP4

## Problèmes rencontrés
Voici vous pouvez trouver les problèmes que j'ai eu lors du développement et comment je les ai résolus (ou pas).

### Superposition joueur-objectif
Dans la première version v1.0.0 où on devait juste gérer le mouvement du joueur dans le vide et sur les objectifs, j'étais bloqué car j'arrivais pas à passer le joueur sur les objectifs. Ceci était dû au fait que mon implémentation de départ était problématique. Pour bouger le joueur dans le sens voulu, j'échangeais la case dans le sens voulu et la case où se situait le joueur. Cette méthode ne marchait bien que quand la case dans le sens voulu était vide. Si elle était un objectif, cela revenait à modifier l'emplacement de l'objectif. J'ai dû repenser mon approche.

J'ai passé à une méthode conditionnelle où en fonction des cases concernées, je modifie manuellement ces cases. J'ai dû étendre les représentations des cases dans la structure de jeu pour représenter la superposition du joueur avec un objectif. Grâce à cela, j'ai pu gérer le mouvement sans bouger les emplacements des objectifs et sans utiliser d'autres champs de données dans la structure de jeu pour stocker les positions de chaque objectif.

### Affichage `ncurses`
À partir des version 0.2.0 de mon programme, j'ai intégré l'affichage à la ligne de commande qui utilise la bibliothèque `ncurses` au lieu des fonctions `printf` et `scanf` de la bibliothèque `stdio`. Avant ce changement mon programme n'avait aucune fuite mémoire ou erreur mémoire après vérification `valgrind`.

J'étais surpris par le nombre de fuites après la nouvelle implémentation d'affichage qui était un changement relativement petit. J'ai appris par après que ces fuites n'étaient pas à cause de mon code à moi mais à cause de la bibliothèque `ncurses`. Cette bibliothèque n'a pas de fuite mémoire d'un point de vue mémoire inaccessible mais c'est des `free` non faits, du coup la mémoire reste toujours accessible.

Finalement, il n'y a aucune fuite ou erreur mémoire due à mon code. Elles sont extérieures à moi. Dans le sujet de TP, il est dit d'éviter les fuites et erreurs dû à notre code mais pas dû aux bibliothèques externes utilisées. Ceci ne doit pas poser problème.

Au cas où, la série de versions 0.1.0 utilisent une méthode d'affichage sans la bibliothèque `ncurses`, du coup elles peuvent être considérées 100% pures.

## Versions gcc/clang
J'ai utilisé comme compilateur GNU gcc et Apple clang. J'ai utilisé gcc lorsque je travaillais sur les machines de l'UFR et lorsque je travaillais depuis chez moi, j'ai utilisé Apple clang.

J'ai fait attention à tester mon programme sur les machines de l'UFR pour vérifier les erreurs avant de rendre sur Moodle.

Ci-dessous sont les versions des compilateurs que j'ai utilisées.

```
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0

Apple clang version 14.0.0 (clang-1400.0.29.102)

Apple clang version 14.0.0 (clang-1400.0.29.202)
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

Une fois cela est fait, rendez-vous dans le répertoire du projet et compilez.
```
cd sokoban/

make
```

Désormais vous pouvez exécuter le jeu tant que vous etes dans le répertoire de celui-ci.
```
./sokoban
```

### Génération de la documentation
Pour générer la documentation pour votre copie du programme, utilisez la commande suivante et jeter un oeil au fichier `doc/doxygen/html/index.html` dans votre navigateur de web préféré.
```
make doc
```

### Génération d'une archive redistribuable
Pour archiver le projet avec tous les fichiers nécessaires pour compiler et générer la documentation dans format `tar.gz` pour redistribuer utiliser la commande suivante :
```
make archive
```

### Comment nettoyer ?
Pour nettoyer le répertoire du projet pour repartir à zéro il existe plusieurs commandes utiles.

Effacer les fichiers de compilation (*.o, *.d, exécutable final). Cela est à faire surtout si vous changez les options de gcc (comme ajouter -g pour déboguer) ou si vous passez à l'exécutable test avec la commande `make test`.
```
make clean
```

Effacer la documentation et ses répertoires
```
make cleandoc
```

Effacer l'archive
```
make cleanarchive
```

Cela est une commande qui regroupe toutes celles qui viennent avant. Elle efface tous les fichiers et répertoires de compilation, de documentation et d'archives.
```
make cleanall
```

## Dépôt Git
Le dépôt git de [ce projet](https://git.unistra.fr/erken/sokoban) suit une structure claire et déterminée proposée par Vincent Driessen à son poste [A successful Git branching model](https://nvie.com/posts/a-successful-git-branching-model/).

Du coup ne soyez pas surpris par le fait que `branch main` n'a presque pas de commit. Tout le développement se passe sur le `branch develop`. Avant chaque version, tout est préparé et assuré fonctionnel pour être inauguré au `branch main` qui n'a que des versions stables et complètes.

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
