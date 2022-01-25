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

typedef struct Main{
	Triominos main[7];
}





Case grille[9][9]; // grille de jeu avec les coordonnées
// Triominos grillePlacement[9][9]; //grille de placement des triminos






int dessinerTriangleHaut(SDL_Renderer* renderer ,int x, int y, int xmod,int ymod){
	/**
	 * (125,75) = (x,y)
	 * Each point:
	 * N: =  (x,y-20)
	 * SE: = (x+25,y+20)
	 * SW: = (x-25,y+20)
	 *
	 * x = horizontal
	 * y = vertical
	 **/  

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
	/**
	 * S: =  (x,y+20)
	 * NE: = (x+25,y-20)
	 * NW: = (x-25,y-20)
	 * x = horizontal
	 * y = vertical
	 **/  


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




int main(int argc, char **argv){
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		SDL_Log("Error: SDL_INIT_VIDEO > %s\n",SDL_GetError());
		exit(-1);
	} 

	//creation rendu et fenetre 
	if(SDL_CreateWindowAndRenderer(600,800,0, &window, &renderer) !=0){//largeur,hauteur,windows_flag,SDL_Window, SDL_Renderer
		SDL_Log("Error: SDL_CreateWindowAndRenderer > %s\n",SDL_GetError());
		exit(-1);
	}

	SDL_Rect rectangle;
	rectangle.x = 50;
	rectangle.y = 100;
	rectangle.w = 500; // weight
	rectangle.h = 500; // height

	if(SDL_SetRenderDrawColor(renderer,0,0,255,SDL_ALPHA_OPAQUE) != 0){
		SDL_Log("Error: SDL_SetRenderDrawColor > %s\n",SDL_GetError());
		exit(-1);
	}

	//Version vide
	if(SDL_RenderDrawRect(renderer, &rectangle) != 0){
		SDL_Log("Error: SDL_SetRenderDrawRect > %s\n",SDL_GetError());
		exit(-1);
	}

	SDL_RenderPresent(renderer);

	if(SDL_SetRenderDrawColor(renderer,0,255,0,SDL_ALPHA_OPAQUE) != 0){
		SDL_Log("Error: SDL_SetRenderDrawColor > %s\n",SDL_GetError());
		exit(-1);
	}

	SDL_RenderPresent(renderer);

	int CoordXCase = 25;
	int CoordYCase = 75;

	int i,j;

	//grille
	for(i=0; i<10; i++){
		CoordYCase = 75;
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

	//Une main de jeu: à titre indicatif
	CoordXCase = 45;
	CoordYCase = 700;

	for(i=0;i<7;i++){
		dessinerTriangleMain(renderer,CoordXCase,CoordYCase);
		CoordXCase = CoordXCase + 85;
	}



	SDL_RenderPresent(renderer);


	//####################################################################//
	if(SDL_RenderClear(renderer) != 0){
		SDL_Log("Error: SDL_RenderClear > %s\n",SDL_GetError());
		exit(-1);
	}
	
	SDL_Delay(10000); // en milliseconde -> 1sec = 1000 

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


############
GRILLE pour un écran de 600*800
Grille Coin Haut Gauche : (50,100)
Grille Coin Haut Droit : (550,100)
Grille Coin Bas Gauche : (50,600)
Grille Coin Bas Droit : (550,600)



###################
// loop to draw point at every center of each case in the grid
	for(i=0; i<10; i++){
		CoordYCase = 75;
		CoordXCase = CoordXCase + 50;
		for(j=0;j<10;j++){
			CoordYCase = CoordYCase +50;
			if(SDL_RenderDrawPoint(renderer,CoordXCase,CoordYCase) != 0){
				SDL_Log("Error: SDL_SetRenderDrawPoint > %s\n",SDL_GetError());
				exit(-1);
			}
			dessinerTriangle(&renderer,CoordXCase,CoordYCase);
		SDL_RenderPresent(renderer);
		}
	}








**/