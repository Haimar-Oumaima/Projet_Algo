
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 

#include <time.h>
#include <string.h>

#include <SDL.h>
#include <SDL_ttf.h>



typedef enum direction
{
	horizontal,
	vertical,
	none
}DIRECTION;

typedef struct Domino
{
	int nombreGauche, nombreDroite;
	DIRECTION dir;
}DOMINO;

typedef struct nbr_Joueur
{
	int nbr_Joueur_H, nbr_Joueur_O;
}NOMBRE_JOUEUR;

typedef struct Joueur
{
	char pseudo[30];
	int score;
	int nbr_dominos;
	DOMINO pioche_joueur[];
}JOUEUR;

typedef enum variante
{
	SANS_PIOCHE,
	AVEC_PIOCHE
} VAR;

typedef struct COORDONNEES
{
	int coordX; // coordonnées horizontal
	int coordY; // coordonnées vertical
} COORDONNEES;

typedef struct CASE{
	COORDONNEES coordonne;
	DIRECTION dir;
}CASE; 


// Source inspi: https://www.codegrepper.com/code-examples/c/creating+a+list+in+c
typedef struct listeEmplacement{
	CASE emplacementVide;
	struct listeEmplacement *next;
}listeEmplacement;


int tour_joueur=0;

// variables globales
DOMINO plateau[28][28]; // Plateau de jeu [ligne][colonne]
DOMINO pioche[28];

CASE tab_grille[28][28];
CASE tab_main[7];

CASE extremiteVide[2];

// listeEmplacement listeEmplacementVide;

//###########

listeEmplacement *ajoutEmplacement(CASE emp){
	listeEmplacement *new_emp = malloc(sizeof(emp));
	new_emp->emplacementVide = emp;
	new_emp->next = NULL;
	return new_emp;
}


listeEmplacement rajouterEmplacement(listeEmplacement liste, CASE emp){
	if(liste.next != NULL){
		*liste.next =rajouterEmplacement(*liste.next,emp);
		return liste;
	} else {
		liste.next = ajoutEmplacement(emp);
		return liste;
	}
}

int trouverIndexCoordX(int coordX){
	int i;
	for(i=0;i<28;i++){
		if(tab_grille[i][0].coordonne.coordX==coordX){
			return i;
		}
	}
}

int trouverIndexCoordY(int coordY){
	int i;
	for(i=0;i<28;i++){
		if(tab_grille[i][0].coordonne.coordY==coordY){
			return i;
		}
	}
}

/**

void testEmplacementVide(){
	CASE case1,case2,case3;

	case1.coordonne.coordX = 30;
	case1.coordonne.coordY = 30;
	case2.coordonne.coordX = 35;
	case2.coordonne.coordY = 35;
	case3.coordonne.coordX = 38;
	case3.coordonne.coordY = 38;


	printf(">Entrée");
	printf("###Creation liste###");
	listeEmplacementVide = ajoutEmplacement(case1);
	listeEmplacementVide = rajouterEmplacement(listeEmplacementVide, case2);
	listeEmplacementVide = rajouterEmplacement(listeEmplacementVide, case3);

	printf("###Explore Liste###");

	printf(">Sortie");

}
**/


//###########

DOMINO inverserValDom(DOMINO dom){
	int temp;
	temp = dom.nombreGauche;
	dom.nombreGauche = dom.nombreDroite;
	dom.nombreDroite = temp;
	return dom;
}

DIRECTION changementDirection(CASE casedom){
	if(casedom.dir == horizontal){
		return vertical;
	} else {
		return horizontal;
	}
}

bool placer_domino(DOMINO dom, int indexI, int indexJ){
	DOMINO temp,dominoVide;
	dominoVide.nombreGauche = -1; dominoVide.nombreDroite = -1;

//	if(plateau[indexI][indexJ]){
		if(plateau[indexI+1][indexJ].nombreDroite !=-1 && plateau[indexI+1][indexJ].nombreGauche !=-1  ){
			temp.nombreDroite= plateau[indexI+1][indexJ].nombreDroite;
			temp.nombreGauche= plateau[indexI+1][indexJ].nombreGauche;
			if((temp.nombreGauche == dom.nombreGauche) && (temp.nombreGauche == dom.nombreDroite)){
				// changement de direction puis placement;
				dom.dir = changementDirection(tab_grille[indexI+1][indexJ]);
				tab_grille[indexI][indexJ].dir = dom.dir;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				return true;
			} else if(temp.nombreGauche == dom.nombreGauche) {
				// placer dans le même sens, mais inverser nombre de Gauche et nombre de droite du domino
				dom = inverserValDom(dom);
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI+1][indexJ].dir;
				return true;
			} else if(temp.nombreGauche == dom.nombreDroite){
				// placer dans le même sens normalement;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI+1][indexJ].dir;
				return true;
			}

		} 
		if(plateau[indexI][indexJ+1].nombreDroite !=-1 && plateau[indexI][indexJ+1].nombreGauche !=-1 ){
			temp = plateau[indexI][indexJ+1];
			if(temp.nombreDroite == dom.nombreGauche && temp.nombreDroite == dom.nombreDroite){
				// changement de direction puis placement;
				dom.dir = changementDirection(tab_grille[indexI][indexJ+1]);
				tab_grille[indexI][indexJ].dir = dom.dir;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				return true;
			} else if(temp.nombreDroite == dom.nombreGauche) {
				// placer dans le même sens normalement;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI][indexJ+1].dir;
				return true;	
			} else if(temp.nombreDroite == dom.nombreDroite){
				// placer dans le même sens, mais inverser nombre de Gauche et nombre de droite du domino
				dom = inverserValDom(dom);
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI][indexJ+1].dir;
				return true;
			}

		}  
		
		if(plateau[indexI-1][indexJ].nombreDroite !=-1 && plateau[indexI-1][indexJ].nombreGauche !=-1 ){
			temp = plateau[indexI-1][indexJ];
			if(temp.nombreGauche == dom.nombreGauche && temp.nombreDroite== dom.nombreDroite){
				// changement de direction puis placement;
				dom.dir = changementDirection(tab_grille[indexI][indexJ+1]);
				tab_grille[indexI][indexJ].dir = dom.dir;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				return true;
			} else if(temp.nombreGauche == dom.nombreGauche) {
				// placer dans le même sens, mais inverser nombre de Gauche et nombre de droite du domino
				dom = inverserValDom(dom);
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI][indexJ+1].dir;
				return true;
			} else if(temp.nombreGauche == dom.nombreDroite){
				// placer dans le même sens normalement;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI][indexJ+1].dir;
				return true;
			}
		}  

		if(plateau[indexI][indexJ-1].nombreDroite !=-1 && plateau[indexI][indexJ-1].nombreGauche !=-1 ){
			temp = plateau[indexI][indexJ-1];
			if(temp.nombreDroite == dom.nombreGauche && temp.nombreDroite == dom.nombreDroite){
				// changement de direction puis placement;
				dom.dir = changementDirection(tab_grille[indexI][indexJ+1]);
				tab_grille[indexI][indexJ].dir = dom.dir;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				return true;
		} else if(temp.nombreDroite == dom.nombreGauche) {
				// placer dans le même sens normalement;
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI][indexJ+1].dir;
				return true;
			} else if(temp.nombreDroite == dom.nombreDroite){
				// placer dans le même sens, mais inverser nombre de Gauche et nombre de droite du domino
				dom = inverserValDom(dom);
				plateau[indexI][indexJ].nombreDroite=dom.nombreDroite;
				plateau[indexI][indexJ].nombreGauche=dom.nombreGauche;
				dom.dir = tab_grille[indexI][indexJ+1].dir;
				return true;
			}

		}
	return false;
}



void initialise_tab_grille()
{
	int x,y,i,j;
	x=0; //Coordonnées de début horizontal
	y=0; //Coordonnées de début vertical
	for (i=0;i<28;i++)
	{ // on boucle verticalement (les lignes = y)
		for (j=0;j<28;j++)
		{ // on boucle horizontalement (les colonnes = x)
			tab_grille[i][j].coordonne.coordX=x; // on place le point horizontal de la case à X
			tab_grille[i][j].coordonne.coordY=y; // on place le point vertical de la case à la valeur y

			x = x + 50; // on va changer de colonne, donc on décalle le point
		}
		// on a finit de boucler dans toute les colonnes donc on revient à la première
		x = 0;
		// on décalle à la prochaine ligne;
		y = y + 50;
	}
}


float alea_float()          //GENERER UNE VALEUR ALEATOIRE (référence : bibliothèque sdl Mme Pillard) et Renvoie un float dans l'intervalle [0;1[
{
	static int init_alea = 1;
	if (init_alea) 
		srand(time(NULL));

	init_alea = 0;
	return (float)rand() / (float)RAND_MAX;
}

int alea_int(int N)			// Renvoie un int dans l'intervalle [0..N[ et soit N valeurs différentes de 0 à N-1
{ 
	return (int)(N*alea_float());
}

void melangerPioche(){
	int i,original, destination;
	DOMINO temporaire;
	for(i=0;i<280;i++){
		original = i%28;
		destination = alea_int(28);
		temporaire = pioche[destination];
		pioche[destination] = pioche[original];
		pioche[original] = temporaire;
	}
}


void initialiser_pioche()		//initialiser pioche
{
	DOMINO dominoPourPioche;
	int i,j,count;
	count =0;
	for(i=0;i<7;i++){
		for(j=i;j<7;j++){
			dominoPourPioche.nombreGauche = i;
			dominoPourPioche.nombreDroite = j;
			pioche[count] = dominoPourPioche;
			count++;
		}

	}
	melangerPioche();
}


//piocher un domino de la pioche
DOMINO piocher_domino(DOMINO p[])
{
	DOMINO val;
	int i;
	
	i=0;
	while (p[i].nombreDroite==-1 && p[i].nombreGauche==-1)
	{
		i++;
	}
	val.nombreDroite=p[i].nombreDroite;
	val.nombreGauche=p[i].nombreGauche;
	
	return val;
}





//spécifier si on joue avec ou sans talon
VAR choisir_variante()
{
	int x;
	printf("Avec pioche: saisir'1', sans pioche: saisir '0'");
	scanf("%d",&x);
	return x;
}

//distribuer les dominos sur les joueurs
NOMBRE_JOUEUR distribue_dominos(JOUEUR joueur[],NOMBRE_JOUEUR nb_Joueur)
{

	int i,j,count;																//i:indice tableau pioche; j:indice tableau joueur; k:indice tableau pioche_joueur
	int nbr_total_joueurs,nbr_dominoDistrib;
    nbr_total_joueurs=nb_Joueur.nbr_Joueur_H + nb_Joueur.nbr_Joueur_O;
   
    if(nbr_total_joueurs==2){
    	nbr_dominoDistrib = 7;
    } else {
    	nbr_dominoDistrib = 6;
    }

    count = nbr_total_joueurs * nbr_dominoDistrib;

    
    DOMINO dominoVide;
    dominoVide.nombreGauche = -1;
    dominoVide.nombreDroite = -1;

    for(i=0; i<nbr_total_joueurs;i++){
    	printf("nbr_dominoDistrib: %d",nbr_dominoDistrib);
    	joueur[i].nbr_dominos = nbr_dominoDistrib;
		for(j=0; j<nbr_dominoDistrib;j++){
			joueur[i].pioche_joueur[i] = pioche[count];
			pioche[count] = dominoVide;
			count--;
		}    	
    }

	return nb_Joueur;
}

//vérifier si le domino est une pièce double
bool piece_double(DOMINO domino)
{
    if (domino.nombreDroite == domino.nombreGauche)
    {
        return true;
    }
    return false;
}

//passer le tour au joueur suivant
void joueur_suivant(int tour_joueur, JOUEUR joueur[], NOMBRE_JOUEUR nb_Joueur)
{
	int nbr_total_joueurs;
	
	nbr_total_joueurs=nb_Joueur.nbr_Joueur_H + nb_Joueur.nbr_Joueur_O;
    tour_joueur++;
    if (tour_joueur >= nbr_total_joueurs)
    {
        tour_joueur=0;
	}
    //printf("Le tour de %s\n",joueur[tour_joueur].pseudo);
}




//FONCTIONS TEST

NOMBRE_JOUEUR testRecupNbrJoueur(){
	NOMBRE_JOUEUR nbr;
	nbr.nbr_Joueur_H = 3;
	nbr.nbr_Joueur_O = 1;
	return nbr;
}

void testRecuperPseudo(JOUEUR joueur[], NOMBRE_JOUEUR nb_Joueur){
	int i;
	for(i = 0; i<nb_Joueur.nbr_Joueur_H;i++){
		strcpy(joueur[i].pseudo, "Mitchel");
	}

	for(i = nb_Joueur.nbr_Joueur_H; i<nb_Joueur.nbr_Joueur_O+nb_Joueur.nbr_Joueur_H;i++){
		strcpy(joueur[i].pseudo, "Machine");

	}
}


bool dominoSuperieur(DOMINO dom1,DOMINO dom2){
	if(piece_double(dom1)){
		if(piece_double(dom2)){
			if(dom1.nombreDroite>dom2.nombreDroite){
				return true;
			}
		}else{
			return true;
		}
	} else {
		if(!piece_double(dom2)){
			if((dom1.nombreDroite>dom2.nombreDroite && dom1.nombreDroite>dom2.nombreGauche) ||
				(dom1.nombreGauche>dom2.nombreDroite && dom1.nombreGauche>dom2.nombreGauche)){
				return true;
			}
		}
	}
	return false;
}

// fonction return dominomax
DOMINO trouverDominoMax(JOUEUR joueur){
	int i,max;
	max = 0;
	for(i=1;i<joueur.nbr_dominos;i++){
		if(dominoSuperieur(joueur.pioche_joueur[i],joueur.pioche_joueur[max])){
			max = i;
		}
	}
	return joueur.pioche_joueur[max];
}


// fonction qui commence
int trouverIndexCommence(JOUEUR joueur[],NOMBRE_JOUEUR nbrJ){
	int index,i;
	DOMINO max,temp;
	max = trouverDominoMax(joueur[0]);
	index = 0;
	for(i=1;i<nbrJ.nbr_Joueur_O+nbrJ.nbr_Joueur_O;i++){
		temp = trouverDominoMax(joueur[i]);
		if(dominoSuperieur(temp,max)){
			max = temp;
			index = i;
		}
	}

	return index;
}




int main(int argc, char *argv[])
{	
	int a;
	initialiser_pioche();
	NOMBRE_JOUEUR nb;
	nb = testRecupNbrJoueur();//TEST
	JOUEUR joueur[nb.nbr_Joueur_H + nb.nbr_Joueur_O];
	nb  = distribue_dominos(joueur,nb); // RETOURNE POUR FIX : bug incompréhensible (changement nbr_Joueur_H)
	testRecuperPseudo(joueur,nb);

	DOMINO test;
	test.nombreGauche = 1;
	test.nombreDroite = 1;
	test.dir = vertical;
	//tab_grille.dir = vertical;
	plateau[1][1] = test;

	test.nombreGauche = 2;
	test.nombreDroite = 1;
	test.dir = none;
	placer_domino(test,0,1);

	printf("nombreDroite : %d  - ",plateau[0][1].nombreDroite);
	printf("nombreGauche : %d\n",plateau[0][1].nombreGauche);


	


	return 0;
}
