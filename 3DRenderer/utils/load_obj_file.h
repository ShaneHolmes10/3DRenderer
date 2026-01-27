
#include "load_data_file.h"
#include "representations/mesh.h"

class LoadObjFile : public LoadDataFile {

public:
    Mesh load(const std::string& filepath) override;

};
