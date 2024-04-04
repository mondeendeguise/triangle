#ifndef CALG_H_
#define CALG_H_

#ifndef CALGDEF
#define CALGDEF static inline
#endif // CALGDEF

typedef struct { float x, y; } V2f;
typedef struct { double x, y; } V2d;
typedef struct { int x, y; } V2i;
typedef struct { unsigned int x, y; } V2u;

typedef struct { float x, y, z; } V3f;
typedef struct { double x, y, z; } V3d;
typedef struct { int x, y, z; } V3i;
typedef struct { unsigned int x, y, z; } V3u;

typedef struct { float x, y, z, w; } V4f;
typedef struct { double x, y, z, w; } V4d;
typedef struct { int x, y, z, w; } V4i;
typedef struct { unsigned int x, y, z, w; } V4u;

CALGDEF V2f v2f(float x, float y);
CALGDEF V2f v2ff(float x);
CALGDEF V2f v2f_sum(V2f a, V2f b);
CALGDEF V2f v2f_sub(V2f a, V2f b);
CALGDEF V2f v2f_mul(V2f a, V2f b);
CALGDEF V2f v2f_div(V2f a, V2f b);

CALGDEF V2d v2d(double x, double y);
CALGDEF V2d v2dd(double x);
CALGDEF V2d v2d_sum(V2d a, V2d b);
CALGDEF V2d v2d_sub(V2d a, V2d b);
CALGDEF V2d v2d_mul(V2d a, V2d b);
CALGDEF V2d v2d_div(V2d a, V2d b);

CALGDEF V2i v2i(int x, int y);
CALGDEF V2i v2ii(int x);
CALGDEF V2i v2i_sum(V2i a, V2i b);
CALGDEF V2i v2i_sub(V2i a, V2i b);
CALGDEF V2i v2i_mul(V2i a, V2i b);
CALGDEF V2i v2i_div(V2i a, V2i b);

CALGDEF V2u v2u(unsigned int x, unsigned int y);
CALGDEF V2u v2uu(unsigned int x);
CALGDEF V2u v2u_sum(V2u a, V2u b);
CALGDEF V2u v2u_sub(V2u a, V2u b);
CALGDEF V2u v2u_mul(V2u a, V2u b);
CALGDEF V2u v2u_div(V2u a, V2u b);

CALGDEF V3f v3f(float x, float y, float z);
CALGDEF V3f v3ff(float x);
CALGDEF V3f v3f_sum(V3f a, V3f b);
CALGDEF V3f v3f_sub(V3f a, V3f b);
CALGDEF V3f v3f_mul(V3f a, V3f b);
CALGDEF V3f v3f_div(V3f a, V3f b);

CALGDEF V3d v3d(double x, double y, double z);
CALGDEF V3d v3dd(double x);
CALGDEF V3d v3d_sum(V3d a, V3d b);
CALGDEF V3d v3d_sub(V3d a, V3d b);
CALGDEF V3d v3d_mul(V3d a, V3d b);
CALGDEF V3d v3d_div(V3d a, V3d b);

CALGDEF V3i v3i(int x, int y, int z);
CALGDEF V3i v3ii(int x);
CALGDEF V3i v3i_sum(V3i a, V3i b);
CALGDEF V3i v3i_sub(V3i a, V3i b);
CALGDEF V3i v3i_mul(V3i a, V3i b);
CALGDEF V3i v3i_div(V3i a, V3i b);

CALGDEF V3u v3u(unsigned int x, unsigned int y, unsigned int z);
CALGDEF V3u v3uu(unsigned int x);
CALGDEF V3u v3u_sum(V3u a, V3u b);
CALGDEF V3u v3u_sub(V3u a, V3u b);
CALGDEF V3u v3u_mul(V3u a, V3u b);
CALGDEF V3u v3u_div(V3u a, V3u b);

CALGDEF V4f v4f(float x, float y, float z, float w);
CALGDEF V4f v4ff(float x);
CALGDEF V4f v4f_sum(V4f a, V4f b);
CALGDEF V4f v4f_sub(V4f a, V4f b);
CALGDEF V4f v4f_mul(V4f a, V4f b);
CALGDEF V4f v4f_div(V4f a, V4f b);

CALGDEF V4d v4d(double x, double y, double z, double w);
CALGDEF V4d v4dd(double x);
CALGDEF V4d v4d_sum(V4d a, V4d b);
CALGDEF V4d v4d_sub(V4d a, V4d b);
CALGDEF V4d v4d_mul(V4d a, V4d b);
CALGDEF V4d v4d_div(V4d a, V4d b);

CALGDEF V4i v4i(int x, int y, int z, int w);
CALGDEF V4i v4ii(int x);
CALGDEF V4i v4i_sum(V4i a, V4i b);
CALGDEF V4i v4i_sub(V4i a, V4i b);
CALGDEF V4i v4i_mul(V4i a, V4i b);
CALGDEF V4i v4i_div(V4i a, V4i b);

CALGDEF V4u v4u(unsigned int x, unsigned int y, unsigned int z, unsigned int w);
CALGDEF V4u v4uu(unsigned int x);
CALGDEF V4u v4u_sum(V4u a, V4u b);
CALGDEF V4u v4u_sub(V4u a, V4u b);
CALGDEF V4u v4u_mul(V4u a, V4u b);
CALGDEF V4u v4u_div(V4u a, V4u b);


#endif // CALG_H_

#ifdef CALG_IMPLEMENTATION

CALGDEF V2f v2f(float x, float y)
{
    V2f v;
    v.x = x;
    v.y = y;
    return v;
}

CALGDEF V2f v2ff(float x)
{
    return v2f(x, x);
}

CALGDEF V2f v2f_sum(V2f a, V2f b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

CALGDEF V2f v2f_sub(V2f a, V2f b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

CALGDEF V2f v2f_mul(V2f a, V2f b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

CALGDEF V2f v2f_div(V2f a, V2f b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

CALGDEF V2d v2d(double x, double y)
{
    V2d v;
    v.x = x;
    v.y = y;
    return v;
}

CALGDEF V2d v2dd(double x)
{
    return v2d(x, x);
}

CALGDEF V2d v2d_sum(V2d a, V2d b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

CALGDEF V2d v2d_sub(V2d a, V2d b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

CALGDEF V2d v2d_mul(V2d a, V2d b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

CALGDEF V2d v2d_div(V2d a, V2d b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

CALGDEF V2i v2i(int x, int y)
{
    V2i v;
    v.x = x;
    v.y = y;
    return v;
}

CALGDEF V2i v2ii(int x)
{
    return v2i(x, x);
}

CALGDEF V2i v2i_sum(V2i a, V2i b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

CALGDEF V2i v2i_sub(V2i a, V2i b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

CALGDEF V2i v2i_mul(V2i a, V2i b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

CALGDEF V2i v2i_div(V2i a, V2i b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

CALGDEF V2u v2u(unsigned int x, unsigned int y)
{
    V2u v;
    v.x = x;
    v.y = y;
    return v;
}

CALGDEF V2u v2uu(unsigned int x)
{
    return v2u(x, x);
}

CALGDEF V2u v2u_sum(V2u a, V2u b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

CALGDEF V2u v2u_sub(V2u a, V2u b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}

CALGDEF V2u v2u_mul(V2u a, V2u b)
{
    a.x *= b.x;
    a.y *= b.y;
    return a;
}

CALGDEF V2u v2u_div(V2u a, V2u b)
{
    a.x /= b.x;
    a.y /= b.y;
    return a;
}

CALGDEF V3f v3f(float x, float y, float z)
{
    V3f v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

CALGDEF V3f v3ff(float x)
{
    return v3f(x, x, x);
}

CALGDEF V3f v3f_sum(V3f a, V3f b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

CALGDEF V3f v3f_sub(V3f a, V3f b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

CALGDEF V3f v3f_mul(V3f a, V3f b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

CALGDEF V3f v3f_div(V3f a, V3f b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

CALGDEF V3d v3d(double x, double y, double z)
{
    V3d v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

CALGDEF V3d v3dd(double x)
{
    return v3d(x, x, x);
}

CALGDEF V3d v3d_sum(V3d a, V3d b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

CALGDEF V3d v3d_sub(V3d a, V3d b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

CALGDEF V3d v3d_mul(V3d a, V3d b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

CALGDEF V3d v3d_div(V3d a, V3d b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

CALGDEF V3i v3i(int x, int y, int z)
{
    V3i v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

CALGDEF V3i v3ii(int x)
{
    return v3i(x, x, x);
}

CALGDEF V3i v3i_sum(V3i a, V3i b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

CALGDEF V3i v3i_sub(V3i a, V3i b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

CALGDEF V3i v3i_mul(V3i a, V3i b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

CALGDEF V3i v3i_div(V3i a, V3i b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

CALGDEF V3u v3u(unsigned int x, unsigned int y, unsigned int z)
{
    V3u v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

CALGDEF V3u v3uu(unsigned int x)
{
    return v3u(x, x, x);
}

CALGDEF V3u v3u_sum(V3u a, V3u b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    return a;
}

CALGDEF V3u v3u_sub(V3u a, V3u b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    return a;
}

CALGDEF V3u v3u_mul(V3u a, V3u b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

CALGDEF V3u v3u_div(V3u a, V3u b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    return a;
}

CALGDEF V4f v4f(float x, float y, float z, float w)
{
    V4f v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

CALGDEF V4f v4ff(float x)
{
    return v4f(x, x, x, x);
}

CALGDEF V4f v4f_sum(V4f a, V4f b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

CALGDEF V4f v4f_sub(V4f a, V4f b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

CALGDEF V4f v4f_mul(V4f a, V4f b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

CALGDEF V4f v4f_div(V4f a, V4f b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

CALGDEF V4d v4d(double x, double y, double z, double w)
{
    V4d v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

CALGDEF V4d v4dd(double x)
{
    return v4d(x, x, x, x);
}

CALGDEF V4d v4d_sum(V4d a, V4d b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

CALGDEF V4d v4d_sub(V4d a, V4d b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

CALGDEF V4d v4d_mul(V4d a, V4d b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

CALGDEF V4d v4d_div(V4d a, V4d b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

CALGDEF V4i v4i(int x, int y, int z, int w)
{
    V4i v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

CALGDEF V4i v4ii(int x)
{
    return v4i(x, x, x, x);
}

CALGDEF V4i v4i_sum(V4i a, V4i b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

CALGDEF V4i v4i_sub(V4i a, V4i b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

CALGDEF V4i v4i_mul(V4i a, V4i b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

CALGDEF V4i v4i_div(V4i a, V4i b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

CALGDEF V4u v4u(unsigned int x, unsigned int y, unsigned int z, unsigned int w)
{
    V4u v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

CALGDEF V4u v4uu(unsigned int x)
{
    return v4u(x, x, x, x);
}

CALGDEF V4u v4u_sum(V4u a, V4u b)
{
    a.x += b.x;
    a.y += b.y;
    a.z += b.z;
    a.w += b.w;
    return a;
}

CALGDEF V4u v4u_sub(V4u a, V4u b)
{
    a.x -= b.x;
    a.y -= b.y;
    a.z -= b.z;
    a.w -= b.w;
    return a;
}

CALGDEF V4u v4u_mul(V4u a, V4u b)
{
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    a.w *= b.w;
    return a;
}

CALGDEF V4u v4u_div(V4u a, V4u b)
{
    a.x /= b.x;
    a.y /= b.y;
    a.z /= b.z;
    a.w /= b.w;
    return a;
}

#endif // CALG_IMPLEMENTATION
