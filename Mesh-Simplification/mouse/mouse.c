#include <GL/gl.h>
#include <GL/glut.h>
#include "../input/types.h"
#include "../draw/draw.h"
#include "../keyboard/keyborad.h"

mouseMove oneMove;

void onClick(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        if(button == GLUT_LEFT_BUTTON)
            oneMove.button = LEFT;
        if(button == GLUT_RIGHT_BUTTON)
            oneMove.button = RIGHT;
        oneMove.xBegin = x;
        oneMove.yBegin = y;
    }
    else if(state == GLUT_UP)
    {
        if(button == GLUT_LEFT_BUTTON)
            oneMove.button = LEFT;
        if(button == GLUT_RIGHT_BUTTON)
            oneMove.button = RIGHT;
        oneMove.xEnd = x;
        oneMove.yEnd = y;
        oneMove.valid = 1;
        oneStroke.valid = 0;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        glClearColor(0.000f, 0.000f, 0.000f, 1.0f);
        drawScene();
    }

}