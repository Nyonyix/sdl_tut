#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Game.hpp"

class TextureManager
{
private:
    
public:

    static SDL_Texture* loadTexture(std::string filename);
    static void draw(SDL_Texture* tex, SDL_Rect src_rect, SDL_Rect dest_rect);
};

#endif