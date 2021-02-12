#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

static bool init();
static bool loadMedia();
static void close();
static SDL_Surface *loadSurface(const char *img_path);


const int SCREEN_W = 640;
const int SCREEN_H = 480;

SDL_Window  *gWindow_w = NULL;
SDL_Surface *gWindow_s = NULL;
SDL_Surface *gImage_s  = NULL;

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

				SDL_Rect rect;
				rect.x = 0;
				rect.y = 0;
				rect.w = SCREEN_W;
				rect.h = SCREEN_H;
				SDL_BlitScaled(gImage_s, NULL, gWindow_s, &rect);
				SDL_UpdateWindowSurface(gWindow_w);
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

		int img_flags = IMG_INIT_JPG;
		int init_flags = IMG_Init(img_flags);
		if((init_flags & img_flags) != img_flags)
		{
				printf("SDL could not IMG_Init(). IMG_Error:%s\n", IMG_GetError());
				return false;
		}

		gWindow_s = SDL_GetWindowSurface(gWindow_w);
		return true;
}

bool loadMedia()
{
		gImage_s = loadSurface("../res/img1.jpg");
		if(gImage_s == NULL)
		{
				printf("SDL could not loadSurface(). SDL_Error:%s\n", SDL_GetError());
				return false;
		}
		return true;
}

static SDL_Surface *loadSurface(const char *img_path)
{
		SDL_Surface *window_format_surface = NULL;

		SDL_Surface *loaded_surface = IMG_Load(img_path);
		if(loaded_surface == NULL)
		{
				fprintf(stderr, "ERROR in IMG_load(%s). IMG_Error:%s\n", img_path, IMG_GetError());
				return NULL;
		}

		window_format_surface = SDL_ConvertSurface(loaded_surface, gWindow_s->format, 0);
		if(window_format_surface == NULL)
		{
				fprintf(stderr, "ERROR in SDL_ConvertSurface() in loadSurface(%s). SDL_Error:%s\n", img_path, IMG_GetError());
				SDL_FreeSurface(loaded_surface);
				return NULL;
		}
		SDL_FreeSurface(loaded_surface);

		return window_format_surface;
}

void close()
{
		SDL_FreeSurface(gImage_s);
		gImage_s = NULL;

		SDL_DestroyWindow(gWindow_w);
		gWindow_w = NULL;

		SDL_Quit();
}
