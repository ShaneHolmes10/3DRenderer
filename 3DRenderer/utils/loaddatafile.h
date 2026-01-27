#pragma once

#include "../representations/mesh.h"
#include <string>

class LoadDataFile {

public:

    virtual ~LoadDataFile() = default;

    virtual Mesh load(const std::string& filepath) = 0;

};


