//
// Created by root on 22-10-25.
//
#include <GL/gl.h>
#include <GL/glut.h>
#include "draw/draw.h"
#include "mouse/mouse.h"
#include "keyboard/keyborad.h"

void initScene();

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("bunny");

    initScene();
    glutMouseFunc(&onClick);
    glutKeyboardFunc(&onStroke);
    glutDisplayFunc(&drawScene);
    glutMainLoop();
}