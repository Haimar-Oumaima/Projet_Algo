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


// #####################
// ### Event Handler ###
// ##################### 


// void Window::pollEvents(){
// 	SDL_Event event;

// 	if(SDL_PollEvent(&event)){
// 		if (event.type == SDL_MOUSEBUTTOMDOWN){
// 			printf("x > %d", event.motion.x);
// 			printf("y > %d", event.motion.y);
// 		}
// 	}
// }



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
	// recritureScore(30);

	int i,j;

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

	SDL_RenderPresent(renderer);

	// while (!window.isClosed()){
	// 	window.pollEvents();
	// }


	//####################################################################//
	if(SDL_RenderClear(renderer) != 0){
		SDL_Log("Error: SDL_RenderClear > %s\n",SDL_GetError());
		exit(-1);
	}
	
	SDL_Delay(25000); // en milliseconde -> 1sec = 1000 

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);


}

// gcc src/triominos.c -o bin/tri -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

/**
Notes à moi-même (à suppr):
//placement 
//void placerTriominos(int coordx,int coordy,Triominos trio)
if([i]%2 == [j]%2) //si les deux sont impairs ou les deux paires, alors on positionne d'une certaine manière
	position = haut
else
	position = bas //si une coord est pair l'autre impair, alors on positionne de l'autre

**/