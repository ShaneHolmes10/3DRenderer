


#ifndef STAGE_H
#define STAGE_H


#include <iostream>
#include "Vector_Object.h"
#include <vector>

/**
 * @brief This object contains all the relevant 
 * objects for projection and drawing such as 
 * vectors and triangles.
 * 
 */
class Stage { 
private:

    /**
     * @brief This contains all the vector objects in the stage.
     * 
     */
    std::vector<VectorObject*> vector_list;

public:

    Stage();

    /**
     * @brief add a new vector object to the containing vector list
     * 
     * @param vec new vector
     */
    void add(VectorObject* vec);

    /**
     * @brief Get the vector list object
     * 
     * @return std::vector<VectorObject*>& 
     */
    std::vector<VectorObject*>& get_vector_list();

};

#endif
