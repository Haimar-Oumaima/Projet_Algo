//std
#include <stdio.h>
#include <stdlib.h>
//SDL
#include <SDL.h>
#include <SDL_ttf.h>

int main(int argc, char **argv){
	
	// Initialisation
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		SDL_Log("Error: SDL_INIT_VIDEO > %s\n",SDL_GetError());
		exit(-1);
	} 

	//Program's body
	/**

	// creation fenetre
	window = SDL_CreateWindow(
		"Fenetre SDL2", 
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		600,800,0);

	if(window == NULL){
		SDL_Log("Error: SDL_CreateWindow > %s\n",SDL_GetError());
		exit(-1);
	}


	//creation rendu
	renderer = SDL_CreateRenderer(
		window, //la fenetre de rendu
		-1, // gestion driver, usuel = -1
		SDL_RENDERER_SOFTWARE // flags
	);

	if(renderer == NULL){
		SDL_Log("Error: SDL_CreateRenderer > %s\n",SDL_GetError());
		exit(-1);
	}

	**/

	//creation rendu et fenetre 
	if(SDL_CreateWindowAndRenderer(600,800,0, &window, &renderer) !=0){//largeur,hauteur,
		SDL_Log("Error: SDL_CreateWindowAndRenderer > %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDL_SetRenderDrawColor(renderer,128,128,255,SDL_ALPHA_OPAQUE) != 0){
		SDL_Log("Error: SDL_SetRenderDrawColor > %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDL_RenderDrawPoint(renderer,100,400) != 0){
		SDL_Log("Error: SDL_SetRenderDrawPoint > %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDL_RenderDrawLine(renderer,100,100,150,100) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	SDL_Rect rectangle;
	rectangle.x = 0;
	rectangle.y = 50;
	rectangle.w = 200; // weight
	rectangle.h = 100; // height

	//Version vide
	if(SDL_RenderDrawRect(renderer, &rectangle) != 0){
		SDL_Log("Error: SDL_SetRenderDrawRect > %s\n",SDL_GetError());
		exit(-1);
	}

	//Version remplie
	if(SDL_RenderFillRect(renderer, &rectangle) != 0){
		SDL_Log("Error: SDL_SetRenderFillRect > %s\n",SDL_GetError());
		exit(-1);
	}





	SDL_RenderPresent(renderer);

	if(SDL_RenderClear(renderer) != 0){
		SDL_Log("Error: SDL_RenderClear > %s\n",SDL_GetError());
		exit(-1);
	}

	/**
	if (TTF_Init() < 0) {
		SDL_Log("Error: TTF_Init > %s\n",SDL_GetError());
		exit(-1);
	}
	**/


	SDL_Delay(5000); // en milliseconde -> 1sec = 1000 



	// Exit 
	/**TTF_Quit();**/
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

/** 
 * COMPILATION:
 *  gcc src/testsdl.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf
**/