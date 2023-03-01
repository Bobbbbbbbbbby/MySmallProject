#ifndef __OBJECT_H
#define __OBJECT_H

#include "../types.h"
#include "sphere.h"

#define MAX_OBJ_NUM 8

enum ObjectType {FACE, SPHERE};

typedef struct object
{
    enum ObjectType type;
    
    // for sphere
    point_t center;
    color_t colorSurface;
    color_t colorEmission;
    float   radius;
    float   radiusSquare;
    float   transparency;
    float   reflection;
} object_t;

extern object_t objects[MAX_OBJ_NUM];
extern int objectNum;
#endif