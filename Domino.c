#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL_ttf.h>

SDL_Window *window = NULL;
//pour créer des rendu
SDL_Renderer *renderer = NULL;

typedef enum nombreDeJoueur
{
	DEUX, PLUS_DE_DEUX
}NOMBRE_DE_JOUEUR;

typedef enum typeJoueur
{
	JOUEUR_HUMAIN, ORDINATEUR
}TYPE_JOUEUR;

typedef struct Dominos
{
	int nombreGauche, nombreDroite;
}DOMINOS;

typedef struct Joueur
{
	char *pseudo1;
	int score1;
	DOMINOS dominosJoueur[28];
	DOMINOS piocheDominosAuDebut;
}JOUEUR;

/*================= VUE ===================*/

/*================= MODELE =================*/

//======== PREPARATION DU JEU ========

//créer pioche
DOMINOS pioche[28];

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

//créer un dominos avec des nombres par hasard
DOMINOS creer_dominos()
{
	DOMINOS this;
	this.nombreGauche = alea_int(7);
	this.nombreDroite = alea_int(7);
	

	return this;
}

//initialiser pioche
void initialiser_pioche()
{
	int i;
	for(i=0;i<28;i++)
	{
		pioche[i] = creer_dominos();
	}
}

//Au début du jeu chacun des 2 joueurs pioche 9 triominos et donc ça retourne un joueur avec ses 9 triominos
JOUEUR piocher_9_dominos(JOUEUR Joueurr)
{
	int indiceTabPioche,indiceTabJoueur;
	
	for(indiceTabPioche=0, indiceTabJoueur=-1;indiceTabPioche<28 && indiceTabJoueur<8;indiceTabPioche++)
	{
		if((pioche[indiceTabPioche].nombreDroite + pioche[indiceTabPioche].nombreGauche) != 0 )
		{
			indiceTabJoueur++;
			Joueurr.dominosJoueur[indiceTabJoueur].nombreDroite = pioche[indiceTabPioche].nombreDroite;
			Joueurr.dominosJoueur[indiceTabJoueur].nombreGauche = pioche[indiceTabPioche].nombreGauche;
			pioche[indiceTabPioche].nombreDroite = 0; 
			pioche[indiceTabPioche].nombreGauche = 0;
		}
	}
	return Joueurr;
}

//Au début du jeu chacun des joueurs pioche 7 triominos et donc ça retourne un joueur avec ses 7 triominos
JOUEUR piocher_7_dominos(JOUEUR Joueurr)
{
	int indiceTabPioche,indiceTabJoueur;
	
	for(indiceTabPioche=0, indiceTabJoueur=-1;indiceTabPioche<28 && indiceTabJoueur<6;indiceTabPioche++)
	{
		if((pioche[indiceTabPioche].nombreDroite + pioche[indiceTabPioche].nombreGauche)!= 0)
		{
			indiceTabJoueur++;
			Joueurr.dominosJoueur[indiceTabJoueur].nombreDroite = pioche[indiceTabPioche].nombreDroite;
			Joueurr.dominosJoueur[indiceTabJoueur].nombreGauche = pioche[indiceTabPioche].nombreGauche;
			pioche[indiceTabPioche].nombreDroite = 0; 
			pioche[indiceTabPioche].nombreGauche = 0;
		}
	}
	return Joueurr;
}




//nombre de dominos disponible  dans la pioche
int enumerer_pioche()
{
	int i, nombreDominosDisponible;
	nombreDominosDisponible = 0;
	for(i=0;i<27;i++)
	{
		if(pioche[i].nombreDroite + pioche[i].nombreGauche!= 0)
		{
			nombreDominosDisponible++;
		}
	}
	
	return nombreDominosDisponible;
}

//initialiser un joueur
JOUEUR creer_joueur(char *pseudo)
{
	JOUEUR this;
	this.pseudo1 = pseudo;
	this.score1 = 0;
	
	return this;
}

//============== DEBUTER JEU ===============

//choix par hazard du dominos à piocher(en occurence le dominos non null avec l'indice le plut petit dans le tab pioche)
DOMINOS choisir_1_dominos()
{
	int indiceTabPioche;
	for(indiceTabPioche=0;indiceTabPioche<27;indiceTabPioche++)
	{
		if(pioche[indiceTabPioche].nombreDroite + pioche[indiceTabPioche].nombreGauche!= 0)
		{	
			return pioche[indiceTabPioche];
		}
	}
}

//piocher un dominos pour débuter le jeu (à remetre dans la pioche et donc renvoie ce domiinos)
//et c lui k'on va appelé dans le besoin pas la peine d'appeler choix_dominos car et deja appelé ici
//là on sait k ça restera toujours dans la pioche car c pas mise à 0 après affectation
DOMINOS piocher_1_dominosAuDebut(JOUEUR joueurr)
{
	DOMINOS a_piocher;
	a_piocher = choisir_1_dominos();
	joueurr.piocheDominosAuDebut.nombreDroite = a_piocher.nombreDroite;
	joueurr.piocheDominosAuDebut.nombreGauche = a_piocher.nombreGauche;
	
	
	return a_piocher;
}


void piocher_1_dominosPendantJeu(JOUEUR joueurr)
{
	DOMINOS a_piocher;
	a_piocher = choisir_1_dominos();
	int indiceTabJoueur, nombreDePioche;
	indiceTabJoueur=0;
	nombreDePioche=1;
	while(indiceTabJoueur<15)
	{
		if((joueurr.dominosJoueur[indiceTabJoueur].nombreDroite + joueurr.dominosJoueur[indiceTabJoueur].nombreGauche ==0 )
			&&
			nombreDePioche<2)
		{
			joueurr.dominosJoueur[indiceTabJoueur].nombreDroite = a_piocher.nombreDroite;
			joueurr.dominosJoueur[indiceTabJoueur].nombreGauche = a_piocher.nombreGauche;
			
			nombreDePioche++;
		}
		
	}
}

//jouer en posant un dominos 
void poser_dominos(){}
//calculer le score du joueur
void calculer_score(){}


int main(int argc, char *argv[])
{
	
	initialiser_pioche();
	int i;

	for(i=0;i<28;i++)
	{
		printf("%d",pioche[i].nombreGauche);
		printf("%d\n",pioche[i].nombreDroite);
	}
	
	
	/*SDL_version version;
	SDL_VERSION(&version);
	
	printf("version de laa SDL: %i.%i.%o\n", version.major, version.minor,version.patch);
	*/
	
	/*Tester laccéssibilité des triominos dans la pioche
	initier_pioche();
	printf("%d",pioche[27].nombreGauche);
	printf("%d",pioche[27].nombreDroite);
	
	
	/*Tester le nombre de dominos restant 
	initialiser_pioche();
	printf("%d",pioche[0].nombreGauche);
	printf("%d\n",pioche[0].nombreDroite);
	JOUEUR J1 = creer_joueur("sinda");
	J1 = piocher_7_dominos(J1);
	printf("%d",J1.dominosJoueur[0].nombreGauche);
	printf("%d\n",J1.dominosJoueur[0].nombreDroite);
	
	printf("%d",pioche[7].nombreGauche);
	printf("%d\n",pioche[7].nombreDroite);
	JOUEUR J2 = creer_joueur("sinda");
	J2 = piocher_7_dominos(J2);
	printf("%d",J2.dominosJoueur[0].nombreGauche);
	printf("%d\n",J2.dominosJoueur[0].nombreDroite);
	*/
	
	return 0;
}
