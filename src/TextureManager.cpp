#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(std::string filename, SDL_Renderer* ren)
{
    SDL_Surface* temp_surface = IMG_Load(filename.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, temp_surface);
    SDL_FreeSurface(temp_surface);
    return tex;
}