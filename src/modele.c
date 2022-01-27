#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define HAUTEUR_MAX 650
#define LARGEUR_MAX 800

// FONCTION POUR VÉRIFIER SI LE CLIQUE EST DANS UN INTERVALLE DONNÉE
SDL_bool est_Dans_Intervalle(SDL_Event E, SDL_Rect rect)
{
    int x = E.button.x;
    int y = E.button.y;
    

    if(x>rect.x && x<rect.x+rect.w && y>rect.y && y<rect.y+rect.h)
    {
        return SDL_TRUE;
    }
    else return SDL_FALSE;
}
void bouton_Selectione(SDL_Renderer *r ,SDL_Rect monBouton)
{
    SDL_SetRenderDrawColor(r,173,255,47,SDL_ALPHA_OPAQUE);
    for (size_t i = 0; i < 5; i++)
    {
        monBouton.x+=i; monBouton.y+=i; monBouton.h-=2*i; monBouton.w-=2*i;
        SDL_RenderDrawRect(r,&monBouton);
    }
    SDL_RenderPresent(r);
}
void bouton_Non_Selectione(SDL_Renderer *r ,SDL_Rect monBouton)
{
    SDL_SetRenderDrawColor(r,255,255,255,SDL_ALPHA_OPAQUE);
        for (size_t i = 0; i < 5; i++)
    {
        monBouton.x+=i; monBouton.y+=i; monBouton.h-=2*i; monBouton.w-=2*i;
        SDL_RenderDrawRect(r,&monBouton);
    }
    SDL_RenderPresent(r);
}

// FONCTION DE TEST :
void affiche_configuration(char type_jeu , char type_joueur , int nbr_joueurs , char pseudo1[3], char pseudo2[3], char pseudo3[3], char pseudo4[3])
{
    printf(" type de jeu :  %c ", type_jeu) ;
    printf(" type de joueurs :  %c ", type_joueur) ;
    printf(" nbr de joueurs :  %d ", nbr_joueurs) ;
    printf(" pseudo1 :  ");
    for (size_t i = 0; i < 4; i++)
    {
        printf("%c",pseudo1[i]);
    }
     printf(" pseudo2 :  ");
    for (size_t i = 0; i < 4; i++)
    {
        printf("%c",pseudo2[i]);
    }
     printf(" pseudo3 :  ");
    for (size_t i = 0; i < 4; i++)
    {
        printf("%c",pseudo3[i]);
    }
     printf(" pseudo4 :  ");
    for (size_t i = 0; i < 4; i++)
    {
        printf("%c",pseudo4[i]);
    }

}