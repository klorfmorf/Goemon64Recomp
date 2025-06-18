@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvarsall.bat" x64
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang-cl -DCMAKE_C_COMPILER=clang-cl -DPATCHES_C_COMPILER="..\..\llvm\bin\clang" -DPATCHES_LD="..\..\llvm\bin\ld.lld" -DCMAKE_MAKE_PROGRAM=ninja -G Ninja -S . -B build/release -DCMAKE_CXX_FLAGS="-Xclang -fexceptions -Xclang -fcxx-exceptions"
cmake --build build/release --config Release --target Goemon64Recompiled -j