# OpenGL Display 3D Model
***Stanford Bunny***

## Directories
```
Project
│   README.md       // here
│   Makefile        // make

│   main.c          // main function
│   init.c          // init scene
└───input
│   │   input.c     // read bunny.obj (remake normal if needed)
│   │   input.h     // let others use functions in input.c
│   │   types.h     // let everyone knows typedef
│   │   bunny.obj   // bunny
└───draw
│   │   draw.c      // draw triangles (can draw lineloop if you like)
│   │   draw.h      // let others use functions in draw.c
└───keyboard
│   │   keyboard.c  // manage keyboard input
│   │   keyboard.h  // let others use functions in keyboard.c
└───mouse
│   │   mouse.c     // manage mouse input
│   │   mouse.h     // let others use functions in mouse.c
```

## Environment
***As basic as possible, same as Lab1***

## How to Use
### How to Compile
*`make` is always neccessary*<br>
Options:
1. `make polygon` is the basic option, using the normal information in `obj` file
2. `make lineloop` is a little bit different, which uses `LINE_LOOP` to draw *triangular nets* instead of *faces*
3. `make renormal` is needed to finish the 'advanced' task, to recalculate the `normal` in my own way.

### How to Start and Use
Use `make run` to launch the program

The bunny will be in a 1000 * 1000 window. <br>You can use `w a s d` to rotate the bunny. <br>You can use `mouse left` to move the bunny in `x & y`.<br>You can use `mouse right` to move closer and farther.

### How it Works
#### Data Structure
Note that I code all those things in C, so I use different data structures from slices.
```
point:      (double)x   (double)y       (double)z
texture:    (double)tu  (double)tv
normal:     (double)nx  (double)ny      (double)nz
face:       (point[3])v (texture[3])t   (normal[3])n
mouseMove:  (int)xBegin (int)xEnd       (int)yBegin (int)yEnd (int)button (int) valid
keyStroke:  (int)x      (int)y          (char)key   (int)valid
```
Use `points[10000]`,`textures[10000]`,`normals[10000]`,`faces[10000]` to store the information from `bunny.obj`
Could be a little bit of waste memory, but in C you know :)
<br><br>
#### `main.c`
*Absolutely not valuable to talk about!*<br>But `glutInitDisplayMode` function confused me for hours, just because I forgot `GLUT_DEPTH`, which caused `glEnable(GL_DEPTH_TEST)` not work.<br><br>
#### `init.c`
Should know that use the code below to enable perspective
```
glLoadIdentity();
gluPerspective(30, 1, -1000, 1000);
```
<br><br>
#### `input.c`
Have to say that use C to read file is quite an annoying thing.<br>
function `reNormal()` is to calculate the normal vectors by myself.
Math:<br>
$(a_1, b_1, c_1)\times (a_2, b_2, c_2)$<br>
$=(b_1 c_2 - b_2 c_1)\vec i + (c_1 a_2 - c_2 a_1)\vec j + (a_1 b_2 - a_2 b_1)\vec k$<br>
A face include 3 vectors, each vector can calculate a normal of face like above.
One vector appear in multiple faces, sum all the normal vectors.
Finally caculate the length, and divide, make sure $x^2 + y^2 + z^2 = 1$
<br><br>
#### `draw.c`
In function `draw()`, the same logic as slices, but use different data structure.
Use a macro to run different code in `make polygon`,`make lineloop` and `make renormal`
You can check the code to see how it works with `#ifndef(#ifdef)` and `endif`
<br><br>
#### `keyboard.c`
Nothing special
<br><br>
#### `mouse.c`
*Note that I use `mouse right` to control the distance and `mouse left` to control `x & y`!*
