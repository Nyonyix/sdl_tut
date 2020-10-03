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

void Map::addTile(Manager& man, int id, int x, int y)
{
    auto& tile(man.addEntity());
    tile.addComponent<TileComponent>(x, y, 64, 64, id);
    tile.addGroup(ECS::group_map);
}

void Map::loadMap(Manager& man, std::string path, int size_x, int size_y)
{
    char tile;
    std::fstream map_file;
    map_file.open(path);

    for (int y = 0; y < size_y; y++)
    {
        for (int x = 0; x < size_x; x++)
        {
            map_file.get(tile);
            addTile(man, atoi(&tile), x * 64, y * 64);
            map_file.ignore();
        }
    }

    map_file.close();
}