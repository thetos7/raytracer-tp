# Raytracer

Implementation of a raytracing engine

## features
- basic raytracing
- support for multiple object types:
  * Spheres
  * Planes
  * Triangles
  * Meshes (collection of triangles implementation)
  * Blobs/Metaballs (generates mesh using marching cubes)
- support for multiple light types:
  * point lights
  * sun lights
  * ambient lights
- supported variable material properties:
  * diffuse color
  * specular factor
  * specular spread/roughness
  * reflectivity
- Image textured material
- UV mapped primitives:
  * Triangles
  * Spheres
  * Meshes
- Graph-based Procedural texturing with many node types
- obj scene importer
- JSON-based scene format (with schemas)

## Building

In the repo's directory, run:
```sh
./setup.sh
```
This will launch cmake to configure the project to build in the `build` directory.

To build the binary (on linux), change into the build directory and run `make`. This will create a `raytracer-tp` binary.

Using VSCode is recommended for editing and viewing the code.

## Usage

you can call the `raytracer-tp` binary in two ways:
```sh
./raytracer-tp
```
will render a predetermined demo scene

```sh
./raytracer-tp <path-to-json-scene>
```
will render a scene bassed on the contents of the json file.

