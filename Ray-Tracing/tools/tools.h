#ifndef __TOOLS_H
#define __TOOLS_H

#include "../types.h"
#include <stdio.h>
#include <unistd.h>

void normalize(direction_t* direction);
void setColor(int x, int y, unsigned char r, unsigned char g, unsigned char b);
void imageOutput();
float vecDot(vector_t a, vector_t b);
float max(float a, float b);
float mix(float a, float b, float ratio);

#endif