#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL_ttf.h>
#include <time.h>
#include "constantes.h"
#include "combat.h"



void Pause(SDL_Event event)
{
    int suivant = 0;
     while(suivant == 0)
    {                                                      //Attend que l'utilisateur appuie sur espace pour afficher le texte suivant
        SDL_WaitEvent(&event);                                              //Attend un évènement de l'utilisateur
        if (event.type==SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)  //Vérification qu'il s'agit de la touche espace
            suivant=1;
    }
}

void combat(SDL_Surface *ecran,Personnage *Joueur,int MECHANT)
{
    char texteint [100];                                //Constante pour stocker le texte de sprintf
    char VieJoueur [100];                               //Constante pour stocker le texte de sprintf
    char VieTroll [100];                                //Constante pour stocker le texte de sprintf
    int CompteurCombat=0;
    int DefautVieJ = 0;                                 //Constante qui stocke la vie par défaut du joueur
    int DefautVieE = 0;                                 //Constante qui stocke la vie par défaut du troll
    Personnage *Ennemi;        //a remplacer par ENNEMI et mettre les stat de ennemi ds cst de combat                           //Initialisation structure troll

    ///initaialisation de l'ennemi///
    if(MECHANT == ENNEMI)//si c'est un troll
    {
        Ennemi->vie = VieDeTroll;
        Ennemi->attaque = ForceDeTroll;
        Ennemi->defense = DefDeTroll;
        Ennemi->VieSur3 =Ennemi->vie/3; //Constante permettant de vérifier le niveau de vie du troll
    }

    if(MECHANT == BOSS)//si c'est un Le BOSS
    {
        Ennemi->vie = VieDeBoss;
        Ennemi->attaque = ForceDeBoss;
        Ennemi->defense = DefDeBoss;
        Ennemi->VieSur3 =Ennemi->vie/3;
    }

    DefautVieJ = Joueur->vie; //sera des cst
    DefautVieE = Ennemi->vie;


    ///initialisation de SDL_TTF///
        if(TTF_Init() == -1)                                //Vérification pas d'erreur de l'initialisation
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Surface *imageDeFond = NULL, *Mechant = NULL, *Attoudef = NULL, *Perso = NULL, *texte = NULL, *Fondtexte = NULL, *VieJ = NULL, *VieE = NULL;  //Déclaration surfaces SDL
    SDL_Event event;                                    //Variable d'évènement

    TTF_Font *police = NULL;                            //Déclaration police d'écriture
    TTF_Font *policevie = NULL;                         //Déclaration police d'écriture
    SDL_Color couleurTexte = {255, 255, 255};           //Déclaration couleur texte
    SDL_Color couleurVert = {0, 255, 0};                //Déclaration couleur texte
    SDL_Color couleurOrange = {255, 128, 0};            //Déclaration couleur texte
    SDL_Color couleurRouge = {255, 0, 0};               //Déclaration couleur texte

    SDL_Rect positionFond, positionMechant, positionAttoudef, positionPerso, positionTexte, positionVieJ, positionVieE;  //Déclaration variable position de chaque surface


    ///PARAMETRAGE POSITION DES SURFACES///
    positionFond.x = 0;
    positionFond.y = 0;
    positionMechant.x=LARGEUR_FENETRE-250;
    positionMechant.y=0;
    positionAttoudef.x=0;
    positionAttoudef.y= HAUTEUR_FENETRE-114;
    positionPerso.x=150;
    positionPerso.y=HAUTEUR_FENETRE-275;
    positionTexte.x=20;
    positionTexte.y=HAUTEUR_FENETRE-70;
    positionVieJ.x = 20;
    positionVieJ.y = HAUTEUR_FENETRE-170;
    positionVieE.x = 340;
    positionVieE.y = 20;

    ///CHARGEMENT DES IMAGES BITMAPS DANS LES SURFACES///
    imageDeFond = SDL_LoadBMP("image/fond.bmp");

    if(MECHANT == ENNEMI)
        Mechant = SDL_LoadBMP("image/Trollcombat.bmp");
    else if(MECHANT == BOSS)
        Mechant = SDL_LoadBMP("image/bossraffy.bmp");
    Attoudef = SDL_LoadBMP("image/atta.bmp");
    Perso = SDL_LoadBMP("image/Teddycombat.bmp");
    Fondtexte = SDL_LoadBMP("image/fondtexte.bmp");

    ///SUPRESSION FOND BLEU DES PERSONNAGES///
    SDL_SetColorKey(Mechant, SDL_SRCCOLORKEY, SDL_MapRGB(Mechant->format, 0, 0, 255));
    SDL_SetColorKey(Perso, SDL_SRCCOLORKEY, SDL_MapRGB(Perso->format, 0, 0, 255));

    ///OUVERTURE POLICES DE TEXTE///
    police = TTF_OpenFont("bebas.ttf", 22);
    policevie = TTF_OpenFont("bebasneue.ttf", 27);


    SDL_Flip(ecran);
    srand(time(NULL));//Utilisé pour choix hasard

    ///boucle de combat///
    while (Joueur->vie >0 && Ennemi->vie >0 && CompteurCombat < 150)                               //Boucle pour tout le combat
   {
       // Comptabilise le nombre de tour de combat
        CompteurCombat++;
        int AttaqueOuDefend=rand()%2;

         ///AFFICHAGE DES IMAGES///
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_BlitSurface(Mechant, NULL, ecran, &positionMechant);
        SDL_BlitSurface(Attoudef, NULL, ecran, &positionAttoudef);
        SDL_BlitSurface(Perso, NULL, ecran, &positionPerso);

        sprintf(VieJoueur, "VIE DE TEDDY : %i PV", Joueur->vie);                                   //Stockage texte de la vie du joueur

         //////////////////        VERIFICATION VIE JOUEUR POUR LA COULEUR        //////////////////
        if(Joueur->vie <= Joueur->VieSur3){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurRouge);
        }
        else if ((Joueur->vie >= Joueur->VieSur3) && (Joueur->vie <= (2*Joueur->VieSur3))){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurOrange);
        }
        else if (Joueur->vie >= (2*Joueur->VieSur3)){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurVert);
        }
        SDL_BlitSurface(VieJ, NULL, ecran, &positionVieJ);                                  //Affichage texte de la vie du joueur


        if(MECHANT == ENNEMI)
            sprintf(VieTroll, "VIE DE TROLL : %i PV", Ennemi->vie);                                     //Stockage texte de la vie du joueur
        else if(MECHANT == BOSS)
            sprintf(VieTroll, "VIE DE LORD RAFFY : %i PV", Ennemi->vie);

        //////////////////        VERIFICATION VIE TROLL POUR LA COULEUR        //////////////////
        if(Ennemi->vie <= Ennemi->VieSur3){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurRouge);
        }
        else if ((Ennemi->vie >= Ennemi->VieSur3) && (Ennemi->vie <= (2*Ennemi->VieSur3))){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurOrange);
        }
        else if (Ennemi->vie >= (2*Ennemi->VieSur3)){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurVert);
        }

        SDL_BlitSurface(VieE, NULL, ecran, &positionVieE);                                  //Affichage texte de la vie du troll
        SDL_Flip(ecran);                                                                    //Actualisation écran

        SDL_WaitEvent(&event);                                                              //Attente d'évènement de l'utilisateur
    switch(event.type)
    {
        case SDL_QUIT:           //a ameliorer pour quitter + ac echape                                                            //Choix : Quitte en appuyant sur la croix
            SDL_Quit();
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
                case SDLK_q: //Fonctionne en QWERTY, pour que cela marche quand on clique sur A, il faut selectionner la touche Q
                    //ATTAQUE
                    {
                        SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);             //Affichage du fond sous le texte
                        sprintf(texteint, "Teddy    attaque    avec    une    force    de    %i", Joueur->attaque);  //Stockage texte
                        texte = TTF_RenderText_Blended(police, texteint, couleurTexte);         //Ecriture texte
                        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);                    //Affichage texte
                        SDL_Flip(ecran); //Actualisation écran
                        Pause(event);
                        texteint[0] = '\0';                                                     //Remise à 0 du tableau contenant le texte

                        if (AttaqueOuDefend == 1)
                        {                            //Si le Troll attaque aussi
                            SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);         //Affichage du fond sous le texte
                            Ennemi->vie -= Joueur->attaque-Ennemi->defense;                     //Enlève la vie du troll due à l'attaque
                            if (Ennemi->vie <= 0)                                                 //Empeche d'afficher une vie négative
                                Ennemi->vie = 0;

                            if(MECHANT == ENNEMI)
                                sprintf(texteint, "Troll    n'a    plus    que    %i    de    vie", Ennemi->vie);  //Stockage texte
                            else if(MECHANT == BOSS)
                                sprintf(texteint, "Lord Raffy    n'a    plus    que    %i    de    vie", Ennemi->vie);  //Stockage texte

                            texte = TTF_RenderText_Blended(police, texteint, couleurTexte);     //Ecriture texte
                            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);                //Affichage texte
                            SDL_Flip(ecran);                                                    //Actualisation écran
                            Pause(event);
                            texteint[0] = '\0';

                            SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);
                            Joueur->vie-=Ennemi->attaque-Joueur->defense;                                          //Enlève la vie du joueur après l'attaque du troll
                            if (Joueur->vie <= 0)                                                //Empeche d'afficher une vie négative
                                Joueur->vie = 0;
                            sprintf(texteint, "Teddy    n'a    plus    que    %i    de    vie!", Joueur->vie);
                            texte = TTF_RenderText_Blended(police, texteint, couleurTexte);
                            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                            SDL_Flip(ecran);
                            Pause(event);
                            texteint[0] = '\0';
                        }
                         else
                        {                                                                   //Si le troll n'attaque pas
                            SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);
                            if ((Ennemi->vie-=Joueur->attaque-2*Ennemi->defense) >= DefautVieE)                       //Vérifie qu'il ne s'ajoute pas plus de vie que celle de départ
                                Ennemi->vie = DefautVieE;
                            if (Ennemi->vie <= 0)                                                 //Empeche d'afficher une vie négative
                                Ennemi->vie = 0;

                            if(MECHANT == ENNEMI)
                                sprintf(texteint, "Le    Troll    s'est    defendu    et    a    donc    %i    de    vie", Ennemi->vie);
                            else if(MECHANT == BOSS)
                                sprintf(texteint, "Lord Raffy    s'est    defendu    et    a    donc    %i    de    vie", Ennemi->vie);

                            texte = TTF_RenderText_Blended(police, texteint, couleurTexte);
                            SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                            SDL_Flip(ecran);
                            Pause(event);
                            texteint[0] = '\0';
                        }
                        break;
                    }

                case SDLK_d:
                    //DEFENSE
                    if(AttaqueOuDefend == 1)
                    {                                               //Si le Troll attaque
                        SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);
                        if ((Joueur->vie+=2*Joueur->defense-Ennemi->attaque/2 ) >= DefautVieJ)                     //Vérifie qu'il ne s'ajoute pas plus de vie que celle de départ
                            Joueur->vie = DefautVieJ;
                        if (Joueur->vie <= 0)                                                //Empeche d'afficher une vie négative
                                Joueur->vie = 0;
                        sprintf(texteint, "Teddy    s'est    defendu    et    a    donc    %i    de    vie", Joueur->vie);
                        texte = TTF_RenderText_Blended(police, texteint, couleurTexte);
                        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                        SDL_Flip(ecran);
                        Pause(event);
                        texteint[0] = '\0';
                    }
                    else
                    {                                                                   //Si personne n'attaque
                        SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);
                        if ((Joueur->vie+=2*Joueur->defense) >= DefautVieJ)                     //Vérifie qu'il ne s'ajoute pas plus de vie que celle de départ
                            Joueur->vie = DefautVieJ;
                        sprintf(texteint, "Personne    n'a    attaque,    Teddy    a    maintenant    %i    de    vie", Joueur->vie);
                        texte = TTF_RenderText_Blended(police, texteint, couleurTexte);
                        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                        SDL_Flip(ecran);
                        Pause(event);
                        texteint[0] = '\0';

                        SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);
                        if ((Ennemi->vie+=Ennemi->defense) >= DefautVieE)                       //Vérifie qu'il ne s'ajoute pas plus de vie que celle de départ
                            Ennemi->vie = DefautVieE;

                        if(MECHANT == ENNEMI)
                            sprintf(texteint, "Troll    n'a    plus    que    %i    de    vie", Ennemi->vie);  //Stockage texte
                        else if(MECHANT == BOSS)
                            sprintf(texteint, "Lord Raffy    n'a    plus    que    %i    de    vie", Ennemi->vie);  //Stockage texte

                        texte = TTF_RenderText_Blended(police, texteint, couleurTexte);
                        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
                        SDL_Flip(ecran);
                        Pause(event);
                        texteint[0] = '\0';
                    }
                    break;
            }
        }
    }

    if (Joueur->vie <= 0 && Ennemi->vie > 0)
    {                                              //Si joueur a perdu

        //////////////////        AFFICHAGE DES IMAGES        //////////////////
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_BlitSurface(Mechant, NULL, ecran, &positionMechant);
        SDL_BlitSurface(Attoudef, NULL, ecran, &positionAttoudef);
        SDL_BlitSurface(Perso, NULL, ecran, &positionPerso);
        SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);

        texte = TTF_RenderText_Blended(police, "Teddy    Rinner", couleurTexte);
        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
        sprintf(VieJoueur, "VIE TEDDY : %i PV", Joueur->vie);

        //////////////////        VERIFICATION VIE JOUEUR POUR LA COULEUR        //////////////////
        if(Joueur->vie <= Joueur->VieSur3){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurRouge);
        }
        else if ((Joueur->vie >= Joueur->VieSur3) && (Joueur->vie <= (2*Joueur->VieSur3))){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurOrange);
        }
        else if (Joueur->vie >= (2*Joueur->VieSur3)){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurVert);
        }

        SDL_BlitSurface(VieJ, NULL, ecran, &positionVieJ);                              //Affichage texte

        if(MECHANT == ENNEMI)
            sprintf(VieTroll, "VIE DE TROLL : %i PV", Ennemi->vie);                                     //Stockage texte de la vie du joueur
        else if(MECHANT == BOSS)
            sprintf(VieTroll, "VIE DE LORD RAFFY: %i PV", Ennemi->vie);

        //////////////////        VERIFICATION VIE TROLL POUR LA COULEUR        //////////////////
        if(Ennemi->vie <= Ennemi->VieSur3){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurRouge);
        }
        else if ((Ennemi->vie >= Ennemi->VieSur3) && (Ennemi->vie <= (2*Ennemi->VieSur3))){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurOrange);
        }
        else if (Ennemi->vie >= (2*Ennemi->VieSur3)){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurVert);
        }

        SDL_BlitSurface(VieE, NULL, ecran, &positionVieE);                              //Affichage texte
        SDL_Flip(ecran);                                                                //Actualisation écran
        Pause(event);
    }

    if (Ennemi->vie <= 0)
    {                                                                //Si joueur a gagné
        //////////////////        AFFICHAGE DES IMAGES        //////////////////
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
        SDL_BlitSurface(Mechant, NULL, ecran, &positionMechant);
        SDL_BlitSurface(Attoudef, NULL, ecran, &positionAttoudef);
        SDL_BlitSurface(Perso, NULL, ecran, &positionPerso);
        SDL_BlitSurface(Fondtexte, NULL, ecran, &positionAttoudef);

        texte = TTF_RenderText_Blended(police, "Vous    avez    gagne    :)", couleurTexte);
        SDL_BlitSurface(texte, NULL, ecran, &positionTexte);
        sprintf(VieJoueur, "VIE DE TEDDY : %i PV", Joueur->vie);

        //////////////////        VERIFICATION VIE JOUEUR POUR LA COULEUR        //////////////////
        if(Joueur->vie <= Joueur->VieSur3){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurRouge);
        }
        else if ((Joueur->vie >= Joueur->VieSur3) && (Joueur->vie <= (2*Joueur->VieSur3))){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurOrange);
        }
        else if (Joueur->vie >= (2*Joueur->VieSur3)){
            VieJ = TTF_RenderText_Blended(policevie, VieJoueur, couleurVert);
        }

        SDL_BlitSurface(VieJ, NULL, ecran, &positionVieJ);                              //Affichage texte


        if(MECHANT == ENNEMI)
            sprintf(VieTroll, "VIE DE TROLL : %i PV", Ennemi->vie);                                     //Stockage texte de la vie du joueur
        else if(MECHANT == BOSS)
            sprintf(VieTroll, "VIE DE LORD RAFFY : %i PV", Ennemi->vie);
        //////////////////        VERIFICATION VIE TROLL POUR LA COULEUR        //////////////////
        if(Ennemi->vie <= Ennemi->VieSur3){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurRouge);
        }
        else if ((Ennemi->vie >= Ennemi->VieSur3) && (Ennemi->vie <= (2*Ennemi->VieSur3))){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurOrange);
        }
        else if (Ennemi->vie >= (2*Ennemi->VieSur3)){
            VieE = TTF_RenderText_Blended(policevie, VieTroll, couleurVert);
        }

        SDL_BlitSurface(VieE, NULL, ecran, &positionVieE);                              //Affichage texte
        SDL_Flip(ecran);                                                                //Actualisation écran
        Pause(event);
    }

    TTF_CloseFont(police);
    TTF_Quit();
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(Mechant);
    SDL_FreeSurface(Attoudef);
    SDL_FreeSurface(Perso);
    SDL_FreeSurface(texte);
}
