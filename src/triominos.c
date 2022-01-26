// ##Include
//std
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
//SDL
#include <SDL.h>
#include <SDL_ttf.h>



typedef struct Case{
	int coordX;
	int coordY;
	bool directionPH; //directionPointeHaut IF TRUE: pointe en haut | ELSE IF FALSE : pointe en bas
} Case; 


typedef struct Triominos {
	//NB: Je nomme les nombres en fonction de leur position cardinal
	int nbrN; // Nord
	int nbrSE; // Sud Est
	int nbrSW; // Sud West 
} Triominos;

typedef struct MainJeu{
	Triominos main[7];
} MainJeu;





Case grille[9][9]; // grille de jeu avec les coordonnées
Triominos grillePlacement[9][9]; //grille de placement des triminos


//Version vide
	// if(SDL_RenderDrawRect(renderer, &rectangle) != 0){
	// 	SDL_Log("Error: SDL_SetRenderDrawRect > %s\n",SDL_GetError());
	// 	exit(-1);
	// }

// #######################
// ### Dessin Triangle ###
// #######################


int dessinerTriangleHaut(SDL_Renderer* renderer ,int x, int y, int xmod,int ymod){

	//From N -> SE
	if(SDL_RenderDrawLine(renderer,x,y-ymod,x+xmod,y+ymod) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	// From N -> SW
	if(SDL_RenderDrawLine(renderer,x,y-ymod,x-xmod,y+ymod) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	//From SW -> SE
	if(SDL_RenderDrawLine(renderer,x+xmod,y+ymod,x-xmod,y+ymod) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}
	return 0;
}

int dessinerTriangleBas(SDL_Renderer* renderer ,int x, int y, int xmod, int ymod){


	//From S -> NE
	if(SDL_RenderDrawLine(renderer,x,y+ymod,x+xmod,y-ymod) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	// From S -> NW
	if(SDL_RenderDrawLine(renderer,x,y+ymod,x-xmod,y-ymod) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	//From NW -> NE
	if(SDL_RenderDrawLine(renderer,x+xmod,y-ymod,x-xmod,y-ymod) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}
	return 0;
}

int dessinerTriangleGrille(bool direct, SDL_Renderer* renderer ,int x, int y){
	int xmod = 38;
	int ymod = 23;

	if(direct){
		dessinerTriangleHaut(renderer ,x, y,xmod,ymod);
	}else{
		dessinerTriangleBas(renderer ,x, y,xmod,ymod);
	}
}

int dessinerTriangleMain(SDL_Renderer* renderer ,int x, int y){
	int xmod = 40;
	int ymod = 35;

	dessinerTriangleHaut(renderer ,x, y,xmod,ymod);
}


// ###################
// ### Ecrire Main ###
// ###################

void ecrireNombres(SDL_Renderer* renderer, const char * num , int x, int y,int xmod, int ymod){
	TTF_Init();

	TTF_Font * font = TTF_OpenFont("font/arial.ttf",55);
	SDL_Color colorfont = {255,255,255};

	//FIX FROM HERE:
	SDL_Rect dstrect = {x+xmod,y+ymod,10,12};
	// printf("num 	> %c \n",num);
	// printf("num[0] 	> %c\n",num[0]);
	// printf("num[1] 	> %c\n",num[1]);
	// printf("num[2] 	> %c\n",num[2]);
	// printf("num[3] 	> %c\n",num[3]);
	SDL_Surface * surface = TTF_RenderText_Solid(font, num, colorfont);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void ecrireNombresMainNord(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = -1;
	int ymod = -25;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}

void ecrireNombresMainSudWest(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = -30;
	int ymod = 20;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}

void ecrireNombresMainSudEst(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = 24;
	int ymod = 20;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}

void ecrireNombresMain(SDL_Renderer* renderer, const char * numMiddle,const char * numRight,const char * numLeft , int x, int y){
	(renderer,numMiddle,x,y);
	ecrireNombresMainSudEst(renderer,numRight,x,y);
	ecrireNombresMainSudWest(renderer,numLeft,x,y);
}



void ecrireNombresGrilleNord(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = -1;
	int ymod = -21;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}

void ecrireNombresGrilleSudWest(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = -25;
	int ymod = 10;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}

void ecrireNombresGrilleSudEst(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = 20;
	int ymod = 10;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}


void ecrireNombresGrilleSud(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = -1;
	int ymod = 9;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}

void ecrireNombresGrilleNordWest(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = -25;
	int ymod = -23;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}

void ecrireNombresGrilleNordEst(SDL_Renderer* renderer, const char * num , int x, int y){
	int xmod = 20;
	int ymod = -23;

	ecrireNombres(renderer,num,x,y,xmod,ymod);
}


void ecrireNombresGrille(bool direct, SDL_Renderer* renderer, const char * numMiddle,const char * numRight,const char * numLeft , int x, int y){
	if(direct){
		ecrireNombresGrilleNord(renderer,numMiddle,x,y);
		ecrireNombresGrilleSudEst(renderer,numRight,x,y);
		ecrireNombresGrilleSudWest(renderer,numLeft,x,y);
	}else{
		ecrireNombresGrilleSud(renderer,numMiddle,x,y);
		ecrireNombresGrilleNordEst(renderer,numRight,x,y);
		ecrireNombresGrilleNordWest(renderer,numLeft,x,y);
	}
}

char intToString(int x){
	char string = x+'0';
	return string; 
}


// ######################
// ### Bouton Quitter ###
// ###################### 

void ajouterBtnQuitter(SDL_Renderer* renderer){

	 SDL_Rect rectangle;
	 rectangle.x = 600;
	 rectangle.y = 1;
	 rectangle.w = 49;
	 rectangle.h = 49;

	 if(SDL_RenderDrawRect(renderer, &rectangle) != 0){
	 	SDL_Log("Error: SDL_SetRenderDrawRect > %s\n",SDL_GetError());
	 	exit(-1);
	 }

	 SDL_RenderDrawLine(renderer, rectangle.x, rectangle.y, rectangle.x + rectangle.w, rectangle.y+rectangle.h);
	 SDL_RenderDrawLine(renderer, rectangle.x+rectangle.w, rectangle.y, rectangle.x, rectangle.y+rectangle.h);

}


// #####################
// ### Afficher Fond ###
// ##################### 


void afficherFond(SDL_Renderer *renderer){
	SDL_Surface *imagefond;
	SDL_Texture *texturefond;

	imagefond = SDL_LoadBMP("images/arriere_plan.bmp");
	if(imagefond == NULL){
		SDL_Log("Error: SDL_LoadBMP > %s\n",SDL_GetError());
		exit(-1);
	}

	texturefond = SDL_CreateTextureFromSurface(renderer,imagefond);
	SDL_RenderCopy(renderer,texturefond,NULL,NULL);

	SDL_DestroyTexture(texturefond);
	SDL_FreeSurface(imagefond);		
}

// ####################
// ### Creer Grille ###
// #################### 

void creerGrille(SDL_Renderer *renderer){
	int CoordXCase = 50;
	int CoordYCase = 125;

	int i,j;

	//grille
	for(i=0; i<10; i++){
		CoordYCase = 125;
		CoordXCase = CoordXCase + 50;
		for(j=0;j<10;j++){
			CoordYCase = CoordYCase +50;
			if(i%2==j%2){
				grille[i][j].directionPH = true ;
			} else {
				grille[i][j].directionPH = false;
			}

			grille[i][j].coordX = CoordXCase;
			grille[i][j].coordY = CoordYCase;


			dessinerTriangleGrille(grille[i][j].directionPH,renderer,grille[i][j].coordX,grille[i][j].coordY);

		}
	}
}

// ######################
// ### Afficher Score ###
// ###################### 

void ecrireScoreTitre(SDL_Renderer *renderer){
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("font/arial.ttf",55);
	SDL_Color colorfont = {255,255,255};
	SDL_Rect dstrect = {10,10,100,50};
	SDL_Surface * surface = TTF_RenderText_Solid(font, "SCORE:", colorfont);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void ecrireScore(SDL_Renderer *renderer, int score){
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("font/arial.ttf",55);
	SDL_Color colorfont = {0,0,0};
	SDL_Rect dstrect = {10,60,100,50};
	SDL_RenderFillRect(renderer,&dstrect);
	SDL_Surface * surface = TTF_RenderText_Solid(font, "002", colorfont);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}

// char recritureScore(int intScore){
// 	char charScore[2];
// 	charScore[0]='0';
// 	charScore[1]='0';
// 	charScore[2] = intScore + '0';
// 	printf("%c",charScore);
// 	return charScore;
// }

// #######################
// ### Afficher Joueur ###
// ####################### 

void ecrireJoueurTitre(SDL_Renderer *renderer){
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("font/arial.ttf",55);
	SDL_Color colorfont = {255,255,255};
	SDL_Rect dstrect = {170,100,100,60};
	SDL_Surface * surface = TTF_RenderText_Solid(font, "Au tour de :", colorfont);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}

void ecrireJoueur(SDL_Renderer *renderer, char *pseudo){
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("font/arial.ttf",55);
	SDL_Color colorfont = {0,0,0};
	SDL_Rect dstrect = {270,110,150,40};
	SDL_RenderFillRect(renderer,&dstrect);
	SDL_Surface * surface = TTF_RenderText_Solid(font, pseudo, colorfont);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();
}
// #####################
// ### Afficher Logo ###
// ##################### 

void afficherLogo(SDL_Renderer *renderer){
	SDL_Surface *logo = NULL;
	SDL_Texture *t_logo = NULL;
	logo = SDL_LoadBMP("images/LOGO.bmp");
	if(logo == NULL){
		SDL_Log("Error: SDL_LoadBMP > %s\n",SDL_GetError());
		exit(-1);
	}
	t_logo = SDL_CreateTextureFromSurface(renderer,logo);
	SDL_FreeSurface(logo);
	SDL_Rect rectLogo;
	SDL_QueryTexture(t_logo,NULL,NULL,&rectLogo.w,&rectLogo.h); 
	rectLogo.x = (650 - rectLogo.w)/2;
	rectLogo.y =30;
	SDL_RenderCopy(renderer,t_logo,NULL,&rectLogo); 
}

// #######################
// ### Afficher Pioche ###
// #######################

void afficherPiocheTitre(SDL_Renderer *renderer){
	SDL_Rect rectPioche = {475,10,100,100};
	SDL_RenderDrawRect(renderer,&rectPioche);

	TTF_Init();
	TTF_Font * font = TTF_OpenFont("font/arial.ttf",155);
	SDL_Color colorfont = {255,255,255};
	SDL_Rect dstrect = {480,15,80,15};
	SDL_Surface * surface = TTF_RenderText_Solid(font, "Pioche:", colorfont);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();

} 

void afficherPioche(SDL_Renderer *renderer){
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("font/arial.ttf",55);
	SDL_Color colorfont = {0,0,0};
	SDL_Rect dstrect = {485,30,80,75};
	SDL_RenderFillRect(renderer,&dstrect);
	SDL_Surface * surface = TTF_RenderText_Solid(font, "02", colorfont);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer, texture, NULL, &dstrect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	TTF_Quit();	
}

// ####################
// ### Gerer Grille ###
// ####################
int trouverJ(int clicY){
	if(150 < clicY && clicY < 200){
		return 0;
	}else if(200 < clicY && clicY < 250){
		return 1;
	}else if(250 < clicY && clicY < 300){
		return 2;
	}else if(300 < clicY && clicY < 350){
		return 3;
	}else if(350 < clicY && clicY < 400){
		return 4;
	}else if(400 < clicY && clicY < 450){
		return 5;
	}else if(450 < clicY && clicY < 500){
		return 6;
	}else if(500 < clicY && clicY < 550){
		return 7;
	}else if(550 < clicY && clicY < 600){
		return 8;
	}else if(600 < clicY && clicY < 650){
		return 9;
	}else{
		return -1;
	}
}


int trouverI_aux(int index, int clicX, int clicY, int indexJ, bool premierHaut, bool repetition){
	int caseX = grille[index][indexJ].coordX;
	int caseY = grille[index][indexJ].coordY;

	if(premierHaut){
		//PREMIER HAUT : 
		//INDEX PAIRE -> vers le bas
		//INDEX IMPAIRE -> vers le haut
		if(index%2){ // haut
			if(
			 	(caseX-37<clicX && clicX<caseX+38 && clicY+8<caseY && caseY<clicY+23) ||
				(caseX-25<clicX && clicX<caseX+25 && clicY-7<caseY && caseY<clicY+8) ||				
				(caseX-12<clicX && clicX<caseX+13 && clicY-22<caseY && caseY<clicY-7)				
				){
				return index;
			}
			else{ 
				if(repetition){
					if(caseX<clicX){
						return trouverI_aux(index+1, clicX, clicY, indexJ, premierHaut, false);
					} else {
						return trouverI_aux(index-1, clicX, clicY, indexJ, premierHaut, false);
					}
				} else {
					return -1;
				} 
			}
		} else { // bas
			if(
			  	(caseX-37<clicX && clicX<caseX+38 && clicY-22<caseY && caseY<clicY-7) ||
				(caseX-25<clicX && clicX<caseX+25 && clicY-7<caseY && caseY<clicY+8) ||				
				(caseX-12<clicX && clicX<caseX+13 && clicY+8<caseY && caseY<clicY+23)			
				){
				return index;
			}
			else{ 
				if(repetition){
					if(caseX<clicX){
						return trouverI_aux(index+1, clicX, clicY, indexJ, premierHaut, false);
					} else {
						return trouverI_aux(index-1, clicX, clicY, indexJ, premierHaut, false);
					}
				} else {
					return -1;
				} 
			}
		}
	}else{
		//PREMIER BAS : 
		//INDEX PAIRE -> vers le haut
		//INDEX IMPAIRE -> vers le bas
		if(index%2){ // haut
			if(
			 	(caseX-37<clicX && clicX<caseX+38 && clicY+8<caseY && caseY<clicY+23) ||
				(caseX-25<clicX && clicX<caseX+25 && clicY-7<caseY && caseY<clicY+8) ||				
				(caseX-12<clicX && clicX<caseX+13 && clicY-22<caseY && caseY<clicY-7)				
				){
				return index;
			}
			else{ 
				if(repetition){
					if(caseX<clicX){
						return trouverI_aux(index+1, clicX, clicY, indexJ, premierHaut, false);
					} else {
						return trouverI_aux(index-1, clicX, clicY, indexJ, premierHaut, false);
					}
				} else {
					return -1;
				} 
			}

		} else { // bas
			if(
				(caseX-37<clicX && clicX<caseX+38 && clicY-22<caseY && caseY<clicY-7) ||
				(caseX-25<clicX && clicX<caseX+25 && clicY-7<caseY && caseY<clicY+8) ||				
				(caseX-12<clicX && clicX<caseX+13 && clicY+8<caseY && caseY<clicY+23)			
				){
				return index;
			}
			else{ 
				if(repetition){
					if(caseX<clicX){
						return trouverI_aux(index+1, clicX, clicY, indexJ, premierHaut, false);
					} else {
						return trouverI_aux(index-1, clicX, clicY, indexJ, premierHaut, false);
					}
				} else {
					return -1;
				} 
			}
		}
	}
}

int trouverI(int clicX,int clicY, int indexJ){
	bool premierHaut;
	if(indexJ%2){
		premierHaut = true;
	}else{
		premierHaut = false;
	}

	if(60 < clicX && clicX < 120){
		return trouverI_aux(0, clicX, clicY, indexJ, premierHaut, true);
	}else if(120 < clicX && clicX < 160){
		return trouverI_aux(1, clicX, clicY, indexJ, premierHaut, true);
	}else if(160 < clicX && clicX < 210){
		return trouverI_aux(2, clicX, clicY, indexJ, premierHaut, true);
	}else if(210 < clicX && clicX < 260){
		return trouverI_aux(3, clicX, clicY, indexJ, premierHaut, true);
	}else if(260 < clicX && clicX < 310){
		return trouverI_aux(4, clicX, clicY, indexJ, premierHaut, true);
	}else if(310 < clicX && clicX < 360){
		return trouverI_aux(5, clicX, clicY, indexJ, premierHaut, true);
	}else if(360 < clicX && clicX < 410){
		return trouverI_aux(6, clicX, clicY, indexJ, premierHaut, true);
	}else if(410 < clicX && clicX < 460){
		return trouverI_aux(7, clicX, clicY, indexJ, premierHaut, true);
	}else if(460 < clicX && clicX < 510){
		return trouverI_aux(8, clicX, clicY, indexJ, premierHaut, true);
	}else if(510 < clicX && clicX < 588){
		return trouverI_aux(9, clicX, clicY, indexJ, premierHaut, true);
	}else{
		printf("retour direct\n");
		return -1;
	}
}

void gereClicGrille(int clicX, int clicY){
	int indexI, indexJ; //Index pour recup la case dans la grille I = longeur / J = hauteur

	indexJ = trouverJ(clicY);
	indexI = trouverI(clicX,clicY,indexJ);

	printf("GRILLE INDEX : i = %d -- j = %d \n",indexI,indexJ);
	if(indexJ == -1 || indexI == -1){
		exit;
	}

	// case selectionné : grille[indexI][indexJ]
}


// ##############
// ### main() ###
// ##############


int main(int argc, char **argv){
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		SDL_Log("Error: SDL_INIT_VIDEO > %s\n",SDL_GetError());
		exit(-1);
	} 

	//creation rendu et fenetre 
	if(SDL_CreateWindowAndRenderer(650,800,0, &window, &renderer) !=0){//largeur,hauteur,windows_flag,SDL_Window, SDL_Renderer
		SDL_Log("Error: SDL_CreateWindowAndRenderer > %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE) != 0){
		SDL_Log("Error: SDL_SetRenderDrawColor > %s\n",SDL_GetError());
		exit(-1);
	}

	SDL_RenderPresent(renderer);

	if(SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE) != 0){
		SDL_Log("Error: SDL_SetRenderDrawColor > %s\n",SDL_GetError());
		exit(-1);
	}

	SDL_RenderPresent(renderer);

	afficherFond(renderer);
	ajouterBtnQuitter(renderer);
	ecrireScoreTitre(renderer);
	ecrireScore(renderer,10);
	creerGrille(renderer);
	ecrireJoueurTitre(renderer);
	ecrireJoueur(renderer,"Gabin");
	afficherLogo(renderer);
	afficherPiocheTitre(renderer);
	afficherPioche(renderer);
	// recritureScore(30);

	int i,j;

	//TEST VISUEL BOUTON
	SDL_Rect rectangleTest;
	rectangleTest.x = 30;
	rectangleTest.y = 665;
	rectangleTest.w = 595;
	rectangleTest.h = 70;
	SDL_RenderDrawRect(renderer,&rectangleTest);


	//Une main de jeu: à titre indicatif
	int CoordXCase = 70;
	int CoordYCase = 700;

	Triominos trio1;
	trio1.nbrN = 1;
	trio1.nbrSE = 2;
	trio1.nbrSW = 3;

	char nbrN = intToString(trio1.nbrN);
	char nbrSE = intToString(trio1.nbrSE);
	char nbrSW = intToString(trio1.nbrSW);
	
	int count = 0;

	count = count +1;
	// printf("#######COUNT#####\nvalue 	> %d\n",count);
	// printf("North 	> %c \n",nbrN);
	// printf("SEst 	> %c \n",nbrSE);
	// printf("SWest 	> %c \n",nbrSW);
	ecrireNombresGrille(grille[1][0].directionPH,renderer,"1","2","3",grille[1][0].coordX,grille[1][0].coordY);

	for(i=0;i<7;i++){
		dessinerTriangleMain(renderer,CoordXCase,CoordYCase);

		count = count +1;
		// printf("#######COUNT#####\nvalue > %d\n",count);
		// printf("North 	> %c \n",nbrN);
		// printf("SEst 	> %c \n",nbrSE);
		// printf("SWest 	> %c \n",nbrSW);
		ecrireNombresMain(renderer,&nbrN,&nbrSE,&nbrSW,CoordXCase, CoordYCase);
		CoordXCase = CoordXCase + 85;
	}

	SDL_Rect rect;
	rect.x =60;
	rect.y = 150;
	rect.w = 528;
	rect.h = 500;
	SDL_RenderDrawRect(renderer,&rect);


	SDL_RenderPresent(renderer);

	SDL_bool progBool = SDL_TRUE;

	while(progBool){		
		SDL_Event event;
		while(SDL_PollEvent(&event)){
			switch(event.type)
			{
				case SDL_QUIT:
					progBool = SDL_FALSE;
					break;
				case SDL_MOUSEBUTTONDOWN:
					printf("x: %d // y: %d ",event.button.x,event.button.y);

					if(475<event.button.x && event.button.x <575 && 10<event.button.y && event.button.y<110){
						//BOUTON PIOCHE
						printf("Jai pioche chef !\n");
					} else if(600<event.button.x && event.button.x <650 && 0<event.button.y && event.button.y<50){
						//BOUTON QUITTER / MENU
						printf("Jai quitte chef...\n");
					} else if(60<event.button.x && event.button.x <588 && 150<event.button.y && event.button.y<650){
						//GRILLE
						gereClicGrille(event.button.x,event.button.y);
						printf("Grille\n");
					} else if(30<event.button.x && event.button.x <625 && 665<event.button.y && event.button.y<735){
						//MAIN
						printf("C'est la main\n");

					}else{
						printf("raté\n");
					}

					break;
				default:
					break;
			}

		}
	} 


	if(SDL_RenderClear(renderer) != 0){
		SDL_Log("Error: SDL_RenderClear > %s\n",SDL_GetError());
		exit(-1);
	}
	
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);


}

// gcc src/triominos.c -o bin/tri -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf



/** HAUT
 	(caseX-37<clicX && clicX<caseX+38 && clicY+8<caseY && caseY<clicY+23) ||
	(caseX-25<clicX && clicX<caseX+25 && clicY-7<caseY && caseY<clicY+8) ||				
	(caseX-12<clicX && clicX<caseX+13 && clicY-22<caseY && caseY<clicY-7)				
**/

/** BAS
  	(caseX-37<clicX && clicX<caseX+38 && clicY-22<caseY && caseY<clicY-7) ||
	(caseX-25<clicX && clicX<caseX+25 && clicY-7<caseY && caseY<clicY+8) ||				
	(caseX-12<clicX && clicX<caseX+13 && clicY+8<caseY && caseY<clicY+23)			
**/



// #############
// ### TESTS ###
// #############


void dessinTestHitBox(SDL_Renderer *renderer){
	int caseX = grille[0][0].coordX;
	int caseY = grille[0][0].coordY;	
	SDL_Rect rectangleTest;
	rectangleTest.x = caseX - 37;
	rectangleTest.y = caseY + 8;
	rectangleTest.w = 75;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 25;
	rectangleTest.y = caseY - 7;
	rectangleTest.w = 50;
	rectangleTest.h = 17;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 12;
	rectangleTest.y = caseY - 22;
	rectangleTest.w = 25;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);


	caseX = grille[3][0].coordX;
	caseY = grille[3][0].coordY;	
	rectangleTest.x = caseX - 37;
	rectangleTest.y = caseY - 22;
	rectangleTest.w = 75;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 25;
	rectangleTest.y = caseY - 7;
	rectangleTest.w = 50;
	rectangleTest.h = 17;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 12;
	rectangleTest.y = caseY + 8;
	rectangleTest.w = 25;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	caseX = grille[0][3].coordX;
	caseY = grille[0][3].coordY;
	rectangleTest.x = caseX - 37;
	rectangleTest.y = caseY - 22;
	rectangleTest.w = 75;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 25;
	rectangleTest.y = caseY - 7;
	rectangleTest.w = 50;
	rectangleTest.h = 17;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 12;
	rectangleTest.y = caseY + 8;
	rectangleTest.w = 25;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	caseX = grille[1][1].coordX;
	caseY = grille[1][1].coordY;	
	rectangleTest.x = caseX - 37;
	rectangleTest.y = caseY + 8;
	rectangleTest.w = 75;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 25;
	rectangleTest.y = caseY - 7;
	rectangleTest.w = 50;
	rectangleTest.h = 17;
	SDL_RenderDrawRect(renderer,&rectangleTest);

	rectangleTest.x = caseX - 12;
	rectangleTest.y = caseY - 22;
	rectangleTest.w = 25;
	rectangleTest.h = 15;
	SDL_RenderDrawRect(renderer,&rectangleTest);
}

