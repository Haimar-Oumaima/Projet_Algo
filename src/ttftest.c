//std
#include <stdio.h>
#include <stdlib.h>
//SDL
#include <SDL.h>
#include <SDL_ttf.h>

// SOURCE CODE : https://www.willusher.io/sdl2%20tutorials/2013/12/18/lesson-6-true-type-fonts-with-sdl_ttf


/**
* Render the message we want to display to a texture for drawing
* @param message The message we want to display
* @param fontFile The font we want to use to render the text
* @param color The color we want the text to be
* @param fontSize The size we want the font to be
* @param renderer The renderer to load the texture in
* @return An SDL_Texture containing the rendered message, or nullptr if something went wrong
*/

SDL_Texture* renderText(const std::string &message, const std::string &fontFile,SDL_Color color, int fontSize, SDL_Renderer *renderer){

	// open font
	TTF_Font *font = TTF_OpenFont(fontFile.c_str(),fontSize);
	if(font==nullptr){
		SDL_Log("Error: font = nullptr> %s\n",SDL_GetError() );
		return nullptr;
	}

	SDL_Surface *surf = TTF_Rendertext_Blended(font, message.c_str(),color);
	if(surf==nullptr){
		TTF_CloseFont(font);
		SDL_Log("Error: surf = nullptr> %s\n",SDL_GetError() );
		return nullptr;
	}

	SDL_Texture *tecture = SDL_CreateTextureFromSurface(renderer,surf);
	if(texture==nullptr){
		SDL_Log("Error: texture = nullptr> %s\n",SDL_GetError() );
	}

	SDL_FreeSurface(surf);
	TTF_CloseFont(font);
	return texture;

}

int main(int argc, char **argv){

	if (TTF_Init() != 0){
		SDL_Log("Error : TTF_Init > %s\n",SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	

}