#include "object.h"

void sphereCenter(float x, float y, float z)
{
    objects[objectNum].center.x = x;
    objects[objectNum].center.y = y;
    objects[objectNum].center.z = z;
}

void sphereColorSurface(float r, float g, float b)
{
    objects[objectNum].colorSurface.r = r;
    objects[objectNum].colorSurface.g = g;
    objects[objectNum].colorSurface.b = b;
}

void sphereColorEmission(float r, float g, float b)
{
    objects[objectNum].colorEmission.r = r;
    objects[objectNum].colorEmission.g = g;
    objects[objectNum].colorEmission.b = b;
}

void sphereRadius(float radius)
{
    objects[objectNum].radius = radius;
    objects[objectNum].radiusSquare = radius * radius;
}

void spherePhysics(float transparency, float reflection)
{
    objects[objectNum].transparency = transparency;
    objects[objectNum].reflection = reflection;
}

void setSphere()
{
    objects[objectNum].type = SPHERE;
    objectNum++;
}