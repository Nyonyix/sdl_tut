#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Game.hpp"
#include <chrono>

#pragma comment (lib, "C:\\dev-libs\\SDL2_image-2.0.5\\lib\\x64\\SDL2_image.lib")
#pragma comment (lib, "C:\\dev-libs\\SDL2-2.0.12\\lib\\x64\\SDL2main.lib")
#pragma comment (lib, "C:\\dev-libs\\SDL2-2.0.12\\lib\\x64\\SDL2.lib")
#pragma comment (lib, "C:\\dev-libs\\x64\\Release\\SDL2_gfx.lib")

using ulong = unsigned long int;

Game *game = nullptr;

ulong getSystemTimeMS();

int main(int argc, char* const argv[])
{
    const int TICK_TIME = 50;
    const int MAX_LOOPS = 20;
    ulong time0 = 0;
    ulong time1 = 0;
    int update_time = 0;
    bool network_game = false;
    int num_loops = 0;
    int game_render_time = 0;

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

    time0 = getSystemTimeMS();

    while (game->is_running)
    {
        game_render_time = getSystemTimeMS();
        time1 = getSystemTimeMS();
        update_time = 0;
        num_loops = 0;

        while ((time1-time0) <= TICK_TIME && num_loops < MAX_LOOPS)
        {
            update_time = getSystemTimeMS();
            game->update();
            time0 += TICK_TIME;
            update_time = getSystemTimeMS() - update_time;
            num_loops++;
        }

        game->eventHandler();
        game->render();

        if (!network_game && (time1 - time0) >= TICK_TIME)
        {
            time0 = time1 - TICK_TIME;
        }

        game_render_time = getSystemTimeMS() - game_render_time;
        

        // frame_start = SDL_GetTicks();

        // game->eventHandler();
        // game->update();
        // game->render();

        // frame_time = SDL_GetTicks() - frame_start;

        // if(frame_delay > frame_time)
        // {
        //     SDL_Delay(frame_delay - frame_time);
        // }
    }

    game->clean();

    return 0;
}

ulong getSystemTimeMS()
{
    using namespace std::chrono;

    return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

}
