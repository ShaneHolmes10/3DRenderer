
#include "loaddatafile.h"
#include "mesh.h"

class LoadObjFile : public LoadDataFile {

public:
    Mesh load(const std::string& filepath) override;

};
