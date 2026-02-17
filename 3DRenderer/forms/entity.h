#pragma once

#include <vector>
#include "forms/model.h"
#include "utils/transform.h"
#include <memory>


/**
 * @brief Represents an object in a 3D scene with hierarchical transformations.
 * 
 * Entity implements a scene graph pattern where objects can be organized in
 * parent-child hierarchies. Each entity maintains a local transformation 
 * (relative to its parent) and computes a world transformation (absolute 
 * position in the scene) by combining its local transform with all parent
 * transforms up the hierarchy.
 * 
 * Scene Graph Example:
 * @code
 * World (at origin)
 *   └─ Sun (100 units from world)
 *       └─ Earth (50 units from sun = 150 units from world)
 *           └─ Moon (10 units from earth = 160 units from world)
 * @endcode
 * 
 * Usage Pattern:
 * @code
 * Entity world, sun, earth;
 * 
 * Transform t_sun(Vector3f(100, 0, 0), Vector3f::Zero());
 * sun.setTransform(t_sun);
 * 
 * world.addChild(sun);
 * sun.addChild(earth);
 * 
 * // earth's world_matrix automatically computed as:
 * // world_matrix = sun.world_matrix * earth.local_matrix
 * @endcode
 */
class Entity {
private:

    /**
     * @brief List of child entities in the scene graph.
     * 
     * Non-owning pointers to child entities. The actual Entity objects
     * should be managed by the user (typically created on stack or 
     * stored elsewhere). When this entity is destroyed, children are
     * not automatically deleted.
     */
    std::vector<Entity*> children;
    

    /**
     * @brief Pointer to parent entity in the scene graph.
     * 
     * nullptr indicates this is a root entity (no parent).
     * Used to compute world transformation by walking up the hierarchy.
     */
    Entity* parent = nullptr;


    /**
     * @brief Local transformation matrix relative to parent.
     * 
     * Represents this entity's position, rotation, and scale in its
     * parent's coordinate space. For root entities, this is the same
     * as the world transformation.
     */
    Eigen::Matrix4f local_matrix;


    /**
     * @brief World transformation matrix (absolute position in scene).
     * 
     * Computed by recursively multiplying all parent world matrices with
     * this entity's local matrix. Updated automatically when transforms
     * change via setTransform(), applyTransform(), or addChild().
     * 
     * Formula: world_matrix = parent.world_matrix * local_matrix
     */
    Eigen::Matrix4f world_matrix;

public:

    /**
     * @brief Pointer to the model containing geometry for rendering.
     * 
     * Can be nullptr if this entity is just a transform node (organizational
     * node with no visual representation). Multiple entities can share the
     * same Model.
     */
    Model* model;

    /**
     * @brief Construct a new Entity with identity transformation.
     * 
     * Initializes the entity with no parent, no model and both local and world 
     * transformation matrices set to identity (positioned at origin with no
     * rotation or scaling).
     */
    Entity() 
        : parent(nullptr),
          model(nullptr),
          local_matrix(Eigen::Matrix4f::Identity()),
          world_matrix(Eigen::Matrix4f::Identity()) {}

    /**
     * @brief Update world matrices for this entity and all descendants.
     * 
     * Recursively computes world matrices by combining this entity's local
     * matrix with its parent's world matrix, then updates all children.
     * Called automatically by setTransform(), applyTransform(), and addChild().
     * 
     * @note Should be called from entities whose parents have up-to-date
     *       world matrices. Typically called automatically, but can be
     *       called manually if needed.
     */
    void updateSelfAndChild();


    /**
     * @brief Add a child entity to this entity.
     * 
     * Establishes parent-child relationship and automatically updates the
     * child's world matrix (and all its descendants) to reflect the new
     * hierarchy. If child already has a parent, it should be removed from
     * the old parent first (currently not handled automatically).
     * 
     * @param child Reference to the entity to add as a child
     * 
     * @code
     * Entity sun, earth;
     * sun.addChild(earth);  // earth is now child of sun
     * @endcode
     */
    void addChild(Entity& child) {
        children.push_back(&child);
        children.back()->parent = this;

        children.back()->updateSelfAndChild();
    }

    /**
     * @brief Set the local transformation, replacing the current transform.
     * 
     * Replaces this entity's local matrix with the matrix from the given
     * Transform, then updates world matrices for this entity and all
     * descendants.
     * 
     * @param trans The new local transformation
     * 
     * @code
     * Transform t(Vector3f(10, 0, 0), Vector3f::Zero());
     * entity.setTransform(t);  // Entity now at (10, 0, 0) relative to parent
     * @endcode
     */
    void setTransform(Transform trans);

    /**
     * @brief Apply an additional transformation to the current transform.
     * 
     * Multiplies the given transformation matrix onto the current local
     * matrix, accumulating transformations. Updates world matrices for
     * this entity and all descendants.
     * 
     * @param trans The transformation to apply (multiply)
     * 
     * @code
     * Transform t1(Vector3f(10, 0, 0), Vector3f::Zero());
     * entity.setTransform(t1);  // At (10, 0, 0)
     * 
     * Transform t2(Vector3f(5, 0, 0), Vector3f::Zero());
     * entity.applyTransform(t2);  // Now at (15, 0, 0)
     * @endcode
     */
    void applyTransform(Transform trans);

    /**
     * @brief Get the world transformation matrix.
     * 
     * Returns the absolute transformation of this entity in world space,
     * computed by combining all parent transforms with this entity's
     * local transform.
     * 
     * @return const Eigen::Matrix4f& Reference to world transformation matrix
     */
    const Eigen::Matrix4f& getWorldMatrix() const { return world_matrix; }
    
    /**
     * @brief Get the local transformation matrix.
     * 
     * Returns the transformation relative to this entity's parent.
     * For root entities, this is the same as the world matrix.
     * 
     * @return const Eigen::Matrix4f& Reference to local transformation matrix
     */
    const Eigen::Matrix4f& getLocalMatrix() const { return local_matrix; }
    
    /**
     * @brief Get the list of child entities.
     * 
     * @return const std::vector<Entity*>& Reference to children vector
     */
    const std::vector<Entity*>& getChildren() const { return children; }

};
