#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include "../include/Texture.h"

static bool         init();
static bool         loadMedia();
static void         close();
static SDL_Texture* loadTexture(const char *img_path);

const int SCREEN_W = 640;
const int SCREEN_H = 480;

SDL_Window   *gWindow_w   = NULL;
SDL_Renderer *gRenderer_r = NULL;
SDL_Rect      gSprites[4];
MY::Texture   gDots_t;

int main(int argc, char **argv)
{
		printf("Hello cmake && SDL2\n");

		if( !init() )
		{
				exit(0);
		}

		if( !loadMedia() )
		{
				exit(0);
		}

		bool quit = false;
		SDL_Event e;

		while( !quit )
		{
				while(SDL_PollEvent(&e) != 0)
				{
						if(e.type == SDL_QUIT)
						{
								quit = true;
						}
				}

				SDL_SetRenderDrawColor(gRenderer_r, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer_r);

				gDots_t.render(0, 0, &gSprites[0]);
				gDots_t.render(SCREEN_W-gSprites[1].w, 0, &gSprites[1]);
				gDots_t.render(0, SCREEN_H-gSprites[2].h, &gSprites[2]);
				gDots_t.render(SCREEN_W-gSprites[3].w, SCREEN_H-gSprites[3].h, &gSprites[3]);

				SDL_RenderPresent(gRenderer_r);

		}

		close();

		printf("End.\n");
		return 0;
}

bool init()
{

		if(SDL_Init(SDL_INIT_VIDEO) == -1)
		{
				printf("SDL could not init. SDL_Error:%s\n", SDL_GetError());
				return false;
		}

		gWindow_w = SDL_CreateWindow("SDL2 and CMake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		if(gWindow_w == NULL)
		{
				printf("SDL could not CreateWindow. SDL_Error:%s\n", SDL_GetError());
				return false;
		}

		gRenderer_r = SDL_CreateRenderer(gWindow_w, -1, SDL_RENDERER_ACCELERATED);
		if(gRenderer_r == NULL)
		{
				printf("SDL could not CreateRenderer. SDL_Error:%s\n", SDL_GetError());
				return false;
		}

		SDL_SetRenderDrawColor(gRenderer_r, 0xFF, 0xFF, 0xFF, 0xFF);


		int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
		int init_flags = IMG_Init(img_flags);
		if((init_flags & img_flags) != img_flags)
		{
				printf("SDL could not IMG_Init(). IMG_Error:%s\n", IMG_GetError());
				return false;
		}

		return true;
}

bool loadMedia()
{
		if( !gDots_t.loadFromFile("../res/dots.png") )
		{
				printf("SDL could not loadTexture(). SDL_Error:%s\n", SDL_GetError()); 
				return false;
		}

		gSprites[0] = {0  , 0  , 100, 100};
		gSprites[1] = {100, 0  , 100, 100};
		gSprites[2] = {0  , 100, 100, 100};
		gSprites[3] = {100, 100, 100, 100};

 
		return true;
}


static SDL_Texture* loadTexture(const char *img_path)
{
		SDL_Texture *new_texture = NULL;

		SDL_Surface *temp_surface = IMG_Load(img_path);
		if(temp_surface == NULL)
		{
				printf("Error in IMG_Load(%s). SDL_Error:%s\n", img_path, SDL_GetError());
				return NULL;
		}

		new_texture = SDL_CreateTextureFromSurface(gRenderer_r, temp_surface);
		if(new_texture == NULL)
		{
				printf("Error in CreateTextureFromSurface() in loadTexutre(%s). SDL_Error:%s\n", img_path, SDL_GetError());
				SDL_FreeSurface(temp_surface);
				return NULL;
		}

		SDL_FreeSurface(temp_surface);
		return new_texture;
}


void close()
{
		gDots_t.free();

		SDL_DestroyRenderer(gRenderer_r);
		SDL_DestroyWindow(gWindow_w);
		gWindow_w   = NULL;
		gRenderer_r = NULL;

		IMG_Quit();
		SDL_Quit();
}
