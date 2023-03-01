#ifndef __TYPES
#define __TYPES

typedef struct
{
    double x;
    double y;
    double z;
} point;

typedef struct
{
    double tu;
    double tv;
} texture;

typedef struct 
{
    double nx;
    double ny;
    double nz;
} normal;

typedef struct 
{
    int v[3];
    int t[3];
    int n[3];
} face;

#define LEFT 1
#define RIGHT 2
typedef struct 
{
    int xBegin;
    int xEnd;
    int yBegin;
    int yEnd;
    int button;
    int valid;
} mouseMove;

typedef struct 
{
    int x;
    int y;
    char key;
    int valid;
} keyStroke;

#endif