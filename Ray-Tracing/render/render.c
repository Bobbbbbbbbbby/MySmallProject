#include "render.h"
#include "../tools/tools.h"
#include <math.h>

extern void render()
{
    float invWidth  = 1.0 / (float) WIDTH;
    float invHeight = 1.0 / (float) HEIGHT;
    float fov = 30;
    float aspectRatio = (float) WIDTH / (float) HEIGHT;
    float angle = tan(M_PI * 0.5 * fov / 180.0);

    for(int j = 0; j < HEIGHT; j++)
    {
        for(int i = 0; i < WIDTH; i++)
        {
            float x = (2 * ((i + 0.5) * invWidth) - 1) * angle * aspectRatio;
            float y = (1 - 2 * ((j + 0.5) * invHeight)) * angle;
            direction_t dir;
            dir.x = x;
            dir.y = y;
            dir.z = -1;
            normalize(&dir);

            point_t origin;
            origin.x = 0;
            origin.y = 0;
            origin.z = 0;

            color_t color = rayTracing(origin, dir, 0);

            // INTEGER COLOR
            unsigned char r = (unsigned char)(color.r * 255);
            unsigned char g = (unsigned char)(color.g * 255);
            unsigned char b = (unsigned char)(color.b * 255);
            setColor(i, j, r, g, b);
        }
    }
}