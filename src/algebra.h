#ifndef ALGEBRA_H_
#define ALGEBRA_H_

#define TAU 6.2831853

typedef struct { float x, y; }       V2f;
typedef struct { float x, y, z; }    V3f;
typedef struct { float x, y, z, w; } V4f;

V2f v2f(float x, float y);
V3f v3f(float x, float y, float z);
V4f v4f(float x, float y, float z, float w);

V2f v2ff(float x);
V3f v3ff(float x);
V4f v4ff(float x);

V2f v2f_sum(V2f a, V2f b);
V2f v2f_sub(V2f a, V2f b);

#endif // ALGEBRA_H_
