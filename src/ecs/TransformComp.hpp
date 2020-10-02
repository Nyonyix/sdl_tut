#ifndef TRANSFORMCOMP
#define TRANSFORMCOMP

#include "ECS.hpp"
#include "Vector2D.hpp"

class TransformComponent : public Component
{
public:

    Vector2D position;
    Vector2D velocity;

    int speed = 3;
    int hight = 64;
    int width = 64;
    int scale = 1;

    TransformComponent() 
    {
        position.x = 0;
        position.y = 0;
    }

    TransformComponent(double x, double y) 
    {
        position.x = x;
        position.y = y;
    }

    TransformComponent(double x, double y, int h, int w, int in_scale) 
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
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }
};

#endif /* POSITIONCOMP */