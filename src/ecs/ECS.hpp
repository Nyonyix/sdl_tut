#ifndef ECS_HPP
#define ECS_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

namespace ECS{
    enum group_label : std::size_t
    {
        group_map,
        group_players,
        group_enemies,
        group_colliders
    };
}

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getNewComponentTypeID()
{
    static ComponentID last_id = 0u;
    return last_id++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept
{
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr std::size_t max_components = 32;
constexpr std::size_t max_groups = 32;

using ComponentBitSet = std::bitset<max_components>;
using GroupBitSet = std::bitset<max_groups>;

using ComponentArray = std::array<Component*, max_components>;

class Component
{
private:
    
public:
    //Component();
    virtual ~Component() {}

    Entity* entity;
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}
};

class Entity
{
private:
    Manager& manager;
    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray component_array;
    ComponentBitSet component_bitset;
    GroupBitSet group_bitset;
    
public:

    Entity(Manager& manager) : manager(manager) {}

    void update()
    {
        for (auto& c : components) c -> update();
    }

    void draw() 
    {
        for (auto& c : components) c -> draw();
    }
    bool isActive() {return active;}
    void destroy() {active = false;}

    bool hasGroup(Group m_group)
    {
        return group_bitset[m_group];
    }

    void addGroup(Group group);

    void delGroup(Group group)
    {
        group_bitset[group] = false;
    }

    template<typename T> bool hasComponent() const
    {
        return component_bitset[getComponentTypeID<T>()];
    }

    template<typename T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c -> entity = this;
        std::unique_ptr<Component> uPtr{ c };
        components.emplace_back(std::move(uPtr));

        component_array[getComponentTypeID<T>()] = c;
        component_bitset[getComponentTypeID<T>()] = true;

        c -> init();
        return *c;
    }

    template<typename T> T& getComponent() const
    {
        auto ptr(component_array[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager
{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, max_groups> grouped_entities;
  
public:
    void update()
    {
        for (auto& e : entities) e -> update();
    }
    void draw()
    {
        for (auto& e : entities) e -> draw();
    }

    void refresh()
    {
        for (auto i(0u); i < max_groups; i++)
        {
            auto& v(grouped_entities[i]);
            v.erase
            (
                std::remove_if(std::begin(v), std::end(v), 
                [i](Entity* mEntity)
                {
                    return !mEntity -> isActive() || !mEntity -> hasGroup(i);

                }),
                std::end(v));
        }

        entities.erase(std::remove_if(std::begin(entities), std::end(entities), 
        [](const std::unique_ptr<Entity> &mEntity)
        {
            return !mEntity -> isActive();
        }),
        std::end(entities));
    }

    void addToGroup(Entity* entity, Group group)
    {
        grouped_entities[group].emplace_back(entity);
    }

    std::vector<Entity*>& getGroup(Group group)
    {
        return grouped_entities[group];
    }

    Entity& addEntity()
    {
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{ e };
        entities.emplace_back(std::move(uPtr));
        return *e;
    }

};

#endif