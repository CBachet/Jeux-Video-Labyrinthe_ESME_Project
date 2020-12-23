#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "affichage.h"
#include <SDL_ttf.h>


void chargersalle(int salle[][NB_BLOCS_HAUTEUR], int typesalle, int** Tableau,int* PositionMap)
{//permet d'init ts les elements d'une salle ds un tableau

    FILE* fichier = NULL;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1] = {0};
    char caractere =0;
    int i = 0, j = 0;//i=colonne , j=ligne

    switch (typesalle)//ouvre le fichier texte de la salle ou on se trouve
    {
        case( 0 ):
            fichier = fopen("salles/salle0.txt", "r");
            break;

        case( 1 ):
            fichier = fopen("salles/salle1.txt", "r");
            break;

        case( 2 ):
            fichier = fopen("salles/salle2.txt", "r");
            break;

        case( 3 ):
            fichier = fopen("salles/salle3.txt", "r");
            break;

        case( 4 ):
            fichier = fopen("salles/salle4.txt", "r");
            break;

        case( 5 ):
            fichier = fopen("salles/salle5.txt", "r");
            break;

        case( 6 ):
            fichier = fopen("salles/salle6.txt", "r");
            break;

        case( 7 ):
            fichier = fopen("salles/salle7.txt", "r");
            break;

        case( 9 ):
            fichier = fopen("salles/salle9.txt", "r");
            break;
    }

    while (caractere != EOF)//tantquejenesuispasalafindufichiertxt
    {
       caractere= fgetc(fichier);//je lis un caractere
       if (caractere != '\n')//si ce n'est pas un saut de ligne
       {
           ligneFichier[i] = caractere;//met le nbr ds un tableau
           i++;
       }
    }

    //remplir le tableau salle qui contient les composant de la salle ou on se trouve actuellement
    for(j=0;j<7;j++)
    {
        for(i=0;i<11;i++)
        {
            switch (ligneFichier[(j*NB_BLOCS_LARGEUR)+i])
            {
                case '0':
                    salle[i][j]=VIDE;
                    break;

                case '1':
                    salle[i][j]=ENNEMI;
                    break;

                case '2':
                    salle[i][j]=PIERRE;
                    break;

                case '3':
                    salle[i][j]=PIC;
                    break;

                case '4':
                    salle[i][j]=OBJECTIF;
                    break;

                case '5':
                    salle[i][j]=CAISSE;
                    break;

                case '6':
                    //salle[i][j]=SORTIE;
                    salle[i][j]=BOSS;
                    break;

                case '7':
                    salle[i][j]=PORTE_F;
                    break;

                case '8':
                    salle[i][j]=PORTE_O;
                    break;

                case '9':
                    salle[i][j]=MUR;
                    break;
            }
        }
    }
    fclose(fichier);


    ///placement des portes dans le tableau salle///
    if(typesalle != 5)
    {
        if (Tableau[PositionMap[0]-1][PositionMap[1]] != MUR)  //ligne /colonne          //si une salle en haut alors on place une porte ouverte
            salle[5][0] = PORTE_O;                                    // colonne /ligne
        if (Tableau[PositionMap[0]][PositionMap[1]-1] != MUR)  //ligne /colonne          //si une salle a gauche alors on place une porte ouverte
            salle[0][3] = PORTE_O;                                    // colonne /ligne
        if (Tableau[PositionMap[0]+1][PositionMap[1]] != MUR)  //ligne /colonne          //si une salle en bas alors on place une porte ouverte
            salle[5][6] = PORTE_O;                                    // colonne /ligne
        if (Tableau[PositionMap[0]][PositionMap[1]+1] != MUR)  //ligne /colonne          //si une salle a droite alors on place une porte ouverte
            salle[10][3] = PORTE_O;                                    // colonne /ligne
    }
    else
    {//si on est dan sune salle 5 ( enigme -> porte se ferme)
        if (Tableau[PositionMap[0]-1][PositionMap[1]] == MUR)  //ligne /colonne           //si une salle en haut alors on place une porte fermee
            salle[5][0] = MUR;                                    // colonne /ligne
        if (Tableau[PositionMap[0]][PositionMap[1]-1] == MUR)  //ligne /colonne           //si une salle a gauche alors on place une porte fermee
            salle[0][3] = MUR;                                    // colonne /ligne
        if (Tableau[PositionMap[0]+1][PositionMap[1]] == MUR)  //ligne /colonne           //si une salle en bas alors on place une porte fermee
            salle[5][6] = MUR;                                    // colonne /ligne
        if (Tableau[PositionMap[0]][PositionMap[1]+1] == MUR)  //ligne /colonne           //si une salle a droite alors on place une porte fermee
            salle[10][3] = MUR;
    }
}


void affichageSalle(int typesalle,SDL_Surface *ecran,int** Tableau,int* PositionMap,int salle[][NB_BLOCS_HAUTEUR],SDL_Rect positionPerso,Personnage Joueur)
{//permet d'afficher ts les elements d'une salle
        SDL_Surface *Porte_O[4] = {NULL};//pour chaque direction
        SDL_Surface *Porte_F[4] = {NULL};
        SDL_Surface *mur =NULL, *pierre =NULL;//les autres plus tard
        SDL_Surface *caisse = NULL , *caisse_ok = NULL, *objectif =NULL,*piege = NULL, *ennemi=NULL ,*boss =NULL, *sortie =NULL;

        SDL_Surface *quad; //a effacer

        SDL_Rect positionPorte, positionMur,position;
        int i = 0;


        ///chargements des sprites///
        mur = SDL_LoadBMP("image/mur2.bmp");                                                              //les murs
        SDL_SetColorKey(mur, SDL_SRCCOLORKEY, SDL_MapRGB(mur->format, 0, 0, 255));
        quad = SDL_LoadBMP("image/quadri.bmp");    //ne sert plus a rien                                                       //la grille
        SDL_SetColorKey(quad, SDL_SRCCOLORKEY, SDL_MapRGB(mur->format, 63, 72, 204));

        ///sprites de la porte :///
        Porte_O[HAUT]= SDL_LoadBMP("image/porte_haut_ouverte.bmp");
        SDL_SetColorKey(Porte_O[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_O[HAUT]->format, 0, 0, 255));
        Porte_O[BAS]= SDL_LoadBMP("image/porte_bas_ouverte.bmp");
        SDL_SetColorKey(Porte_O[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_O[BAS]->format, 0, 0, 255));
        Porte_O[DROITE]= SDL_LoadBMP("image/porte_droit_ouverte.bmp");
        SDL_SetColorKey(Porte_O[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_O[DROITE]->format, 0, 0, 255));
        Porte_O[GAUCHE]= SDL_LoadBMP("image/porte_gauche_ouverte.bmp");
        SDL_SetColorKey(Porte_O[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_O[GAUCHE]->format, 0, 0, 255));

        //pour la salle ac les portes fermees
            Porte_F[HAUT]= SDL_LoadBMP("image/porte_haut_fermee.bmp");
            SDL_SetColorKey(Porte_F[HAUT], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_F[HAUT]->format, 0, 0, 255));
            Porte_F[BAS]= SDL_LoadBMP("image/porte_bas_fermee.bmp");
            SDL_SetColorKey(Porte_F[BAS], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_F[BAS]->format, 0, 0, 255));
            Porte_F[DROITE]= SDL_LoadBMP("image/porte_droite_fermee.bmp");
            SDL_SetColorKey(Porte_F[DROITE], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_F[DROITE]->format, 0, 0, 255));
            Porte_F[GAUCHE]= SDL_LoadBMP("image/porte_gauche_fermee.bmp");
            SDL_SetColorKey(Porte_F[GAUCHE], SDL_SRCCOLORKEY, SDL_MapRGB(Porte_F[GAUCHE]->format, 0, 0, 255));

        ///sprite de caillou///
        pierre = SDL_LoadBMP("image/rocher.bmp");
        SDL_SetColorKey(pierre, SDL_SRCCOLORKEY, SDL_MapRGB(pierre->format, 0, 0, 255));
        /// les autres
        objectif = SDL_LoadBMP("image/objectif.bmp");
        SDL_SetColorKey(objectif, SDL_SRCCOLORKEY, SDL_MapRGB(objectif->format, 0, 0, 255));
        caisse = SDL_LoadBMP("image/caisse.bmp");
         SDL_SetColorKey(caisse, SDL_SRCCOLORKEY, SDL_MapRGB(caisse->format, 0, 0, 255));
        caisse_ok = SDL_LoadBMP("image/caisse_ok.bmp");
        SDL_SetColorKey(caisse_ok, SDL_SRCCOLORKEY, SDL_MapRGB(caisse_ok->format, 0, 0, 255));
        piege = SDL_LoadBMP("image/piege.bmp");
        SDL_SetColorKey(piege, SDL_SRCCOLORKEY, SDL_MapRGB(piege->format, 0, 0, 255));
        ennemi = SDL_LoadBMP("image/troll.bmp");
        SDL_SetColorKey(ennemi, SDL_SRCCOLORKEY, SDL_MapRGB(ennemi->format, 0, 0, 255));
        boss = SDL_LoadBMP("image/icoraffi.bmp");
        SDL_SetColorKey(boss, SDL_SRCCOLORKEY, SDL_MapRGB(boss->format, 0, 0, 255));
        sortie = SDL_LoadBMP("image/Escalier.bmp");
        SDL_SetColorKey(sortie, SDL_SRCCOLORKEY, SDL_MapRGB(sortie->format, 0, 0, 255));

        positionMur.x=0;//placement de la position des murs
        positionMur.y=0;
        SDL_BlitSurface(mur,NULL,ecran,&positionMur); //affichage des murs
        //SDL_BlitSurface(quad,NULL,ecran,&positionMur);

        ///affichage des portes///
        if (salle[0][3] == PORTE_O)  //tableau[ligne][colonne]  //a gauche //si il y a une porte ouverte a la place de la porte de gauche
        {
            positionPorte.x = 0;//placement de la porte
            positionPorte.y = 3*TAILLE_BLOC+5;
            SDL_BlitSurface(Porte_O[GAUCHE],NULL,ecran,&positionPorte);//affiche la porte
        }
        if (salle[5][0] == PORTE_O)//si il y a une porte ouverte a la place de la porte du haut
        {
            positionPorte.x = 5*TAILLE_BLOC+5;//placement de la porte
            positionPorte.y = 0;
            SDL_BlitSurface(Porte_O[HAUT],NULL,ecran,&positionPorte);//affiche la porte
        }
        if (salle[10][3] == PORTE_O)//si il y a une porte ouverte a la place de la porte de droite
        {
            positionPorte.x = 10*TAILLE_BLOC;//placement de la porte
            positionPorte.y = 3*TAILLE_BLOC+5;
            SDL_BlitSurface(Porte_O[DROITE],NULL,ecran,&positionPorte);//affiche la porte
        }
        if (salle[5][6] == PORTE_O)//si il y a une porte ouverte a la place de la porte du bas
        {
            positionPorte.x = 5*TAILLE_BLOC+5;//placement de la porte
            positionPorte.y = 6*TAILLE_BLOC;
            SDL_BlitSurface(Porte_O[BAS],NULL,ecran,&positionPorte);//affiche la porte
        }

        if(typesalle == 5)
        {
            if (salle[0][3] == PORTE_F)  //tableau[ligne][colonne]  //a gauche //si il y a une porte fermee a la place de la porte de gauche
            {
                positionPorte.x = 0; //placement de la porte
                positionPorte.y = 3*TAILLE_BLOC+5;
                SDL_BlitSurface(Porte_F[GAUCHE],NULL,ecran,&positionPorte);//affiche la porte
            }
            if (salle[5][0] == PORTE_F) //si il y a une porte fermee a la place de la porte du haut
            {
                positionPorte.x = 5*TAILLE_BLOC+5;//placement de la porte
                positionPorte.y = 0;
                SDL_BlitSurface(Porte_F[HAUT],NULL,ecran,&positionPorte);//affiche la porte
            }
            if (salle[10][3] == PORTE_F)//si il y a une porte fermee a la place de la porte de droite
            {
                positionPorte.x = 10*TAILLE_BLOC;//placement de la porte
                positionPorte.y = 3*TAILLE_BLOC+5;
                SDL_BlitSurface(Porte_F[DROITE],NULL,ecran,&positionPorte);//affiche la porte
            }
            if (salle[5][6] == PORTE_F)//si il y a une porte fermee a la place de la porte du bas
            {
                positionPorte.x = 5*TAILLE_BLOC+5;//placement de la porte
                positionPorte.y = 6*TAILLE_BLOC;
                SDL_BlitSurface(Porte_F[BAS],NULL,ecran,&positionPorte);//affiche la porte
            }
        }


        ///afficher les autres elements///
         int j=0,k=0;

        for (j = 0 ; j < NB_BLOCS_LARGEUR ; j++)//va se ballader dans le tableau
        {
            for (k = 0 ; k < NB_BLOCS_HAUTEUR ; k++)
            {
                position.x = j * TAILLE_BLOC;
                position.y = k * TAILLE_BLOC;

                switch(salle[j][k])//si il y a un element: va l'afficher a cette case
                {
                    case PIERRE:
                        SDL_BlitSurface(pierre, NULL, ecran, &position);
                        break;

                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        break;

                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;

                    case CAISSE_OK:
                        SDL_BlitSurface(caisse_ok, NULL, ecran, &position);
                        break;

                    case PIC:
                        SDL_BlitSurface(piege, NULL, ecran, &position);
                        break;

                    case ENNEMI:
                        SDL_BlitSurface(ennemi, NULL, ecran, &position);
                        break;

                    case BOSS:
                        SDL_BlitSurface(boss, NULL, ecran, &position);
                        break;

                    case SORTIE:
                        SDL_BlitSurface(sortie, NULL, ecran, &position);
                        break;
                }
            }
        }


        ///affichage de la vie du personnage///
        SDL_Surface *texte = NULL;
        SDL_Rect posVie;
        TTF_Font *police = NULL;
        char VieJoueur [20];

        TTF_Init();

        police = TTF_OpenFont("arial.ttf", 25);
        SDL_Color Blanc = {255, 255, 255};


        sprintf(VieJoueur, "Vie : %i pv ", Joueur.vie);
        texte = TTF_RenderText_Blended(police, VieJoueur, Blanc );//ecrire du texte ac une police, le texte, la couleur
        posVie.x = 20;
        posVie.y = 20;
        SDL_BlitSurface(texte, NULL, ecran, &posVie); /* Blit du texte */





        ///liberation de memoire///
        TTF_CloseFont(police);//ferme le dossier police
        TTF_Quit();

        SDL_FreeSurface(mur);
        SDL_FreeSurface(quad);
        SDL_FreeSurface(pierre);
        SDL_FreeSurface(objectif);
        SDL_FreeSurface(caisse);
        SDL_FreeSurface(caisse_ok);
        SDL_FreeSurface(piege);
        SDL_FreeSurface(ennemi);
        for (i = 0 ; i < 4 ; i++)
        {
            SDL_FreeSurface(Porte_O[i]);
            SDL_FreeSurface(Porte_F[i]);
        }


}

//fonction optionnelle non finie
void minimap(int nbrdecara,SDL_Surface *ecran,int** Tableau,int* PositionMap , int NbLigne)
{
    SDL_Surface *carte = NULL;
    SDL_Rect positioncarte;

    positioncarte.x = 9*TAILLE_BLOC+10;
    positioncarte.y = 5*TAILLE_BLOC+20;

    carte = SDL_CreateRGBSurface(SDL_HWSURFACE, 110, 90, 32, 0, 0, 0, 0);//cree une surfface rectangulaire
    SDL_FillRect(carte, NULL, SDL_MapRGB(carte->format, 255, 255, 255));


    SDL_BlitSurface(carte, NULL, ecran, &positioncarte);


   // SDL_Surface *salle[100]={NULL};
    SDL_Surface *salle = NULL;
    SDL_Rect positionsalle;
//    int i = 0;

    //for (i = 0 ; i <=100 ; i++)
       // salle[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, 100, 50, 32, 0, 0, 0, 0);
    salle = SDL_CreateRGBSurface(SDL_HWSURFACE, 20, 10, 32, 0, 0, 0, 0);



    positionsalle.x = positioncarte.x + 110/2;
    positionsalle.y = positioncarte.y + 90/2;
    //positionsalle.x = 34;
    //positionsalle.y = 60;

    switch(Tableau[PositionMap[0]][PositionMap[1]])
     {

        case (0):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
            break;

        case (1):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
            break;

        case (2):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
            break;

        case (3):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
            break;

        case (4):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
            break;

        case (5):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
            break;

        case (6):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 0, 255, 255));
            break;

        case (8):
            SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 0255, 0 , 255));
            break;

     }


    //SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, Tableau[PositionMap[0]][PositionMap[1]*2], Tableau[PositionMap[0]][PositionMap[1]-58], Tableau[PositionMap[0]][PositionMap[1]+54]));
    //SDL_FillRect(salle, NULL, SDL_MapRGB(ecran->format, 0*2, 0+22, 0-4));
    SDL_BlitSurface(salle, NULL, ecran, &positionsalle);

    SDL_Flip(ecran);

    SDL_FreeSurface(carte);
    SDL_FreeSurface(salle);
    //for (i = 0 ; i <= 100 ; i++)
      //  SDL_FreeSurface(salle[i]);
}
