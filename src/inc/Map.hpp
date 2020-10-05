#ifndef MAP_HPP
#define MAP_HPP

#include "Components.hpp"

class Map
{
private:

public:
    Map();
    ~Map();

    static void addTile(Manager& man, int id, int x, int y, int tile_size_width, int tile_size_height, double tile_scale);
    static void loadMap(Manager& man, std::string path, int map_size_x, int map_size_y, int tile_size_width, int tile_size_height, double tile_scale);
};

#endif