# Building
## Prerequisites
1. Git
2. CMake
3. Any build environment (Unix Makefiles, Visual Studio, whatever, CMake deals with it instead of us)
4. Any shell that can run `cmake` command.
## Cloning the repo
That should be pretty easy AFAIK:
```bash
git clone --recursive https://github.com/undnull/voxelius.git
cd voxelius
```
## Generating the build files
The build files are supposed to be placed in the _build_ directory, thus CMake needs to output these files to it:
```bash
cmake -B build .
```
## Building, finally!
The project structure requires every dependency to be built from sources along with the core project, thus you won't need any additional actions required to build/install dependencies.  
And that means you can build the entire project by using the one simple command:
```bash
cmake --build build
```
