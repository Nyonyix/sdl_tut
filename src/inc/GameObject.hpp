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
    
public:
    GameObject(std::string texture_sheet, int x, int y);
    ~GameObject();

    void update();
    void render();
};

#endif