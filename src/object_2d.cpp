#include "include/object_2d.h"
#include <iostream>

using namespace std;

object_2d :: object_2d(std::vector<vertex_2d> T_vertices, std::vector<vertex_2d> F_vertices,
            std::vector<vertex_2d> S_vertices, std::vector<edge_2d_v2v> T_edges,
            std::vector<edge_2d_v2v> F_edges, std::vector<edge_2d_v2v> S_edges)
{
    for(int i=0;i<(int)T_vertices.size();i++)
        this->T_vertices.push_back(T_vertices[i]);

    for(int i=0;i<(int)F_vertices.size();i++)
        this->F_vertices.push_back(F_vertices[i]);

    for(int i=0;i<(int)S_vertices.size();i++)
        this->S_vertices.push_back(S_vertices[i]);

    // here major change has to be done as now inputs are edge_2d_v2v

    // for(int i=0;i<T_edges.size();i++)
    // 	this->T_edges.push_back(T_edges[i]);

    // for(int i=0;i<F_edges.size();i++)
    // 	this->F_edges.push_back(F_edges[i]);

    // for(int i=0;i<S_edges.size();i++)
    // 	this->S_edges.push_back(S_edges[i]);

    for(int i=0; i<(int)T_edges.size(); i++)
    {
        //T_edges[i].f & T_edges[i].s
        std::vector<int> tmp1,tmp2;
        for(int j=0; j<(int)T_vertices.size(); j++)
        {
            if(T_vertices[j] == T_edges[i].f)
                tmp1.push_back(j);
            if(T_vertices[j] == T_edges[i].s)
                tmp2.push_back(j);
        }
        for(int k=0; k<(int)tmp1.size(); k++)
        {
            for(int k1=0; k1<(int)tmp2.size(); k1++)
            {
                edge_2d e(tmp1[k],tmp2[k1]);
                this->T_edges.push_back(e);
            }
        }
    }

    for(int i=0; i<(int)S_edges.size(); i++)
    {
        //T_edges[i].f & T_edges[i].s
        std::vector<int> tmp1,tmp2;
        for(int j=0; j<(int)S_vertices.size(); j++)
        {
            if(S_vertices[j] == S_edges[i].f)
                tmp1.push_back(j);
            if(S_vertices[j] == S_edges[i].s)
                tmp2.push_back(j);
        }
        for(int k=0; k<(int)tmp1.size(); k++)
        {
            for(int k1=0; k1<(int)tmp2.size(); k1++)
            {
                edge_2d e(tmp1[k],tmp2[k1]);
                this->S_edges.push_back(e);
            }
        }
    }

    for(int i=0; i<(int)F_edges.size(); i++)
    {
        //T_edges[i].f & T_edges[i].s
        std::vector<int> tmp1,tmp2;
        for(int j=0; j<(int)F_vertices.size(); j++)
        {
            if(F_vertices[j] == F_edges[i].f)
                tmp1.push_back(j);
            if(F_vertices[j] == F_edges[i].s)
                tmp2.push_back(j);
        }
        for(int k=0; k<(int)tmp1.size(); k++)
        {
            for(int k1=0; k1<(int)tmp2.size(); k1++)
            {
                edge_2d e(tmp1[k],tmp2[k1]);
                this->F_edges.push_back(e);
            }
        }
    }
}

object_2d :: object_2d(std::vector<vertex_3d> v3d_list,
         std::vector<edge_3d> e3d_list, std::vector< std::vector<edge_3d> > surface_list)
{
    for(int i=0;i<(int)v3d_list.size();i++)
    {
        std::vector<vertex_2d> v;
        v = converter(v3d_list[i]);
        add_T_vertex(v[0]);
        add_F_vertex(v[1]);
        add_S_vertex(v[2]);
    }

    // cout<<"size "<<e3d_list.size()<<"\n";

    for(int i=0;i<(int)e3d_list.size();i++)
    {
        // cout<<e3d_list[i].f<<' '<<e3d_list[i].s<<"-> \n";
        std::vector<bool> checker_bool;
        checker_bool = checker(e3d_list[i]);
        // cout<<checker_bool[0]<<' '<<checker_bool[1]<<' '<<checker_bool[2]<<"\n";
        int f,s;
        f = e3d_list[i].f; s = e3d_list[i].s;
        if(checker_bool[0] == true)
        {
            edge_2d Tv(f,s);
            add_T_edge(Tv);
        }
        if(checker_bool[1] == true)
        {
            edge_2d Fv(f,s);
            add_F_edge(Fv);
        }
        if(checker_bool[2] == true)
        {
            edge_2d Sv(f,s);
            add_S_edge(Sv);
        }
    }
}

void object_2d :: add_T_vertex(vertex_2d v)
{
    this->T_vertices.push_back(v);
    return;
}

void object_2d :: add_F_vertex(vertex_2d v)
{
    this->F_vertices.push_back(v);
    return;
}

void object_2d :: add_S_vertex(vertex_2d v)
{
    this->S_vertices.push_back(v);
    return;
}

void object_2d :: add_T_edge(edge_2d e)
{
    this->T_edges.push_back(e);
    return;
}

void object_2d :: add_F_edge(edge_2d e)
{
    this->F_edges.push_back(e);
    return;
}

void object_2d :: add_S_edge(edge_2d e)
{
    this->S_edges.push_back(e);
    return;
}

// object_2d :: object_2d(Object_3d obj)
// {

// }

std::vector<vertex_2d> object_2d :: converter(vertex_3d v)
{
    std::vector<vertex_2d> v2d_list;
    //top view 2d vertex
    // vertex_2d v_top(v.x,v.y);
    v2d_list.push_back(vertex_2d (v.x,v.y));

    //front view 2d vertex
    vertex_2d v_front(v.x,v.z);
    v2d_list.push_back(v_front);

    //side view 2d vertex
    vertex_2d v_side(v.y,v.z);
    v2d_list.push_back(v_side);


    return v2d_list;
}


std::vector<bool> object_2d :: checker(edge_3d e)
{
    std::vector<bool> checker_bool;
    checker_bool.push_back(true);checker_bool.push_back(true);checker_bool.push_back(true);
    int v1 = e.f;
    int v2 = e.s;

    // top view 2d edge
    if(T_vertices[v1] == T_vertices[v2])
        checker_bool[0] = false;

    // front view 2d edge
    if(F_vertices[v1] == F_vertices[v2])
        checker_bool[1] = false;

    // side view 2d edge
    if(S_vertices[v1] == S_vertices[v2])
        checker_bool[2] = false;

    return checker_bool;
}
