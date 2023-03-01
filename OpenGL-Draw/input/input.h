#ifndef _INPUT
#define _INPUT
#include "types.h"

extern point    points[10000];
extern texture  textures[10000];
extern normal   normals[10000];
extern face     faces[10000];

extern int pointIndex;
extern int textureIndex;
extern int normalIndex;
extern int faceIndex;

void readObj();
#endif