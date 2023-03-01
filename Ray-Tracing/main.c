#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "object/object.h"
#include "tools/tools.h"
#include "render/render.h"

unsigned char image[WIDTH * HEIGHT * 3];
// init scene(add object) return void
// ray tracing return struct color
// write png return void
// return 0
void initScene();

int main()
{
    initScene();
    render();
    imageOutput();
}

void initScene()
{
    sphereCenter(0.0, -10003.0, 0.0);
    sphereRadius(10000.0);
    sphereColorSurface(0.5, 0.5, 0.5);
    sphereColorEmission(0, 0, 0);
    spherePhysics(0.0, 0.7);
    setSphere();


    sphereCenter(0.0, 0.0, -50.0);
    sphereRadius(2.0);
    sphereColorSurface(0.2, 0.9, 0.2);
    sphereColorEmission(0, 0, 0);
    spherePhysics(0.0, 1.0);
    setSphere();

    sphereCenter(3.0, 0.0, -20.0);
    sphereRadius(3.0);
    sphereColorSurface(0.2, 0.2, 0.8);
    sphereColorEmission(0, 0, 0);
    spherePhysics(1.0, 1.0);
    setSphere();

    sphereCenter(5.0, 0.0, -20.0);
    sphereRadius(2.0);
    sphereColorSurface(0.33, 1.00, 0.36);
    sphereColorEmission(0.0, 0.0, 0.0);
    spherePhysics(1, 1);
    setSphere();

    sphereCenter(-5.0, 2.0, -30.0);
    sphereRadius(2.0);
    sphereColorSurface(1.00, 1.00, 0.36);
    sphereColorEmission(0.0, 0.0, 0.0);
    spherePhysics(1, 1);
    setSphere();

    sphereCenter(-10.0, 5.0, -40.0);
    sphereRadius(3.0);
    sphereColorSurface(1.0, 0.0, 0.0);
    sphereColorEmission(1.0, 0.0, 0.0);
    spherePhysics(1.0, 1.0);
    setSphere();
}