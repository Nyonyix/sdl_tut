#ifndef TRANSFORMCOMP
#define TRANSFORMCOMP

#include "ECS.hpp"
#include "Vector2D.hpp"
#include <SDL2/SDL.h>

class TransformComponent : public Component
{
public:

    Vector2D position;
    Vector2D velocity;

    int speed = 3;
    int hight = 64;
    int width = 64;
    double scale = 1;

    TransformComponent() 
    {
        position.x = 0;
        position.y = 0;
    }

    TransformComponent(SDL_Window* win, int in_scale)
    {
        SDL_DisplayMode DM;
        SDL_GetCurrentDisplayMode(0, &DM);
        int win_width = DM.w;
        int win_height = DM.h;

        position.x = int(win_width / 2);
        position.y = int(win_height / 2);
        scale = in_scale;
    }

    TransformComponent(double x, double y) 
    {
        position.x = x;
        position.y = y;
    }

    TransformComponent(double x, double y, int h, int w, double in_scale) 
    {
        position.x = x;
        position.y = y;
        hight = h;
        width = w;
        scale = in_scale;
    }

    void init() override
    {
        velocity.x = 0;
        velocity.y = 0;
    }

    void update() override
    {

    }
};

#endif /* POSITIONCOMP */