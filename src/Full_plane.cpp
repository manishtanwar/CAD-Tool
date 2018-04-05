
#include "include/Full_plane.h"
#include "include/general_methods.h"
#define epsilon 0.000001
#include <cmath>

Full_plane::Full_plane(plane p, std::vector<vertex_3d> v3d_list, std::vector<edge_3d> e3d_list)
{
    this->p.a = p.a;
    this->p.b = p.b;
    this->p.c = p.c;
    this->p.d = p.d;

    add_vertices(v3d_list);
    add_edges(e3d_list,v3d_list);


}

Full_plane::Full_plane(plane p)
{
    std::vector<vertex_3d> v1;
    std::vector<edge_3d> e1;
    Full_plane(p,v1,e1);
}

bool Full_plane :: v_on_this_plane(vertex_3d v)
{
    vertex_3d v1(p.a,p.b,p.c);
    float ans = dot_product(v,v1);
    ans -= p.d;
    ans = std::abs(ans);
    if(ans < epsilon) return true;
    return false;
}

bool Full_plane :: e_on_this_plane(vertex_3d v1,vertex_3d v2)
{
    if(v_on_this_plane(v1) && v_on_this_plane(v2))
        return true;
    return false;
}

void Full_plane :: add_vertices(std::vector<vertex_3d> v3d_list)
{
    for(int i=0;i<(int)v3d_list.size();i++)
    {
        bool check = v_on_this_plane(v3d_list[i]);
        if(check==true)
            vertices_on_it.push_back(i);
    }
}

void Full_plane :: add_edges(std::vector<edge_3d> e3d_list, std::vector<vertex_3d> v3d_list)
{
    for(auto zz : e3d_list)
    {
        bool check = e_on_this_plane(v3d_list[zz.f],v3d_list[zz.s]);
        if(check==true)
            edges_on_it.push_back(zz);
    }
}


