
#include "forms/entity.h"


void Entity::updateSelfAndChild() {

    if(parent) {
        world_matrix = parent->world_matrix * local_matrix;
    } else {
        world_matrix = local_matrix;
    }

    for (auto&& child : children) {
        child->updateSelfAndChild();
    }

}

void Entity::setTransform(Transform trans) {

    local_matrix = trans.getMatrix();
    updateSelfAndChild();

}

void Entity::applyTransform(Transform trans) {
   
    local_matrix = local_matrix * trans.getMatrix();
    updateSelfAndChild();
    
}
