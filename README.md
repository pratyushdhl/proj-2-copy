# Project 2

C++ program that loads campus data from text files and lets a user locate facilities, explore building connections, find routes, browse a department hierarchy, and view summary reports.

Milestone 1 build, run, and test instructions are in [README.txt](README.txt).

Build instructions:

* Ensure MinGW is installed and added to PATH if using Windows
* Run from the repository root:
* `mkdir -p build`
* `g++ -std=c++11 -Wall -Wextra -Wpedantic src/*.cpp -o build/campus`

Run instructions:

* Run from the repository root:
* Linux: `./build/campus`
* Windows: use the executable path produced by your compiler.

Custom Data Directory instructions:

* This is not required, data/ relative to the working directory will be used by default
* Add an argument containing the directory name
* Examples:
* `./build/campus data/`
* `./build/campus testdata/collision`
