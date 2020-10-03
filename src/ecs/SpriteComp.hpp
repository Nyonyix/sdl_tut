#ifndef SPRITECOMP
#define SPRITECOMP

#include "Components.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect src_rect, dest_rect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:

    int anim_index = 0;

    std::map<std::string, Animation> animations;


    SpriteComponent() = default;
    SpriteComponent(std::string path)
    {
        setTexture(path);
    }

    SpriteComponent(std::string path, bool is_animated)
    {
        animated = is_animated;

        Animation idle = Animation(0, 4, 200);
        Animation walk = Animation(1, 4, 300);

        animations.emplace("idle", idle);
        animations.emplace("walk", walk);

        play("walk");

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

        if (animated)
        {
            src_rect.x = src_rect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        src_rect.y = anim_index * transform -> hight;

        dest_rect.x = (int)transform -> position.x;
        dest_rect.y = (int)transform -> position.y;
        dest_rect.w = transform -> width * transform -> scale;
        dest_rect.h = transform -> hight * transform -> scale;
    }

    void draw() override
    {
        TextureManager::draw(texture, src_rect, dest_rect);
    }

    void play(std::string anim_name)
    {
        frames = animations[anim_name].frames;
        anim_index = animations[anim_name].index;
        speed = animations[anim_name].speed;
    }

};

#endif /* SPRITECOMP */