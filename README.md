# prog-distrib

## Introduction

Ces sources sont une copie des sources pcsc-lite permettant la communication entre le système et les lecteurs de puces NFC, avec ajout d'une fonction et de ses fichiers d'entête spécifique à notre projet objet connecté.

Tous les ajouts spécifiques au projet du distributeur (donc tout ce qui n'est pas natif aux sources pcsc-lite) se trouvent dans le dossier `include`.
Ajout également d'une ligne de code dans le programme principal `pcsc_scan.c` nommée `onTagOn()` visible à la ligne 830.

```
			if (rgReaderStates_t[current_reader].dwEventState &
				SCARD_STATE_PRESENT){

					printf("Card inserted, ");
					onTagOn(tagChat);
				
				}
```
> Ce README ne portera que sur cette fonctionnalité et tout ce qui en découle. Pour plus d'informations sur le fonctionnement des librairies pcsc, je vous invite à consulter la page git du paquet natif.

**TODO**
Ajouter la librairie wiringPi à la compilation et les programmes `run()` et  `stop()` pour faire fonctionner le moteur.
