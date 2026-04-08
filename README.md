# macrocommand
otus homework on stable abstractions

![CMake](https://github.com/ddatinwavedotru/macrocommand/actions/workflows/cmake-multi-platform.yml/badge.svg)
![Coverage](coverage.svg)

A C++ project with CMake, Google Test, and code coverage on creating stable abstractions.

## Building

```bash
mkdir build && cd build
cmake ..
make

## Code Coverage

### Using CMake target:
```bash
mkdir build && cd build
cmake -DENABLE_COVERAGE=ON ..
make coverage
open coverage_report/index.html
