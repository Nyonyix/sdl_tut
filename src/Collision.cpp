#include "Collision.hpp"
#include "ColliderComp.hpp"

bool Collision::AABB(const SDL_Rect& rect_a, const SDL_Rect& rect_b)
{
    int rect_a_space_x = rect_a.x + rect_a.w;
    int rect_a_space_y = rect_a.y + rect_a.h;

    int rect_b_space_x = rect_b.x + rect_b.w;
    int rect_b_space_y = rect_b.y + rect_b.h;

    if(rect_a_space_x >= rect_b.x &&
        rect_b_space_x >= rect_a.x &&
        rect_a_space_y >= rect_b.y &&
        rect_b_space_y >= rect_a.y)
        {
            return true;
        }
        else
        {
            return false;
        }
        
    
}

bool Collision::AABB(const ColliderComponent& col_a, const ColliderComponent& col_b)
{
    if (AABB(col_a.collider, col_b.collider))
    {
        std::cout << col_a.tag << "Hit: " << col_b.tag << std::endl;
        return true;
    }
    else
    {
        return false;
    }
    
}