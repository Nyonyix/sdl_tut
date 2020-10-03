#include "ECS.hpp"

void Entity::addGroup(Group group)
{
    group_bitset[group] = true;
    manager.addToGroup(this, group);
}