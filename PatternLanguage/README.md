# PatternLanguage

Requirements:
- Zig 0.13 (installed in `PATH`)
- CMake
- Ninja

Compilation:

```sh
git clone https://github.com/mrexodia/zig-cross
cmake -B build -G Ninja --toolchain zig-cross/x86_64-windows-gnu.cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build build
```
