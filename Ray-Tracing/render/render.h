#ifndef __RENDER_H
#define __RENDER_H

#include "../object/object.h"
#include "../types.h"

void render();
color_t rayTracing(point_t rayOrigin, direction_t direction, int depth);

#endif