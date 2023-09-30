Crazy_Monkey

##Présentation du jeu:

Notre projet est un jeu vidéo intitulé Crazy Monkey. Il est destiné à être joué sur ordinateur. La clientèle cible est des personnes de tous âges, à partir de 6 ans et plus. Il a été développé dans le contexte d’un projet d’études de licence informatique à l’université Claude Bernard Lyon 1. L’objectif du jeu est de distraire ses utilisateurs.

##Description du jeu:

Le joueur manipule un singe, qui a pour but d’atteindre un coffret de bananes. Mais pour cela, il va rencontrer des obstacles tout au long du chemin qui est une jungle représentée par des arbres. C’est l’utilisateur qui lance le singe avec une certaine force ainsi que une vitesse qui forment une trajectoire bien précise. Le singe se déplace alors selon une trajectoire parabolique grâce à la lancée de l’utilisateur, le singe peut soit atteindre un arbre soit tomber et il perd.
Le jeu comporte certaines règles comme:
Au début, le singe a trois vies.
Si le singe arrive sur un arbre qui contient un serpent et que le singe tombe dessus alors le singe perdra une vie.
Si le singe arrive sur un arbre qui contient une banane magique alors il gagne du temps en plus.
Si le singe atteint l’arbre avec le coffret de banane, il gagne et le jeu se termine. Si le temps s'écoule avant que le singe arrive au coffret de banane, il perd.
Si le singe perd toutes ses vies avant d‘arriver au coffret de bananes, il perd.

Il y a trois niveaux de difficulté : facile-> 1, moyen-> 2 et difficile-> 3.
- Le niveau facile comporte 40 secondes, moins d’arbres à
parcourir, sans serpents dans les arbres et sans bananes magiques.
- Le niveau moyen comporte un peu moins de temps que le niveau facile, plus
d’arbres, avec des serpents dedans et avec des bananes magiques.
- Le niveau difficile a un temps plus limité, contient beaucoup plus d’arbres à
parcourir pour atteindre le coffret de bananes,avec plus d’arbres avec des serpents ainsi que des bananes magiques.
Ce projet est jouable avec SDL2.

## Installation
Lien pour cloner le dépôt git: https://forge.univ-lyon1.fr/p2102583/crazy-monkey.git 


## L'organisation de l'archive: 

- CRAZY_MOKNEY_12102583_12101522/src  contient en trois dossiers:

        core contient les fichiers avec les classes du noyau:
        ¤ ./core/Arbre.cpp core/Arbre.h : classe qui représente un arbre dans le jeu, et ses données membres et son header avec le prototype des fonctions
        ¤ ./core/Singe.cpp core/Singe.h : classe qui représente un singe dans le jeu, et ses données membres et son header avec le prototype des fonctions
        ¤ ./core/Vec2.cpp core/Vec2.h : structure vecteur et ses opérateurs, et son header avec le prototype des fonctions
        ¤ ./core/Jungle.cpp core/Jungle.h : classe qui rassemble tous les objets présentes dans la jungle (arbre + singe) et fait la base du jeu et son header avec le prototype des fonctions
        ¤ ./core/mainRegression.cpp : fait appel à une fonction testRegression membre de Jungle pour vérifier que le module fonctionne

        sdl2 : 
        ¤ ./sdl2/AffichageSDL2.cpp sdl2/AffichageSDL2.h : contient la classe AffichageSDL2 et Image qui permettent le fonctionnent du jeu avec l'interface graphique SDL2 et son header avec le prototype des fonctions
        ¤ ./sdl2/mainSDL2.cpp : fait appel au jeu dans AffichageSDL2.cpp pour l'afficher

        txt 
        ¤ ./txt/AffichageTxt.cpp txt/AffichageTxt.h : contient les fonctions pour une première version minimale du jeu et son header avec le prototype des fonctions
        ¤ ./txt/winTxt.cpp ./txt/winTxt.h : contient des fonctions de bases requises pour l'affichage texte et son header avec le prototype des fonctions
        ¤ ./txt/main_txt.cpp : fait appel à l'affichage txt

- CRAZY_MONKEY_12102583_12101522/data contient en trois dossiers: 
        
        ¤ ./fonts  : contient les fonts nommées PTS55F.ttf et Samson.ttf qu'on utilise pour le style d'écriture de l'affichage

        ¤ ./img    : contient les fichiers images arbre.png, banane_magique.png, bananes.png, serpent.png, singe.png

        ¤ ./sounds : contient le fichier son ArthurVyncke-childhoodFriend.mp3 qui contient le son du jeu.


- CRAZY_MONKEY_12102583_12101522/bin   : contient les deux éxécutables suivantes: 

        ¤ ./testR: exécute mainRegression.cpp qui effectue une série de tests vérifiant que le jeu fonctionne et que les données membres de l'objet sont conformes

        ¤ ./sdl2: exécute mainSDL2.cpp qui affiche dans une fenêtre SDL2 le jeu.

        ¤ ./Txt : exécute main_txt.cpp qui affiche une version minimale du jeu dans un terminal

- CRAZY_MONKEY_12102583_12101522/obj         : contient les fichiers .o 


- CRAZY_MONKEY_12102583_12101522/doc         : contient la documentaton doxygen image.doxy 

        ¤ ./html    : contient index.html la documentation html générée par doxygen



##Compilation

Le projet peut se compiler sous Linux en ligne de commande avec un IDE (codeblocks, Visual code).
Pour compiler le programme, il y a certaines étapes à suivre: 

- Il faut avoir déjà installé les dépendances requises pour le programme: SDL2. 
-  Un makefile est utilisé pour simplifier la compilation de tous les fichiers et on tape la commande 'make' dans le 
    terminal pour compiler le programme (mais assurez-vous d'être dans le bon répertoire dans le terminal ).
    
Si la compilation réussit, le binaire exécutable sera généré dans le dossier bin.


Pour télécharger SDL2 :
Sous linux : 
	sudo apt-get install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
Sous windows et MacOS il faut suivre le guide suivant : https://wiki.libsdl.org/SDL2/Installation

Pout la documentation doxygen : 
- Se génère avec le makefile grâce à : 
        docs: doc/image.doxy
	        doxygen doc/image.doxy
 - Ligne de commande pour compiler : 
  	make
 - ouvrez la page principale générée avec Firefox (ou autre browser) en tapant:
   firefox doc/html/index.html
   


## Exécution

Pour exécuter le programme, on ouvre une console dans le dossier où se trouve le makefile, puis on 
exécute la commande suivante (selon le programme qu'on veut exécuter): 
- bin/testR 
- bin/Txt
- bin/Sdl2

## Auteurs

Sarra Mejri, numéro étudiant: 12101522
Maya Soufan, numéro étudiant: 12102583