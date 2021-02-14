#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cstdint>


extern SDL_Renderer *gRenderer_r;

namespace MY{

		class Texture
		{
				public:
						Texture();
						~Texture();

						bool loadFromFile(const std::string &path);

						void free();

						void render(int32_t x, int32_t y, SDL_Rect *clip = NULL);

						int32_t getWidth()  const;
						int32_t getHeight() const;

				private:
						SDL_Texture *mTexture;

						int32_t mWidth;
						int32_t mHeight;
		};
};


#endif
