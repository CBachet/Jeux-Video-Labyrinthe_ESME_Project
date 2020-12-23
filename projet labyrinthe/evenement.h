#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

        int deplacement(int DIRECTION, SDL_Rect position, int salle[][NB_BLOCS_HAUTEUR],int* PositionSalle,SDL_Surface *ecran,Personnage *Joueur);
        void changementSalle(SDL_Surface *ecran,SDL_Surface* PersoActuel,int DIRECTION,int** Tableau,int* PositionMap,SDL_Rect positionPerso,int salle[][NB_BLOCS_HAUTEUR],int* PositionSalle);
        int ouvrirPortes (int salle[][NB_BLOCS_HAUTEUR]);
        int deplacementCaisse(int DIRECTION, int salle[][NB_BLOCS_HAUTEUR], int* PositionSalle);
        void MaFin(SDL_Surface *ecran,int typedefin);

#endif // EVENEMENT_H_INCLUDED
