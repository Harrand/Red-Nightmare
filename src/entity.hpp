//
// Created by Harrand on 07/09/2018.
//

#ifndef REDNIGHTMARE_ENTITY_HPP
#define REDNIGHTMARE_ENTITY_HPP
#include "game_sprite.hpp"

class Player;

class EntityManager;

class Entity : public GameSprite
{
public:
    Entity(Vector2F position, float rotation, Vector2F scale, const Texture* texture);
    virtual void update(EntityManager& manager, float delta_time);
    Vector2F forward() const;
    bool is_moving() const;
    bool is_dead() const;
    unsigned int get_health() const;
    void set_health(unsigned int health);
    void add_health(unsigned int health);
    void remove_health(unsigned int health);
    const Vector2F* get_target() const;
    bool has_target() const;
    void set_target(Vector2F target);
    void remove_target();
    static constexpr unsigned int default_health = 100;
    static constexpr float default_speed = 50.0f;
protected:
    Player* get_closest_player(EntityManager& manager);
    unsigned int health;
    std::optional<Vector2F> target;
};


#endif //REDNIGHTMARE_ENTITY_HPP
