#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "Vue.c"
#include "Vue.h"
#include "modele.c"
#define HAUTEUR_MAX 650
#define LARGEUR_MAX 800

int main(int argc, char **argv)
{
//-----------------DECLARATION FENETRE----------------------------------------------

    SDL_Window *fenetre = NULL;
    SDL_Renderer *rendu = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    //Creation de fenetre
    fenetre = SDL_CreateWindow("DOMINO",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_MAX,HAUTEUR_MAX,0);
    //Creation du rendu
    rendu = SDL_CreateRenderer(fenetre,-1,0);

    //Coordonnees generales
    bouton_Next.x=365; bouton_Next.y=500; bouton_Next.w=70; bouton_Next.h=70;
    SDL_SetRenderDrawColor(rendu,255,255,255,SDL_ALPHA_OPAQUE);

    //  booleens buttons selectionées et compteurs 

SDL_bool Est_Dominos=SDL_FALSE;
SDL_bool Est_Triominos=SDL_FALSE;
SDL_bool Est_Humain = SDL_FALSE;
SDL_bool Est_Ordi = SDL_FALSE;
SDL_bool Commencer = SDL_FALSE;
int next=0;
int nbr_joueurs=0;
int nbr_lettres=0;
char type_jeu=' ';
char type_joueur=' ';

/*****************************/
/*** GESTION DES EVENEMENTS***/
/*****************************/

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
                    Commencer = SDL_TRUE;
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
                    Commencer = SDL_TRUE;

                    switch(nbr_joueurs)
                    {
                        case 2 :  break;
                        case 3 : //meme chose 3 joueurs break;
                        case 4 : break;
    
                    }
                    
                }
                break;
                
            case SDL_KEYDOWN : 
            if(evenement.key.keysym.scancode == SDL_SCANCODE_A)
            {

                switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/A.bmp"); nbr_lettres++; pseudo1[0]='A';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/A.bmp"); nbr_lettres++; pseudo1[1]='A';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/A.bmp"); nbr_lettres++; pseudo1[2]='A';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/A.bmp"); nbr_lettres++; pseudo1[3]='A';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/A.bmp"); nbr_lettres++; pseudo2[0]='A';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/A.bmp"); nbr_lettres++; pseudo2[1]='A';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/A.bmp"); nbr_lettres++; pseudo2[2]='A';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/A.bmp"); nbr_lettres++; pseudo2[3]='A';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/A.bmp"); nbr_lettres++; pseudo3[0]='A';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/A.bmp"); nbr_lettres++; pseudo3[1]='A';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/A.bmp"); nbr_lettres++; pseudo3[2]='A';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/A.bmp"); nbr_lettres++; pseudo3[3]='A';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/A.bmp"); nbr_lettres++; pseudo4[0]='A';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/A.bmp"); nbr_lettres++; pseudo4[1]='A';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/A.bmp"); nbr_lettres++; pseudo4[2]='A';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/A.bmp"); nbr_lettres++; pseudo4[3]='A';
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_B)
            {

                switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/B.bmp"); nbr_lettres++; pseudo1[0]='B';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/B.bmp"); nbr_lettres++; pseudo1[1]='B';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/B.bmp"); nbr_lettres++;pseudo1[2]='B';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/B.bmp"); nbr_lettres++;pseudo1[3]='B';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/B.bmp"); nbr_lettres++;pseudo2[0]='B';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/B.bmp"); nbr_lettres++;pseudo2[1]='B';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/B.bmp"); nbr_lettres++;pseudo2[2]='B';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/B.bmp"); nbr_lettres++;pseudo2[3]='B';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/B.bmp"); nbr_lettres++;pseudo3[0]='B';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/B.bmp"); nbr_lettres++;pseudo3[1]='B';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/B.bmp"); nbr_lettres++;pseudo3[2]='B';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/B.bmp"); nbr_lettres++;pseudo3[3]='B';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/B.bmp"); nbr_lettres++;pseudo4[0]='B';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/B.bmp"); nbr_lettres++;pseudo4[1]='B';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/B.bmp"); nbr_lettres++;pseudo4[2]='B';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/B.bmp"); nbr_lettres++;pseudo4[3]='B';
                    break;
                }
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_C)
            {

                switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/C.bmp"); nbr_lettres++; pseudo1[0]='C';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/C.bmp"); nbr_lettres++; pseudo1[1]='C';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/C.bmp"); nbr_lettres++;pseudo1[2]='C';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/C.bmp"); nbr_lettres++;pseudo1[3]='C';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/C.bmp"); nbr_lettres++;pseudo2[0]='C';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/C.bmp"); nbr_lettres++;pseudo2[1]='C';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/C.bmp"); nbr_lettres++;pseudo2[2]='C';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/C.bmp"); nbr_lettres++;pseudo2[3]='C';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/C.bmp"); nbr_lettres++;pseudo3[0]='C';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/C.bmp"); nbr_lettres++;pseudo3[1]='C';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/C.bmp"); nbr_lettres++;pseudo3[2]='C';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/C.bmp"); nbr_lettres++;pseudo3[3]='C';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/C.bmp"); nbr_lettres++;pseudo4[0]='C';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/C.bmp"); nbr_lettres++;pseudo4[1]='C';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/C.bmp"); nbr_lettres++;pseudo4[2]='C';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/C.bmp"); nbr_lettres++;pseudo4[3]='C';
                    break;
                }
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_D)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/D.bmp"); nbr_lettres++; pseudo1[0]='D';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/D.bmp"); nbr_lettres++; pseudo1[1]='D';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/D.bmp"); nbr_lettres++;pseudo1[2]='D';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/D.bmp"); nbr_lettres++;pseudo1[3]='D';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/D.bmp"); nbr_lettres++;pseudo2[0]='D';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/D.bmp"); nbr_lettres++;pseudo2[1]='D';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/D.bmp"); nbr_lettres++;pseudo2[2]='D';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/D.bmp"); nbr_lettres++;pseudo2[3]='D';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/D.bmp"); nbr_lettres++;pseudo3[0]='D';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/D.bmp"); nbr_lettres++;pseudo3[1]='D';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/D.bmp"); nbr_lettres++;pseudo3[2]='D';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/D.bmp"); nbr_lettres++;pseudo3[3]='D';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/D.bmp"); nbr_lettres++;pseudo4[0]='D';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/D.bmp"); nbr_lettres++;pseudo4[1]='D';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/D.bmp"); nbr_lettres++;pseudo4[2]='D';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/D.bmp"); nbr_lettres++;pseudo4[3]='D';
                    break;
                }
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_E)
            {

                switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/E.bmp"); nbr_lettres++; pseudo1[0]='E';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/E.bmp"); nbr_lettres++; pseudo1[1]='E';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/E.bmp"); nbr_lettres++;pseudo1[2]='E';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/E.bmp"); nbr_lettres++;pseudo1[3]='E';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/E.bmp"); nbr_lettres++;pseudo2[0]='E';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/E.bmp"); nbr_lettres++;pseudo2[1]='E';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/E.bmp"); nbr_lettres++;pseudo2[2]='E';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/E.bmp"); nbr_lettres++;pseudo2[3]='E';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/E.bmp"); nbr_lettres++;pseudo3[0]='E';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/E.bmp"); nbr_lettres++;pseudo3[1]='E';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/E.bmp"); nbr_lettres++;pseudo3[2]='E';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/E.bmp"); nbr_lettres++;pseudo3[3]='E';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/E.bmp"); nbr_lettres++;pseudo4[0]='E';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/E.bmp"); nbr_lettres++;pseudo4[1]='E';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/E.bmp"); nbr_lettres++;pseudo4[2]='E';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/E.bmp"); nbr_lettres++;pseudo4[3]='E';
                    break;
                }
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_F)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/F.bmp"); nbr_lettres++; pseudo1[0]='F';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/F.bmp"); nbr_lettres++; pseudo1[1]='F';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/F.bmp"); nbr_lettres++;pseudo1[2]='F';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/F.bmp"); nbr_lettres++;pseudo1[3]='F';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/F.bmp"); nbr_lettres++;pseudo2[0]='F';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/F.bmp"); nbr_lettres++;pseudo2[1]='F';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/F.bmp"); nbr_lettres++;pseudo2[2]='F';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/F.bmp"); nbr_lettres++;pseudo2[3]='F';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/F.bmp"); nbr_lettres++;pseudo3[0]='F';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/F.bmp"); nbr_lettres++;pseudo3[1]='F';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/F.bmp"); nbr_lettres++;pseudo3[2]='F';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/F.bmp"); nbr_lettres++;pseudo3[3]='F';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/F.bmp"); nbr_lettres++;pseudo4[0]='F';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/F.bmp"); nbr_lettres++;pseudo4[1]='F';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/F.bmp"); nbr_lettres++;pseudo4[2]='F';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/F.bmp"); nbr_lettres++;pseudo4[3]='F';
                    break;
                }
                
            }   
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_G)
            {

                switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/G.bmp"); nbr_lettres++; pseudo1[0]='G';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/G.bmp"); nbr_lettres++; pseudo1[1]='G';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/G.bmp"); nbr_lettres++;pseudo1[2]='G';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/G.bmp"); nbr_lettres++;pseudo1[3]='G';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/G.bmp"); nbr_lettres++;pseudo2[0]='G';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/G.bmp"); nbr_lettres++;pseudo2[1]='G';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/G.bmp"); nbr_lettres++;pseudo2[2]='G';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/G.bmp"); nbr_lettres++;pseudo2[3]='G';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/G.bmp"); nbr_lettres++;pseudo3[0]='G';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/G.bmp"); nbr_lettres++;pseudo3[1]='G';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/G.bmp"); nbr_lettres++;pseudo3[2]='G';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/G.bmp"); nbr_lettres++;pseudo3[3]='G';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/G.bmp"); nbr_lettres++;pseudo4[0]='G';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/G.bmp"); nbr_lettres++;pseudo4[1]='G';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/G.bmp"); nbr_lettres++;pseudo4[2]='G';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/G.bmp"); nbr_lettres++;pseudo4[3]='G';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_H)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/H.bmp"); nbr_lettres++; pseudo1[0]='H';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/H.bmp"); nbr_lettres++; pseudo1[1]='H';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/H.bmp"); nbr_lettres++;pseudo1[2]='H';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/H.bmp"); nbr_lettres++;pseudo1[3]='H';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/H.bmp"); nbr_lettres++;pseudo2[0]='H';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/H.bmp"); nbr_lettres++;pseudo2[1]='H';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/H.bmp"); nbr_lettres++;pseudo2[2]='H';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/H.bmp"); nbr_lettres++;pseudo2[3]='H';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/H.bmp"); nbr_lettres++;pseudo3[0]='H';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/H.bmp"); nbr_lettres++;pseudo3[1]='H';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/H.bmp"); nbr_lettres++;pseudo3[2]='H';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/H.bmp"); nbr_lettres++;pseudo3[3]='H';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/H.bmp"); nbr_lettres++;pseudo4[0]='H';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/H.bmp"); nbr_lettres++;pseudo4[1]='H';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/H.bmp"); nbr_lettres++;pseudo4[2]='H';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/H.bmp"); nbr_lettres++;pseudo4[3]='H';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_I)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/I.bmp"); nbr_lettres++; pseudo1[0]='I';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/I.bmp"); nbr_lettres++; pseudo1[1]='I';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/I.bmp"); nbr_lettres++;pseudo1[2]='I';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/I.bmp"); nbr_lettres++;pseudo1[3]='I';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/I.bmp"); nbr_lettres++;pseudo2[0]='I';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/I.bmp"); nbr_lettres++;pseudo2[1]='I';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/I.bmp"); nbr_lettres++;pseudo2[2]='I';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/I.bmp"); nbr_lettres++;pseudo2[3]='I';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/I.bmp"); nbr_lettres++;pseudo3[0]='I';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/I.bmp"); nbr_lettres++;pseudo3[1]='I';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/I.bmp"); nbr_lettres++;pseudo3[2]='I';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/I.bmp"); nbr_lettres++;pseudo3[3]='I';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/I.bmp"); nbr_lettres++;pseudo4[0]='I';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/I.bmp"); nbr_lettres++;pseudo4[1]='I';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/I.bmp"); nbr_lettres++;pseudo4[2]='I';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/I.bmp"); nbr_lettres++;pseudo4[3]='I';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_J)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/J.bmp"); nbr_lettres++; pseudo1[0]='J';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/J.bmp"); nbr_lettres++; pseudo1[1]='J';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/J.bmp"); nbr_lettres++;pseudo1[2]='J';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/J.bmp"); nbr_lettres++;pseudo1[3]='J';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/J.bmp"); nbr_lettres++;pseudo2[0]='J';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/J.bmp"); nbr_lettres++;pseudo2[1]='J';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/J.bmp"); nbr_lettres++;pseudo2[2]='J';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/J.bmp"); nbr_lettres++;pseudo2[3]='J';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/J.bmp"); nbr_lettres++;pseudo3[0]='J';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/J.bmp"); nbr_lettres++;pseudo3[1]='J';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/J.bmp"); nbr_lettres++;pseudo3[2]='J';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/J.bmp"); nbr_lettres++;pseudo3[3]='J';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/J.bmp"); nbr_lettres++;pseudo4[0]='J';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/J.bmp"); nbr_lettres++;pseudo4[1]='J';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/J.bmp"); nbr_lettres++;pseudo4[2]='J';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/J.bmp"); nbr_lettres++;pseudo4[3]='J';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_K)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/K.bmp"); nbr_lettres++; pseudo1[0]='K';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/K.bmp"); nbr_lettres++; pseudo1[1]='K';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/K.bmp"); nbr_lettres++;pseudo1[2]='K';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/K.bmp"); nbr_lettres++;pseudo1[3]='K';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/K.bmp"); nbr_lettres++;pseudo2[0]='K';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/K.bmp"); nbr_lettres++;pseudo2[1]='K';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/K.bmp"); nbr_lettres++;pseudo2[2]='K';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/K.bmp"); nbr_lettres++;pseudo2[3]='K';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/K.bmp"); nbr_lettres++;pseudo3[0]='K';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/K.bmp"); nbr_lettres++;pseudo3[1]='K';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/K.bmp"); nbr_lettres++;pseudo3[2]='K';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/K.bmp"); nbr_lettres++;pseudo3[3]='K';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/K.bmp"); nbr_lettres++;pseudo4[0]='K';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/K.bmp"); nbr_lettres++;pseudo4[1]='K';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/K.bmp"); nbr_lettres++;pseudo4[2]='K';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/K.bmp"); nbr_lettres++;pseudo4[3]='K';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_L)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/L.bmp"); nbr_lettres++; pseudo1[0]='L';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/L.bmp"); nbr_lettres++; pseudo1[1]='L';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/L.bmp"); nbr_lettres++;pseudo1[2]='L';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/L.bmp"); nbr_lettres++;pseudo1[3]='L';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/L.bmp"); nbr_lettres++;pseudo2[0]='L';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/L.bmp"); nbr_lettres++;pseudo2[1]='L';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/L.bmp"); nbr_lettres++;pseudo2[2]='L';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/L.bmp"); nbr_lettres++;pseudo2[3]='L';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/L.bmp"); nbr_lettres++;pseudo3[0]='L';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/L.bmp"); nbr_lettres++;pseudo3[1]='L';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/L.bmp"); nbr_lettres++;pseudo3[2]='L';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/L.bmp"); nbr_lettres++;pseudo3[3]='L';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/L.bmp"); nbr_lettres++;pseudo4[0]='L';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/L.bmp"); nbr_lettres++;pseudo4[1]='L';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/L.bmp"); nbr_lettres++;pseudo4[2]='L';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/L.bmp"); nbr_lettres++;pseudo4[3]='L';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_M)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/M.bmp"); nbr_lettres++; pseudo1[0]='M';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/M.bmp"); nbr_lettres++; pseudo1[1]='M';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/M.bmp"); nbr_lettres++;pseudo1[2]='M';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/M.bmp"); nbr_lettres++;pseudo1[3]='M';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/M.bmp"); nbr_lettres++;pseudo2[0]='M';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/M.bmp"); nbr_lettres++;pseudo2[1]='M';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/M.bmp"); nbr_lettres++;pseudo2[2]='M';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/M.bmp"); nbr_lettres++;pseudo2[3]='M';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/M.bmp"); nbr_lettres++;pseudo3[0]='M';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/M.bmp"); nbr_lettres++;pseudo3[1]='M';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/M.bmp"); nbr_lettres++;pseudo3[2]='M';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/M.bmp"); nbr_lettres++;pseudo3[3]='M';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/M.bmp"); nbr_lettres++;pseudo4[0]='M';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/M.bmp"); nbr_lettres++;pseudo4[1]='M';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/M.bmp"); nbr_lettres++;pseudo4[2]='M';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/M.bmp"); nbr_lettres++;pseudo4[3]='M';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_N)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/N.bmp"); nbr_lettres++; pseudo1[0]='N';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/N.bmp"); nbr_lettres++; pseudo1[1]='N';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/N.bmp"); nbr_lettres++;pseudo1[2]='N';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/N.bmp"); nbr_lettres++;pseudo1[3]='N';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/N.bmp"); nbr_lettres++;pseudo2[0]='N';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/N.bmp"); nbr_lettres++;pseudo2[1]='N';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/N.bmp"); nbr_lettres++;pseudo2[2]='N';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/N.bmp"); nbr_lettres++;pseudo2[3]='N';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/N.bmp"); nbr_lettres++;pseudo3[0]='N';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/N.bmp"); nbr_lettres++;pseudo3[1]='N';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/N.bmp"); nbr_lettres++;pseudo3[2]='N';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/N.bmp"); nbr_lettres++;pseudo3[3]='N';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/N.bmp"); nbr_lettres++;pseudo4[0]='N';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/N.bmp"); nbr_lettres++;pseudo4[1]='N';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/N.bmp"); nbr_lettres++;pseudo4[2]='N';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/N.bmp"); nbr_lettres++;pseudo4[3]='N';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_O)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/O.bmp"); nbr_lettres++; pseudo1[0]='O';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/O.bmp"); nbr_lettres++; pseudo1[1]='O';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/O.bmp"); nbr_lettres++;pseudo1[2]='O';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/O.bmp"); nbr_lettres++;pseudo1[3]='O';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/O.bmp"); nbr_lettres++;pseudo2[0]='O';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/O.bmp"); nbr_lettres++;pseudo2[1]='O';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/O.bmp"); nbr_lettres++;pseudo2[2]='O';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/O.bmp"); nbr_lettres++;pseudo2[3]='O';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/O.bmp"); nbr_lettres++;pseudo3[0]='O';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/O.bmp"); nbr_lettres++;pseudo3[1]='O';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/O.bmp"); nbr_lettres++;pseudo3[2]='O';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/O.bmp"); nbr_lettres++;pseudo3[3]='O';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/O.bmp"); nbr_lettres++;pseudo4[0]='O';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/O.bmp"); nbr_lettres++;pseudo4[1]='O';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/O.bmp"); nbr_lettres++;pseudo4[2]='O';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/O.bmp"); nbr_lettres++;pseudo4[3]='O';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_P)
            {

                switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/P.bmp"); nbr_lettres++; pseudo1[0]='P';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/P.bmp"); nbr_lettres++; pseudo1[1]='P';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/P.bmp"); nbr_lettres++;pseudo1[2]='P';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/P.bmp"); nbr_lettres++;pseudo1[3]='P';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/P.bmp"); nbr_lettres++;pseudo2[0]='P';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/P.bmp"); nbr_lettres++;pseudo2[1]='P';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/P.bmp"); nbr_lettres++;pseudo2[2]='P';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/P.bmp"); nbr_lettres++;pseudo2[3]='P';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/P.bmp"); nbr_lettres++;pseudo3[0]='P';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/P.bmp"); nbr_lettres++;pseudo3[1]='P';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/P.bmp"); nbr_lettres++;pseudo3[2]='P';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/P.bmp"); nbr_lettres++;pseudo3[3]='P';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/P.bmp"); nbr_lettres++;pseudo4[0]='P';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/P.bmp"); nbr_lettres++;pseudo4[1]='P';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/P.bmp"); nbr_lettres++;pseudo4[2]='P';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/P.bmp"); nbr_lettres++;pseudo4[3]='P';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_Q)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/Q.bmp"); nbr_lettres++; pseudo1[0]='Q';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/Q.bmp"); nbr_lettres++; pseudo1[1]='Q';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/Q.bmp"); nbr_lettres++;pseudo1[2]='Q';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/Q.bmp"); nbr_lettres++;pseudo1[3]='Q';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/Q.bmp"); nbr_lettres++;pseudo2[0]='Q';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/Q.bmp"); nbr_lettres++;pseudo2[1]='Q';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/Q.bmp"); nbr_lettres++;pseudo2[2]='Q';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/Q.bmp"); nbr_lettres++;pseudo2[3]='Q';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/Q.bmp"); nbr_lettres++;pseudo3[0]='Q';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/Q.bmp"); nbr_lettres++;pseudo3[1]='Q';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/Q.bmp"); nbr_lettres++;pseudo3[2]='Q';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/Q.bmp"); nbr_lettres++;pseudo3[3]='Q';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/Q.bmp"); nbr_lettres++;pseudo4[0]='Q';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/Q.bmp"); nbr_lettres++;pseudo4[1]='Q';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/Q.bmp"); nbr_lettres++;pseudo4[2]='Q';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/Q.bmp"); nbr_lettres++;pseudo4[3]='Q';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_R)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/R.bmp"); nbr_lettres++; pseudo1[0]='R';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/R.bmp"); nbr_lettres++; pseudo1[1]='R';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/R.bmp"); nbr_lettres++;pseudo1[2]='R';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/R.bmp"); nbr_lettres++;pseudo1[3]='R';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/R.bmp"); nbr_lettres++;pseudo2[0]='R';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/R.bmp"); nbr_lettres++;pseudo2[1]='R';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/R.bmp"); nbr_lettres++;pseudo2[2]='R';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/R.bmp"); nbr_lettres++;pseudo2[3]='R';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/R.bmp"); nbr_lettres++;pseudo3[0]='R';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/R.bmp"); nbr_lettres++;pseudo3[1]='R';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/R.bmp"); nbr_lettres++;pseudo3[2]='R';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/R.bmp"); nbr_lettres++;pseudo3[3]='R';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/R.bmp"); nbr_lettres++;pseudo4[0]='R';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/R.bmp"); nbr_lettres++;pseudo4[1]='R';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/R.bmp"); nbr_lettres++;pseudo4[2]='R';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/R.bmp"); nbr_lettres++;pseudo4[3]='R';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_S)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/S.bmp"); nbr_lettres++; pseudo1[0]='S';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/S.bmp"); nbr_lettres++; pseudo1[1]='S';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/S.bmp"); nbr_lettres++;pseudo1[2]='S';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/S.bmp"); nbr_lettres++;pseudo1[3]='S';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/S.bmp"); nbr_lettres++;pseudo2[0]='S';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/S.bmp"); nbr_lettres++;pseudo2[1]='S';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/S.bmp"); nbr_lettres++;pseudo2[2]='S';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/S.bmp"); nbr_lettres++;pseudo2[3]='S';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/S.bmp"); nbr_lettres++;pseudo3[0]='S';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/S.bmp"); nbr_lettres++;pseudo3[1]='S';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/S.bmp"); nbr_lettres++;pseudo3[2]='S';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/S.bmp"); nbr_lettres++;pseudo3[3]='S';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/S.bmp"); nbr_lettres++;pseudo4[0]='S';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/S.bmp"); nbr_lettres++;pseudo4[1]='S';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/S.bmp"); nbr_lettres++;pseudo4[2]='S';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/S.bmp"); nbr_lettres++;pseudo4[3]='S';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_T)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/T.bmp"); nbr_lettres++; pseudo1[0]='T';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/T.bmp"); nbr_lettres++; pseudo1[1]='T';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/T.bmp"); nbr_lettres++;pseudo1[2]='T';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/T.bmp"); nbr_lettres++;pseudo1[3]='T';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/T.bmp"); nbr_lettres++;pseudo2[0]='T';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/T.bmp"); nbr_lettres++;pseudo2[1]='T';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/T.bmp"); nbr_lettres++;pseudo2[2]='T';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/T.bmp"); nbr_lettres++;pseudo2[3]='T';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/T.bmp"); nbr_lettres++;pseudo3[0]='T';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/T.bmp"); nbr_lettres++;pseudo3[1]='T';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/T.bmp"); nbr_lettres++;pseudo3[2]='T';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/T.bmp"); nbr_lettres++;pseudo3[3]='T';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/T.bmp"); nbr_lettres++;pseudo4[0]='T';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/T.bmp"); nbr_lettres++;pseudo4[1]='T';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/T.bmp"); nbr_lettres++;pseudo4[2]='T';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/T.bmp"); nbr_lettres++;pseudo4[3]='T';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_U)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/U.bmp"); nbr_lettres++; pseudo1[0]='U';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/U.bmp"); nbr_lettres++; pseudo1[1]='U';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/U.bmp"); nbr_lettres++;pseudo1[2]='U';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/U.bmp"); nbr_lettres++;pseudo1[3]='U';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/U.bmp"); nbr_lettres++;pseudo2[0]='U';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/U.bmp"); nbr_lettres++;pseudo2[1]='U';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/U.bmp"); nbr_lettres++;pseudo2[2]='U';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/U.bmp"); nbr_lettres++;pseudo2[3]='U';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/U.bmp"); nbr_lettres++;pseudo3[0]='U';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/U.bmp"); nbr_lettres++;pseudo3[1]='U';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/U.bmp"); nbr_lettres++;pseudo3[2]='U';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/U.bmp"); nbr_lettres++;pseudo3[3]='U';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/U.bmp"); nbr_lettres++;pseudo4[0]='U';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/U.bmp"); nbr_lettres++;pseudo4[1]='U';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/U.bmp"); nbr_lettres++;pseudo4[2]='U';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/U.bmp"); nbr_lettres++;pseudo4[3]='U';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_V)
            {

                switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/V.bmp"); nbr_lettres++; pseudo1[0]='V';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/V.bmp"); nbr_lettres++; pseudo1[1]='V';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/V.bmp"); nbr_lettres++;pseudo1[2]='V';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/V.bmp"); nbr_lettres++;pseudo1[3]='V';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/V.bmp"); nbr_lettres++;pseudo2[0]='V';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/V.bmp"); nbr_lettres++;pseudo2[1]='V';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/V.bmp"); nbr_lettres++;pseudo2[2]='V';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/V.bmp"); nbr_lettres++;pseudo2[3]='V';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/V.bmp"); nbr_lettres++;pseudo3[0]='V';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/V.bmp"); nbr_lettres++;pseudo3[1]='V';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/V.bmp"); nbr_lettres++;pseudo3[2]='V';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/V.bmp"); nbr_lettres++;pseudo3[3]='V';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/V.bmp"); nbr_lettres++;pseudo4[0]='V';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/V.bmp"); nbr_lettres++;pseudo4[1]='V';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/V.bmp"); nbr_lettres++;pseudo4[2]='V';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/V.bmp"); nbr_lettres++;pseudo4[3]='V';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_W)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/W.bmp"); nbr_lettres++; pseudo1[0]='W';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/W.bmp"); nbr_lettres++; pseudo1[1]='W';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/W.bmp"); nbr_lettres++;pseudo1[2]='W';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/W.bmp"); nbr_lettres++;pseudo1[3]='W';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/W.bmp"); nbr_lettres++;pseudo2[0]='W';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/W.bmp"); nbr_lettres++;pseudo2[1]='W';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/W.bmp"); nbr_lettres++;pseudo2[2]='W';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/W.bmp"); nbr_lettres++;pseudo2[3]='W';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/W.bmp"); nbr_lettres++;pseudo3[0]='W';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/W.bmp"); nbr_lettres++;pseudo3[1]='W';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/W.bmp"); nbr_lettres++;pseudo3[2]='W';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/W.bmp"); nbr_lettres++;pseudo3[3]='W';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/W.bmp"); nbr_lettres++;pseudo4[0]='W';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/W.bmp"); nbr_lettres++;pseudo4[1]='W';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/W.bmp"); nbr_lettres++;pseudo4[2]='W';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/W.bmp"); nbr_lettres++;pseudo4[3]='W';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_X)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/X.bmp"); nbr_lettres++; pseudo1[0]='X';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/X.bmp"); nbr_lettres++; pseudo1[1]='X';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/X.bmp"); nbr_lettres++;pseudo1[2]='X';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/X.bmp"); nbr_lettres++;pseudo1[3]='X';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/X.bmp"); nbr_lettres++;pseudo2[0]='X';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/X.bmp"); nbr_lettres++;pseudo2[1]='X';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/X.bmp"); nbr_lettres++;pseudo2[2]='X';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/X.bmp"); nbr_lettres++;pseudo2[3]='X';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/X.bmp"); nbr_lettres++;pseudo3[0]='X';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/X.bmp"); nbr_lettres++;pseudo3[1]='X';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/X.bmp"); nbr_lettres++;pseudo3[2]='X';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/X.bmp"); nbr_lettres++;pseudo3[3]='X';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/X.bmp"); nbr_lettres++;pseudo4[0]='X';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/X.bmp"); nbr_lettres++;pseudo4[1]='X';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/X.bmp"); nbr_lettres++;pseudo4[2]='X';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/X.bmp"); nbr_lettres++;pseudo4[3]='X';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_Y)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/Y.bmp"); nbr_lettres++; pseudo1[0]='Y';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/Y.bmp"); nbr_lettres++; pseudo1[1]='Y';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/Y.bmp"); nbr_lettres++;pseudo1[2]='Y';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/Y.bmp"); nbr_lettres++;pseudo1[3]='Y';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/Y.bmp"); nbr_lettres++;pseudo2[0]='Y';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/Y.bmp"); nbr_lettres++;pseudo2[1]='Y';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/Y.bmp"); nbr_lettres++;pseudo2[2]='Y';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/Y.bmp"); nbr_lettres++;pseudo2[3]='Y';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/Y.bmp"); nbr_lettres++;pseudo3[0]='Y';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/Y.bmp"); nbr_lettres++;pseudo3[1]='Y';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/Y.bmp"); nbr_lettres++;pseudo3[2]='Y';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/Y.bmp"); nbr_lettres++;pseudo3[3]='Y';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/Y.bmp"); nbr_lettres++;pseudo4[0]='Y';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/Y.bmp"); nbr_lettres++;pseudo4[1]='Y';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/Y.bmp"); nbr_lettres++;pseudo4[2]='Y';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/Y.bmp"); nbr_lettres++;pseudo4[3]='Y';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_Z)
            {

                 switch (nbr_lettres)
                {
                case 0 :    ecrire_Lettre1(rendu, zone_Pseudo1 , "lettres/Z.bmp"); nbr_lettres++; pseudo1[0]='Z';
                    break;
                case 1 :    ecrire_Lettre2(rendu, zone_Pseudo1 , "lettres/Z.bmp"); nbr_lettres++; pseudo1[1]='Z';
                    break;
                case 2 :     ecrire_Lettre3(rendu, zone_Pseudo1 , "lettres/Z.bmp"); nbr_lettres++;pseudo1[2]='Z';
                    break;
                case 3 :     ecrire_Lettre4(rendu, zone_Pseudo1 , "lettres/Z.bmp"); nbr_lettres++;pseudo1[3]='Z';
                    break;
                case 4 :    ecrire_Lettre1(rendu, zone_Pseudo2 , "lettres/Z.bmp"); nbr_lettres++;pseudo2[0]='Z';
                    break;
                case 5 :    ecrire_Lettre2(rendu, zone_Pseudo2 , "lettres/Z.bmp"); nbr_lettres++;pseudo2[1]='Z';
                    break;
                case 6 :     ecrire_Lettre3(rendu, zone_Pseudo2 , "lettres/Z.bmp"); nbr_lettres++;pseudo2[2]='Z';
                    break;
                case 7 :     ecrire_Lettre4(rendu, zone_Pseudo2 , "lettres/Z.bmp"); nbr_lettres++;pseudo2[3]='Z';
                    break;
                case 8 :    ecrire_Lettre1(rendu, zone_Pseudo3 , "lettres/Z.bmp"); nbr_lettres++;pseudo3[0]='Z';
                    break;
                case 9 :    ecrire_Lettre2(rendu, zone_Pseudo3 , "lettres/Z.bmp"); nbr_lettres++;pseudo3[1]='Z';
                    break;
                case 10 :     ecrire_Lettre3(rendu, zone_Pseudo3 , "lettres/Z.bmp"); nbr_lettres++;pseudo3[2]='Z';
                    break;
                case 11 :     ecrire_Lettre4(rendu, zone_Pseudo3 , "lettres/Z.bmp"); nbr_lettres++;pseudo3[3]='Z';
                    break;
                 case 12 :    ecrire_Lettre1(rendu, zone_Pseudo4 , "lettres/Z.bmp"); nbr_lettres++;pseudo4[0]='Z';
                    break;
                case 13 :    ecrire_Lettre2(rendu, zone_Pseudo4 , "lettres/Z.bmp"); nbr_lettres++;pseudo4[1]='Z';
                    break;
                case 14 :     ecrire_Lettre3(rendu, zone_Pseudo4 , "lettres/Z.bmp"); nbr_lettres++;pseudo4[2]='Z';
                    break;
                case 15 :     ecrire_Lettre4(rendu, zone_Pseudo4 , "lettres/Z.bmp"); nbr_lettres++;pseudo4[3]='Z';
                    break;
                }
                
            }
            else if(evenement.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                program_lance = SDL_FALSE;
            }
            break;
            case SDL_QUIT: program_lance = SDL_FALSE; /* la ligne suivante c' est pour tester : */ printf("type de jeu : %c type de joueur: %c , nombre de joueurs : %d " ,type_jeu,type_joueur,nbr_joueurs); 
            break; // cas cliquer sur croix quitter
            default : continue;
        }
    }
}

    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();

    return EXIT_SUCCESS;
}

//gcc src/controleur.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
//   .\bin\prog.exe
//  set PATH=C:\MinGW\bin;%PATH%
// cd OneDrive/Desktop/DOMINO