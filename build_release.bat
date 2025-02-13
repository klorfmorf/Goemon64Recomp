@echo off
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_C_COMPILER=clang-cl -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B build/release -DCMAKE_CXX_FLAGS="-Xclang -fexceptions -Xclang -fcxx-exceptions"
cmake --build build/release --config Release --target Zelda64Recompiled -j