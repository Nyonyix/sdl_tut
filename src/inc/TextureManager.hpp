#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include "Game.hpp"

class TextureManager
{
private:
    
public:

    static SDL_Texture* loadTexture(std::string filename, SDL_Renderer* ren);

};

#endif