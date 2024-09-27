# 3DRenderer
The objective of this project is to explore building a 3D rendering system, specifically using rasterization. <br> <br>
![RotSph_2_1](https://github.com/user-attachments/assets/68725838-f044-49b1-a266-e1800a013f41)


# Building 
To interact with the building system simply navigate to the build directory and call 
```sh
cmake ..
cmake --build .
```

To clean the build folder, stay in the build folder and call
```sh
rm -rf *
```

to run the main file call (while still in the build directory)
```sh
./bin/exec
```

to run any of the test files run this (while still in the build directory)
```sh
./bin/unit_tests/[name of test]
./bin/integration_tests/[name of test]
./bin/performance_tests/[name of test]
```




