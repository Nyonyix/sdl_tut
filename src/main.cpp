#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"

#pragma comment (lib, "C:\\dev-libs\\SDL2_image-2.0.5\\lib\\x86\\SDL2_image.lib")
#pragma comment (lib, "C:\\dev-libs\\SDL2-2.0.12\\lib\\x86\\SDL2main.lib")
#pragma comment (lib, "C:\\dev-libs\\SDL2-2.0.12\\lib\\x86\\SDL2.lib")

Game *game = nullptr;

int main(int argc, char* const argv[])
{

    const int fps = 60;
    const int frame_delay = 1000 / fps;

    Uint32 frame_start;
    int frame_time;

    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    Uint32 win_flags = 0;
    int win_width = 800;
    int win_height = 640;

    if (argc > 1)
    {
        if (argv[1] == std::string("-f") || argv[1] == std::string("-fullscreen"))
        {
            if (argc == 4)
            {
                win_flags = SDL_WINDOW_FULLSCREEN;
                win_width = SDL_atoi(argv[2]);
                win_height = SDL_atoi(argv[3]);
            }
            else
            {
                win_flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
            }
        }
    }

    game = new Game();
    game->init("Test Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_width, win_height, win_flags);

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
