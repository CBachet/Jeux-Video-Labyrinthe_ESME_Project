//tts les fonction necessaire pour init le jeu
#ifndef JEU_H_INCLUDED
#define JEU_H_INCLUDED

        typedef struct Position
        {
            int ligne;
            int colonne;
        }Position;

        int NbrdeLigne(FILE* fichier);//sert a compter le nombre de lignes du fichier labyrinthe
        void ChercheNombre(char valeurcherchee,int Nbligne, int *Taille, int **Tableau, Position* position);
        //permet de verifier/chercher la presence d'un nombre(valeurcherchee) dans tableau et indique sa position
        void jeu(SDL_Surface *ecran);//fonction principale qui va lancer tous les mecanismes du jeu

#endif // JEU_H_INCLUDED
