#include "../include/Texture.h"




namespace MY{
		Texture::Texture():
				mTexture{NULL},
				mWidth{0},
				mHeight{0}
		{
		}

		Texture::~Texture()
		{
				Texture::free();
		}

		bool Texture::loadFromFile(const std::string &path)
		{
				Texture::free();

				SDL_Texture *new_texture = NULL;

				SDL_Surface *temp_surface = IMG_Load(path.c_str()); 
				if(temp_surface == NULL)
				{
						fprintf(stderr, "ERROR in IMG_Load(%s) in loadFromFile(). SDL_Error%s\n", path.c_str(), IMG_GetError());
						return false;
				}
				SDL_SetColorKey(temp_surface, SDL_TRUE, SDL_MapRGB(temp_surface->format, 0x00, 0xFF, 0xFF));
				new_texture = SDL_CreateTextureFromSurface(gRenderer_r, temp_surface); 
				if(new_texture == NULL)
				{
						fprintf(stderr, "ERROR in SDL_CreateTextureFromSurface() in loadFromFile(%s). SDL_Error%s\n", path.c_str(), SDL_GetError());
						SDL_FreeSurface(temp_surface);
						return false;
				}

				Texture::mWidth   = temp_surface->w;
				Texture::mHeight  = temp_surface->h;
				Texture::mTexture = new_texture;
				SDL_FreeSurface(temp_surface);
				
				return true;

		}

		void Texture::free()
		{
				if(Texture::mTexture != NULL)
				{
						SDL_DestroyTexture(Texture::mTexture);
						mTexture = NULL;
						mWidth   = 0;
						mHeight  = 0;
				}
		}

		void Texture::render(int32_t x, int32_t y)
		{
				SDL_Rect rect = {x, y, Texture::mWidth, Texture::mHeight};
				SDL_RenderCopy(gRenderer_r, Texture::mTexture, NULL, &rect);
		}

		int32_t Texture::getWidth() const
		{
				return Texture::mWidth;
		}

		int32_t Texture::getHeight() const
		{
				return Texture::mHeight;
		}

};



