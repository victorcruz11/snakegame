#pragma once
#include "ofMain.h"

class Entity {
public:
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual bool isColliding(Entity* other) = 0;
    virtual void onCollision(Entity* other) = 0;
    virtual ~Entity() {};
};