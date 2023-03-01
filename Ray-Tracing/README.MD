# Ray Tracing Homework
Modified into `C Programming Language` from the given code in the slice of exercise class<br>
Because I cannot understand C++

## Directories
```
Project
│   README.md       // here
│   Makefile        // make

│   main.c          // main function
│   types.h         // include all data structures
└───object
│   │   object.c    // just for arrays holding object in scene
│   │   object.h    // define object structure
│   │   sphere.c    // used when creating a sphere object
│   │   sphere.h    // functions declaration
└───tools
│   │   tools.c     // some basic functions as my tools
│   │   tools.h     // function declaration
│   │   svpng.inc   // to output .png file
└───keyboard
│   │   render.c    // to render
│   │   rayTracing.c// to do rayTracing for render
│   │   render.h    // function declaration
```

## Environment
***Build Essential*** & ***svpng***
to know more about `svpng`, check github: `https://github.com/miloyip/svpng`

## How to Use
### How to Compile
*`make` is always neccessary*
Options:
`build`: build `rt` executable<br>
`debug`: build `rt` executable with `-g`<br>
`clean`(.PHONY): do clean

### How to Run
`./rt` and wait for a long time

### How it Works
Let's see `int main()`
```c
    initScene();
    render();
    imageOutput();
```
#### `initScene()`
This function uses functions in `sphere.c` to set attributes of spheres in the scene.<br>
The info of objects is stored in `object_t objects` in `object.c`
#### `render()`
Implement the thoughts of class<br>
1. Light Casting
2. Light Intersect
3. Ray Tracing Recursion<br>`surfaceColor += target.colorSurface * transmission * max(0.0, vecDot(centerToHitPoint, lightDirection)) * target.colorEmission;`
#### `imageOutput()`
Info of output is stored in the array image<br>
Use function provided by `svpng` to output `output.png`
