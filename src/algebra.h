#ifndef ALGEBRA_H_
#define ALGEBRA_H_

typedef struct { float x, y; }       V2f;
typedef struct { float x, y, z; }    V3f;
typedef struct { float x, y, z, w; } V4f;

V2f v2f(float x, float y);
V3f v3f(float x, float y, float z);
V4f v4f(float x, float y, float z, float w);

#endif // ALGEBRA_H_
