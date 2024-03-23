#include "algebra.h"

V2f v2f(float x, float y)
{
    V2f v;
    v.x = x;
    v.y = y;
    return v;
}

V3f v3f(float x, float y, float z)
{
    V3f v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

V4f v4f(float x, float y, float z, float w)
{
    V4f v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

V2f v2ff(float x)
{
    return v2f(x, x);
}

V3f v3ff(float x)
{
    return v3f(x, x, x);
}

V4f v4ff(float x)
{
    return v4f(x, x, x, x);
}

V2f v2f_sum(V2f a, V2f b)
{
    a.x += b.x;
    a.y += b.y;
    return a;
}

V2f v2f_sub(V2f a, V2f b)
{
    a.x -= b.x;
    a.y -= b.y;
    return a;
}
