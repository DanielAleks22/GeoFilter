

## Description

Le projet consiste a utiliser des données tirer de [GeoNames](http://www.geonames.org/), ces données sont par la suite utiliser avec but de permettre un affichage clair et simple tout en ordonnant en ordre croissant les villes les plus peuples provenant de la base de données.

Le programme utilise le fichier `cities15000.txt` qui contient toutes les villes ayant plus de 15000 habitants. Les données tirées du fichier seront chargées dans des `struct` qui seront par la suite chargés dans un tableau, ceci facilite le triage. Le fichier `countryInfo.txt` est utilisé pour coupler les villes à leurs pays, puisque `cities15000.txt` contient seulement des codes `ASCII` pour représenter les pays des villes. Lorsque l'utilisateur entre en argument un entier, cet entier représentera le nombre de villes à afficher après triage en ordre croissant.

## Auteur
Daniel Aleksandrov (ALED22119901)

## Fonctionnement

En premier lieu, il faut ouvrir un terminal `bash` dans le répertoire du projet. Par la suite, en entrant les commandes suivantes, vous auriez accès au fonctionnement complet du projet.

1. `make database` : permet le téléchargement des fichiers provenant de la base donnée  
2. `make`: compile le fichier `geonames.c`
3. `make test`: vérifie le fonctionnement du programme
4. `./geonames (entier)`: exécute le programme, **IMPORTANT**: l'entier devrait se  situer entre *1* et *5000*
5. `make html`: créer une version *html* des fichiers
6. `make clean`: nettoie le répertoire en supprimant les fichier indésirables.

```sh
$ make databas
$ make
$ make test
$ ./geonames (entier)
$ make html
$ make clean
```
## Tests

En entrant la commande `make test` dans votre terminal vous lancerait une suite de tests
automatiques.

* `test0`: vérifie si le programme est en mesure de terminer l'exécution lorsqu'aucun argument (nombre de villes) ne lui est donné.
* `test1`: vérifie si le programme est en mesure de terminer l'exécution lorsque trop d'arguments lui sont fournis. 
* `test2`: vérifie  si le programme est en mesure de terminer l'exécution lorsque l'argument fourni est trop petit (*argument < 1*).
* `test3`: vérifie  si le programme est en mesure de terminer l'exécution lorsque l'argument fourni dépasse le nombre de villes permis (*argument > 5000*).
* `test4`: vérifie  si le programme est en mesure de terminer l'exécution lorsque l'argument fourni n'est pas un entier.
* `test5`: vérifie  si le programme est en mesure de terminer l'exécution lorsque l'argument fourni n'est pas un entier.
* `test6`: vérifie  si le programme affiche correctement les 5 villes les plus nombreuses selon la base de données.
* `test7`: vérifie  si le programme affiche correctement un argument (*1* ville) tirer d'un fichier texte.
* `test8`: vérifie si le programme affiche correctement un argument (*10* villes) tirer d'un
fichier texte.
*  `test9`: vérifie si le programme affiche correctement les 5000 villes les plus nombreuses selon la base de données.
*  `test10`: vérifie si le programme affiche correctement les 5000 villes les plus nombreuses selon la base de données.


## Dépendances

* [GCC](https://gcc.gnu.org/)
* [Bats](https://github.com/bats-core/bats-core)
* [Curl](https://curl.se/)

## Références

* Utilisation de [strok](https://www.educative.io/answers/splitting-a-string-using-strtok-in-c?fbclid=IwAR0bAzfbel3GLQIN9EQCJqN-Fxizg5iuWYxwVErVr3BLEM4D6lejKV1se2o)
* Utilisation de [qsort](https://stackoverflow.com/questions/6105513/need-help-using-qsort-with-an-array-of-structs?fbclid=IwAR2PO01Btkg-aJBpOpNc_x6nd35NsLkom7GuxQYjakZyprxlDMjjSJ1yDAQ) avec
`struct`.

