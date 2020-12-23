#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "evenement.h"
#include "affichage.h"


int deplacement(int DIRECTION, SDL_Rect position, int salle[][NB_BLOCS_HAUTEUR], int* PositionSalle,SDL_Surface *ecran,Personnage *Joueur)
{
    if(DIRECTION == HAUT)//si je me deplace en haut
    {
        if (salle[PositionSalle[0]][PositionSalle[1]-1] == ENNEMI)
            {
                combat(ecran,Joueur,ENNEMI);
                salle[PositionSalle[0]][PositionSalle[1]-1] = VIDE;
            }

        if (salle[PositionSalle[0]][PositionSalle[1]-1] == BOSS)
            {
                combat(ecran,Joueur,BOSS);
                salle[PositionSalle[0]][PositionSalle[1]-1] = SORTIE;
                return 0;
            }

        if (salle[PositionSalle[0]][PositionSalle[1]-1] == PIC)
            {
                Joueur->vie-=10;
                if(Joueur->vie<0)
                    Joueur->vie=0;
            }

        if (salle[PositionSalle[0]][PositionSalle[1]-1] ==CAISSE_OK ||
            salle[PositionSalle[0]][PositionSalle[1]-1] ==MUR ||
            salle[PositionSalle[0]][PositionSalle[1]-1] == PIERRE ||
            salle[PositionSalle[0]][PositionSalle[1]-1] == PORTE_F) //colonne/ ligne //si qqchose qui bloque le perso
            return 0;//on bouge pas

        if(salle[PositionSalle[0]][PositionSalle[1]-1] ==CAISSE) //si il y a une caisse en haut
            return deplacementCaisse(DIRECTION,salle,PositionSalle);//lance le deplacement de la caisse

        PositionSalle[1]-=1;//indique le deplacemenet au vect position
        return 1;//on bouge
    }

    if(DIRECTION == DROITE)//si je me deplace a droite
    {

        if (salle[PositionSalle[0]+1][PositionSalle[1]] == ENNEMI)
            {
                combat(ecran,Joueur,ENNEMI);
                salle[PositionSalle[0]+1][PositionSalle[1]] = VIDE;
            }

        if (salle[PositionSalle[0]+1][PositionSalle[1]] == BOSS)
            {
                combat(ecran,Joueur,BOSS);
                salle[PositionSalle[0]+1][PositionSalle[1]] = SORTIE;
                return 0;
            }

        if (salle[PositionSalle[0]+1][PositionSalle[1]] == PIC)
            {
                Joueur->vie-=10;
                if(Joueur->vie<0)
                    Joueur->vie=0;
            }

        if (salle[PositionSalle[0]+1][PositionSalle[1]] == CAISSE_OK || //s'il n'y a pas d'obstacle " infranchissable"
            salle[PositionSalle[0]+1][PositionSalle[1]] == MUR ||
            salle[PositionSalle[0]+1][PositionSalle[1]] == PIERRE ||
            salle[PositionSalle[0]+1][PositionSalle[1]] == PORTE_F )
           return 0;//on bouge pas

        if(salle[PositionSalle[0]+1][PositionSalle[1]] ==CAISSE)//s'il y a une caisse sur ma droite -> lance le deplacement de la caisse
            return deplacementCaisse(DIRECTION,salle,PositionSalle);

        PositionSalle[0]+=1;//indique le deplacemenet au vect position
        return 1;//on bouge
    }

    if(DIRECTION == BAS)//si je me deplace en bas
    {
        if (salle[PositionSalle[0]][PositionSalle[1]+1] == ENNEMI)
            {
                combat(ecran,Joueur,ENNEMI);
                salle[PositionSalle[0]][PositionSalle[1]+1] = VIDE;
            }

        if (salle[PositionSalle[0]][PositionSalle[1]+1] == BOSS)
            {
                combat(ecran,Joueur,BOSS);
                salle[PositionSalle[0]][PositionSalle[1]+1] = SORTIE;
                return 0;
            }

        if (salle[PositionSalle[0]][PositionSalle[1]+1] == PIC)
            {
                Joueur->vie-=10;
                if(Joueur->vie<0)
                    Joueur->vie=0;
            }

        if (salle[PositionSalle[0]][PositionSalle[1]+1] == CAISSE_OK ||
            salle[PositionSalle[0]][PositionSalle[1]+1] == MUR ||
            salle[PositionSalle[0]][PositionSalle[1]+1] == PIERRE ||
            salle[PositionSalle[0]][PositionSalle[1]+1] == PORTE_F) //colonne/ ligne //si qqchose qui bloque le perso
             return 0;//colonne/ ligne //on bouge pas

        if(salle[PositionSalle[0]][PositionSalle[1]+1] ==CAISSE)//si il y a une caisse en bas
            return deplacementCaisse(DIRECTION,salle,PositionSalle);//lance le deplacement de la caisse

        PositionSalle[1]+=1;//indique le deplacemenet au vect position
        return 1;//on bouge
    }

    if(DIRECTION == GAUCHE)//si je me deplace a gauche
    {

        if (salle[PositionSalle[0]-1][PositionSalle[1]] == ENNEMI)
            {
                combat(ecran,Joueur,ENNEMI);
                salle[PositionSalle[0]-1][PositionSalle[1]] = VIDE;
            }

        if (salle[PositionSalle[0]-1][PositionSalle[1]] == BOSS)
            {
                combat(ecran,Joueur,BOSS);
                salle[PositionSalle[0]-1][PositionSalle[1]] = SORTIE;
                return 0;
            }

        if (salle[PositionSalle[0]-1][PositionSalle[1]] == PIC)
            {//
                Joueur->vie-=10;
                if(Joueur->vie<0)
                    Joueur->vie=0;
            }

        if (salle[PositionSalle[0]-1][PositionSalle[1]] == CAISSE_OK ||
            salle[PositionSalle[0]-1][PositionSalle[1]] == MUR ||
            salle[PositionSalle[0]-1][PositionSalle[1]] == PIERRE ||
            salle[PositionSalle[0]-1][PositionSalle[1]] == PORTE_F) //si qqchose qui bloque le perso
            return 0;//on bouge pas

        if(salle[PositionSalle[0]-1][PositionSalle[1]] ==CAISSE)//si il y a une caisse a gauche
            return deplacementCaisse(DIRECTION,salle,PositionSalle);//lance le deplacement de la caisse

        PositionSalle[0]-=1;//indique le deplacemenet au vect position
        return 1;//on bouge
    }
    return -1;
}

void changementSalle(SDL_Surface *ecran,SDL_Surface* PersoActuel,int DIRECTION,int** Tableau,int* PositionMap,SDL_Rect positionPerso,int salle[][NB_BLOCS_HAUTEUR],int* PositionSalle)
{//                                              ligne/colonne                               colonne/ligne              colonne /ligne
    if(DIRECTION == HAUT)//si je me deplace en haut
    {
        PositionMap[0]-=1;//indique le deplacemenet dans la salle d'en haut
        chargersalle(salle,Tableau[PositionMap[0]][PositionMap[1]],Tableau,PositionMap);//charge la nouvelle salle
        PositionSalle[1]=6-1;//replacement du personnage dans le tableau positionsalle
    }

    if(DIRECTION == BAS)//si je me deplace en bas
    {
        PositionMap[0]+=1;//indique le deplacemenet dans la salle d'en bas
        chargersalle(salle,Tableau[PositionMap[0]][PositionMap[1]],Tableau,PositionMap);//charge la nouvelle salle
        PositionSalle[1]=0+1;//replacement du personnage dans le tableau positionsalle
    }

    if(DIRECTION == DROITE)//si je me deplace a droite
    {
        PositionMap[1]+=1;//indique le deplacemenet dans la salle de droite
        chargersalle(salle,Tableau[PositionMap[0]][PositionMap[1]],Tableau,PositionMap);//charge la nouvelle salle
        PositionSalle[0]=0+1;//replacement du personnage dans le tableau positionsalle
    }

    if(DIRECTION == GAUCHE)//si je me deplace a gauche
    {
        PositionMap[1]-=1;//indique le deplacemenet dans la salle de droite
        chargersalle(salle,Tableau[PositionMap[0]][PositionMap[1]],Tableau,PositionMap);//charge la nouvelle salle
        PositionSalle[0]=10-1;//replacement du personnage dans le tableau positionsalle
    }
}

int ouvrirPortes (int salle[][NB_BLOCS_HAUTEUR])
{
    int i = 0;
    int j = 0;
    while (i<NB_BLOCS_LARGEUR)
    {
        while(j<NB_BLOCS_HAUTEUR)
        {
          if(salle[i][j]==OBJECTIF)//s'il reste un objectif dans la salle alors
            return 0;//n'ouvre pas les portes.
          j++;
        }
        j=0;
        i++;
    }
    //a partir d'ici, plus d'objectif dans la salle
    i=0;
    j=0;
    while (i<NB_BLOCS_LARGEUR)
    {
        while(j<NB_BLOCS_HAUTEUR)
        {
          if(salle[i][j]==PORTE_F)//va transformer toutes les portes fermees
            salle[i][j]=PORTE_O;// en porte ouvertes
          j++;
        }
        j=0;
        i++;
    }
}

int deplacementCaisse(int DIRECTION, int salle[][NB_BLOCS_HAUTEUR], int* PositionSalle)
{
    if(DIRECTION == HAUT)//si je me deplace en haut
    {
       if (salle[PositionSalle[0]][PositionSalle[1]-2] ==CAISSE ||  //s'il y a un obstacle devant la caisse que l'on veut pousser
           salle[PositionSalle[0]][PositionSalle[1]-2] ==CAISSE_OK ||
           salle[PositionSalle[0]][PositionSalle[1]-2] ==MUR ||
           salle[PositionSalle[0]][PositionSalle[1]-2] == PIERRE ||
           salle[PositionSalle[0]][PositionSalle[1]-2] == PORTE_F ||
           salle[PositionSalle[0]][PositionSalle[1]-2] == PORTE_O) //colonne/ ligne
        {
            return 0;//pas de deplacement
        }

        if(salle[PositionSalle[0]][PositionSalle[1]-2] == OBJECTIF)//s'il y a un objectif devant la caisse que l'on veut pousser
        {
            salle [PositionSalle[0]][PositionSalle[1]-1] = VIDE;  //on enleve la caisse de son ancienne position
            salle[PositionSalle[0]][PositionSalle[1]-2] =CAISSE_OK;//on la place sur l'objectif et on la note "a sa place "
            PositionSalle[1]-=1;//deplacement de notre personnage dans la salle
            ouvrirPortes(salle);//regarde si l'ouverture des portes est possible ( plus d'objectif)
            return 1;
        }
        salle [PositionSalle[0]][PositionSalle[1]-1] = VIDE;//on enleve la caisse de son ancienne position
        salle[PositionSalle[0]][PositionSalle[1]-2] =CAISSE;//on la place sur la case plus loin
        PositionSalle[1]-=1;//deplacement de notre personnage dans la salle
        return 1;
    }

    if(DIRECTION == BAS)//si je me deplace en bas
    {
       if (salle[PositionSalle[0]][PositionSalle[1]+2] ==CAISSE ||  //s'il y a un obstacle devant la caisse que l'on veut pousser
           salle[PositionSalle[0]][PositionSalle[1]+2] ==CAISSE_OK ||
           salle[PositionSalle[0]][PositionSalle[1]+2] ==MUR ||
           salle[PositionSalle[0]][PositionSalle[1]+2] == PIERRE ||
           salle[PositionSalle[0]][PositionSalle[1]+2] == PORTE_F ||
           salle[PositionSalle[0]][PositionSalle[1]+2] == PORTE_O) //colonne/ ligne
        {
            return 0;//pas de deplacement
        }

        if(salle[PositionSalle[0]][PositionSalle[1]+2] == OBJECTIF)//s'il y a un objectif devant la caisse que l'on veut pousser
        {
            salle [PositionSalle[0]][PositionSalle[1]+1] = VIDE;//on enleve la caisse de son ancienne position
            salle[PositionSalle[0]][PositionSalle[1]+2] =CAISSE_OK;//on la place sur l'objectif et on la note "a sa place "
            PositionSalle[1]+=1;//deplacement de notre personnage dans la salle
            ouvrirPortes(salle);//regarde si l'ouverture des portes est possible ( plus d'objectif)
            return 1;
        }
        salle [PositionSalle[0]][PositionSalle[1]+1] = VIDE;//on enleve la caisse de son ancienne position
        salle[PositionSalle[0]][PositionSalle[1]+2] =CAISSE;//on la place sur la case plus loin
        PositionSalle[1]+=1;//deplacement de notre personnage dans la salle
        return 1;
    }

    if(DIRECTION == GAUCHE)//si je me deplace a gauche
    {
       if (salle[PositionSalle[0]-2][PositionSalle[1]] ==CAISSE ||  //s'il y a un obstacle devant la caisse que l'on veut pousser
           salle[PositionSalle[0]-2][PositionSalle[1]] ==CAISSE_OK ||
           salle[PositionSalle[0]-2][PositionSalle[1]] ==MUR ||
           salle[PositionSalle[0]-2][PositionSalle[1]] == PIERRE ||
           salle[PositionSalle[0]-2][PositionSalle[1]] == PORTE_F ||
           salle[PositionSalle[0]-2][PositionSalle[1]] == PORTE_O) //colonne/ ligne
        {
            return 0;//pas de deplacement
        }

        if(salle[PositionSalle[0]-2][PositionSalle[1]] == OBJECTIF)//s'il y a un objectif devant la caisse que l'on veut pousser
        {
            salle [PositionSalle[0]-1][PositionSalle[1]] = VIDE;//on enleve la caisse de son ancienne position
            salle[PositionSalle[0]-2][PositionSalle[1]] =CAISSE_OK;//on la place sur l'objectif et on la note "a sa place "
            PositionSalle[0]-=1;//deplacement de notre personnage dans la salle
            ouvrirPortes(salle);//regarde si l'ouverture des portes est possible ( plus d'objectif)
            return 1;
        }
        salle [PositionSalle[0]-1][PositionSalle[1]] = VIDE;//on enleve la caisse de son ancienne position
        salle[PositionSalle[0]-2][PositionSalle[1]] =CAISSE;//on la place sur la case plus loin
        PositionSalle[0]-=1;//deplacement de notre personnage dans la salle
        return 1;
    }

    if(DIRECTION == DROITE)//si je me deplace a droite
    {
       if (salle[PositionSalle[0]+2][PositionSalle[1]] ==CAISSE ||   //s'il y a un obstacle devant la caisse que l'on veut pousser
           salle[PositionSalle[0]+2][PositionSalle[1]] ==CAISSE_OK ||
           salle[PositionSalle[0]+2][PositionSalle[1]] ==MUR ||
           salle[PositionSalle[0]+2][PositionSalle[1]] == PIERRE ||
           salle[PositionSalle[0]+2][PositionSalle[1]] == PORTE_F ||
           salle[PositionSalle[0]+2][PositionSalle[1]] == PORTE_O) //colonne/ ligne
        {
            return 0;//pas de deplacement
        }

        if(salle[PositionSalle[0]+2][PositionSalle[1]] == OBJECTIF)//s'il y a un objectif devant la caisse que l'on veut pousser
        {
            salle [PositionSalle[0]+1][PositionSalle[1]] = VIDE; //on enleve la caisse de son ancienne position
            salle[PositionSalle[0]+2][PositionSalle[1]] =CAISSE_OK;//on la place sur l'objectif et on la note "a sa place "
            PositionSalle[0]+=1;//deplacement de notre personnage dans la salle
            ouvrirPortes(salle);//regarde si l'ouverture des portes est possible ( plus d'objectif)
            return 1;
        }
        salle [PositionSalle[0]+1][PositionSalle[1]] = VIDE; //on enleve la caisse de son ancienne position
        salle[PositionSalle[0]+2][PositionSalle[1]] =CAISSE;//on la place sur la case plus loin
        PositionSalle[0]+=1;//deplacement de notre personnage dans la salle
        return 1;
    }
    return -1;
}

void MaFin(SDL_Surface *ecran,int typedefin)
{
    SDL_Event event;
    int continuer = 1;
    SDL_Surface *imagedefin = NULL;
    SDL_Rect position;
    position.x=0;
    position.y=0;
    ///chargement de l'image souhaité///
    if (typedefin == GAGNEE)
    {
        imagedefin = SDL_LoadBMP("image/felicitation.bmp");
    }

    else if(typedefin == PERDU)
    {
        imagedefin = SDL_LoadBMP("image/game_over.bmp");
    }

    SDL_BlitSurface(imagedefin, NULL, ecran, &position);
    SDL_Flip(ecran);//maj de l'ecran

    while (continuer)//mise en pause de l'ecran afin de montrer l'image de fin au joueur
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

                    case SDLK_SPACE: // Appuier sur la touche Echap,
                        continuer = 0;//on arrête le programme
                        break;
                }
        }
    }
}
