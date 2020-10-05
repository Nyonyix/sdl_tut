#ifndef SPRITECOMP
#define SPRITECOMP

#include "Components.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include "Animation.hpp"
#include <map>
#include <random>

class TileComponent;

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

    SDL_RendererFlip sprite_flip = SDL_FLIP_NONE;


    SpriteComponent() = default;
    SpriteComponent(std::string path)
    {
        setTexture(path);
    }

    SpriteComponent(std::string path, std::vector<Animation> anim_list)
    {
        animated = true;

        for (auto m : anim_list)
        {
            animations.emplace(m.id_str, m);
        }

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
        dest_rect.w = int(transform -> width * transform -> scale);
        dest_rect.h = int(transform -> hight * transform -> scale); 
    }

    void draw() override
    {

        /* if (entity -> hasComponent<TileComponent>())
        {

            std::default_random_engine gen;
            std::uniform_int_distribution<int> dist(0, 1);

            int rand_int = dist(gen);

            switch (rand_int)
            {
            case 0:
                sprite_flip = SDL_FLIP_HORIZONTAL;
                break;

            case 1:
                sprite_flip = SDL_FLIP_VERTICAL;
                break;
            
            default:
                break;
            }


        } */

        TextureManager::draw(texture, src_rect, dest_rect, sprite_flip);
    }

    void play(std::string anim_name)
    {
        frames = animations[anim_name].frames;
        anim_index = animations[anim_name].index;
        speed = animations[anim_name].speed;
    }

};

#endif /* SPRITECOMP */