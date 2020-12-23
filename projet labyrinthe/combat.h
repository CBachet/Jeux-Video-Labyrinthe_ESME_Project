#ifndef COMBAT_H_INCLUDED
#define COMBAT_H_INCLUDED

        void combat(SDL_Surface *ecran,Personnage *Joueur, int Mechant);
        void Pause(SDL_Event event);

        ///TROLL///
        const int VieDeTroll = 100;
        const int ForceDeTroll = 50;
        const int DefDeTroll = 5;

        ///BOSS///
        const int VieDeBoss = 400;
        const int ForceDeBoss = 70;
        const int DefDeBoss = 10;



#endif // COMBAT_H_INCLUDED
