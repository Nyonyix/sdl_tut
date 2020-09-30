#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include <SDL2/SDL_image.h>

Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
auto& Player(manager.addEntity());

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
    map = new Map();

    Player.addComponent<TransformComponent>();
    Player.addComponent<SpriteComponent>("res/sdl_player.png");
    Player.addComponent<KeyboardController>();
    
}

void Game::eventHandler()
{
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
    manager.refresh();
    manager.update();
}

void Game::render()
{
    SDL_RenderClear(renderer);
    map -> drawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}