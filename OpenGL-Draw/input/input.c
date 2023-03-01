#include "types.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

point points[10000];
texture textures[10000];
normal normals[10000];
face faces[10000];

char mtllib[50];
char usemtl[50];
int pointIndex = 0;
int textureIndex = 0;
int normalIndex = 0;
int faceIndex = 0;
#ifdef RENORMAL
void reNormal();
void reNormal()
{
    for (int i = 0; i < normalIndex; i++)
    {
        normals[i].nx = 0;
        normals[i].ny = 0;
        normals[i].nz = 0;
    }
    for (int i = 0; i < faceIndex; i++)
    {
        typedef struct
        {
            double x;
            double y;
            double z;
        } vector;

        int av = faces[i].v[0] - 1;
        int bv = faces[i].v[1] - 1;
        int cv = faces[i].v[2] - 1;
        point pa = points[av];
        point pb = points[bv];
        point pc = points[cv];

        int an = faces[i].n[0] - 1;
        int bn = faces[i].n[1] - 1;
        int cn = faces[i].n[2] - 1;
        normal na = normals[an];
        normal nb = normals[bn];
        normal nc = normals[cn];

        vector N;
        vector A;
        vector B;

        double length;
        // for na use pb pc
        A.x = pb.x - pa.x;
        A.y = pb.y - pa.y;
        A.z = pb.z - pa.z;
        B.x = pc.x - pa.x;
        B.y = pc.y - pa.y;
        B.z = pc.z - pa.z;
        N.x = A.y * B.z - B.y * A.z;
        N.y = B.x * A.z - A.x * B.z;
        N.z = A.x * B.y - B.x * A.y;

        normals[an].nx += N.x;
        normals[an].ny += N.y;
        normals[an].nz += N.z;
        // for nb use pc pa
        A.x = pc.x - pb.x;
        A.y = pc.y - pb.y;
        A.z = pc.z - pb.z;
        B.x = pa.x - pb.x;
        B.y = pa.y - pb.y;
        B.z = pa.z - pb.z;
        N.x = A.y * B.z - B.y * A.z;
        N.y = B.x * A.z - A.x * B.z;
        N.z = A.x * B.y - B.x * A.y;

        normals[bn].nx += N.x;
        normals[bn].ny += N.y;
        normals[bn].nz += N.z;
        // for nc use pa pb
        A.x = pa.x - pc.x;
        A.y = pa.y - pc.y;
        A.z = pa.z - pc.z;
        B.x = pb.x - pc.x;
        B.y = pb.y - pc.y;
        B.z = pb.z - pc.z;
        N.x = A.y * B.z - B.y * A.z;
        N.y = B.x * A.z - A.x * B.z;
        N.z = A.x * B.y - B.x * A.y;

        normals[cn].nx += N.x;
        normals[cn].ny += N.y;
        normals[cn].nz += N.z;
    }
    // go to 1
    for (int i = 0; i < normalIndex; i++)
    {
        normal N = normals[i];
        double length = sqrt(N.nx * N.nx + N.ny * N.ny + N.nz * N.nz);
        normals[i].nx /= length;
        normals[i].ny /= length;
        normals[i].nz /= length;
    }
}
#endif

int myGetline(char *str, FILE *fd);
int myGetline(char *str, FILE *fd)
{
    char c;
    int index = 0;
    int notEOF = 1;
    while (notEOF)
    {
        if (fscanf(fd, "%c", &c) == EOF)
        {
            notEOF = 0;
            break;
        }
        else if (c != '\n')
        {
            str[index++] = c;
        }
        else
        {
            break;
        }
    }
    str[index] = '\0';
    if (notEOF == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void readObj()
{
    FILE *fd;
    fd = fopen("input/bunny.obj", "r");
    char *str = malloc(sizeof(char) * 200);
    char strHead;
    int eof = 0;
    while (fscanf(fd, "%c", &strHead))
    {
        if (strHead == 'u')
        {
            fscanf(fd, "%s", str);
            if (str[0] == 's' && str[1] == 'e' && str[2] == 'm' && str[3] == 't' && str[4] == 'l')
            {
                fscanf(fd, "%s\n", str);
                int i = 0;
                while (str[i] != '\0')
                {
                    usemtl[i] = str[i];
                    i++;
                }
            }
        }
        if (strHead == 'm')
        {
            fscanf(fd, "%s", str);
            if (str[0] == 't' && str[1] == 'l' && str[2] == 'l' && str[3] == 'i' && str[4] == 'b')
            {
                fscanf(fd, "%s\n", str);
                int i = 0;
                while (str[i] != '\0')
                {
                    mtllib[i] = str[i];
                }
            }
        }
        if (strHead == '#' || strHead == 'g')
        {
            if (strHead == 'g')
            {
                fscanf(fd, "%[^\n]%*c", str);
                printf("name: %s\n", str);
                continue;
            }
            fscanf(fd, "%[^\n]%*c", str);
            printf("%s\n", str);
        }
        else if (strHead == 'v')
        {
            fscanf(fd, "%c", &strHead);
            if (strHead == ' ')
            {
                double a, b, c;
                fscanf(fd, "%lf %lf %lf\n", &a, &b, &c);
                points[pointIndex].x = a;
                points[pointIndex].y = b;
                points[pointIndex].z = c;
                pointIndex++;
            }
            else if (strHead == 'n')
            {
                double a, b, c;
                fscanf(fd, "%lf %lf %lf\n", &a, &b, &c);
                normals[normalIndex].nx = a;
                normals[normalIndex].ny = b;
                normals[normalIndex].nz = c;
                normalIndex++;
            }
        }
        else if (strHead == 'f')
        {
            char a[10];
            char b[10];
            char c[10];

            if (myGetline(str, fd))
            {
                eof = 1;
                break;
            }
            int i = 0;
            int index = 0;
            while (str[i] != '/')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    a[index++] = str[i];
                i++;
            }
            a[index] = '\0';
            i++;

            index = 0;
            while (str[i] != '/')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    b[index++] = str[i];
                i++;
            }
            b[index] = '\0';
            i++;

            index = 0;
            while (str[i] != ' ')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    c[index++] = str[i];
                i++;
            }
            c[index] = '\0';
            i++;

            faces[faceIndex].v[0] = atoi(a);
            faces[faceIndex].t[0] = atoi(b);
            faces[faceIndex].n[0] = atoi(c);

            index = 0;
            while (str[i] != '/')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    a[index++] = str[i];
                i++;
            }
            a[index] = '\0';
            i++;

            index = 0;
            while (str[i] != '/')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    b[index++] = str[i];
                i++;
            }
            b[index] = '\0';
            i++;

            index = 0;
            while (str[i] != ' ')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    c[index++] = str[i];
                i++;
            }
            c[index] = '\0';
            i++;

            faces[faceIndex].v[1] = atoi(a);
            faces[faceIndex].t[1] = atoi(b);
            faces[faceIndex].n[1] = atoi(c);

            index = 0;
            while (str[i] != '/')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    a[index++] = str[i];
                i++;
            }
            a[index] = '\0';
            i++;

            index = 0;
            while (str[i] != '/')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    b[index++] = str[i];
                i++;
            }
            b[index] = '\0';
            i++;

            index = 0;
            while (str[i] != '\0')
            {
                if (str[i] >= '0' && str[i] <= '9')
                    c[index++] = str[i];
                i++;
            }
            c[index] = '\0';
            i++;

            faces[faceIndex].v[2] = atoi(a);
            faces[faceIndex].t[2] = atoi(b);
            faces[faceIndex].n[2] = atoi(c);
            faceIndex++;
        }
        if (eof == 1)
            break;
    }
    #ifdef RENORMAL
    reNormal();
#endif
    fclose(fd);
}