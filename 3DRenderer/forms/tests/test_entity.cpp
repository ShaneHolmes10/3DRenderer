#include "CppUnitLite/TestHarness.h"
#include "forms/entity.h"
#include "utils/transform.h"
#include <Eigen/Dense>
#include <cmath>

/*!SECTION
Test default entity construction
Test entity world matrix initialization
Test setTransform on entity
Test applyTransform on entity
Test parent-child relationship
Test world matrix propagation through hierarchy
Test multi-level hierarchies
Test rotation and scale propagation
*/

TEST(Entity, DefaultConstruction)
{
    Entity e;
    
    Eigen::Matrix4f expected = Eigen::Matrix4f::Identity();
    
    CHECK((e.getWorldMatrix() - expected).norm() < 0.1f);
    CHECK((e.getLocalMatrix() - expected).norm() < 0.1f);
}

TEST(Entity, SetTransformPosition)
{
    Entity e;
    
    Transform t(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    e.setTransform(t);
    
    Eigen::Vector3f pos = e.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(10, 0, 0);
    
    CHECK((pos - expected).norm() < 0.1f);
}

TEST(Entity, SetTransformReplacesLocalMatrix)
{
    Entity e;
    
    Transform t1(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    e.setTransform(t1);
    
    Transform t2(Eigen::Vector3f(20, 0, 0), Eigen::Vector3f::Zero());
    e.setTransform(t2);
    
    Eigen::Vector3f pos = e.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(20, 0, 0);
    
    CHECK((pos - expected).norm() < 0.1f);
}

TEST(Entity, ApplyTransformAccumulatesMatrix)
{
    Entity e;
    
    Transform t1(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    e.setTransform(t1);
    
    Transform t2(Eigen::Vector3f(5, 0, 0), Eigen::Vector3f::Zero());
    e.applyTransform(t2);
    
    Eigen::Vector3f pos = e.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(15, 0, 0);
    
    CHECK((pos - expected).norm() < 0.1f);
}

TEST(Entity, ParentChildRelationship)
{
    Entity parent;
    Entity child;
    
    Transform t_parent(Eigen::Vector3f(100, 0, 0), Eigen::Vector3f::Zero());
    parent.setTransform(t_parent);
    
    Transform t_child(Eigen::Vector3f(50, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    
    parent.addChild(child);
    
    Eigen::Vector3f child_world_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(150, 0, 0);
    
    CHECK((child_world_pos - expected).norm() < 0.1f);
}

TEST(Entity, AddChildAutoUpdates)
{
    Entity parent;
    Entity child;
    
    Transform t_parent(Eigen::Vector3f(50, 0, 0), Eigen::Vector3f::Zero());
    parent.setTransform(t_parent);
    
    Transform t_child(Eigen::Vector3f(30, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    
    parent.addChild(child);
    
    Eigen::Vector3f child_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(80, 0, 0);
    
    CHECK((child_pos - expected).norm() < 0.1f);
}

TEST(Entity, ModifyingParentUpdatesChild)
{
    Entity parent;
    Entity child;
    
    Transform t_child(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    
    parent.addChild(child);
    
    Transform t_parent(Eigen::Vector3f(100, 0, 0), Eigen::Vector3f::Zero());
    parent.setTransform(t_parent);
    
    Eigen::Vector3f child_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(110, 0, 0);
    
    CHECK((child_pos - expected).norm() < 0.1f);
}

TEST(Entity, ThreeLevelHierarchy)
{
    Entity grandparent;
    Entity parent;
    Entity child;
    
    Transform t_gp(Eigen::Vector3f(100, 0, 0), Eigen::Vector3f::Zero());
    grandparent.setTransform(t_gp);
    
    Transform t_p(Eigen::Vector3f(50, 0, 0), Eigen::Vector3f::Zero());
    parent.setTransform(t_p);
    
    Transform t_c(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_c);
    
    grandparent.addChild(parent);
    parent.addChild(child);
    
    Eigen::Vector3f child_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(160, 0, 0);
    
    CHECK((child_pos - expected).norm() < 0.1f);
}

TEST(Entity, RotationPropagation)
{
    Entity parent;
    Entity child;
    
    Transform t_parent(Eigen::Vector3f::Zero(), Eigen::Vector3f(0, M_PI/2, 0));
    parent.setTransform(t_parent);
    
    Transform t_child(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    
    parent.addChild(child);
    
    Eigen::Vector3f child_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(0, 0, -10);
    
    CHECK((child_pos - expected).norm() < 0.5f);
}

TEST(Entity, ScalePropagation)
{
    Entity parent;
    Entity child;
    
    Transform t_parent(Eigen::Vector3f::Zero(), 
                       Eigen::Vector3f::Zero(),
                       Eigen::Vector3f(2, 2, 2));
    parent.setTransform(t_parent);
    
    Transform t_child(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    
    parent.addChild(child);
    
    Eigen::Vector3f child_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(20, 0, 0);
    
    CHECK((child_pos - expected).norm() < 0.1f);
}

TEST(Entity, ApplyTransformWithRotation)
{
    Entity e;
    
    Transform t1(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    e.setTransform(t1);
    
    Transform t2(Eigen::Vector3f::Zero(), Eigen::Vector3f(0, M_PI/2, 0));
    e.applyTransform(t2);
    
    Eigen::Vector3f pos = e.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(10, 0, 0);
    
    CHECK((pos - expected).norm() < 0.5f);
}

TEST(Entity, MultipleChildren)
{
    Entity parent;
    Entity child1;
    Entity child2;
    
    Transform t_parent(Eigen::Vector3f(100, 0, 0), Eigen::Vector3f::Zero());
    parent.setTransform(t_parent);
    
    Transform t_c1(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    child1.setTransform(t_c1);
    
    Transform t_c2(Eigen::Vector3f(20, 0, 0), Eigen::Vector3f::Zero());
    child2.setTransform(t_c2);
    
    parent.addChild(child1);
    parent.addChild(child2);
    
    Eigen::Vector3f pos1 = child1.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f pos2 = child2.getWorldMatrix().block<3,1>(0,3);
    
    Eigen::Vector3f expected1(110, 0, 0);
    Eigen::Vector3f expected2(120, 0, 0);
    
    CHECK((pos1 - expected1).norm() < 0.1f && (pos2 - expected2).norm() < 0.1f);
}

TEST(Entity, ModelAttachment)
{
    Entity e;
    Model test_model;
    
    e.model = &test_model;
    
    CHECK(e.model == &test_model);
}

TEST(Entity, SolarSystemExample)
{
    Entity world;
    Entity sun;
    Entity earth;
    Entity moon;
    
    Transform t_sun(Eigen::Vector3f(100, 0, 0), Eigen::Vector3f::Zero());
    sun.setTransform(t_sun);
    
    Transform t_earth(Eigen::Vector3f(50, 0, 0), Eigen::Vector3f::Zero());
    earth.setTransform(t_earth);
    
    Transform t_moon(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    moon.setTransform(t_moon);
    
    world.addChild(sun);
    sun.addChild(earth);
    earth.addChild(moon);
    
    Eigen::Vector3f moon_pos = moon.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(160, 0, 0);
    
    CHECK((moon_pos - expected).norm() < 0.1f);
}

TEST(Entity, LocalMatrixIndependentOfParent)
{
    Entity parent;
    Entity child;
    
    Transform t_parent(Eigen::Vector3f(100, 0, 0), Eigen::Vector3f::Zero());
    parent.setTransform(t_parent);
    
    Transform t_child(Eigen::Vector3f(50, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    
    parent.addChild(child);
    
    Eigen::Vector3f child_local_pos = child.getLocalMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected_local(50, 0, 0);
    
    Eigen::Vector3f child_world_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected_world(150, 0, 0);
    
    CHECK((child_local_pos - expected_local).norm() < 0.1f);
    CHECK((child_world_pos - expected_world).norm() < 0.1f);
}

TEST(Entity, ApplyMultipleTransforms)
{
    Entity e;
    
    Transform t1(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    e.setTransform(t1);
    
    Transform t2(Eigen::Vector3f(5, 0, 0), Eigen::Vector3f::Zero());
    e.applyTransform(t2);
    
    Transform t3(Eigen::Vector3f(3, 0, 0), Eigen::Vector3f::Zero());
    e.applyTransform(t3);
    
    Eigen::Vector3f pos = e.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(18, 0, 0);
    
    CHECK((pos - expected).norm() < 0.1f);
}

TEST(Entity, CombinedRotationAndTranslation)
{
    Entity parent;
    Entity child;
    
    Transform t_parent(Eigen::Vector3f(50, 0, 0), 
                       Eigen::Vector3f(0, M_PI/2, 0));
    parent.setTransform(t_parent);
    
    Transform t_child(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f::Zero());
    child.setTransform(t_child);
    
    parent.addChild(child);
    
    Eigen::Vector3f child_pos = child.getWorldMatrix().block<3,1>(0,3);
    Eigen::Vector3f expected(50, 0, -10);
    
    CHECK((child_pos - expected).norm() < 0.5f);
}

TEST(Entity, MultiLevelRotation)
{
    Entity root;
    Entity middle;
    Entity leaf;
    
    Transform t_root(Eigen::Vector3f::Zero(), Eigen::Vector3f(0, M_PI/4, 0));
    root.setTransform(t_root);
    
    Transform t_middle(Eigen::Vector3f(10, 0, 0), Eigen::Vector3f(0, M_PI/4, 0));
    middle.setTransform(t_middle);
    
    Transform t_leaf(Eigen::Vector3f(5, 0, 0), Eigen::Vector3f::Zero());
    leaf.setTransform(t_leaf);
    
    root.addChild(middle);
    middle.addChild(leaf);
    
    Eigen::Vector3f leaf_pos = leaf.getWorldMatrix().block<3,1>(0,3);
    
    CHECK(leaf_pos.norm() > 0.1f);
}

int main() {
    TestResult tr;
    return TestRegistry::runAllTests(tr);
}