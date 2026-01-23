

#ifndef TESTING_METHODS_H
#define TESTING_METHODS_H


#include <Eigen/Dense>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

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





inline int triangle_edge_function(std::array<float, 2> A, std::array<float, 2> B, std::array<float, 2> C) {
    return ((B[0] - A[0]) * (C[1] - A[1]) - (B[1] - A[1]) * (C[0] - A[0])) / 2;
}

inline void create_triangle(sf::Image& ret_image, 
                                std::array<float, 2> A, std::array<float, 2> B, std::array<float, 2> C, 
                                std::array<float, 3> A_color, std::array<float, 3> B_color, std::array<float, 3> C_color) {
    
    


    // First get the bounding box of the triangle
    float left_side = std::min({A[0], B[0], C[0]});
    float right_side = std::max({A[0], B[0], C[0]});
    float bottom_side = std::min({A[1], B[1], C[1]});
    float top_side = std::max({A[1], B[1], C[1]});


    int ABC_edge_area = triangle_edge_function(A, B, C);

    // Scan through all the pixels in the bounding box
    for(int x_pixel_ind = left_side; x_pixel_ind < right_side; x_pixel_ind++) {
        for(int y_pixel_ind = bottom_side; y_pixel_ind < top_side; y_pixel_ind++) {

            int AB_edge_area = triangle_edge_function(A, B, {(float)x_pixel_ind, (float)y_pixel_ind});
            int CA_edge_area = triangle_edge_function(C, A, {(float)x_pixel_ind, (float)y_pixel_ind});
            int BC_edge_area = triangle_edge_function(B, C, {(float)x_pixel_ind, (float)y_pixel_ind});

            float weight_A = ((float)BC_edge_area / (float)ABC_edge_area);
            float weight_B = ((float)CA_edge_area / (float)ABC_edge_area);
            float weight_C = ((float)AB_edge_area / (float)ABC_edge_area);

            // Determine if the pixel we're looking at is inside the triangle
            if(AB_edge_area >= 0 &&
               CA_edge_area >= 0 &&
               BC_edge_area >= 0) {

                int pixel_r = (int)(A_color[0]*weight_A + B_color[0]*weight_B + C_color[0]*weight_C); 
                int pixel_g = (int)(A_color[1]*weight_A + B_color[1]*weight_B + C_color[1]*weight_C); 
                int pixel_b = (int)(A_color[2]*weight_A + B_color[2]*weight_B + C_color[2]*weight_C); 
                
                sf::Color pixel_color(pixel_r, pixel_g, pixel_b, 255);

                ret_image.setPixel(x_pixel_ind, y_pixel_ind, pixel_color);
            }
        }
    }
    
}


} 

#endif 
