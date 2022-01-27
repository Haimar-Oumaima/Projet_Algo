#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define HAUTEUR_MAX 650
#define LARGEUR_MAX 800

// boutons :

SDL_Rect bouton_Dominos;
SDL_Rect bouton_Triominos;
SDL_Rect bouton_Next;
SDL_Rect bouton_2joueurs;
SDL_Rect bouton_3joueurs;
SDL_Rect bouton_4joueurs;
SDL_Rect bouton_Humain;
SDL_Rect bouton_Ordi;
SDL_Rect zone_Pseudo1;
SDL_Rect zone_Pseudo2;
SDL_Rect zone_Pseudo3;
SDL_Rect zone_Pseudo4;
SDL_Rect bouton_Commencer;
SDL_Rect bouton_affiche_plus;
// POUR ENREGISTRER LES PSEUDOS :
char pseudo1[3];
char pseudo2[3];
char pseudo3[3];
char pseudo4[3];

// fonction affiche arriere plan et logo

void affiche_arriere_plan_logo(SDL_Renderer *rendu)
{
    SDL_Surface *arriere_plan = NULL;
    SDL_Surface *logo = NULL;

    SDL_Texture *t_arriere_plan = NULL;
    SDL_Texture *t_logo = NULL;

    arriere_plan = SDL_LoadBMP("images/arriere_plan.bmp"); //charger l'image d'arriere plan
    logo = SDL_LoadBMP("images/LOGO.bmp"); //charger l'image de logo

    t_arriere_plan = SDL_CreateTextureFromSurface(rendu,arriere_plan); //creer texture d'ar plan
    t_logo = SDL_CreateTextureFromSurface(rendu,logo); //creer texture de logo

    SDL_FreeSurface(arriere_plan);
    SDL_FreeSurface(logo);
    SDL_Rect rect_arriere_plan;
    SDL_Rect rect_logo;
    SDL_QueryTexture(t_arriere_plan,NULL,NULL,&rect_arriere_plan.w,&rect_arriere_plan.h); //Charger la texture d'ar plan
    SDL_QueryTexture(t_logo,NULL,NULL,&rect_logo.w,&rect_logo.h); //Charger la texture de logo
    
    //pour centrer les images
    rect_arriere_plan.x = (LARGEUR_MAX - rect_arriere_plan.w)/2 ;
    rect_arriere_plan.y= (HAUTEUR_MAX - rect_arriere_plan.h)/2;

    rect_logo.x = (LARGEUR_MAX - rect_logo.w)/2 ; //Centrer par rapport à la largeur du fenetre
    rect_logo.y= 30;

    SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
    SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo
    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_logo);
    SDL_DestroyTexture(t_arriere_plan);

}
// afficher le texte de l'interface pseudo

void affiche_texte_pseudo(SDL_Renderer *rendu)
{
    SDL_Surface *textePseudo = NULL;
    SDL_Texture *t_textePseudo = NULL;
    textePseudo = SDL_LoadBMP("images/textePseudo.bmp"); //charger le texte du l'interface pseudo

    t_textePseudo = SDL_CreateTextureFromSurface(rendu,textePseudo);
    SDL_FreeSurface(textePseudo);
    SDL_Rect rect_textePseudo;
    
    SDL_QueryTexture(t_textePseudo,NULL,NULL,&rect_textePseudo.w,&rect_textePseudo.h);

    rect_textePseudo.x = (LARGEUR_MAX - rect_textePseudo.w)/2 ;
    rect_textePseudo.y= (HAUTEUR_MAX - rect_textePseudo.h)/2;
    SDL_RenderCopy(rendu,t_textePseudo,NULL,&rect_textePseudo); 
    SDL_RenderPresent(rendu);
}

void interface_Menu1(SDL_Renderer *rendu)
{

    affiche_arriere_plan_logo(rendu);
    // COORDONNEES DE BOUTONS
    bouton_Dominos.x=200; bouton_Dominos.y=250; bouton_Dominos.w=400; bouton_Dominos.h=70;
    bouton_Triominos.x=200; bouton_Triominos.y=350; bouton_Triominos.w=400; bouton_Triominos.h=70;
    //Dessiner les boutons
    SDL_RenderFillRect(rendu,&bouton_Dominos);
    SDL_RenderFillRect(rendu,&bouton_Triominos);
    SDL_RenderFillRect(rendu,&bouton_Next);
    
    SDL_Surface *texteMenu1 = NULL;
    SDL_Texture *t_texteMenu1 = NULL;
    texteMenu1 = SDL_LoadBMP("images/texteMenu1.bmp"); //charger l'image de text de premier interface menu
    t_texteMenu1 = SDL_CreateTextureFromSurface(rendu,texteMenu1); //creer texture de logo
    SDL_FreeSurface(texteMenu1);
    SDL_Rect rect_texteMenu1;
    SDL_QueryTexture(t_texteMenu1,NULL,NULL,&rect_texteMenu1.w,&rect_texteMenu1.h); //Charger la texture d'ar plan

    rect_texteMenu1.x = (LARGEUR_MAX - rect_texteMenu1.w)/2 ;
    rect_texteMenu1.y= (HAUTEUR_MAX - rect_texteMenu1.h)/2;
    SDL_RenderCopy(rendu,t_texteMenu1,NULL,&rect_texteMenu1); //afficher la texture de logo

    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_texteMenu1);

}

void interface_Menu2(SDL_Renderer *rendu)
{   //mettre les boutons anciens hors la fenetre
    bouton_Dominos.x+=1000;
    bouton_Triominos.x+=1000;   
    // coordonees de boutons
    bouton_2joueurs.x = 280;bouton_2joueurs.y =300 ;bouton_2joueurs.w =70 ;bouton_2joueurs.h =70 ;
    bouton_3joueurs.x = 365;bouton_3joueurs.y =300 ;bouton_3joueurs.w =70 ;bouton_3joueurs.h = 70;
    bouton_4joueurs.x = 450;bouton_4joueurs.y =300 ;bouton_4joueurs.w =70 ;bouton_4joueurs.h =70 ;
    //dessiner la nouveau interface
    affiche_arriere_plan_logo(rendu);
    SDL_RenderFillRect(rendu,&bouton_2joueurs);
    SDL_RenderFillRect(rendu,&bouton_3joueurs);
    SDL_RenderFillRect(rendu,&bouton_4joueurs);
    SDL_RenderFillRect(rendu,&bouton_Next);

    SDL_Surface *texteMenu2 = NULL;
    SDL_Texture *t_texteMenu2 = NULL;
    texteMenu2 = SDL_LoadBMP("images/texteMenu2.bmp");
    t_texteMenu2 = SDL_CreateTextureFromSurface(rendu,texteMenu2); //creer texture de logo
    SDL_FreeSurface(texteMenu2);
    SDL_Rect rect_texteMenu2;
    SDL_QueryTexture(t_texteMenu2,NULL,NULL,&rect_texteMenu2.w,&rect_texteMenu2.h); //Charger la texture d'ar plan

    rect_texteMenu2.x = (LARGEUR_MAX - rect_texteMenu2.w)/2 ;
    rect_texteMenu2.y= (HAUTEUR_MAX - rect_texteMenu2.h)/2;
    SDL_RenderCopy(rendu,t_texteMenu2,NULL,&rect_texteMenu2); //afficher la texture de logo

    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_texteMenu2);

}
    
void interface_Menu3(SDL_Renderer *rendu)
{
    bouton_2joueurs.x+=1000;
    bouton_3joueurs.x+=1000;
    bouton_4joueurs.x+=1000;
    //coordonnees de boutons :
    bouton_Humain.x = 250; bouton_Humain.y = 300; bouton_Humain.w = 140; bouton_Humain.h =70 ; 
    bouton_Ordi.x = 410; bouton_Ordi.y = 300 ; bouton_Ordi.w = 140; bouton_Ordi.h = 70 ; 

    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&bouton_Humain);
    SDL_RenderFillRect(rendu,&bouton_Ordi);
    SDL_RenderFillRect(rendu,&bouton_Next);
    SDL_Surface *texteMenu3 = NULL;
    SDL_Texture *t_texteMenu3 = NULL;
    texteMenu3 = SDL_LoadBMP("images/texteMenu3.bmp");
    t_texteMenu3 = SDL_CreateTextureFromSurface(rendu,texteMenu3); //creer texture de logo
    SDL_FreeSurface(texteMenu3);
    SDL_Rect rect_texteMenu3;
    SDL_QueryTexture(t_texteMenu3,NULL,NULL,&rect_texteMenu3.w,&rect_texteMenu3.h); //Charger la texture d'ar plan

    rect_texteMenu3.x = (LARGEUR_MAX - rect_texteMenu3.w)/2 ;
    rect_texteMenu3.y= (HAUTEUR_MAX - rect_texteMenu3.h)/2;
    SDL_RenderCopy(rendu,t_texteMenu3,NULL,&rect_texteMenu3); //afficher la texture de logo

    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_texteMenu3);

}
    void interface_Menu4_2joueurs(SDL_Renderer *rendu)
{
    bouton_Humain.x+=1000;
    bouton_Ordi.x+=1000;
    //coordonnees de boutons :
    zone_Pseudo1.x=200; zone_Pseudo1.y=250; zone_Pseudo1.w=400; zone_Pseudo1.h=70;
    zone_Pseudo2.x=200; zone_Pseudo2.y=350; zone_Pseudo2.w=400; zone_Pseudo2.h=70;

    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&zone_Pseudo1);
    SDL_RenderFillRect(rendu,&zone_Pseudo2);
    SDL_RenderFillRect(rendu,&bouton_Next);

    affiche_texte_pseudo(rendu);

    SDL_RenderPresent(rendu);

}
void interface_Menu4_3joueurs(SDL_Renderer *rendu)
{
    bouton_Humain.x+=1000;
    bouton_Ordi.x+=1000;
    //coordonnees de boutons :
    zone_Pseudo1.x=200; zone_Pseudo1.y=200; zone_Pseudo1.w=400; zone_Pseudo1.h=70;
    zone_Pseudo2.x=200; zone_Pseudo2.y=300; zone_Pseudo2.w=400; zone_Pseudo2.h=70;
    zone_Pseudo3.x=200; zone_Pseudo3.y=400; zone_Pseudo3.w=400; zone_Pseudo3.h=70;

    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&zone_Pseudo1);
    SDL_RenderFillRect(rendu,&zone_Pseudo2);
    SDL_RenderFillRect(rendu,&zone_Pseudo3);
    SDL_RenderFillRect(rendu,&bouton_Next);

    affiche_texte_pseudo(rendu);
    SDL_RenderPresent(rendu);
}
void interface_Menu4_4joueurs(SDL_Renderer *rendu)
{
    bouton_Humain.x+=1000;
    bouton_Ordi.x+=1000;
    //coordonnees de boutons :
    zone_Pseudo1.x=200; zone_Pseudo1.y=190; zone_Pseudo1.w=400; zone_Pseudo1.h=60;
    zone_Pseudo2.x=200; zone_Pseudo2.y=260; zone_Pseudo2.w=400; zone_Pseudo2.h=60;
    zone_Pseudo3.x=200; zone_Pseudo3.y=330; zone_Pseudo3.w=400; zone_Pseudo3.h=60;
    zone_Pseudo4.x=200; zone_Pseudo4.y=400; zone_Pseudo4.w=400; zone_Pseudo4.h=60;

    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&zone_Pseudo1);
    SDL_RenderFillRect(rendu,&zone_Pseudo2);
    SDL_RenderFillRect(rendu,&zone_Pseudo3);
    SDL_RenderFillRect(rendu,&zone_Pseudo4);
    SDL_RenderFillRect(rendu,&bouton_Next);

    affiche_texte_pseudo(rendu);

    SDL_RenderPresent(rendu);
}
// si l'utilisateur choisi de jouer aved des ordi il est demandé juste d'entrer juste son pseudo
void interface_Menu4_1joueur(SDL_Renderer *rendu)
{
    bouton_Humain.x+=1000;
    bouton_Ordi.x+=1000;
    //coordonnees de boutons :
    zone_Pseudo1.x=200; zone_Pseudo1.y=300; zone_Pseudo1.w=400; zone_Pseudo1.h=70;

    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&zone_Pseudo1);
    SDL_RenderFillRect(rendu,&bouton_Next);

    affiche_texte_pseudo(rendu);

    SDL_RenderPresent(rendu);

}
void affiche_Aide_Dominos(SDL_Renderer *rendu)
{
    //coordonnees de boutons :
    bouton_Commencer.x=250; bouton_Commencer.y=500; bouton_Commencer.w=300; bouton_Commencer.h=60;
    
    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&bouton_Commencer);

    SDL_Surface *texteAide_dominos = NULL;
    SDL_Texture *t_texteAide_dominos = NULL;
    texteAide_dominos = SDL_LoadBMP("images/Aide_dominos.bmp");
    t_texteAide_dominos = SDL_CreateTextureFromSurface(rendu,texteAide_dominos); //creer texture de logo
    SDL_FreeSurface(texteAide_dominos);
    SDL_Rect rect_texteAide_dominos;
    SDL_QueryTexture(t_texteAide_dominos,NULL,NULL,&rect_texteAide_dominos.w,&rect_texteAide_dominos.h); //Charger la texture d'ar plan

    rect_texteAide_dominos.x = (LARGEUR_MAX - rect_texteAide_dominos.w)/2 ;
    rect_texteAide_dominos.y= (HAUTEUR_MAX - rect_texteAide_dominos.h)/2;
    SDL_RenderCopy(rendu,t_texteAide_dominos,NULL,&rect_texteAide_dominos); //afficher la texture de logo

    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_texteAide_dominos);

    SDL_RenderPresent(rendu);
}
void affiche_Aide_Triominos(SDL_Renderer *rendu)
{
    //coordonnees de boutons :

    bouton_Commencer.x=250; bouton_Commencer.y=500; bouton_Commencer.w=300; bouton_Commencer.h=60;
    bouton_affiche_plus.x=700; bouton_affiche_plus.y=450; bouton_affiche_plus.w=30; bouton_affiche_plus.h=30;

    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&bouton_Commencer);

    SDL_Surface *texteAide_triominos = NULL;
    SDL_Texture *t_texteAide_triominos = NULL;
    texteAide_triominos = SDL_LoadBMP("images/Aide_triominos.bmp");
    t_texteAide_triominos = SDL_CreateTextureFromSurface(rendu,texteAide_triominos); //creer texture de logo
    SDL_FreeSurface(texteAide_triominos);
    SDL_Rect rect_texteAide_triominos;
    SDL_QueryTexture(t_texteAide_triominos,NULL,NULL,&rect_texteAide_triominos.w,&rect_texteAide_triominos.h); //Charger la texture d'ar plan

    rect_texteAide_triominos.x = (LARGEUR_MAX - rect_texteAide_triominos.w)/2 ;
    rect_texteAide_triominos.y= (HAUTEUR_MAX - rect_texteAide_triominos.h)/2;
    SDL_RenderCopy(rendu,t_texteAide_triominos,NULL,&rect_texteAide_triominos); //afficher la texture de logo

    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_texteAide_triominos);

    SDL_RenderPresent(rendu);
}
void affiche_Aide_Triominos2(SDL_Renderer *rendu)
{
    //coordonnees de boutons :

    bouton_Commencer.x=250; bouton_Commencer.y=500; bouton_Commencer.w=300; bouton_Commencer.h=60;
    bouton_affiche_plus.x=700; bouton_affiche_plus.y=450; bouton_affiche_plus.w=30; bouton_affiche_plus.h=30;

    affiche_arriere_plan_logo(rendu);

    SDL_RenderFillRect(rendu,&bouton_Commencer);

    SDL_Surface *texteAide_triominos2 = NULL;
    SDL_Texture *t_texteAide_triominos2 = NULL;
    texteAide_triominos2 = SDL_LoadBMP("images/Aide_triominos2.bmp");
    t_texteAide_triominos2 = SDL_CreateTextureFromSurface(rendu,texteAide_triominos2); //creer texture de logo
    SDL_FreeSurface(texteAide_triominos2);
    SDL_Rect rect_texteAide_triominos2;
    SDL_QueryTexture(t_texteAide_triominos2,NULL,NULL,&rect_texteAide_triominos2.w,&rect_texteAide_triominos2.h); //Charger la texture d'ar plan

    rect_texteAide_triominos2.x = (LARGEUR_MAX - rect_texteAide_triominos2.w)/2 ;
    rect_texteAide_triominos2.y= (HAUTEUR_MAX - rect_texteAide_triominos2.h)/2;
    SDL_RenderCopy(rendu,t_texteAide_triominos2,NULL,&rect_texteAide_triominos2); //afficher la texture de logo

    SDL_RenderPresent(rendu);
    SDL_DestroyTexture(t_texteAide_triominos2);

    SDL_RenderPresent(rendu);
}

void ecrire_Lettre1(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin)  
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
void ecrire_Lettre2(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin)  
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
void ecrire_Lettre3(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin)  
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
void ecrire_Lettre4(SDL_Renderer *rendu ,SDL_Rect rect, char* chemin)  
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

