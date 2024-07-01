
#ifndef REFERENCE_FRAME_H
#define REFERENCE_FRAME_H

#include "Math_Position_Object.h"
#include <Eigen/Dense>
#include <vector>

class ReferenceFrame : public MathPositionObject {
private:
    Eigen::Matrix4d transformation_matrix;
    Eigen::Vector3d angles;
    std::vector<MathPositionObject*> children_list;

public:
    ReferenceFrame(float ox, float oy, float oz) = delete;
    ReferenceFrame(float ox = 0, float oy = 0, float oz = 0, float ax = 0, float ay = 0, float az = 0);
    void set_ax(float value);
    void set_ay(float value);
    void set_az(float value);
    void set_ox(float value);
    void set_oy(float value);
    void set_oz(float value);
    
    const Eigen::Vector3d& get_angles() const;
    const Eigen::Matrix4d& get_transformation_matrix() const;

    void add(ReferenceFrame* child);

    ReferenceFrame* get_expressed_in(ReferenceFrame* expressing_frame);
    

};


#endif
