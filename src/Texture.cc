#include "Texture.h"




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

		void Texture::free()
		{
				if(Texture::mTexture != NULL)
				{
						SDL_DestroyTexture(Texture::mTexture);
						mWidth  = 0;
						mHeight = 0;
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

		int32_t gTexture::etHeight() const
		{
				return Texture::mHeight;
		}

};



