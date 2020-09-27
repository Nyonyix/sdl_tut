#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Game.hpp"

class GameObject
{
private:

    int xpos;
    int ypos;

    SDL_Texture* obj_texture;
    SDL_Rect src_rect, dest_rect;
    SDL_Renderer* renderer;
    
public:
    GameObject(std::string texture_sheet, SDL_Renderer* ren, int x, int y);
    ~GameObject();

    void update();
    void render();
};

#endif