#include "../types.h"
#include "../object/object.h"
#include "../tools/tools.h"
#include <math.h>

#define MAX_DEPTH 100
extern object_t objects[MAX_OBJ_NUM];
int intersect(point_t origin, direction_t direction, float *t0, float *t1, int objectIdx);

color_t rayTracing(point_t rayOrigin, direction_t direction, int depth)
{
    color_t white;
    white.r = 1;
    white.g = 1;
    white.b = 1;
    float tnear = INFINITY;
    int nearObjectIdx = -1;
    for (int i = 0; i < objectNum; i++)
    {
        float t0 = INFINITY;
        float t1 = INFINITY;
        point_t origin;
        origin.x = rayOrigin.x;
        origin.y = rayOrigin.y;
        origin.z = rayOrigin.z;
        if (intersect(origin, direction, &t0, &t1, i))
        {
            if (t0 < 0)
                t0 = t1;
            if (t0 < tnear)
            {
                tnear = t0;
                nearObjectIdx = i;
            }
        }
    }
    if (nearObjectIdx == -1)
        return white;

    if (objects[nearObjectIdx].type == SPHERE)
    {
        color_t surfaceColor;
        object_t target = objects[nearObjectIdx];
        point_t hitPoint;
        vector_t centerToHitPoint;
        int inside = 0;

        surfaceColor.r = 0;
        surfaceColor.g = 0;
        surfaceColor.b = 0;

        hitPoint.x = rayOrigin.x + tnear * direction.x;
        hitPoint.y = rayOrigin.y + tnear * direction.y;
        hitPoint.z = rayOrigin.z + tnear * direction.z;

        centerToHitPoint.x = hitPoint.x - target.center.x;
        centerToHitPoint.y = hitPoint.y - target.center.y;
        centerToHitPoint.z = hitPoint.z - target.center.z;

        normalize(&centerToHitPoint);

        float bias = 1e-4;
        if (vecDot(direction, centerToHitPoint) > 0)
        {
            centerToHitPoint.x = 0 - centerToHitPoint.x;
            centerToHitPoint.y = 0 - centerToHitPoint.y;
            centerToHitPoint.z = 0 - centerToHitPoint.z;
            inside = 1;
        }

        if ((target.transparency > 0 || target.reflection > 0) && depth < MAX_DEPTH)
        {
            float facingRatio;
            float fresnelEffect;
            direction_t reflectDirection;
            color_t nextReflection;
            color_t nextRefraction;

            facingRatio = -vecDot(direction, centerToHitPoint);
            fresnelEffect = mix(pow(1 - facingRatio, 3), 1, 0.1);

            vector_t delta;
            delta.x = centerToHitPoint.x * 2 * vecDot(centerToHitPoint, direction);
            delta.y = centerToHitPoint.y * 2 * vecDot(centerToHitPoint, direction);
            delta.z = centerToHitPoint.z * 2 * vecDot(centerToHitPoint, direction);

            reflectDirection.x = direction.x - delta.x;
            reflectDirection.y = direction.y - delta.y;
            reflectDirection.z = direction.z - delta.z;
            normalize(&reflectDirection);

            point_t newOrigin;
            newOrigin.x = hitPoint.x + centerToHitPoint.x * bias;
            newOrigin.y = hitPoint.y + centerToHitPoint.y * bias;
            newOrigin.z = hitPoint.z + centerToHitPoint.z * bias;
            nextReflection = rayTracing(newOrigin, reflectDirection, depth + 1);

            if (target.transparency > 0)
            {
                float ior;
                float eta;
                float cosi;
                float k;
                vector_t refractionDirection;
                point_t newOrigin1;

                ior = 1.1;
                eta = (inside) ? ior : 1.0 / ior;
                cosi = -vecDot(centerToHitPoint, direction);
                k = 1 - eta * eta * (1 - cosi * cosi);
                refractionDirection.x = direction.x * eta + centerToHitPoint.x * (eta * cosi - sqrt(k));
                refractionDirection.y = direction.y * eta + centerToHitPoint.y * (eta * cosi - sqrt(k));
                refractionDirection.z = direction.z * eta + centerToHitPoint.z * (eta * cosi - sqrt(k));
                normalize(&refractionDirection);

                newOrigin1.x = hitPoint.x - centerToHitPoint.x * bias;
                newOrigin1.y = hitPoint.y - centerToHitPoint.y * bias;
                newOrigin1.z = hitPoint.z - centerToHitPoint.z * bias;

                nextRefraction = rayTracing(newOrigin1, refractionDirection, depth + 1);
            }
            surfaceColor.r = (nextReflection.r * fresnelEffect * target.reflection + nextRefraction.r * (1 - fresnelEffect) * target.transparency) * target.colorSurface.r;
            surfaceColor.g = (nextReflection.g * fresnelEffect * target.reflection + nextRefraction.g * (1 - fresnelEffect) * target.transparency) * target.colorSurface.g;
            surfaceColor.b = (nextReflection.b * fresnelEffect * target.reflection + nextRefraction.b * (1 - fresnelEffect) * target.transparency) * target.colorSurface.b;
        }
        else
        {
            for (int i = 0; i < objectNum; i++)
            {
                object_t target = objects[i];
                if (target.type == SPHERE && (target.colorEmission.r > 0 || target.colorEmission.g > 0 || target.colorEmission.b > 0))
                {
                    float transmission = 1;
                    vector_t lightDirection;
                    lightDirection.x = target.center.x - hitPoint.x;
                    lightDirection.y = target.center.y - hitPoint.y;
                    lightDirection.z = target.center.z - hitPoint.z;
                    normalize(&lightDirection);

                    for (int j = 0; j < objectNum; j++)
                    {
                        if (j != i)
                        {
                            float t0, t1;
                            point_t temp;
                            temp.x = hitPoint.x + centerToHitPoint.x * bias;
                            temp.y = hitPoint.y + centerToHitPoint.y * bias;
                            temp.z = hitPoint.z + centerToHitPoint.z * bias;
                            if (intersect(temp, lightDirection, &t0, &t1, j))
                            {
                                transmission = 0;
                                break;
                            }
                        }
                    }
                    surfaceColor.r = surfaceColor.r + target.colorSurface.r * transmission * max(0.0, vecDot(centerToHitPoint, lightDirection)) * target.colorEmission.r;
                    surfaceColor.g = surfaceColor.g + target.colorSurface.g * transmission * max(0.0, vecDot(centerToHitPoint, lightDirection)) * target.colorEmission.g;
                    surfaceColor.b = surfaceColor.b + target.colorSurface.b * transmission * max(0.0, vecDot(centerToHitPoint, lightDirection)) * target.colorEmission.b;
                }
            }
        }
        color_t ret;
        ret.r = surfaceColor.r + objects[nearObjectIdx].colorEmission.r;
        ret.g = surfaceColor.g + objects[nearObjectIdx].colorEmission.g;
        ret.b = surfaceColor.b + objects[nearObjectIdx].colorEmission.b;
        return ret;
    }
}

int intersect(point_t origin, direction_t direction, float *t0, float *t1, int objectIdx)
{
    if (objects[objectIdx].type == FACE)
    {
    }
    else if (objects[objectIdx].type == SPHERE)
    {
        float radiusSquare = objects[objectIdx].radiusSquare;
        point_t center;
        center.x = objects[objectIdx].center.x;
        center.y = objects[objectIdx].center.y;
        center.z = objects[objectIdx].center.z;

        vector_t l;
        l.x = center.x - origin.x;
        l.y = center.y - origin.y;
        l.z = center.z - origin.z;

        float dotProduct = vecDot(direction, l);
        if (dotProduct < 0)
            return 0;

        float distance = vecDot(l, l) - dotProduct * dotProduct;
        if (distance > radiusSquare)
            return 0;

        float thc = sqrt(radiusSquare - distance);
        *t0 = dotProduct - thc;
        *t1 = dotProduct + thc;

        return 1;
    }
}