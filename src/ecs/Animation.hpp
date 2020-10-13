#ifndef ANIMATION
#define ANIMATION

struct Animation
{
    std::string id_str;
    int index;
    int frames;
    int speed;

    Animation() {}
    Animation(std::string i_str, int i, int f, int s)
    {
        id_str = i_str;
        index = i;
        frames = f;
        speed = s;
    }
};


#endif /* ANIMATION */
