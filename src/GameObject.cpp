#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(std::string texture_sheet, SDL_Renderer* ren, int x, int y)
{
    renderer = ren;
    obj_texture = TextureManager::loadTexture(texture_sheet, ren);

    xpos = x;
    ypos = y;
}

void GameObject::update()
{
    xpos++;
    ypos++;

    src_rect.h = 64;
    src_rect.w = 64;
    src_rect.x = 0;
    src_rect.y = 0;

    dest_rect.x = xpos;
    dest_rect.y = ypos;
    dest_rect.w = src_rect.w * 2;
    dest_rect.h = src_rect.h * 2;
}

void GameObject::render()
{
    SDL_RenderCopy(renderer, obj_texture, &src_rect, &dest_rect);
}