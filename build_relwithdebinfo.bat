@echo off
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_C_COMPILER=clang-cl -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B build/relwithdebinfo -DCMAKE_CXX_FLAGS="-Xclang -fexceptions -Xclang -fcxx-exceptions"
cmake --build build/relwithdebinfo --config RelWithDebInfo --target Zelda64Recompiled -j