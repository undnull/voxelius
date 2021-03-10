# Building
## Prerequisites
* Git
* CMake >=3.10
* Any build environment
* Any C and C++ compiler

## Actions
### 1. Cloning
Clone the repository recursively, then go to the directory:
```
git clone --recursive https://github.com/undnull/voxelius.git
cd voxelius
```

### 2. Generating build files
The `build` directory is chosen as a default one for storing the build files.  
Run CMake:
```
cmake -B build .
```

### 3. Building
Run CMake:
```
cmake --build build
```

### 4. Running
Depending on your environment, run one of the following commands:
```
./build/Debug/voxelius
```
```
./build/Release/voxelius
```
```
./build/voxelius
```

### 5. (Optional) building shaders
This step requires Vulkan SDK to be installed.  
If you don't have Vulkan SDK installed, you may download the latest release of _glslangValidator_ and _spirv-cross_ and put the binary into the `tools` directory.  

Run the following command:
```
./tools/buildshaders.sh shaders
```
