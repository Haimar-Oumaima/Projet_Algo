//std
#include <stdio.h>
#include <stdlib.h>
//SDL
#include <SDL.h>
#include <SDL_ttf.h>


int dessinerTriangle(SDL_Renderer *renderer,int ptx, int pty){
	if(SDL_RenderDrawPoint(renderer,ptx,pty) != 0){
		SDL_Log("Error: SDL_SetRenderDrawPoint > %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDL_RenderDrawLine(renderer,ptx,pty,0,pty) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDL_RenderDrawLine(renderer,ptx,pty,2*ptx,0) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	if(SDL_RenderDrawLine(renderer,ptx,pty,2*ptx,2*pty) != 0){
		SDL_Log("Error: SDL_SetRenderDrawLine > %s\n",SDL_GetError());
		exit(-1);
	}

	return 0;
}

int main(int argc, char **argv){
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;

	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		SDL_Log("Error: SDL_INIT_VIDEO > %s\n",SDL_GetError());
		exit(-1);
	} 

	//creation rendu et fenetre 
	if(SDL_CreateWindowAndRenderer(800,800,0, &window, &renderer) !=0){//largeur,hauteur,windows_flag,SDL_Window, SDL_Renderer
		SDL_Log("Error: SDL_CreateWindowAndRenderer > %s\n",SDL_GetError());
		exit(-1);
	}

	int pointCentralX = 400;
	int pointCentralY = 400;

	if(dessinerTriangle(pointCentralX,pointCentralY) !=0){
		SDL_Log("Error: dessinerTriangle ");
		exit(-1);
	}



	SDL_RenderPresent(renderer);

	if(SDL_RenderClear(renderer) != 0){
		SDL_Log("Error: SDL_RenderClear > %s\n",SDL_GetError());
		exit(-1);
	}



	SDL_Delay(5000); // en milliseconde -> 1sec = 1000 

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
}

// gcc src/test.c -o bin/progtest -I include -L lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf