# Troglodyte C
General library primarily for scientific computing in C.
Desined with custom maths containers and efficient allocator stategies.

## Dependencies
- CMake
- OpenBlas and/or CUDA

### Optional
- gnuplot (if plotting is needed)

## Installation
```bash
git clone --recursive git@github.com:MHardenberg/trog.git
cd trog/bin
cmake ..
make
cd ../../
```
## Compile options
```cmake
# Set debug flag
target_compile_definitions(trogc PRIVATE _TROG_DEBUG)

# Set precision to double (default)
    target_compile_definitions(trogc PRIVATE _TROG_DOUBLE_PRECISION)

# Set precision to single
# (yet to be added)
    target_compile_definitions(trogc PRIVATE _TROG_SINGLE_PRECISION)

```


