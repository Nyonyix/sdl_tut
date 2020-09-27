#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL_image.h>

GameObject* player;
GameObject* player2;

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(std::string title, int xpos, int ypox, int width, int height, bool fullscreen)
{
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem Initialised" << std::endl;

        window = SDL_CreateWindow(title.c_str(), xpos, ypox, width, height, flags);
        if(window)
        {
            std::cout << "Window Created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Active" << std::endl;
        }

        is_running = true;
    }
    player = new GameObject("res/sdl_player.png", renderer, 0, 0);
    player2 = new GameObject("res/sdl_player.png", renderer, 200, 200);
}

void Game::eventHandler()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        is_running = false;
        break;
    
    default:
        break;
    }
}

void Game::update()
{
    count++;

    player -> update();
    player2 -> update();

    std::cout << count << std::endl;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    player -> render();
    player2 -> render();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}