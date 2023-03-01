#include <GL/glut.h>
#include <GL/gl.h>
#include "../input/types.h"
#include "../mouse/mouse.h"
#include "../draw/draw.h"

keyStroke oneStroke;

void onStroke(unsigned char key, int x, int y)
{
    oneStroke.key = key;
    oneStroke.x = x;
    oneStroke.y = y;
    oneStroke.valid = 1;
    oneMove.valid = 0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(0.000f, 0.000f, 0.000f, 1.0f);
    drawScene();
}
