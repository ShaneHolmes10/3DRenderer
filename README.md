# 3D Renderer

![ezgif-23b9d6c5b2bee0d4](https://github.com/user-attachments/assets/c52a00a0-5276-4a7f-aec9-f0bad245920b)

A software-based 3D rendering engine built from scratch in C++. No GPU acceleration or graphics libraries like OpenGL are used for rendering. The entire pipeline from 3D transformations to triangle rasterization is implemented manually, with the goal of understanding graphics programming fundamentals from first principles.

## Features

- **Complete rendering pipeline**: Model space to world space to camera space to screen space
- **Scene graph system**: Hierarchical parent-child entity relationships with automatic world matrix propagation
- **Triangle rasterization**: Barycentric coordinate-based rasterization with per-vertex color interpolation
- **OBJ file loading**: Support for standard Wavefront OBJ files and an extended color OBJ format with per-vertex color data
- **Camera system**: Mountable camera that attaches to entities in the scene graph, enabling camera rigs and orbital views
- **Transform system**: Position, rotation (Euler angles), and scale with automatic matrix recomputation
- **Multithreaded display**: Viewport runs on a separate thread, decoupling rendering from display

## Dependencies

- **Eigen**: Linear algebra (matrix operations, vector math)
- **SFML**: Windowing and display only (not used for rendering)
- **CMake**: Build system
- **X11**: Thread initialization for SFML on Linux
- **CppUnitLite**: Unit testing framework


## Building 
Create build directory and make a file:
```sh
mkdir build && cd build
cmake ..
make [filename]
```

To run 3D render demo:
```sh
make 3d_render_demo
./bin/examples/3d_render_demo
```

To run tests:
```sh
ctest
```

## Project Structure
```sh
3DRenderer/
├── 3DRenderer/
│   ├── display/         # Viewport class
│   │    └── tests/      # Test files for display classes 
│   ├── forms/           # Entity, Model, Mesh (scene graph and geometry)
│   │    └── tests/      # Test files for forms classes
│   ├── renderer/        # Rendering pipeline, triangle rasterization
│   │    └── tests/      # Test files for renderer classes
│   └── utils/           # Transform, file loaders, testing utilities
│       └── tests/       # Test files for utils classes
├── cmake/                # Cmake dependency handler modules
├── data/                # Data files
├── examples/            # Demo programs
├── tests/               # Unit, integration, and performance tests
└── doc/                 # Documentation

```

## File Descriptions
### Display
- **Viewport.h / Viewport.cpp** - Manages an SFML window on a separate thread, displays FrameBuffer contents to the screen.
- **frame_buffer.h / frame_buffer.cpp** - Pixel buffer storing RGBA data, provides per-pixel write access.

### Forms
- **Entity.h / Entity.cpp** - Scene graph node with parent-child hierarchy, manages local and world transformation matrices.
- **Model.h / Model.cpp** - Container for one or more meshes, supports loading from OBJ files.
- **Mesh.h / Mesh.cpp** - Stores vertices and triangular faces, validates face indices on insertion.

### Renderer
- **Camera.h / Camera.cpp** - Camera class that mounts to entities and handles the transformation pipeline from world space to screen space.

### Utils
- **Transform.h / Transform.cpp** - Encapsulates position, rotation, and scale into a 4x4 transformation matrix with auto-recomputation.
- **load_data_file.h** - Abstract base class defining the file loader interface (strategy pattern).
- **load_obj_file.h / load_obj_file.cpp** - Loads standard Wavefront OBJ files (vertices and faces).
- **load_cobj_file.h / load_cobj_file.cpp** - Loads extended OBJ files with per-vertex color data.
- **draw_triangles.h / draw_triangles.cpp** - Triangle rasterization using edge functions and barycentric coordinate color interpolation.
