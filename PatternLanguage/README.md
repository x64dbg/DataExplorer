# PatternLanguage

Requirements:
- Zig 0.15 (installed in `PATH`)
- CMake
- Ninja

Compilation:

```sh
git clone https://github.com/mrexodia/zig-cross
cmake -B build64 -G Ninja --toolchain zig-cross/x86_64-windows-gnu.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build64
cmake -B build32 -G Ninja --toolchain zig-cross/x86-windows-gnu.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build32
```

With Visual Studio:

```
cmake -B build-vs64 -A x64
cmake --build build-vs64 --config Release
cmake -B build-vs32 -A Win32
cmake --build build-vs32 --config Release
```
