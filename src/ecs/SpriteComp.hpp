#ifndef SPRITECOMP
#define SPRITECOMP

#include "Components.hpp"
#include "TextureManager.hpp"
#include "TransformComp.hpp"
#include <SDL2/SDL.h>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect src_rect, dest_rect;

public:
    SpriteComponent() = default;
    SpriteComponent(std::string path)
    {
        setTexture(path);
    }

    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void setTexture(std::string path)
    {
        texture = TextureManager::loadTexture(path);
    }

    void init() override
    {

        transform = &entity -> getComponent<TransformComponent>();

        src_rect.x = src_rect.y = 0;
        src_rect.w = transform -> width;
        src_rect.h = transform -> hight;

    }

    void update() override
    {
        dest_rect.x = (int)transform -> position.x;
        dest_rect.y = (int)transform -> position.y;
        dest_rect.w = transform -> width * transform -> scale;
        dest_rect.h = transform -> hight * transform -> scale;
    }

    void draw() override
    {
        TextureManager::draw(texture, src_rect, dest_rect);
    }

};

#endif /* SPRITECOMP */