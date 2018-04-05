#include "include/general_methods.h"

using namespace std;

vertex_3d cross_product(vertex_3d a, vertex_3d b)
{
    float x,y,z;

    x = a.y * b.z - a.z * b.y;
    y = b.x * a.z - a.x * b.z;
    z = a.x * b.y - a.y * b.x;

    vertex_3d ans(x,y,z);
    return ans;
}

float dot_product(vertex_3d a, vertex_3d b)
{
    float ans;
    ans = a.x*b.x + a.y*b.y + a.z*b.z;
    return ans;
}
