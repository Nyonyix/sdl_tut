#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include <SDL2/SDL_image.h>
#include "Collision.hpp"
#include "Animation.hpp"
#include <map>

Map* map;
Manager manager;
SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

auto& Player(manager.addEntity());
auto& Wall(manager.addEntity());

std::vector<ColliderComponent*> Game::colliders;

bool Game::is_running = false;

auto& tiles(manager.getGroup(ECS::group_map));
auto& players(manager.getGroup(ECS::group_players));
auto& enemies(manager.getGroup(ECS::group_enemies));

Game::Game()
{
}

Game::~Game()
{
}

void Game::init(std::string title, int xpos, int ypos, int width, int height, Uint32 flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout << "Subsystem Initialised" << std::endl;

        window = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);
        if(window)
        {
            std::cout << "Window Created" << std::endl;
            is_running = true;
        }
        else
        {
            std::cout << "Window Failed\n" << SDL_GetError() <<std::endl;
            std::cout << "Window Info: \n" << "xpos: " << xpos << '\n' 
            << "ypos: " << ypos << '\n' << "width: " << width << '\n'
            << "height" << height << '\n' << "flags: " << flags << std::endl;
            is_running = false;
        }
        

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer Active" << std::endl;
            is_running = true;
        }
        else
        {
            std::cout << "Renderer Failed\n" << SDL_GetError() << std::endl;
            is_running = false;
        }
    }
    map = new Map();

    Map::loadMap(manager, "res/map.csv", "res/terrain_texture_map.png", 32, 32 , 64, 64, 0.5);

    Animation walk = Animation("walk", 1, 5, 200);
    Animation idle = Animation("idle", 0, 4, 200);
    
    std::vector<Animation> anim_list;
    anim_list.push_back(walk);
    anim_list.push_back(idle);

    Player.addComponent<TransformComponent>(window, 1);
    Player.addComponent<SpriteComponent>("res/sdl_player_anim.png", anim_list);
    Player.getComponent<SpriteComponent>().play("idle");
    Player.addComponent<KeyboardController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(ECS::group_players);

    Wall.addComponent<TransformComponent>(0, 250, 64, 1000, 1);
    Wall.addComponent<SpriteComponent>("res/dirt.png");
    Wall.addComponent<ColliderComponent>("wall");

    
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

    Vector2D player_velocity = Player.getComponent<TransformComponent>().velocity;
    int player_speed = Player.getComponent<TransformComponent>().speed;

    for (auto t : tiles)
    {
        t -> getComponent<TileComponent>().dest_rect.x += -(player_velocity.x * player_speed);
        t -> getComponent<TileComponent>().dest_rect.y += -(player_velocity.y * player_speed);
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);

    for (auto& t : tiles)
    {
        t -> draw();
    }

    for (auto& p : players)
    {
        p -> draw();
    }

    for (auto& e : enemies)
    {
        e -> draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game Cleaned" << std::endl;
}