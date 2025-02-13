@echo off
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_C_COMPILER=clang-cl -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B build/debug -DCMAKE_CXX_FLAGS="-Xclang -fexceptions -Xclang -fcxx-exceptions"
cmake --build build/debug --config Debug --target Zelda64Recompiled -j