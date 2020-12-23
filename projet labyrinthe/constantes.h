//va permettre de def/init tts les constantes necessaire au code
#ifndef CONSTANTES_H_INCLUDED
#define CONSTANTES_H_INCLUDED


        #define TAILLE_BLOC         65 // Taille d'un bloc en pixels
        #define NB_BLOCS_LARGEUR    11
        #define NB_BLOCS_HAUTEUR    7
        #define LARGEUR_FENETRE     715 //TAILLE_BLOC*NB_BLOCS_LARGEUR
        #define HAUTEUR_FENETRE     455

        enum {HAUT, BAS, GAUCHE, DROITE};//initialisation des directions pour la clarté du code
        enum {VIDE = 0,ENNEMI = 1,BOSS = 10, PIERRE = 2,PIC = 3, OBJECTIF = 4,CAISSE = 5, CAISSE_OK = 50,SORTIE = 6, PORTE_F = 7, PORTE_O = 8, MUR = 9};//init des objets ds les salles
        enum { PERDU, GAGNEE, FIN = 5};

        typedef struct Personnage //Structure pour joueur et ennemi
        {
            int vie;
            int attaque;
            int defense;
            int VieSur3;
        } Personnage;


        ///Joueur///
        #define VieDeJoueur    300;
        #define ForceDeJoueur   40;
        #define DefDeJoueur     25;

#endif // CONSTANTES_H_INCLUDED
