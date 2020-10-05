#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(std::string filename)
{
    SDL_Surface* temp_surface = IMG_Load(filename.c_str());
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, temp_surface);
    SDL_FreeSurface(temp_surface);
    return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect src_rect, SDL_Rect dest_rect, SDL_RendererFlip flip)
{
    SDL_RenderCopyEx(Game::renderer, tex, &src_rect, &dest_rect, NULL, NULL, flip);
}