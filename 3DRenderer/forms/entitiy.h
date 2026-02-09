#pragma once

#include <vector>
#include "forms/model.h"
#include "utils/transform.h"
#include <memory>

class Entity {
private:

    Transform local_transform;

    std::vector<std::unique_ptr<Entity>> children;
    
    Entity* parent = nullptr;

    Eigen::Matrix4f world_matrix;

public:

    Model* model;

    void updateSelfAndChild();

    template<typename... TArgs>
    void addChild(const TArgs&... args);

    void setTransform(Transform trans);

    void applyTransform(Transform trans);

};
