# 3DRenderer
The objective of this project is to explore building a 3D CPU software rasterizer from scratch.

![ezgif-23b9d6c5b2bee0d4](https://github.com/user-attachments/assets/c52a00a0-5276-4a7f-aec9-f0bad245920b)



# Building 
Create build directory.
```sh
mkdir build && cd build
```

Then in the build directory call the following.
```sh
cmake ..
```

Then to make a specific file just call. The thing we're making has to have a main in it. 
```sh
make [filename]
```

To run tests just make the test file and then run the following (with or without the filename).

```sh
ctest [filename]
```


To clean the build folder, stay in the build folder and call the following.
```sh
rm -rf *
```





