


#ifndef STAGE_H
#define STAGE_H


#include <iostream>
#include "Vector_Object.h"
#include <vector>

class Stage { 
private:
    std::vector<VectorObject*> vector_list;

public:
    Stage();

    void add(VectorObject* vec);

    std::vector<VectorObject*>& get_vector_list();

};

#endif
