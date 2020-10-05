#ifndef TILECOMP
#define TILECOMP

#include "ECS.hpp"
#include "Components.hpp"
#include <SDL2/SDL.h>

class TransformComponent;

class TileComponent : public Component
{
public:

    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tile_rect;
    int tile_id;
    std::string path;
    double scale;

    TileComponent() = default;

    TileComponent(int x, int y, int w, int h, int id, double in_scale)
    {
        tile_rect.x = x;
        tile_rect.y = y;
        tile_rect.w = w;
        tile_rect.h = h;
        tile_id = id;
        scale = in_scale;

        switch (tile_id)
        {
        case 0:
            path = "res/grass_bottom.png";
            break;

        case 1:
            path = "res/grass_middle.png";
            break;

        case 2:
            path = "res/grass_right.png";
            break;
        
        default:
            break;
        }
    }

    void init() override
    {
        entity -> addComponent<TransformComponent>((double)tile_rect.x, (double)tile_rect.y, tile_rect.w, tile_rect.h, scale);
        transform = &entity -> getComponent<TransformComponent>();

        entity -> addComponent<SpriteComponent>(path);
        sprite = &entity -> getComponent<SpriteComponent>();
    }

};

#endif /* TILECOMP */
