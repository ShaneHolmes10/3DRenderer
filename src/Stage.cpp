
#include "Stage.h"

Stage::Stage() {

};

void Stage::add(VectorObject* vec) {
    vector_list.push_back(vec);
};

std::vector<VectorObject*>& Stage::get_vector_list() {
    return vector_list;

};


