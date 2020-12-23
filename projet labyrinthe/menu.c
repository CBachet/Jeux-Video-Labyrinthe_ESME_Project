#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "constantes.h"
#include "menu.h"
#include "jeu.h"

//fct qui va lancer la SDL et afficher l'ecran de menu (espace pour lancer le jeu, echap pour quitter)

void menu()
{
    SDL_Surface *ecran = NULL,*menu = NULL; //creation des surface SDL
    SDL_Event event;//var event de la SDL qui va contenir un evenement
    SDL_Rect positionMenu;//vecteur position  du menu
    int continuer = 1;//variable qui permet de faire tourner la boucle des evenements

    positionMenu.x = 0; // tt en haut a gauche ( pour prendre tte la taille de l'écran)
    positionMenu.y = 0;

    SDL_Init(SDL_INIT_VIDEO);//initialisation de la SDL

    SDL_WM_SetIcon(SDL_LoadBMP("image/porte_ico.bmp"), NULL);//init icone
    ecran=SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);//creation de la surface ac les dim contenu dans constante.h
    menu = SDL_LoadBMP("image/menulaby.bmp");//chargement de l'image du menu
    SDL_WM_SetCaption("Projet labyrinthe", NULL);//changement du nom de la fenetre
    //SDL_BlitSurface(menu,NULL,ecran,&positionMenu); //on affiche l'image du menu sur l'ecran


    while (continuer)
    {//boucle des evenements
        SDL_WaitEvent(&event);//va attendre un evenement
        switch (event.type)
        {
            case SDL_QUIT://si on appuie sur la croix:
                continuer = 0;//la fenetre SDL se ferme
                break;

            case SDL_KEYDOWN://si on appuie sur une touche
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appuie sur la touche Echap: on arrête le programme */
                        continuer = 0;
                        break;

                    case SDLK_SPACE://appuie sur espace : on lance le jeu
                        jeu(ecran);
                        //continuer = 0; //pt etre pas le mettre pour remettre au menu a la fin du jeu
                        break;
                }
                break;
        }
        SDL_BlitSurface(menu,NULL,ecran,&positionMenu);
        SDL_Flip(ecran);//met a jour l'ecran
    }

    SDL_FreeSurface(menu);//libere la place prise par la surface menu
    SDL_Quit();
}
