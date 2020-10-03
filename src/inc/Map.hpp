#ifndef MAP_HPP
#define MAP_HPP

#include "Components.hpp"

class Map
{
private:

public:
    Map();
    ~Map();

    static void addTile(Manager& man, int id, int x, int y);
    static void loadMap(Manager& man, std::string path, int size_x, int size_y);
};

#endif