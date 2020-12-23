#include <stdlib.h>
#include <stdio.h>
#include <string.h>//pr str split
#include <assert.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "jeu.h"
#include "affichage.h"
#include "evenement.h"


char** str_split(char* a_str, const char a_delim)
{//fction pour decomposer le fichier labyrinthe en une serie de nombre (qui seront mis dans tableau)
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;}
        tmp++;}

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);
    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}


int NbrdeLigne(FILE* fichier)
{//sert a compter le nbr de lignes du fichier labyrinthe
    char caractere = 0;
    int compteur=0;
    while (caractere != EOF) //s'arrete a la fin du texte
     {
        caractere= fgetc(fichier); // permet de lire les caractere un a un dans le texte
        if (caractere == '\n')//ne compte que les sauts de ligne
            compteur++;
        }
    return compteur+1;//(car a la derniere lign, EOF et non \n dc +1)
}


void ChercheNombre(char valeurcherchee,int Nbligne, int *Taille, int **Tableau, Position* position)
{//permet de verifier/chercher la presence d'un nombre(valeurcherchee) dans tableau et indique sa position
    int i = 0;
    int ligne = 0;
    while(ligne < Nbligne)
    {
        i=0;
        while(i<Taille[ligne])
        {
            if(Tableau[ligne][i] == valeurcherchee)//si la valeur recherchée est comprise dans le tableau alors :
            {
                position->colonne=i; //on rentre le num de sa ligne ds position [0]
                position->ligne=ligne; // et le num de sa colonne de pos[1]
            }
            i++;
        }
        ligne++;
    }
}


void jeu(SDL_Surface *ecran)
{//fction principale qui va lancer tous les mecanismes du jeu

    SDL_Event event;//variable event de la SDL qui va contenir un evenement
    int continuer = 1;//variable qui permet de faire tourner la boucle des evenements
    SDL_EnableKeyRepeat(100, 100);//permet la repetition des touches


     ///initialisation des images pour le personnage///
        SDL_Surface *Perso[4] = {NULL};// init un tableau pour le perso selon ses 4 directions (haut, droite , bas, gauche)
        SDL_Surface *PersoActuel = NULL;// init une surface SDL qui va comprendre l'image actuel du perso (haut, droite , bas, gauche)
        Perso[HAUT]= SDL_LoadBMP("image/perso_haut.bmp"); //enregistre l'image du perso direction haut dans la surface SDL perso[HAUT]
        SDL_SetColorKey(Perso[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(Perso[HAUT]->format, 0, 0, 255));// efface la couleur bleu de l'image
        Perso[BAS]= SDL_LoadBMP("image/perso_bas.bmp");//enregistre l'image du perso direction bas dans la surface SDL perso[BAS]
        SDL_SetColorKey(Perso[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(Perso[BAS]->format, 0, 0, 255));// efface la couleur bleu de l'image
        Perso[GAUCHE]= SDL_LoadBMP("image/perso_gauche.bmp");//enregistre l'image du perso direction gauche dans la surface SDL perso[GAUCHE]
        SDL_SetColorKey(Perso[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(Perso[GAUCHE]->format, 0, 0, 255));// efface la couleur bleu de l'image
        Perso[DROITE]= SDL_LoadBMP("image/perso_droit.bmp");//enregistre l'image du perso direction droite dans la surface SDL perso[DROITE]
        SDL_SetColorKey(Perso[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(Perso[DROITE]->format, 0, 0, 255));// efface la couleur bleu de l'image

        PersoActuel = Perso[BAS];// la direction initial du perso est vers le bas


  ///formation du tableau labyrinthe///
    int Nbligne=0;
    int ligne =0;
    int i = 0;
    FILE* fichier= NULL;

    //va calculer le nombre de lignes du fichier texte
        fichier = fopen("Labyrinthe.txt","r");
        Nbligne=NbrdeLigne(fichier);
        fclose(fichier);


    // va calculer la longueur de chacune des lignes
    fichier = fopen("Labyrinthe.txt", "r");
    char caractere = 0;
    int compteur=0;
    int caractotal=0;//nombre total de caracteres dans le tableau
    int Taille[Nbligne];//tableau qui va contenir la longueur de chaque lignes
    do{//creation de Taille, un tableau qui va contenir la taille de chaque ligne
        caractere= fgetc(fichier);//va lire caractere par caractere
        if (caractere != '\n' && caractere != ';' && caractere != EOF)//si le caractere n'est pas un retour a la igne , un point-virgule(ce qui separe les lettres) ou la fin du doc alors compteur +1
        {
            compteur++;
        }
        if (caractere == '\n' || caractere == EOF)//si on arrive a la fin d'une ligne(fin du dossier compris )
        {
            Taille[ligne]=compteur; //le tableau taille prend le nbr de caractere ds la ligne
            ligne++;
            compteur = 0;
        }
        caractotal++;
    }while (caractere != EOF);
    fclose(fichier);

    //creation du tableau comprenant tts les valeurs du labyrinthe

    int** Tableau= malloc(Nbligne*sizeof(int*));
    ligne=0;
    while (ligne<Nbligne)
    {
        Tableau[ligne]=malloc(Taille[ligne]*sizeof(int));//creation du tableau pour le labyrinthe avec exactement le bon nombre de place pour lui
        ligne++;
    }


    //remplir le tableau contenant la carte
    char str[caractotal];
    char** element;
    fichier = fopen("Labyrinthe.txt", "r");
    ligne = 0;
    i = 0;
    while (fgets(str,caractotal,fichier)!= NULL)
    {
        element = str_split(str,';');
        i=0;
        for (i = 0; *(element + i); i++)
            {
                Tableau[ligne][i]=atoi(*(element+i));//va rentrer chaque element dans le tableau Tableau (qui corespond au labyrinthe)

              }
            free(element);
            ligne++;
            printf("\n");
    }
    //////////

    //creation d'une structure pour se reperer dans le labyrinthe
    Position *Positionmap;
    Positionmap = malloc(sizeof(Position));
    ChercheNombre(1,Nbligne,Taille,Tableau,Positionmap);//recherche de la position de l'entrée en 1

    SDL_Rect positionPerso;


///init fichier text pour la premiere salle///

/*
        Position *PositionSalle;
        PositionSalle = malloc(sizeof(Position));
        PositionSalle->colonne = 5;
        PositionSalle->ligne = 3;*/

    int salle[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};
    int PositionSalle[2]; //vecteur de position dans la salle ( a changer ac une struct)(colonne/ligne)
    PositionSalle[0] = 5;//positionnement du perso a sa position initial , au centre de la salle 0
    PositionSalle[1] = 3;

    chargersalle(salle,Tableau[Positionmap->ligne][Positionmap->colonne],Tableau,Positionmap);//va charger la premiere salle du labyrinthe

    positionPerso.x = 5*TAILLE_BLOC; //init de la position du perso au centre de l'ecran
    positionPerso.y = 3*TAILLE_BLOC;


    Personnage *Joueur;//initialisation des donnees de notre personnage dans une structure
    Joueur = malloc(sizeof(Personnage));
    Joueur->vie = VieDeJoueur;
    Joueur->attaque = ForceDeJoueur;
    Joueur->defense = DefDeJoueur;
    Joueur->VieSur3 = Joueur->vie/3;   //Constante permettant de vérifier le niveau de vie du joueur


    ///boucle des evenements///
    while(continuer)
    {
        SDL_WaitEvent(&event);//va attendre un evenement
        switch (event.type)
        {
            case SDL_QUIT://si on appuie sur la croix: la fenetre SDL se ferme
                continuer = 0;//la fenetre SDL se ferme
                break;

            case SDL_KEYDOWN://si on appuie sur une touche
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // Appuier sur la touche Echap,
                        continuer = 0;//on arrête le programme
                        break;

                    case SDLK_UP://si touche du haut
                        PersoActuel = Perso[HAUT];//change l'image du perso actuel vers le haut
                        if(deplacement(HAUT,positionPerso,salle,PositionSalle,ecran,Joueur))//si pas de probleme pour se deplacer vers le haut
                           positionPerso.y-=TAILLE_BLOC;// se decale d'un bloc

                        if(PositionSalle[0] == 5 && PositionSalle[1] == 0)//si on est sur la case d'une porte  //peut etre modifié en disant "si on est sur une porte..."
                        {//"anim" de changement de salle
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            //affichageSalle(Tableau[PositionMap[0]][PositionMap[1]],ecran,Tableau,PositionMap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le perso sur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            changementSalle(ecran,PersoActuel,HAUT,Tableau,Positionmap,positionPerso,salle,PositionSalle);//passe a la salle du haut
                            positionPerso.y = 6*TAILLE_BLOC;//replace le perso tt en bas
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le persosur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            positionPerso.y-=TAILLE_BLOC;//decale d'une case pour sortir de la porte
                        }
                        break;

                    case SDLK_DOWN: // Flèche bas
                        PersoActuel = Perso[BAS];//change l'image du perso actuel vers le bas
                        if(deplacement(BAS,positionPerso,salle,PositionSalle,ecran,Joueur))//si pas de probleme pour se deplacer vers le bas
                           positionPerso.y+=TAILLE_BLOC;//se decale d'un bloc
                        if(PositionSalle[0] == 5 && PositionSalle[1] == 6)//si on est sur la case d'une porte
                        {
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le persosur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            changementSalle(ecran,PersoActuel,BAS,Tableau,Positionmap,positionPerso,salle,PositionSalle);//passe a la salle du bas
                            positionPerso.y = 0;//replace le perso tt en haut
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le persosur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            positionPerso.y+=TAILLE_BLOC;//decale d'une case pour sortir de la porte
                        }
                        break;

                    case SDLK_RIGHT: // Flèche droite
                        PersoActuel = Perso[DROITE];//change l'image du perso actuel vers le droite
                        if(deplacement(DROITE,positionPerso,salle,PositionSalle,ecran,Joueur))//si pas de probleme pour se deplacer vers la droite
                           positionPerso.x+=TAILLE_BLOC;//se decale d'un bloc
                        if(PositionSalle[0] == 10 && PositionSalle[1] == 3)//si on est sur la case d'une porte
                        {
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            //affichageSalle(Tableau[PositionMap[0]][PositionMap[1]],ecran,Tableau,PositionMap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le persosur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            changementSalle(ecran,PersoActuel,DROITE,Tableau,Positionmap,positionPerso,salle,PositionSalle);//passe a la salle de droite
                            positionPerso.x = 0;//replace le perso tt a gauche
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le persosur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            positionPerso.x+=TAILLE_BLOC;//decale d'une case pour sortir de la porte
                        }
                        break;

                    case SDLK_LEFT: // Flèche gauche
                        PersoActuel = Perso[GAUCHE];//change l'image du perso actuel vers le gauche
                        if(deplacement(GAUCHE,positionPerso,salle,PositionSalle,ecran,Joueur))//si pas de probleme pour se deplacer vers la gauche
                           positionPerso.x-=TAILLE_BLOC;//se decale d'un bloc
                        if(PositionSalle[0] == 0 && PositionSalle[1] == 3)//si on est sur la case d'une porte
                        {
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le persosur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            changementSalle(ecran,PersoActuel,GAUCHE,Tableau,Positionmap,positionPerso,salle,PositionSalle);//passe a la salle du haut
                            positionPerso.x = 10*TAILLE_BLOC;//replace le perso tt a droite
                            SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));
                            affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//rafraissiment de la salle
                            SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le persosur la case de la porte
                            SDL_Flip(ecran);//maj de l'ecran
                            SDL_Delay(20);//met une pause pour permettre de voir le deplacement
                            positionPerso.x-=TAILLE_BLOC;//decale d'une case pour sortir de la porte
                        }
                        break;
                    //si bloqué dans une salle ( salle 5)
                    case SDLK_r:
                        {
                            chargersalle(salle,Tableau[Positionmap->ligne][Positionmap->colonne],Tableau,Positionmap);//va charger la salle du labyrinthe
                            PositionSalle[0] = 1;//positionnement du perso
                            PositionSalle[1] = 5;
                            positionPerso.x = 1*TAILLE_BLOC; //init de la position du perso au centre de l'ecran
                            positionPerso.y = 5*TAILLE_BLOC;
                            Joueur->vie-=50;
                        }
                        break;

                    case SDLK_o://"code triche" pour ouvrir toutes les portes d'une salle
                        {
                            int i = 0;
                            int j = 0;
                            while (i<NB_BLOCS_LARGEUR)
                            {
                                while(j<NB_BLOCS_HAUTEUR)
                                {
                                  if(salle[i][j]==OBJECTIF)//s'il reste un objectif dans la salle alors
                                     salle[i][j]=VIDE;
                                  j++;
                                }
                                j=0;
                                i++;
                            }
                            ouvrirPortes(salle);
                        }
                        break;
                    //codes de triches pour "booster " notre personnage
                    case SDLK_h:
                        Joueur->vie+=20;
                        break;

                    case SDLK_q:
                        Joueur->attaque+=10;
                        break;
                    //triche pour faire disparaitre un obstacle  qui se trouve devant nous
                    case SDLK_c:
                        {
                            if(PersoActuel==Perso[HAUT])
                                salle[PositionSalle[0]][PositionSalle[1]-1]=VIDE;
                            if(PersoActuel==Perso[BAS])
                                salle[PositionSalle[0]][PositionSalle[1]+1]=VIDE;
                            if(PersoActuel==Perso[GAUCHE])
                                salle[PositionSalle[0]-1][PositionSalle[1]]=VIDE;
                            if(PersoActuel==Perso[DROITE])
                                salle[PositionSalle[0]+1][PositionSalle[1]]=VIDE;
                        }

                }
        }


        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 115, 57, 0));//remet la couleur du sol
        affichageSalle(Tableau[Positionmap->ligne][Positionmap->colonne],ecran,Tableau,Positionmap,salle,positionPerso,*Joueur);//place ts les elements de la salle
        SDL_BlitSurface(PersoActuel, NULL, ecran, &positionPerso);//affiche le perso
        SDL_Flip(ecran);//maj de l'ecran


        if(salle[PositionSalle[0]][PositionSalle[1]]==SORTIE)//si on atteint la sortie
           {
               SDL_Delay(600);
               MaFin(ecran,GAGNEE);// on gagne
               continuer = 0;
           }

        if(Joueur->vie <= 0)//si on a plus de vie
           {
               MaFin(ecran,PERDU);//on perd
               continuer = 0;
           }
        }

        SDL_FreeSurface(PersoActuel);//liberation de memoire
        for (i = 0 ; i < 4 ; i++)
        {
           SDL_FreeSurface(Perso[i]);
        }
}
