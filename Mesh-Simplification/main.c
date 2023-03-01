//
// Created by root on 22-10-25.
//
#include <GL/gl.h>
#include <GL/glut.h>
#include "draw/draw.h"
#include "mouse/mouse.h"
#include "keyboard/keyborad.h"
#include <stdio.h>

void initScene(double ratio);
double my_atof(char *argv);

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("bunny");

    initScene(my_atof(argv[1]));
    glutMouseFunc(&onClick);
    glutKeyboardFunc(&onStroke);
    glutDisplayFunc(&drawScene);
    glutMainLoop();
}

double my_atof(char* argv)
{
    double a = 0;
    int i = 2;
    int j = 1;

    if(argv[0] != '0' || argv[1] != '.')
    {
        printf("wrong input");
        exit(1);
    }

    while(argv[i] != '\0')
    {
        double b = (double)(argv[i] - '0');
        for (int k = 0; k < j; k++)
        {
            b /= 10;
        }
        a += b;
        i++;
        j++;
    }
}