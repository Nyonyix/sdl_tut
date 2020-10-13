#ifndef TILECOMP
#define TILECOMP

#include "ECS.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>

class TransformComponent;

class TileComponent : public Component
{
public:

    SDL_Texture *texture;
    SDL_Rect src_rect, dest_rect;

    TileComponent() = default;

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    TileComponent(int src_x, int src_y, int x_pos, int y_pos, int src_width, int src_height, int draw_width, int draw_height, std::string path)
    {
        texture = TextureManager::loadTexture(path);

        src_rect.x = src_x;
        src_rect.y = src_y;
        src_rect.w = src_width;
        src_rect.h = src_height;

        dest_rect.x = x_pos;
        dest_rect.y = y_pos;
        dest_rect.w = draw_width;
        dest_rect.h = draw_height;
    }

    void draw() override
    {
        TextureManager::draw(texture, src_rect, dest_rect, SDL_FLIP_NONE);
    }
};

#endif /* TILECOMP */
