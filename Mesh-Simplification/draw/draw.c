#include "../input/types.h"
#include "../input/input.h"
#include "../mouse/mouse.h"
#include "../keyboard/keyborad.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <math.h>

void draw();
double translateX;
double translateY;
double translateZ = -1;
int rotateX;
int rotateY;
void drawScene()
{
    glLoadIdentity();
    GLfloat glfLight[] = {-4.0f, 4.0f, 4.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, glfLight);
    if(!oneMove.valid && !oneStroke.valid)
    {
        glTranslatef(translateX, translateY, translateZ);
        glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
        glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
    }
    if(oneMove.valid)
    {
        if(oneMove.button == LEFT)
        {
            translateX += (double)(oneMove.xEnd - oneMove.xBegin) / 1000;
            translateY -= (double)(oneMove.yEnd - oneMove.yBegin) / 1000;
            glTranslatef(translateX, translateY, translateZ);
            glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
            glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
        }
        else if(oneMove.button == RIGHT)
        {
            translateZ += (double)(oneMove.xEnd - oneMove.xBegin + oneMove.yEnd - oneMove.yBegin) / 1000;
            glTranslatef(translateX, translateY, translateZ);
            glRotatef(rotateX, 1.0f, 0.0f, 0.0f);
            glRotatef(rotateY, 0.0f, 1.0f, 0.0f);
            printf("%lf\n", translateZ);
        }
    }
    else if(oneStroke.valid)
    {
        rotateY += (oneStroke.key == 'a') ? -10 : (oneStroke.key == 'd') ? 10
                                                                            : 0;
        rotateX += (oneStroke.key == 'w') ? 10 : (oneStroke.key == 's') ? -10
                                                                            : 0;
        glTranslatef(translateX, translateY, translateZ);
        glRotatef(rotateX, 1.0f, 0.0f, 0.0f);   // need change
        glRotatef(rotateY, 0.0f, 1.0f, 0.0f);   // need change

    }
    draw();
    glFlush();
    glutSwapBuffers();
}

void draw()
{
    #ifndef LINE_LOOP
    glBegin(GL_TRIANGLES);
    #endif
    for (int i = 0; i < faceIndex; i++)
    {
        #ifdef LINE_LOOP
        glBegin(GL_LINE_LOOP);
        #endif
        int an = faces[i].n[0] - 1;
        int bn = faces[i].n[1] - 1;
        int cn = faces[i].n[2] - 1;

        int av = faces[i].v[0] - 1;
        int bv = faces[i].v[1] - 1;
        int cv = faces[i].v[2] - 1;

        double nx = -normals[cv].nx - normals[bv].nx - normals[cv].nx;
        double ny = -normals[cv].ny - normals[bv].ny - normals[cv].ny;
        double nz = -normals[cv].nz - normals[bv].nz - normals[cv].nz;

        double length = sqrt(nx * nx + ny * ny + nz * nz);
        nx /= length;
        ny /= length;
        nz /= length;

        glNormal3f(nx, ny, nz);
        //glNormal3f(-normals[cv].nx, -normals[cv].ny, -normals[cv].nz);
        // glTexCoord2f(textures[faces[i].t[2] - 1].tu, textures[faces[i].t[2] - 1].tv);
        glVertex3f(points[cv].x, points[cv].y, points[cv].z);
        
        

        //glNormal3f(-normals[bv].nx, -normals[bv].ny, -normals[bv].nz);
        // glTexCoord2f(textures[faces[i].t[1] - 1].tu, textures[faces[i].t[1] - 1].tv);
        glVertex3f(points[bv].x, points[bv].y, points[bv].z);
        
        

        //glNormal3f(-normals[av].nx, -normals[av].ny, -normals[av].nz);
        // glTexCoord2f(textures[faces[i].t[0] - 1].tu, textures[faces[i].t[0] - 1].tv);
        glVertex3f(points[av].x, points[av].y, points[av].z);
        
        
        #ifdef LINE_LOOP
        glEnd();
        #endif
    }
    #ifndef LINE_LOOP
    glEnd();
    #endif
}