#include "Map.hpp"
#include "TextureManager.hpp"
#include "ECS.hpp"
#include <fstream>

Map::Map()
{
}

Map::~Map()
{
}

void Map::addTile(Manager& man, int id, int x, int y, int tile_size_width, int tile_size_height, double tile_scale)
{
    auto& tile(man.addEntity());
    tile.addComponent<TileComponent>(x, y, tile_size_width, tile_size_height, id, tile_scale);
    tile.addGroup(ECS::group_map);
}

void Map::loadMap(Manager& man, std::string path, int map_size_x, int map_size_y, int tile_size_width, int tile_size_height, double tile_scale)
{

    int scaled_x = int(tile_size_width * tile_scale);
    int scaled_y = int(tile_size_height * tile_scale);

    char tile;
    std::fstream map_file;
    map_file.open(path);

    for (int y = 0; y < map_size_y; y++)
    {
        for (int x = 0; x < map_size_x; x++)
        {
            map_file.get(tile);
            addTile(man, atoi(&tile), x * scaled_x, y * scaled_y, tile_size_width, tile_size_height, tile_scale);
            map_file.ignore();
        }
    }

    map_file.close();
}