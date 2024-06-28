
#ifndef MATH_POSITION_OBJECT_H
#define MATH_POSITION_OBJECT_H

#include <Eigen/Dense>

class MathPositionObject {
private:
    MathPositionObject* defining_frame;
    Eigen::Vector3d placement_vector;
    
public:
    MathPositionObject(float ox = 0, float oy = 0, float oz = 0);
    void set_ox(float value);
    void set_oy(float value);
    void set_oz(float value);
    const Eigen::Vector3d& get_placement_vector() const;

protected:
    virtual MathPositionObject* get_expressed_in(MathPositionObject* expressing_frame) = 0;
    
};


#endif
