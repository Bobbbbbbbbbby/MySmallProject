#include "tools.h"
#include <math.h>
#include "svpng.inc"

void normalize(direction_t* direction)
{
    float x = direction->x;
    float y = direction->y;
    float z = direction->z;

    float lengthSquare = x * x + y * y + z * z;
    float length = sqrtf(lengthSquare);

    direction->x = x / length;
    direction->y = y / length;
    direction->z = z / length;
}

void setColor(int x, int y, unsigned char r, unsigned char g, unsigned char b)
{
    int colorIdx = (y * WIDTH + x) * 3;
    image[colorIdx++] = r;
    image[colorIdx++] = g;
    image[colorIdx++] = b;
}

void imageOutput()
{
    FILE* fd;
    fd = fopen("output.png", "w+");

    svpng(fd, WIDTH, HEIGHT, image, 0);

    fclose(fd);
}

float vecDot(vector_t a, vector_t b)
{
    float ret = a.x * b.x + a.y * b.y + a.z * b.z;
    return ret;
}

float max(float a, float b)
{
    if(a >= b)
        return a;
    else
        return b;
}

float mix(float a, float b, float ratio)
{
    float ret;
    ret = a * (1 - ratio) + b * ratio;
    return ret;
}