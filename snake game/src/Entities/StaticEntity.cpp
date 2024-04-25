#include "StaticEntity.h"

StaticEntity::StaticEntity(float x, float y, float w, float h) : bounds(x, y, w, h) {}

void StaticEntity::draw() {
    ofSetColor(ofColor::red);
    ofDrawRectangle(bounds);
}

bool StaticEntity::isColliding(Entity* other) {
    StaticEntity* staticEntity = dynamic_cast<StaticEntity*>(other);
    if (staticEntity != nullptr) {
        return bounds.intersects(staticEntity->bounds);
    }
    return false;
}
