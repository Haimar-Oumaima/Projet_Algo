#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>


typedef enum nombreDeJoueur
{
	DEUX, PLUS_DE_DEUX
}NOMBRE_DE_JOUEUR;

typedef enum typeJoueur
{
	JOUEUR_HUMAIN, ORDINATEUR
}TYPE_JOUEUR;

typedef struct Triominos
{
	int nombreGauche, nombreDroite, nombreMilieu;
}TRIOMINOS;

typedef struct Joueur
{
	char *pseudo;
	int score;
	TRIOMINOS triominosJoueur[30];
	TRIOMINOS piocheTriominosAuDebut;
}JOUEUR;

typedef struct Liste_joueur
{
	JOUEUR Joueurs[4];
}LISTE_JOUEUR;

// Définition du type POINT
	typedef struct point {int x,y;} POINT;
	
	POINT ___MOUSE_POSITION = {0,0};
	
	// Définition du type COULEUR
	typedef Uint32 COULEUR;

TRIOMINOS piocher_1_triominosAuDebut(JOUEUR);


//POINT
POINT wait_clic()
	{
	int encore = 1;
	POINT P;
	SDL_Event event;
	P.x = 0;
	P.y = 0;
#ifdef EN_LOCAL
// A ne mettre que si on est en local, sur les ordi des étudiants, c'est trop lent
	#ifdef SDL_TTF_OK
		POINT E,F;
		char S[16];
		E.x = WIDTH - 55; E.y = 15;
		F.x = WIDTH; F.y = 0;
	#endif
#endif
	while (SDL_WaitEvent(&event) && encore)
		{
		/* Si l'utilisateur clique avec la souris */
		if ((event.type == SDL_MOUSEBUTTONDOWN) && (event.button.button == SDL_BUTTON_LEFT))
			{
			encore=0;
			P.x = event.button.x;
			P.y = event.button.y;
			}
		/* Si l'utilisateur déplace la souris */
		if (event.type == SDL_MOUSEMOTION)
			{
#ifdef EN_LOCAL
// A ne mettre que si on est en local, sur les ordi des étudiants, c'est trop lent
			#ifdef SDL_TTF_OK
				if (police[10]) 
					{
					draw_fill_rectangle(E,F,noir);
					sprintf(S,"%4d %4d",event.motion.x,HEIGHT - event.motion.y);
					aff_pol(S,10,E,gris);
					affiche_all();
					}
			#endif
#endif
			printf("%cEn attente de clic ... %4d %4d           %c",13,event.motion.x,event.motion.y,13);
			fflush(stdout);
			}
		/* Si l'utilisateur a demandé à fermer la fenêtre, on quitte */
		if (event.type == SDL_QUIT) exit(0);
	
		}
#ifdef EN_LOCAL
// A ne mettre que si on est en local, sur les ordi des étudiants, c'est trop lent
	#ifdef SDL_TTF_OK
		aff_pol(S,10,E,noir);
		//draw_fill_rectangle(E,F,jaune);
		affiche_all();
	#endif
#endif
	printf("%cClic en %4d %4d                                           \n",13,P.x,P.y);
	___MOUSE_POSITION = P;
	return P;
	}
//FIN POINT

void aff_pol(char *a_ecrire, int taille, POINT p, COULEUR C)
	{
	#ifdef SDL_TTF_OK
	    int i;
	    SDL_Color color;
	    SDL_Surface *texte = NULL;
	    SDL_Rect position;
	    static int premiere_fois = 1;
	    static TTF_Font *police[256];
	    TTF_Font *pol;
	    
	    // Initialisation de la police (n'est fait qu'une seule fois pour les tailles < 256)
	    if (premiere_fois)  { TTF_Init(); for (i=0;i<256;i++) police[i] = NULL; premiere_fois = 0;}
	    if (taille>=256) pol = TTF_OpenFont(POLICE_NAME, taille);
		    else {
			 if (police[taille]==NULL) police[taille] = TTF_OpenFont(POLICE_NAME, taille);
		         pol = police[taille];
			 }
	    SDL_GetRGB(C,SDL_screen->format,&(color.r),&(color.g),&(color.b));

	    /* Ecriture du texte dans la SDL_Surface "texte" en mode Blended (optimal) */
	    if (pol) texte = TTF_RenderText_Blended(pol, a_ecrire, color); else texte = NULL;
	    if (texte)  {
		    	position.x = p.x;
		    	position.y = HEIGHT - p.y;
		    	SDL_BlitSurface(texte, NULL, SDL_screen, &position); /* Blit du texte par-dessus */
	            	if (SDL_AFFICHE_AUTO) affiche_all();
			SDL_FreeSurface(texte);
		    	}
		    else printf("%s\n",a_ecrire);
/*	
	    if (SDL_AFFICHE_AUTO) affiche_all();
	    if (police) TTF_CloseFont(police);
	    TTF_Quit();
	    if (texte) SDL_FreeSurface(texte);
*/
	#else 
		taille = 0; p.x = p.y = 0; C = 0;
		printf("%s\n",a_ecrire);
	#endif
	}

	// 5.2 Affiche un entier
	// Meme sémantique que aff_pol()
void aff_int(int n,  int taille, POINT p, COULEUR C)
	{
	char s[32];
	sprintf(s,"%d",n);
	aff_pol(s,taille,p,C);
	}

/*================= MODELE =================*/

//======== PREPARATION DU JEU ========

//créer pioche
TRIOMINOS pioche[56];

//GENERER UNE VALEUR ALEATOIRE (référence : bibliothèque sdl Mme Pillard)
//Renvoie un float dans l'intervalle [0;1[
float alea_float()
{
	static int init_alea = 1;
	if (init_alea) 
		srand(time(NULL));

	init_alea = 0;
	return (float)rand() / (float)RAND_MAX;
}
// Renvoie un int dans l'intervalle [0..N[
// soit N valeurs différentes de 0 à N-1
int alea_int(int N)
{ 
	return (int)(N*alea_float());
}

//créer un triominos avec des nombres par hasard
TRIOMINOS creer_Triominos()
{
	TRIOMINOS this;
	this.nombreGauche = alea_int(6);
	this.nombreDroite = alea_int(6);
	this.nombreMilieu = alea_int(6);

	return this;
}

//initialiser pioche
void initialiser_pioche()
{
	int i;
	for(i=0;i<56;i++)
	{
		pioche[i] = creer_Triominos();
	}
}

//Au début du jeu chacun des 2 joueurs pioche 9 triominos et donc ça retourne un joueur avec ses 9 triominos
JOUEUR piocher_9_triominos(JOUEUR Joueurr)
{
	int indiceTabPioche,indiceTabJoueur;
	
	for(indiceTabPioche=0, indiceTabJoueur=-1;indiceTabPioche<56 && indiceTabJoueur<8;indiceTabPioche++)
	{
		if((pioche[indiceTabPioche].nombreDroite + pioche[indiceTabPioche].nombreGauche + pioche[indiceTabPioche].nombreMilieu ) != 0 )
		{
			indiceTabJoueur++;
			Joueurr.triominosJoueur[indiceTabJoueur].nombreDroite = pioche[indiceTabPioche].nombreDroite;;
			Joueurr.triominosJoueur[indiceTabJoueur].nombreGauche = pioche[indiceTabPioche].nombreGauche;
			Joueurr.triominosJoueur[indiceTabJoueur].nombreMilieu = pioche[indiceTabPioche].nombreMilieu;
			pioche[indiceTabPioche].nombreDroite = 0; 
			pioche[indiceTabPioche].nombreGauche = 0;
			pioche[indiceTabPioche].nombreMilieu = 0;
		}
	}
	return Joueurr;
}

//Au début du jeu chacun des joueurs pioche 7 triominos et donc ça retourne un joueur avec ses 7 triominos
JOUEUR piocher_7_triominos(JOUEUR Joueurr)
{
	int indiceTabPioche,indiceTabJoueur;
	
	for(indiceTabPioche=0, indiceTabJoueur=-1;indiceTabPioche<56 && indiceTabJoueur<6;indiceTabPioche++)
	{
		if((pioche[indiceTabPioche].nombreDroite + pioche[indiceTabPioche].nombreGauche + pioche[indiceTabPioche].nombreMilieu ) != 0 )
		{
			indiceTabJoueur++;
			Joueurr.triominosJoueur[indiceTabJoueur].nombreDroite = pioche[indiceTabPioche].nombreDroite;
			Joueurr.triominosJoueur[indiceTabJoueur].nombreGauche = pioche[indiceTabPioche].nombreGauche;
			Joueurr.triominosJoueur[indiceTabJoueur].nombreMilieu = pioche[indiceTabPioche].nombreMilieu;
			pioche[indiceTabPioche].nombreDroite = 0; 
			pioche[indiceTabPioche].nombreGauche = 0;
			pioche[indiceTabPioche].nombreMilieu = 0;
		}
	}
	return Joueurr;
}

//nombre de triominos disponible  dans la pioche
int enumerer_pioche()
{
	int i, nombreTriominosDisponible;
	nombreTriominosDisponible = 0;
	for(i=0;i<59;i++)
	{
		if(pioche[i].nombreDroite + pioche[i].nombreGauche + pioche[i].nombreMilieu != 0)
		{
			nombreTriominosDisponible++;
		}
	}
	return nombreTriominosDisponible;
}

//initialiser un joueur
JOUEUR initialiser_joueur(char *pseudo)
{
	JOUEUR this;
	this.pseudo = pseudo;
	this.score = 0;
	
	return this;
}

//============== DEBUTER JEU ===============

//choix par hazard du triominos à piocher(en occurence le triominos non null avec l'indice le plut petit dans le tab pioche)
TRIOMINOS choisir_1_triominos(int interval)
{
	int indiceTabPioche;
	for(indiceTabPioche=interval;indiceTabPioche<56;indiceTabPioche++)
	{
		if(pioche[indiceTabPioche].nombreDroite + pioche[indiceTabPioche].nombreGauche + pioche[indiceTabPioche].nombreMilieu != 0)
		{	
			return pioche[indiceTabPioche];
		}
	}
}

//piocher un triominos pour débuter le jeu (à remetre dans la pioche et donc renvoie ce triominos)
//et c lui k'on va appelé dans le besoin pas la peine d'appeler choix_triominos car et deja appelé ici
//là on sait k ça restera toujours dans la pioche car c pas mise à 0 après affectation
TRIOMINOS piocher_1_triominosAuDebut(JOUEUR joueurr)
{
	TRIOMINOS a_piocher;
	a_piocher = choisir_1_triominos(alea_int(29));
	joueurr.piocheTriominosAuDebut.nombreDroite = a_piocher.nombreDroite;
	joueurr.piocheTriominosAuDebut.nombreGauche = a_piocher.nombreGauche;
	joueurr.piocheTriominosAuDebut.nombreMilieu = a_piocher.nombreMilieu;
	
	return a_piocher;
}


void piocher_1_triominosPendantJeu(JOUEUR joueurr)
{
	TRIOMINOS a_piocher;
	a_piocher = choisir_1_triominos(alea_int(57));
	int indiceTabJoueur, nombreDePioche;
	indiceTabJoueur=0;
	nombreDePioche=1;
	while(indiceTabJoueur<30)
	{
		if((joueurr.triominosJoueur[indiceTabJoueur].nombreDroite + joueurr.triominosJoueur[indiceTabJoueur].nombreGauche + joueurr.triominosJoueur[indiceTabJoueur].nombreMilieu == 0)
			&&
			nombreDePioche<2)
		{
			joueurr.triominosJoueur[indiceTabJoueur].nombreDroite = a_piocher.nombreDroite;
			joueurr.triominosJoueur[indiceTabJoueur].nombreGauche = a_piocher.nombreGauche;
			joueurr.triominosJoueur[indiceTabJoueur].nombreMilieu = a_piocher.nombreMilieu;
			nombreDePioche++;
		}	
	}
}

//liste des pseudo entrée
char *listePseudo[4] = {"Cheikh","Omar","Ousmane","Aliou"};

//creer les joueurs dont on a entré les pseudos par le renvoie d'une liste de joueurs
LISTE_JOUEUR creer_joueur(char *listePseud[4])
{
	LISTE_JOUEUR listeJoueurCreer;
	int i;
	for(i=0;i<4;i++)
	{
		listeJoueurCreer.Joueurs[i] = initialiser_joueur(listePseud[i]);
	}
	
	return listeJoueurCreer;
}

//renvoie le joueur qui doit commencer le jeu
/* Test fonctionnement
JOUEUR commencer_jeu(LISTE_JOUEUR listeGamer)
{
	int i, indiceJoueurDebut;
	int max = 0;
	for(i=0;i<4;i++)
	{
		listeGamer.Joueurs[i].piocheTriominosAuDebut = piocher_1_triominosAuDebut(listeGamer.Joueurs[i]);
		printf("%s ",listeGamer.Joueurs[i].pseudo);
		printf("%d\n",listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreDroite+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreGauche+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreMilieu);
		if(listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreDroite+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreGauche+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreMilieu>=max)
		{	
			max = listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreDroite+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreGauche+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreMilieu;
			indiceJoueurDebut = i;
		}
	}
	printf("%s ",listeGamer.Joueurs[indiceJoueurDebut].pseudo);
	printf("%d\n",max);
	
	return listeGamer.Joueurs[indiceJoueurDebut];
	
	/*Dans le main
	initialiser_pioche();
	LISTE_JOUEUR k;
	k = creer_joueur(listePseudo);
	JOUEUR l;
	l = commencer_jeu(k);
}
*/

//renvoie le joueur qui doit commencer le jeu
JOUEUR commencer_jeu(LISTE_JOUEUR listeGamer)
{
	int i, indiceJoueurDebut;
	int max = 0;
	for(i=0;i<4;i++)
	{
		listeGamer.Joueurs[i].piocheTriominosAuDebut = piocher_1_triominosAuDebut(listeGamer.Joueurs[i]);
		//printf("%s ",listeGamer.Joueurs[i].pseudo);
		//printf("%d\n",listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreDroite+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreGauche+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreMilieu);
		if(listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreDroite+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreGauche+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreMilieu>=max)
		{	
			max = listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreDroite+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreGauche+listeGamer.Joueurs[i].piocheTriominosAuDebut.nombreMilieu;
			indiceJoueurDebut = i;
		}
	}
	//printf("%s est joueur au debut som = ",listeGamer.Joueurs[indiceJoueurDebut].pseudo);
	//printf("%d\n",max);
	
	return listeGamer.Joueurs[indiceJoueurDebut];
}


//jouer en posant un triominos 
void poser_triominos(){}

//calculer le score du joueur
int calculer_score(JOUEUR nomJoueur, TRIOMINOS triominosPose)
{
	nomJoueur.score += triominosPose.nombreGauche+triominosPose.nombreDroite+triominosPose.nombreMilieu;
	
	return nomJoueur.score;
}


int main(int argc, char *argv[])
{
	
	
	
}
	
	/*initialiser_pioche();
	JOUEUR J1;
	LISTE_JOUEUR k;
	k = creer_joueur(listePseudo);
	J1 = piocher_7_triominos(k.Joueurs[0]);
	printf("le nom du premier joueur est %s %d %d %d\n",J1.pseudo, J1.triominosJoueur[0].nombreGauche, J1.triominosJoueur[0].nombreDroite, J1.triominosJoueur[0].nombreMilieu);
	J1.score = calculer_score(J1,  J1.triominosJoueur[0]);
	printf("le score est pour le moment : %d\n",J1.score);
	
	printf("le nom du premier joueur est %s %d %d %d\n",J1.pseudo, J1.triominosJoueur[1].nombreGauche, J1.triominosJoueur[1].nombreDroite, J1.triominosJoueur[1].nombreMilieu);
	J1.score = calculer_score(J1,  J1.triominosJoueur[1]);
	printf("le score est pour le moment : %d\n",J1.score);
	
	printf("le nom du premier joueur est %s %d %d %d\n",J1.pseudo, J1.triominosJoueur[2].nombreGauche, J1.triominosJoueur[2].nombreDroite, J1.triominosJoueur[2].nombreMilieu);
	J1.score = calculer_score(J1,  J1.triominosJoueur[2]);
	printf("le score est pour le moment : %d\n",J1.score);
	*/
	/* Tester le score 
	 * 
	 * 
	 * 
	initialiser_pioche();
	JOUEUR J1;
	LISTE_JOUEUR k;
	k = creer_joueur(listePseudo);
	J1 = piocher_7_triominos(k.Joueurs[0]);
	printf("le nom du premier joueur est %s %d %d %d\n",J1.pseudo, J1.triominosJoueur[0].nombreGauche, J1.triominosJoueur[0].nombreDroite, J1.triominosJoueur[0].nombreMilieu);
	J1.score = calculer_score(J1,  J1.triominosJoueur[0]);
	printf("le score est pour le moment : %d\n",J1.score);
	
	printf("le nom du premier joueur est %s %d %d %d\n",J1.pseudo, J1.triominosJoueur[1].nombreGauche, J1.triominosJoueur[1].nombreDroite, J1.triominosJoueur[1].nombreMilieu);
	J1.score = calculer_score(J1,  J1.triominosJoueur[1]);
	printf("le score est pour le moment : %d\n",J1.score);
	
	printf("le nom du premier joueur est %s %d %d %d\n",J1.pseudo, J1.triominosJoueur[2].nombreGauche, J1.triominosJoueur[2].nombreDroite, J1.triominosJoueur[2].nombreMilieu);
	J1.score = calculer_score(J1,  J1.triominosJoueur[2]);
	printf("le score est pour le moment : %d\n",J1.score);
	* 
	*
	* /
	
	/*int i;
	for(i=0;i<56;i++)
	{
		printf("%d",pioche[i].nombreGauche);
		printf("%d",pioche[i].nombreDroite);
		printf("%d\n",pioche[i].nombreMilieu);
	}*/
	/*printf("%d",pioche[0].nombreGauche);
	printf("%d",pioche[0].nombreDroite);
	printf("%d",pioche[0].nombreMilieu);
	
	printf("%d",pioche[1].nombreGauche);
	printf("%d",pioche[1].nombreDroite);
	printf("%d",pioche[1].nombreMilieu);
	
	printf("%d",pioche[4].nombreGauche);
	printf("%d",pioche[4].nombreDroite);
	printf("%d",pioche[4].nombreMilieu);
	*/
	/*
	JOUEUR J1 = initialiser_joueur("Cheikh");
	J1=piocher_9_triominos(J1);
	printf("%d",J1.triominosJoueur[0].nombreGauche);
	printf("%d",J1.triominosJoueur[0].nombreDroite);
	printf("%d",J1.triominosJoueur[0].nombreMilieu);
	
	printf("%d",J1.triominosJoueur[1].nombreGauche);
	printf("%d",J1.triominosJoueur[1].nombreDroite);
	printf("%d",J1.triominosJoueur[1].nombreMilieu);
	
	printf("%d",J1.triominosJoueur[4].nombreGauche);
	printf("%d",J1.triominosJoueur[4].nombreDroite);
	printf("%d",J1.triominosJoueur[4].nombreMilieu);
	
	printf("%d",pioche[0].nombreGauche);
	printf("%d",pioche[0].nombreDroite);
	printf("%d",pioche[0].nombreMilieu);
	
	printf("%d",pioche[1].nombreGauche);
	printf("%d",pioche[1].nombreDroite);
	printf("%d",pioche[1].nombreMilieu);
	
	printf("%d",pioche[4].nombreGauche);
	printf("%d",pioche[4].nombreDroite);
	printf("%d",pioche[4].nombreMilieu);
	
	printf("%d",pioche[9].nombreGauche);
	printf("%d",pioche[9].nombreDroite);
	printf("%d",pioche[9].nombreMilieu);
	
	JOUEUR J2 = initialiser_joueur("Cheik");
	J2=piocher_9_triominos(J2);
	printf("%d",J2.triominosJoueur[0].nombreGauche);
	printf("%d",J2.triominosJoueur[0].nombreDroite);
	printf("%d",J2.triominosJoueur[0].nombreMilieu);
	
	printf("%d",pioche[9].nombreGauche);
	printf("%d",pioche[9].nombreDroite);
	printf("%d",pioche[9].nombreMilieu);
	*/
	

	
	
	
	/*Tester le nombre de triominos restant 
	initialiser_pioche();
	JOUEUR J1 = creer_joueur("Cheikh");
	piocher_7_triominos(J1);
	JOUEUR J2 = creer_joueur("Cheikh");
	piocher_7_triominos(J2);
	int g = enumerer_pioche();
	printf("%d",g);
	*/
	

