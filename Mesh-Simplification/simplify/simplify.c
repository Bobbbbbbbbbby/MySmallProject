#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../input/input.h"
#include "../input/types.h"

int currentFaces;

face facesTemp[100000];
point pointsTemp[100000];
int accuracy = 100;

void do_simplify();

void simplify(double ratio)
{
    currentFaces = faceIndex;
    do_simplify();
    while ((double)currentFaces / (double)faceIndex > ratio)
    {
        do_simplify();
        accuracy *= 9;
        accuracy /= 10;
        printf("accuracy: %d\n currentFaces: %d\n", accuracy, currentFaces);
    }
    for (int i = 0; i < currentFaces; i++)
    {
        faces[i].v[0] = facesTemp[i].v[0];
        faces[i].v[1] = facesTemp[i].v[1];
        faces[i].v[2] = facesTemp[i].v[2];
    }
    faceIndex = currentFaces;

    // output
    FILE *fd;
    fd = fopen("output.obj", "w");
    fprintf(fd, "# %d %d\n", pointIndex, faceIndex);
    for (int i = 0; i < pointIndex; i++)
    {
        fprintf(fd, "v %lf %lf %lf\n", pointsTemp[i].x, pointsTemp[i].y, pointsTemp[i].z);
    }
    for (int i = 0; i < faceIndex; i++)
    {
        fprintf(fd, "f %d %d %d\n", faces[i].v[0], faces[i].v[1], faces[i].v[2]);
    }
    fclose(fd);
}

void do_simplify()
{

    int duplicatePoint[100000];
    int duplicateFace[100000];
    for (int i = 0; i < 100000; i++)
    {
        pointsTemp[i].x = 0;
        pointsTemp[i].y = 0;
        pointsTemp[i].z = 0;

        duplicateFace[i] = 0;
        duplicatePoint[i] = 0;

        facesTemp[i].v[0] = 0;
        facesTemp[i].v[1] = 0;
        facesTemp[i].v[2] = 0;
    }

    double increment = 2.0 / (double)accuracy;

    // do resampling
    for (int i = 0; i < pointIndex; i++)
    {
        double x = points[i].x;
        double y = points[i].y;
        double z = points[i].z;

        double x1 = x / increment;
        double y1 = y / increment;
        double z1 = z / increment;

        int x1i = (int)x1;
        int y1i = (int)y1;
        int z1i = (int)z1;

        double xResult = (double)x1i * increment;
        double yResult = (double)y1i * increment;
        double zResult = (double)z1i * increment;

        pointsTemp[i].x = xResult;
        pointsTemp[i].y = yResult;
        pointsTemp[i].z = zResult;
    }

    // tag duplicate points, if it is the same point, the number points to the first same point
    int pointCount = 0;
    for (int i = 0; i < pointIndex; i++)
    {
        point target;
        if (duplicatePoint[i] == 0)
        {
            target = pointsTemp[i];
            pointCount++;
        }
        else
        {
            continue;
        }

        int j = i + 1;
        for (j; j < pointIndex; j++)
        {
            point toCompare;
            if (duplicatePoint[j] == 0)
            {
                toCompare = pointsTemp[j];
            }
            else
            {
                continue;
            }
            // do compare
            if (toCompare.x - target.x < increment / 2 && toCompare.y - target.y < increment / 2 && toCompare.z - target.z < increment / 2 && target.x - toCompare.x < increment / 2 && target.y - toCompare.y < increment / 2 && target.z - toCompare.z < increment / 2)
            {
                duplicatePoint[j] = i;
            }
        }
    }

    /*for (int i = 0; i < faceIndex; i++)
    {
        face target = faces[i];
        int v1 = target.v[0] - 1;
        int v2 = target.v[1] - 1;
        int v3 = target.v[2] - 1;

        v1 = duplicatePoint[v1] == 0 ? v1 : duplicatePoint[v1];
        v2 = duplicatePoint[v2] == 0 ? v2 : duplicatePoint[v2];
        v3 = duplicatePoint[v3] == 0 ? v3 : duplicatePoint[v3];
        faces[i].v[0] = v1 + 1;
        faces[i].v[1] = v2 + 1;
        faces[i].v[2] = v3 + 1;
    }
    */
    // tag duplicate faces, if it is the same face, the number points to the first same face

    int faceCount = 0;
    int closedFaces = 0;
    for (int i = 0; i < faceIndex; i++)
    {
        face target;
        target = faces[i];
        int targetV1 = target.v[0] - 1;
        int targetV2 = target.v[1] - 1;
        int targetV3 = target.v[2] - 1;

        int targetV1R = (duplicatePoint[targetV1] != 0) ? duplicatePoint[targetV1] : targetV1;
        int targetV2R = (duplicatePoint[targetV2] != 0) ? duplicatePoint[targetV2] : targetV2;
        int targetV3R = (duplicatePoint[targetV3] != 0) ? duplicatePoint[targetV3] : targetV3;

        if (targetV1R == targetV2R || targetV2R == targetV3R || targetV3R == targetV1R)
        {
            duplicateFace[i] = -1;
            closedFaces++;
        }
    }

    for (int i = 0; i < faceIndex; i++)
    {
        face target;
        if (duplicateFace[i] == 0)
        {
            target = faces[i];
            faceCount++;
        }
        else
        {
            continue;
        }
        int targetV1 = target.v[0] - 1;
        int targetV2 = target.v[1] - 1;
        int targetV3 = target.v[2] - 1;

        int targetV1R = (duplicatePoint[targetV1] != 0) ? duplicatePoint[targetV1] : targetV1;
        int targetV2R = (duplicatePoint[targetV2] != 0) ? duplicatePoint[targetV2] : targetV2;
        int targetV3R = (duplicatePoint[targetV3] != 0) ? duplicatePoint[targetV3] : targetV3;

        int j = i + 1;
        for (j; j < faceIndex; j++)
        {
            face toCompare;
            if (duplicateFace[j] == 0)
            {
                toCompare = faces[j];
            }
            else
            {
                continue;
            }

            int v1 = toCompare.v[0] - 1;
            int v2 = toCompare.v[1] - 1;
            int v3 = toCompare.v[2] - 1;

            int v1R = (duplicatePoint[v1] != 0) ? duplicatePoint[v1] : v1;
            int v2R = (duplicatePoint[v2] != 0) ? duplicatePoint[v2] : v2;
            int v3R = (duplicatePoint[v3] != 0) ? duplicatePoint[v3] : v3;

            if (v1R == targetV1R && v2R == targetV2R && v3R == targetV3R)
            {
                duplicateFace[j] = i;
            }
            else if (v1R == targetV1R && v2R == targetV3R && v3R == targetV2R)
            {
                duplicateFace[j] = i;
            }
            else if (v1R == targetV2R && v2R == targetV3R && v3R == targetV1R)
            {
                duplicateFace[j] = i;
            }
            else if (v1R == targetV2R && v2R == targetV1R && v3R == targetV3R)
            {
                duplicateFace[j] = i;
            }
            else if (v1R == targetV3R && v2R == targetV2R && v3R == targetV1R)
            {
                duplicateFace[j] = i;
            }
            else if (v1R == targetV3R && v2R == targetV1R && v3R == targetV2R)
            {
                duplicateFace[j] = i;
            }
        }
    }

    int j = 0;
    for (int i = 0; i < faceIndex; i++)
    {
        face target;
        if (duplicateFace[i] == 0)
        {
            target = faces[i];
        }
        else
        {
            continue;
        }

        int targetV1 = target.v[0] - 1;
        int targetV2 = target.v[1] - 1;
        int targetV3 = target.v[2] - 1;

        int targetV1R = (duplicatePoint[targetV1] != 0) ? duplicatePoint[targetV1] : targetV1;
        int targetV2R = (duplicatePoint[targetV2] != 0) ? duplicatePoint[targetV2] : targetV2;
        int targetV3R = (duplicatePoint[targetV3] != 0) ? duplicatePoint[targetV3] : targetV3;

        facesTemp[j].v[0] = targetV1R + 1;
        facesTemp[j].v[1] = targetV2R + 1;
        facesTemp[j].v[2] = targetV3R + 1;
        j++;
    }

    currentFaces = faceCount;
}