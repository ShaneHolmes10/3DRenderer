
#include "forms/entity.h"


void Entity::updateSelfAndChild() {

    if(parent) {
        world_matrix = parent->world_matrix * local_transform.getMatrix();
    } else {
        world_matrix = local_transform.get_matrix();
    }

    for (auto&& child : children) {
        child->updateSelfAndChild();
    }

}

void Entity::addChild(const const TArgs&... args) {

    children.push_back(std::make_unique<Entity>(args...));
    children.back()->parent = this;

    children.back()->updateSelfAndChild();

}

void Entity::setTransform(Transform trans) {

    transform = trans;
    updateSelfAndChild();

}

void Entity::applyTransform(Transform trans) {
   
    transform = transform * trans;
    updateSelfAndChild();
    
}
