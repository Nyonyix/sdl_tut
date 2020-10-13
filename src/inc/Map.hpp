#ifndef MAP_HPP
#define MAP_HPP

#include "Components.hpp"

class Map
{
private:

public:
    Map();
    ~Map();

    static void addTile(Manager& man, int src_x, int src_y, int x, int y, int tile_size_width, int tile_size_height, int draw_width, int draw_height, std::string path);
    static void loadMap(Manager& man, std::string path, std::string texture_path, int map_size_x, int map_size_y, int tile_size_width, int tile_size_height, double tile_scale);
};

#endif