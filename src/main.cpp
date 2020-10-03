#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

#pragma comment (lib, "C:\\dev-libs\\SDL2_image-2.0.5\\lib\\x86\\SDL2_image.lib")
#pragma comment (lib, "C:\\dev-libs\\SDL2-2.0.12\\lib\\x86\\SDL2main.lib")
#pragma comment (lib, "C:\\dev-libs\\SDL2-2.0.12\\lib\\x86\\SDL2.lib")

Game *game = nullptr;

int main(int argc, char const *argv[])
{

    const int fps = 144;
    const int frame_delay = 1000 / fps;

    Uint32 frame_start;
    int frame_time;

    game = new Game();
    game->init("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    while (game->running())
    {
        frame_start = SDL_GetTicks();

        game->eventHandler();
        game->update();
        game->render();

        frame_time = SDL_GetTicks() - frame_start;

        if(frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }
    }

    game->clean();

    return 0;
}
