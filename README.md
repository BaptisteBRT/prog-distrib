# prog-distrib

## Introduction

Ces sources sont une copie des sources pcsc-lite permettant la communication entre le système et les lecteurs de puces NFC, avec ajout d'une fonction et de ses fichiers d'entête spécifique à notre projet objet connecté.

Tous les ajouts spécifiques au projet du distributeur (donc tout ce qui n'est pas natif aux sources pcsc-lite) se trouvent dans le dossier `include`.
Ajout également d'une ligne de code dans le programme principal `pcsc_scan.c` nommée `onTagOn()` visible à la ligne 895.

> Ce README ne portera que sur cette fonctionnalité et tout ce qui en découle. Pour plus d'informations sur le fonctionnement des librairies pcsc, je vous invite à consulter la page git du paquet natif.

## Mise en place programme

Exécuter les commandes suivantes à la racine du projet

`./configure`

puis

`sudo make install`


Lancer le programme à l'aide de la commande `pcsc_scan`


**TODO**
Ajouter la librairie wiringPi à la compilation et les programmes `run()` et  `stop()` pour faire fonctionner le moteur.


## Le script auto
install
install gawk
install mariadb-server
install libmariadb-dev
install libmariadb-dev-compat
install pcscd
install libpcsclite-dev

