

#ifndef TESTING_METHODS_H
#define TESTING_METHODS_H


#include <Eigen/Dense>
#include <iostream>
#include <vector>

namespace TestMeth {


inline std::array<std::vector<int>, 2> Bresenham(int x1, int y1, int x2, int y2) {
    std::vector<int> x_values;
    std::vector<int> y_values;
    
  
    int dx = ((x2 < x1) ? (-1) : (1))*(x2 - x1);
    int dy = ((y2 < y1) ? (-1) : (1))*(y2 - y1);
    
    if(dx*dx > dy*dy) {      
        int error = 2*dy - dx;
        
        for(int x = x1, 
              y = y1; 
            ((x2 < x1) ? (x > x2+1) : (x < x2-1));
        ) {
            
            error += 2*dy;
    
            if(error >= 0) { 
                error -= 2*dx;
                ((y2 < y1) ? (y--) : (y++));
      
            }
            
            ((x2 < x1) ? (x--) : (x++));
            
            x_values.push_back(x);
            y_values.push_back(y);
            //std::cout << "(" << x << ", " << y << ")\n";
            
        }
        
    } else {
        int error = 2*dx - dy;
  
        for(int y = y1, 
              x = x1; 
            ((y2 < y1) ? (y > y2+1) : (y < y2-1));
        ) {
    
            error += 2*dx;
    
            if(error >= 0) { 
                error -= 2*dy;
                ((x2 < x1) ? (x--) : (x++));
      
            }
            
            ((y2 < y1) ? (y--) : (y++));
            
            x_values.push_back(x);
            y_values.push_back(y);
            //std::cout << "(" << x << ", " << y << ")\n";
            
        }
    }
  
    return {x_values, y_values};
    
}


inline std::vector<std::array<int, 3>> color_interpolation(const std::array<int, 3>& start_point, const std::array<int, 3>& end_point, int N) {

    float Nr = N-1;
    std::vector<std::array<int, 3>> return_vector = {};

    for(float k = 1; k < Nr; k++) {

        return_vector.push_back({
            (int)(((Nr - k) / (Nr))*start_point[0] + ((k) / (Nr))*end_point[0]),
            (int)(((Nr - k) / (Nr))*start_point[1] + ((k) / (Nr))*end_point[1]),
            (int)(((Nr - k) / (Nr))*start_point[2] + ((k) / (Nr))*end_point[2]),
        });

    }

    return return_vector;

}




} 

#endif 
