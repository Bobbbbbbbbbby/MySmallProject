# OpenGL Mesh Simplification
## With Cuboid Filtering Algorithm
***Bunny***<br>Note that what I did in this project was not completely the same as the requirement.<br>I use `C` to implement the function because I did not think `C++` is more advanced in this situation.<br>I use `mouse right` to control `Z` position, `mouse left` to control `X & Y` position.<br>I use `Makefile` to pass the ratio to the `C` program.<br>*If you have noticed that the name of the window is bunny, I would like to tell you that someone said that `bunny` sounds better than `dragon`*:)

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
│   │   dragon.obj  // dragon
│   │   //bunny.obj   // bunny
└───draw
│   │   draw.c      // draw triangles (can draw lineloop if you like)
│   │   draw.h      // let others use functions in draw.c
└───keyboard
│   │   keyboard.c  // manage keyboard input
│   │   keyboard.h  // let others use functions in keyboard.c
└───mouse
│   │   mouse.c     // manage mouse input
│   │   mouse.h     // let others use functions in mouse.c
└───simplify
│   │   simplify.c  // to simplify the mesh
│   │   simplify.h  // provide the functions to other functions
```

## Environment
***As basic as possible, same as Lab1***

## How to Use
### How to Compile
*`make` is always neccessary*<br>
Options:
**Always use `make renormal`**<br>Because there are no normals at the beginning.
<br>
### How to Start and Use
*Change the ratio of simplification in Makefile, using `RATIO`*
`make renormal` to compile
`make run` to launch
*Note: if you donot want to modify `settings.json` of `.vscode`, just use command line to do `make *`
Other things are the same with project 2.
Remind again that use `mouse right` to control `Z` position.
<br>

### How it Works
#### Data Structure
The same with project 2. Also:
Could be a little bit of waste memory, but in C you know :)
<br><br>
#### `main.c`
*Absolutely not valuable to talk about!*<br>But `glutInitDisplayMode` function confused me for hours, just because I forgot `GLUT_DEPTH`, which caused `glEnable(GL_DEPTH_TEST)` not work.<br><br>
#### `init.c`
Identical with project 2
<br><br>
#### `input.c`
Difference with project 2:
Using `void simplify(double ratio)` to do ***mesh simplification***
<br><br>
#### `draw.c`
Difference with project 2:
Now 3 vectors using the same normal.
If you want to use different normals, de-comment sentences befor `glVector3f`.
<br><br>
#### `keyboard.c`
Nothing special
<br><br>
#### `mouse.c`
*Note that I use `mouse right` to control the distance and `mouse left` to control `x & y`!*
<br><br>
#### `simplify.c`
***Ultimate Importance***
*Using `Cuboid Filtering` Algorithm* because I feel that this way is very easy to understand, although *there were no code for me to learn from*
Basic thought: Everytime, do cuboid filtering with a certain accuracy. If faces are still more than needed, cut down accuracy and do it again.
In function `void do_simplify(void)`, there are four steps:
1. Re-locating points
2. Find out duplicated points
3. Find out duplicated faces
4. If finished, output to `output.obj` in workspace root.