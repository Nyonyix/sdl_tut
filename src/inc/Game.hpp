#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Game
{
private:
    
    int count = 0;
    bool is_running;
    SDL_Window *window;
    
public:
    Game();
    ~Game();

    void init(std::string title, int xpos, int ypox, int width, int height, bool fullscreen);

    void eventHandler();
    void update();
    void render();
    void clean();

    static SDL_Renderer *renderer;
    static SDL_Event event;

    bool running() {return is_running;}

};

#endif