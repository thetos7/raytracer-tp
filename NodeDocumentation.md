# Node documentation

- [Node documentation](#node-documentation)
  - [Concepts](#concepts)
    - [Pin system](#pin-system)
    - [Internal compute](#internal-compute)
    - [NodeData](#nodedata)
    - [Control Flow](#control-flow)
  - [Nodes](#nodes)
    - [Input nodes](#input-nodes)
      - [ValueNode](#valuenode)
      - [IntersectionInfo](#intersectioninfo)
    - [Texture nodes](#texture-nodes)
      - [VoronoiTextureNode](#voronoitexturenode)
      - [FractalNoiseTextureNode](#fractalnoisetexturenode)
      - [WaveTextureNode](#wavetexturenode)
    - [Converter Nodes](#converter-nodes)
      - [ScalarToSpatialNode](#scalartospatialnode)
      - [PlanarToSpatialNode](#planartospatialnode)
      - [DestructPlanarNode](#destructplanarnode)
      - [DestructSpatialNode](#destructspatialnode)
      - [ConstructPlanarNode](#constructplanarnode)
      - [ConstructSpatialNode](#constructspatialnode)
      - [ColorRampNode](#colorrampnode)
    - [Arithmetic nodes](#arithmetic-nodes)
      - [MixNode](#mixnode)
      - [BinaryMathNode](#binarymathnode)
      - [UnaryMathNode](#unarymathnode)

## Concepts

### Pin system
Nodes work using a "pin" system where each pin can be referenced using a formatted string as their "address" following the format `<node-name>.<pin-name>`. Each node type exposes a number of output pins and expects a number of input pins to be specified. The input pins of a node are specified using a map mapping each expected input to a pin address. Pin addresses are resolved at run-time by the NodeShader which allows nodes to link up with each other. Pins allow lazy computation of the nodes' values as well as caching so that reusing a node's output has little to no performance cost. Think of it like creating variables.

### Internal compute
Each node type has its own `compute` method which acts as a little program, read the input pins, processing them and writing to the outputs.

### NodeData
Data that flows through the graph can be of three types: floating point numbers, 2d vectors or 3d vectors.

### Control Flow
The control flows backwards through the graph, from outputs to inputs.

## Nodes

### Input nodes
input nodes only have output pins

#### ValueNode
Wraps a constant value

**Output pins:**

#### IntersectionInfo
This exposes the intersection's properties as pins

**Output pins:**

- *uv* - `Vector2`: The uv coordinate of the intersection
- *t*  - `double` : The distance from the ray origin to the intersection
- *ray_origin* - `Vector3`: The ray's origin point's position
- *ray_direction* - `Vector3`: The ray's direction as a normalized vector

### Texture nodes
Texture nodes take a uv coordinate from which to sample a color, or a scalar value.

#### VoronoiTextureNode
Models a voronoi texture where the value at each coordinate is a normalized distance to the closest point in a randomly generated set. This implementation supports a seamless, optimized voronoi texture.

The optimization relies on a regular grid with each cell containing a single point. The size of this grid is passed as a parameter. The optimization relies on the fact that the nearest point is always either within the cell of the coordinates, or in the neighbouring one in an 8-connex manner, meaning for each position point there is only 9 points to account for.

example grid of size 5:
```
(0,0)                          (1,0)
+------+------+------+------+------+
|    * |*     |      |      |      |
|      |      |   *  |     *|   *  |
+------+------+------+------+------+
|      |  *   |   *  |   *  |   *  |
| *    |      |      |      |      |
+------+------+------+------+------+
|    * |      |      | *    |      |
|      |     *|  *   |      | *    |
+------+------+------+------+------+
|   *  |  *   |*     | *    |      |
|      |      |      |      |     *|
+------+------+------+------+------+
|   *  |      |   *  |   *  |      |
|      | *    |      |      |  *   |
+------+------+------+------+------+
(0,1)                          (1,1)
```

**Parameters:**

- *size* - `int` > 0: The size of the underlying grid on which the node relies

**Input pins:**

- *uv* - `Vector2`: the UV coordinate to sample

**Output pins:**

- *factor* - `double`: The normalized distance to the nearest point.

#### FractalNoiseTextureNode
Models a fractal Brownian motion noise texture, where multiple noises of decreasing scale and amplitude are added together. The generated noise is based on perlin noise.

**Parameters:**

- *scale* - `double`, default `1.0`: A scaling factor applied to the input coordinates before computing the noise value. Higher values make the noise have a higher frequency.
- *octaves* - `int` > 0, default `6`: The number of noise layers to overlay. Higher values increase the details of the texture.

**Input pins:**

- *uv* - `Vector2`: the UV coordinate to sample

**Output pins:**

- *factor* - `double`: The sampled value.

#### WaveTextureNode
Models a wave texture based on a sine wave.

**Parameters:**

- *scale* - `double`, default `1.0`: A scaling factor applied to the input coordinates before computing the texture value. Higher values make the waves have a higher frequency.
- *angle* - `double`, default `0.0`: The angle of the direction in which the waves go, in radians.
- *offset* - `double`, default `0.0`: a starting offset. transltes the waves along the axis described by *angle*.

**Input pins:**

- *uv* - `Vector2`: the UV coordinate to sample

**Output pins:**

- *factor* - `double`: The sampled value.

### Converter Nodes
Converter nodes allow conversion of data from one type to data of another type, with a specified mapping.

#### ScalarToSpatialNode
Outputs a 3D vector where all components are equal to the input scalar

**Input pins:**

- *in* - `double`: The scalar value

**Output pins:**

- *out* - `Vector3`: The constructed vector

#### PlanarToSpatialNode
Outputs a 3D vector where the first two components are equal to the input's components.

**Input pins:**

- *in* - `Vector2`: The vector2 value

**Output pins:**

- *out* - `Vector3`: The constructed vector

#### DestructPlanarNode
Destructures a 2D vector into its components.

**Input pins:**

- *in* - `Vector2`: The vector to deconstruct

**Output pins:**

- *x* - `double`: The x component of the `in` vector
- *y* - `double`: The y component of the `in` vector

#### DestructSpatialNode
Destructures a 3D vector into its components.

**Input pins:**

- *in* - `Vector3`: The vector to deconstruct

**Output pins:**

- *x* - `double`: The x component of the `in` vector
- *y* - `double`: The y component of the `in` vector
- *z* - `double`: The z component of the `in` vector

#### ConstructPlanarNode
Constructs a 2D vector from its components.

**Input pins:**

- *x* - `double`: The x component of the `result` vector
- *y* - `double`: The y component of the `result` vector

**Output pins:**

- *result* - `Vector2`: The constructed vector

#### ConstructSpatialNode
Constructs a 3D vector from its components.

**Input pins:**

- *x* - `double`: The x component of the `result` vector
- *y* - `double`: The y component of the `result` vector
- *z* - `double`: The z component of the `result` vector

**Output pins:**

- *result* - `Vector3`: The constructed vector

#### ColorRampNode
maps a scalar value to a color/3D vector by linearly interpolating between color values using nearest stopping points.

for example, let's use a color ramp with the stops:
```yaml
0.0: [0.0, 0.0, 0.0]
0.5: [0.0, 1.0, 0.0]
1.0: [1.0, 1.0, 0.0]
```

If we sample the value `0.70`, we will linearly interpolate between $a = (0.0, 1.0, 0.0)$ and $b = (1.0, 1.0, 0.0)$ of stop value $x_1 = 0.5$ and $x_2 = 1.0$ respectively using a factor 
$$t = \frac{value - x_1}{x_2 - x_1}$$
The output color is thus equal to:
$$c = (1-t).a+t.b$$

**Parameters:**
- *stops* - `ColorStop[]`: the collection of color stops of the color ramp, in any order.
  *  `ColorStop`: object desscribing a single stop
     *  *value* - `double`: The value of the color stop
     *  *color* - `Vector3`: The color of the stop
    
    JSON example:
    ```json
    {
        "stops": [
            {"value": 0.0, "color": [1.0,1.0,1.0]},
            {"value": 1.0, "color": [0.0,0.0,0.0]}
        ]
    }
    ```


**Input pins:**

- *value* - `double`: The value to map

**Output pins:**

- *color* - `Vector3`: The mapped color

### Arithmetic nodes
#### MixNode
Linearly interpolates, or extrapolates the `left` pin's value to the `right` depending on the `factor` pin's value when applicable.

**Input pins:**

- *left* - `Any`: The left value
- *right* - `Any`: The right value
- *factor* - `double`: The interpolation factor

**Output pins:**

- *result* - `Any`: The interpolated value

#### BinaryMathNode
Applies a math operation with 2-arity from a preset set as specified by `op` to `lhs` and `rhs`

BinaryOperation:

| string value     | operation description                          |
| ---------------- | ---------------------------------------------- |
| `addition`       | adds `lhs` and `rhs` together                  |
| `subtraction`    | subtracts `rhs` from `lhs`                     |
| `multiplication` | multiplies `lhs` and `rhs` together            |
| `division`       | divides `lhs` by `rhs`                         |
| `power`          | raises `lhs` to the `rhs`-th power             |
| `dot_product`    | performs the dot product of `lhs` with `rhs`   |
| `cross_product`  | performs the cross product of `lhs` with `rhs` |
*Note: each operation may accept some, but not all, type combinations*

**Parameters:**

- *op* - `BinaryOperation`: The operation to execute

**Input pins:**

- *lhs* - `Any`: The left-hand side value
- *rhs* - `Any`: The right-hand side value

**Output pins:**

- *result* - `Any`: The computation result

#### UnaryMathNode
Applies a math operation with 1-arity from a preset set as specified by `op` to `in`

UnaryOperation:

| string value | operation description               |
| ------------ | ----------------------------------- |
| `negation`   | negates `in`                        |
| `norm`       | computes the 2-norm of `in`         |
| `sq_norm`    | computes the squared 2-norm of `in` |
*Note: each operation may accept some, but not all, type combinations*

**Parameters:**

- *op* - `UnaryOperation`: The operation to execute

**Input pins:**

- *in* - `Any`: The operation input value

**Output pins:**

- *result* - `Any`: The computation result

