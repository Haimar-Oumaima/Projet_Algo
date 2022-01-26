#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#define HAUTEUR_MAX 650
#define LARGEUR_MAX 800



SDL_bool est_Dans_Intervalle();
void bouton_Selectione(SDL_Renderer* ,SDL_Rect);
void bouton_Non_Selectione(SDL_Renderer * ,SDL_Rect);
int main(int argc, char **argv)
{
    /*  VUE  */
//-----------------DECLARATION FENETRE----------------------------------------------

    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    //Creation de fenetre
    fenetre = SDL_CreateWindow("DOMINO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_MAX,HAUTEUR_MAX,0);
    //Creation du rendu
    rendu = SDL_CreateRenderer(fenetre,-1,0);
//-----------------DECLARATION IMAGES----------------------------------------------
    SDL_Surface *arriere_plan = NULL;
    SDL_Surface *logo = NULL;
    SDL_Surface *textePseudo = NULL;

    SDL_Texture *t_arriere_plan = NULL;
    SDL_Texture *t_logo = NULL;
    SDL_Texture *t_textePseudo = NULL;

    arriere_plan = SDL_LoadBMP("images/arriere_plan.bmp"); //charger l'image d'arriere plan
    logo = SDL_LoadBMP("images/LOGO.bmp"); //charger l'image de logo
    textePseudo = SDL_LoadBMP("images/textePseudo.bmp"); //charger le texte du l'interface pseudo

 
    t_arriere_plan = SDL_CreateTextureFromSurface(rendu,arriere_plan); //creer texture d'ar plan
    t_logo = SDL_CreateTextureFromSurface(rendu,logo); //creer texture de logo
    t_textePseudo = SDL_CreateTextureFromSurface(rendu,textePseudo);
    SDL_FreeSurface(arriere_plan);
    SDL_FreeSurface(logo);
    SDL_FreeSurface(textePseudo);
    SDL_Rect rect_arriere_plan;
    SDL_Rect rect_logo;
    SDL_Rect rect_textePseudo;
    
    SDL_QueryTexture(t_arriere_plan,NULL,NULL,&rect_arriere_plan.w,&rect_arriere_plan.h); //Charger la texture d'ar plan
    SDL_QueryTexture(t_logo,NULL,NULL,&rect_logo.w,&rect_logo.h); //Charger la texture de logo
    SDL_QueryTexture(t_textePseudo,NULL,NULL,&rect_textePseudo.w,&rect_textePseudo.h);

    //pour centrer l'image
    rect_arriere_plan.x = (LARGEUR_MAX - rect_arriere_plan.w)/2 ;
    rect_arriere_plan.y= (HAUTEUR_MAX - rect_arriere_plan.h)/2;

    rect_textePseudo.x = (LARGEUR_MAX - rect_textePseudo.w)/2 ;
    rect_textePseudo.y= (HAUTEUR_MAX - rect_textePseudo.h)/2;

    rect_logo.x = (LARGEUR_MAX - rect_logo.w)/2 ; //Centrer par rapport à la largeur du fenetre
    rect_logo.y= 30;

    //DECLARATION BOUTONS 
        SDL_Rect bouton_Dominos;
        SDL_Rect bouton_Triominos;
        SDL_Rect bouton_Next;
        SDL_Rect bouton_2joueurs;
        SDL_Rect bouton_3joueurs;
        SDL_Rect bouton_4joueurs;
        SDL_Rect cadre;
        SDL_Rect bouton_Humain;
        SDL_Rect bouton_Ordi;
        SDL_Rect bouton_Pseudo1;
        SDL_Rect bouton_Pseudo2;
        SDL_Rect bouton_Pseudo3;
        SDL_Rect bouton_Pseudo4;
        SDL_Rect bouton_Commencer;
        SDL_Rect bouton_affiche_plus;
        //Coordonnees generales
        bouton_Next.x=365; bouton_Next.y=500; bouton_Next.w=70; bouton_Next.h=70;
        cadre.x = 200 ;cadre.y =250 ;cadre.w = 400 ;cadre.h =170 ;
        SDL_SetRenderDrawColor(rendu,255,255,255,SDL_ALPHA_OPAQUE);
    void interface_Menu1(SDL_Renderer *rendu)
    {
        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo
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
        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo
        SDL_RenderFillRect(rendu,&bouton_2joueurs);
        SDL_RenderFillRect(rendu,&bouton_3joueurs);
        SDL_RenderFillRect(rendu,&bouton_4joueurs);
        SDL_RenderDrawRect(rendu,&cadre);
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

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

        SDL_RenderFillRect(rendu,&bouton_Humain);
        SDL_RenderFillRect(rendu,&bouton_Ordi);
        SDL_RenderFillRect(rendu,&bouton_Next);
        SDL_RenderDrawRect(rendu,&cadre);

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
        bouton_Pseudo1.x=200; bouton_Pseudo1.y=250; bouton_Pseudo1.w=400; bouton_Pseudo1.h=70;
        bouton_Pseudo2.x=200; bouton_Pseudo2.y=350; bouton_Pseudo2.w=400; bouton_Pseudo2.h=70;

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

        SDL_RenderFillRect(rendu,&bouton_Pseudo1);
        SDL_RenderFillRect(rendu,&bouton_Pseudo2);
        SDL_RenderFillRect(rendu,&bouton_Next);

        SDL_RenderCopy(rendu,t_textePseudo,NULL,&rect_textePseudo); 


        SDL_RenderPresent(rendu);

    }
    void interface_Menu4_3joueurs(SDL_Renderer *rendu)
    {
        bouton_Humain.x+=1000;
        bouton_Ordi.x+=1000;
        //coordonnees de boutons :
        bouton_Pseudo1.x=200; bouton_Pseudo1.y=200; bouton_Pseudo1.w=400; bouton_Pseudo1.h=70;
        bouton_Pseudo2.x=200; bouton_Pseudo2.y=300; bouton_Pseudo2.w=400; bouton_Pseudo2.h=70;
        bouton_Pseudo3.x=200; bouton_Pseudo3.y=400; bouton_Pseudo3.w=400; bouton_Pseudo3.h=70;

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

        SDL_RenderFillRect(rendu,&bouton_Pseudo1);
        SDL_RenderFillRect(rendu,&bouton_Pseudo2);
        SDL_RenderFillRect(rendu,&bouton_Pseudo3);
        SDL_RenderFillRect(rendu,&bouton_Next);

        SDL_RenderCopy(rendu,t_textePseudo,NULL,&rect_textePseudo); 

        SDL_RenderPresent(rendu);

    }
    void interface_Menu4_4joueurs(SDL_Renderer *rendu)
    {
        bouton_Humain.x+=1000;
        bouton_Ordi.x+=1000;
        //coordonnees de boutons :
        bouton_Pseudo1.x=200; bouton_Pseudo1.y=190; bouton_Pseudo1.w=400; bouton_Pseudo1.h=60;
        bouton_Pseudo2.x=200; bouton_Pseudo2.y=260; bouton_Pseudo2.w=400; bouton_Pseudo2.h=60;
        bouton_Pseudo3.x=200; bouton_Pseudo3.y=330; bouton_Pseudo3.w=400; bouton_Pseudo3.h=60;
        bouton_Pseudo4.x=200; bouton_Pseudo4.y=400; bouton_Pseudo4.w=400; bouton_Pseudo4.h=60;

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

        SDL_RenderFillRect(rendu,&bouton_Pseudo1);
        SDL_RenderFillRect(rendu,&bouton_Pseudo2);
        SDL_RenderFillRect(rendu,&bouton_Pseudo3);
        SDL_RenderFillRect(rendu,&bouton_Pseudo4);
        SDL_RenderFillRect(rendu,&bouton_Next);

        SDL_RenderCopy(rendu,t_textePseudo,NULL,&rect_textePseudo); 

        SDL_RenderPresent(rendu);

    }
    // si l'utilisateur choisi de jouer aved des ordi il est demandé juste d'entrer juste son pseudo
    void interface_Menu4_1joueur(SDL_Renderer *rendu)
    {
        bouton_Humain.x+=1000;
        bouton_Ordi.x+=1000;
        //coordonnees de boutons :
        bouton_Pseudo1.x=200; bouton_Pseudo1.y=300; bouton_Pseudo1.w=400; bouton_Pseudo1.h=70;

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

        SDL_RenderFillRect(rendu,&bouton_Pseudo1);
        SDL_RenderFillRect(rendu,&bouton_Next);

        SDL_RenderCopy(rendu,t_textePseudo,NULL,&rect_textePseudo); 

        SDL_RenderPresent(rendu);

    }
    void affiche_Aide_Dominos(SDL_Renderer *rendu)
    {
        //coordonnees de boutons :
        bouton_Commencer.x=250; bouton_Commencer.y=500; bouton_Commencer.w=300; bouton_Commencer.h=60;

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

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

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

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

        SDL_RenderCopy(rendu,t_arriere_plan,NULL,&rect_arriere_plan); //afficher la texture d'ar plan
        SDL_RenderCopy(rendu,t_logo,NULL,&rect_logo); //afficher la texture de logo

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
    //  booleens buttons selectionées et compteurs 

SDL_bool Est_Dominos=SDL_FALSE;
SDL_bool Est_Triominos=SDL_FALSE;
SDL_bool Est_Humain = SDL_FALSE;
SDL_bool Est_Ordi = SDL_FALSE;
int next=0;
int nbr_joueurs=0;
char type_jeu;
char type_joueur;


    //------------------GESTION DES EVENEMENTS------------------------
interface_Menu1(rendu); //dessiner la premiere interface
SDL_bool program_lance = SDL_TRUE;

while (program_lance)
{
    SDL_Event evenement;

    while (SDL_PollEvent(&evenement)) //capturer tous les evenements
    {
        switch (evenement.type)
        { 

            case SDL_MOUSEBUTTONDOWN :
                if (est_Dans_Intervalle(evenement, bouton_Dominos)&&(next==0))
                {
                    Est_Dominos=SDL_TRUE; bouton_Selectione(rendu , bouton_Dominos);
                    Est_Triominos=SDL_FALSE; bouton_Non_Selectione(rendu,bouton_Triominos);
                    type_jeu = 'D'; //Dominos

                } 
                if (est_Dans_Intervalle(evenement, bouton_Triominos)&&(next==0))
                {
                    Est_Triominos=SDL_TRUE; bouton_Selectione(rendu , bouton_Triominos);
                    Est_Dominos=SDL_FALSE; bouton_Non_Selectione(rendu,bouton_Dominos);
                    type_jeu = 'T'; //Triominos

                }
                if(est_Dans_Intervalle(evenement,bouton_2joueurs)&&(next==1))
                {
                    nbr_joueurs = 2;
                    bouton_Selectione(rendu,bouton_2joueurs);
                    bouton_Non_Selectione(rendu,bouton_3joueurs);
                    bouton_Non_Selectione(rendu,bouton_4joueurs);

                }
                if(est_Dans_Intervalle(evenement,bouton_3joueurs)&&(next==1))
                {
                    nbr_joueurs = 3;
                    bouton_Selectione(rendu,bouton_3joueurs);
                    bouton_Non_Selectione(rendu,bouton_2joueurs);
                    bouton_Non_Selectione(rendu,bouton_4joueurs);

                }
                if(est_Dans_Intervalle(evenement,bouton_4joueurs)&&(next==1))
                {
                    nbr_joueurs = 4;
                    bouton_Selectione(rendu,bouton_4joueurs);
                    bouton_Non_Selectione(rendu,bouton_2joueurs);
                    bouton_Non_Selectione(rendu,bouton_3joueurs);

                }
                if(est_Dans_Intervalle(evenement,bouton_Humain)&&(next==2))
                {
                    Est_Humain = SDL_TRUE; bouton_Selectione(rendu,bouton_Humain);
                    Est_Ordi = SDL_FALSE; bouton_Non_Selectione(rendu, bouton_Ordi);
                    type_joueur='H'; //Humain
                }
                if(est_Dans_Intervalle(evenement,bouton_Ordi)&&(next==2))
                {
                    Est_Ordi = SDL_TRUE; bouton_Selectione(rendu,bouton_Ordi);
                    Est_Humain = SDL_FALSE; bouton_Non_Selectione(rendu, bouton_Humain);
                    type_joueur='O'; //Ordinateur

                }
                // GESTION DU BOUTON NEXT
                if (est_Dans_Intervalle(evenement, bouton_Next))
                {   

                    if((Est_Triominos || Est_Dominos)&&next==0)
                    {
                        next++;
                        //passer a la page suivante si un des boutons sont selectionees
                        interface_Menu2(rendu);
                        
                    }
                    else if(nbr_joueurs !=0 && next==1)
                    {
                        next++;
                        //passer à l'interface suivante
                        interface_Menu3(rendu);
                    }
                    else if ((Est_Humain || Est_Ordi)&&next==2)
                    {
                        next++;
                        //passera l'interface suivante
                        if(Est_Humain){
                            switch (nbr_joueurs)
                            {
                                case 2 : interface_Menu4_2joueurs(rendu); break;
                                case 3 : interface_Menu4_3joueurs(rendu); break;
                                case 4 : interface_Menu4_4joueurs(rendu); break;
                            }
                        }
                        else if(Est_Ordi)
                        {
                            interface_Menu4_1joueur(rendu);
                        }
                    }
                    else if (next == 3)
                    {
                        next++;
                        //afficher l'interface aide
                        if(Est_Dominos)
                        {   
                            affiche_Aide_Dominos(rendu);
                        }
                        else if(Est_Triominos)
                        {   
                            affiche_Aide_Triominos(rendu);
                        }
                    }
                }
                else if (est_Dans_Intervalle(evenement, bouton_affiche_plus) && (next == 4))
                {
                    affiche_Aide_Triominos2(rendu);
                }
                else if (est_Dans_Intervalle(evenement, bouton_Commencer) && (next == 4) && Est_Dominos)
                {
                    /*
                    switch(nbr_joueurs)
                    {
                        case 2 : //on demarre le jeu dominos avec 2 joueurs break;
                        case 3 : //meme chose 3 joueurs break;
                        case 4 : break;
    
                    }
                    */

                }
                else if (est_Dans_Intervalle(evenement, bouton_Commencer) && (next == 4) && Est_Triominos)
                {
                    // meme chose ici un switch en fonction de nombre de joueurs .
                }
                break;
            case SDL_KEYDOWN : 
            if(evenement.key.keysym.scancode == SDL_SCANCODE_ESCAPE){
                program_lance = SDL_FALSE;
            }
            case SDL_QUIT: program_lance = SDL_FALSE; /* la ligne suivante c' est pour tester : */ printf("type de jeu : %c type de joueur: %c , nombre de joueurs : %d " ,type_jeu,type_joueur,nbr_joueurs); 
            break; // cas cliquer sur croix quitter
            default : continue;
        }
    }
}

    SDL_DestroyTexture(t_logo);
    SDL_DestroyTexture(t_arriere_plan);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return EXIT_SUCCESS;
}

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




//gcc src/menu.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
//   .\bin\prog.exe
//  set PATH=C:\MinGW\bin;%PATH%
// cd OneDrive/Desktop/DOMINO