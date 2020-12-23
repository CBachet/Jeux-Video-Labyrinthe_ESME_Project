#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED

        void chargersalle(int salle[][NB_BLOCS_HAUTEUR],int typesalle,int** Tableau,int* PositionMap);
        void affichageSalle(int typesalle,SDL_Surface *ecran,int** Tableau,int* PositionMap,int salle[][NB_BLOCS_HAUTEUR],SDL_Rect positionPerso,Personnage Joueur);


#endif // AFFICHAGE_H_INCLUDED
