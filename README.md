# Path Tracer

A Monte Carlo path tracer written in C++ from scratch, implementing physically-based rendering with support for multiple material types and camera effects. Currently working on CUDA support.

<table>
  <tr>
    <td><img src="renders/image1.png" width="400"></td>
    <td><img src="renders/image2.png" width="400"></td>
  </tr>
  <tr>
    <td><img src="renders/image3.png" width="400"></td>
    <td><img src="renders/image4.png" width="400"></td>
  </tr>
</table>

## Building

Requires CMake 3.10+ and a C++11 compatible compiler.

```bash
mkdir -p build && cd build
cmake ..
make
```

## Usage

The path tracer outputs PPM format to stdout:

```bash
./build/main > image.ppm
```

## Acknowledgements

Based on [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) 

---

<sub>**License:** MIT © 2025 Lucas Cogrossi</sub>
