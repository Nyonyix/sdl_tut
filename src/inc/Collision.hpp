#ifndef COLLISION
#define COLLISION

#include <SDL2/SDL.h>

class Collision
{
    
public:
    static bool AABB(const SDL_Rect& rect_a, const SDL_Rect& rect_b);
};

#endif /* COLLISION */
