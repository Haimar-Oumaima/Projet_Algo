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

void ecrire_Lettre1(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin) // num_L le numéro attaché à une lettre de 1 - 26
{
    SDL_Surface *lettre = SDL_LoadBMP(chemin);
    SDL_Rect pos;
    pos.x = rect.x;
    pos.y = rect.y;
    SDL_Texture *t_lettre = SDL_CreateTextureFromSurface(rendu,lettre);
    SDL_QueryTexture(t_lettre,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(rendu,t_lettre,NULL,&pos); 
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_lettre);
    SDL_RenderPresent(rendu);
}
void ecrire_Lettre2(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin) // num_L le numéro attaché à une lettre de 1 - 26
{
    SDL_Surface *lettre = SDL_LoadBMP(chemin);
    SDL_Rect pos;
    pos.x = rect.x+100;
    pos.y = rect.y;
    SDL_Texture *t_lettre = SDL_CreateTextureFromSurface(rendu,lettre);
    SDL_QueryTexture(t_lettre,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(rendu,t_lettre,NULL,&pos); 
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_lettre);
    SDL_RenderPresent(rendu);
}
void ecrire_Lettre3(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin) // num_L le numéro attaché à une lettre de 1 - 26
{
    SDL_Surface *lettre = SDL_LoadBMP(chemin);
    SDL_Rect pos;
    pos.x = rect.x+200;
    pos.y = rect.y;
    SDL_Texture *t_lettre = SDL_CreateTextureFromSurface(rendu,lettre);
    SDL_QueryTexture(t_lettre,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(rendu,t_lettre,NULL,&pos); 
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_lettre);
    SDL_RenderPresent(rendu);
}
void ecrire_Lettre4(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin) // num_L le numéro attaché à une lettre de 1 - 26
{
    SDL_Surface *lettre = SDL_LoadBMP(chemin);
    SDL_Rect pos;
    pos.x = rect.x+300;
    pos.y = rect.y;
    SDL_Texture *t_lettre = SDL_CreateTextureFromSurface(rendu,lettre);
    SDL_QueryTexture(t_lettre,NULL,NULL,&pos.w,&pos.h);
    SDL_RenderCopy(rendu,t_lettre,NULL,&pos); 
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_lettre);
    SDL_RenderPresent(rendu);
}

