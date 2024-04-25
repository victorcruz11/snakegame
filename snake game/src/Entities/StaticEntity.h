#pragma once
#include "Entity.h"

class StaticEntity : public Entity {
public:
    StaticEntity(float x, float y, float w, float h);
    void update() override {};
    void draw() override;
    bool isColliding(Entity* other) override;
    void onCollision(Entity* other) override {};
protected:
    ofRectangle bounds;
};