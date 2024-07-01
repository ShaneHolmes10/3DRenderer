#include <Eigen/Dense>
#include <iostream>

int main() {
    
	
    Eigen::Matrix3d rotation_z;
	rotation_z = Eigen::AngleAxisd(2.7937, Eigen::Vector3d::UnitZ()); 

	Eigen::Matrix3d rotation_y;
	rotation_y = Eigen::AngleAxisd(-0.264749, Eigen::Vector3d::UnitY());

	Eigen::Matrix3d rotation_x;
	rotation_x = Eigen::AngleAxisd(-1.38284, Eigen::Vector3d::UnitX());

	Eigen::Matrix3d combined_rotation = rotation_z * rotation_y * rotation_x;
	

	Eigen::Matrix3d combined_rotation_2;
	combined_rotation_2 << -0.91, -0.30, -0.29,
						 0.33, -0.09, -0.94,
						 0.26, -0.94, 0.19;


	Eigen::Vector3d euler_angles = combined_rotation.eulerAngles(2, 1, 0);
	Eigen::Vector3d euler_angles_2 = combined_rotation_2.eulerAngles(2, 1, 0);

	std::cout << "Combined rotation matrix _ 2:\n" << combined_rotation_2 << "\n";
	std::cout << "Combined rotation matrix:\n" << combined_rotation << "\n";
	std::cout << "Euler angles (Z-Y-X) in radians _ 2: " << euler_angles_2 << "\n";
	std::cout << "Euler angles (Z-Y-X) in radians: " << euler_angles << "\n";



    return 0;
}

