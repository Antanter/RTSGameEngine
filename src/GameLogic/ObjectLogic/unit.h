#pragma once

#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <algorithm>

class Entity : public GameObject {
    protected:
        float maxHealth;
        float health;
    
        float armor;
        float attackPower;
        float damage;
        bool isAlive;
    
        float range;
        float cooldown;
    
        float speed;
        float acceleration;
    
    public:
        Entity(float maxHp) : maxHealth(maxHp), health(maxHp) {}
        bool IsAlive() const { return isAlive; }
    
        virtual void TakeDamage(float amount) {
            health -= amount;
            if (health <= 0) Die();
        };
        virtual void Die() = 0;
        virtual ~Entity() {}
    };

class AIControlledEntity : public Entity {
    protected:

    //AIController* aiController;

    public:

    void update(float deltaTime) override;
};
    
class PlayerControlledEntity : public Entity {
    protected:

    //PlayerInput* input;

    public:

    void update(float deltaTime) override;
};

class ArtificialEntity : public Entity {
    public:

    void update(float deltaTime) override;
};