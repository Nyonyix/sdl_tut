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

void Map::addTile(Manager& man, int src_x, int src_y, int x, int y, int tile_size_width, int tile_size_height, int draw_width, int draw_height, std::string path)
{
    auto& tile(man.addEntity());
    tile.addComponent<TileComponent>(src_x, src_y, x, y, tile_size_width, tile_size_height, draw_width, draw_height, path);
    tile.addGroup(ECS::group_map);
}

void Map::loadMap(Manager& man, std::string path, std::string texture_path, int map_size_x, int map_size_y, int tile_size_width, int tile_size_height, double tile_scale)
{

    int scaled_x = int(tile_size_width * tile_scale);
    int scaled_y = int(tile_size_height * tile_scale);

    int src_x;
    int src_y;

    char tile;
    std::fstream map_file;
    map_file.open(path);

    for (int y = 0; y < map_size_y; y++)
    {
        for (int x = 0; x < map_size_x; x++)
        {
            map_file.get(tile);
            src_y = atoi(&tile) * tile_size_height;
            map_file.get(tile);
            src_x = atoi(&tile) * tile_size_width;
            addTile(man, src_x, src_y, x * scaled_x, y * scaled_y, tile_size_width, tile_size_height, scaled_x, scaled_y, texture_path);
            map_file.ignore();
        }
    }

    map_file.close();
}