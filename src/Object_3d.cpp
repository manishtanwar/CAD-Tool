#include "include/Object_3d.h"
#include "include/general_methods.h"
#include "include/planar_graph_generator.h"
#include "include/faceloop_generator.h"
#include "include/body_loop.h"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <set>

#define epsilon 0.000001

Object_3d::Object_3d(std::vector<vertex_3d> v3d_list,
 std::vector<edge_3d> e3d_list, std::vector< std::vector<int> > surface_list)
{
    for(int i=0; i<v3d_list.size() ; i++)
    {
        this->v3d_list.push_back(v3d_list[i]);
    }
    for(int i=0; i<e3d_list.size() ; i++)
    {
        this->e3d_list.push_back(e3d_list[i]);
    }
    for(int i=0; i<surface_list.size() ; i++)
    {
        this->surface_list.push_back(surface_list[i]);
    }
}


//! \fn Constructor which process the 2d projection and returns full 3D object
/*!
 *This constructor consists -
 *1. Adding vertices
 *2. Decision-tree processing for adding edges.
 *3. RER (Redundant Edges Removal)
 *4. Planer graph generation
 *5. Face Loop generation
 *6. Body Part generation

*/
Object_3d::Object_3d(object_2d o)
{
    add_vertices(o.T_vertices, o.F_vertices, o.S_vertices);

    decision_tree(o);

    RER();

    std::vector< Full_plane > f_list;
    f_list = planar_graph_generator(v3d_list, e3d_list);

    std::vector< face_loop > face_loop_list;

    for(auto z : f_list){
        std::vector< face_loop > qface_loop_list;
        qface_loop_list = generate_face_loops(z.p, z.vertices_on_it, z.edges_on_it, v3d_list);
        for(auto zz : qface_loop_list){
            face_loop_list.pb(zz);
        }
    }

    std::vector< body_loop > body_loop_list = generate_body_loop(face_loop_list, v3d_list);

    for(int i=0;i<(int)body_loop_list[0].face_loop_list.size();i++){
        //side_of_face_loop
        for(auto zz : body_loop_list[0].face_loop_list[i].basic_loop_list){
            std::vector<int> add_loop; add_loop.pb(zz.edge_list[0].f);
            for(auto z1 : zz.edge_list){
                add_loop.pb(z1.s);
            }
            if(zz.inner)
            std::reverse(add_loop.begin(), add_loop.end());
            if(body_loop_list[0].side_of_face_loop[i])
            std::reverse(add_loop.begin(), add_loop.end());
            surface_list.pb(add_loop);
        }

    }
}

Object_3d::Object_3d()
{
    // empty
}

// // **************** how to generate surfaces ?? ***********

void Object_3d::add_vertex(vertex_3d v)
{
    v3d_list.push_back(v);
}

void Object_3d::add_edge(edge_3d e)
{
    e3d_list.push_back(e);
}

void Object_3d::remove_edge(edge_3d e)
{
    int j;
    for(int i=0; i<e3d_list.size(); i++)
    {
        if(e == e3d_list[i])
        {
            j = i; break;
        }
    }
    for(int i=j; i<e3d_list.size()-1 ; i++)
    {
        e3d_list[i] = e3d_list[i+1];
    }
    e3d_list.pop_back();
}

// //! function to add vertices_3d form T,F,S 2d coordinate
void Object_3d::add_vertices(std::vector<vertex_2d> T_vertices, std::vector<vertex_2d> F_vertices,
    std::vector<vertex_2d> S_vertices)
{
    for(int i=0;i<T_vertices.size(); i++)
    {
        vertex_3d tmp_ver(T_vertices[i].x, T_vertices[i].y, -F_vertices[i].x);
        v3d_list.push_back(tmp_ver);
    }
}

bool compare (pair<vertex_2d,int>& lhs, pair<vertex_2d,int>& rhs)
{
    if(lhs.first == rhs.first)
    {
        return lhs.second < rhs.second;
    }
    return (lhs.first < rhs.first);
}

// //! function to add edges_3d corresponding to the edges in top, front and side view
void Object_3d::decision_tree(object_2d o)
{
    // adding top-view edges
    for(int i=0; i< o.T_edges.size() ; i++)
    {
        bool tmp1 = is_front_edge(o.F_vertices, o.F_edges, o.T_edges[i]);
        bool tmp2 = is_side_edge( o.S_vertices, o.S_edges, o.T_edges[i]);
        if(tmp1 && tmp2)
        {
            edge_3d tmp(o.T_edges[i].f, o.T_edges[i].s);
            e3d_list.push_back(tmp);
        }
    }

    // adding top-view overlapping points
    std::vector< pair<vertex_2d,int> > tmp_sorted_Fvector;

    for(int i=0; i< o.T_vertices.size(); i++)
    {
        tmp_sorted_Fvector.push_back(make_pair(o.T_vertices[i],i));
    }

    std::sort(tmp_sorted_Fvector.begin(), tmp_sorted_Fvector.end(), compare);

    for(int i=0; i<tmp_sorted_Fvector.size(); i++)
    {
        int j=i+1;
        while(j<tmp_sorted_Fvector.size() && tmp_sorted_Fvector[j].first == tmp_sorted_Fvector[i].first)
        {
            j++;
        }
        // range [i,j-1] is equal
        for(int k=i; k<j ;k++)
        {
            for(int l=k+1; l<j ;l++)
            {
                edge_2d e(tmp_sorted_Fvector[k].second, tmp_sorted_Fvector[l].second);
                bool tmp1 = is_front_edge(o.F_vertices, o.F_edges, e);
                bool tmp2 = is_side_edge( o.S_vertices, o.S_edges, e);
                if(tmp1 && tmp2)
                {
                    edge_3d tmp(e.f, e.s);
                    e3d_list.push_back(tmp);
                }
            }
        }
    }
}

//! function that returns true if edge_2d e is an edge in the front-view
bool Object_3d::is_front_edge(std::vector<vertex_2d> F_vertices, std::vector<edge_2d> F_edges, edge_2d e)
{
    // when projection of edge e in the front view is a point
    if(F_vertices[e.f] == F_vertices[e.s])
        return true;
    for(int i=0; i<F_edges.size(); i++)
    {
        if(e.f == F_edges[i].f && e.s == F_edges[i].s)
        {
            return true;
        }
        if(e.s == F_edges[i].f && e.f == F_edges[i].s)
        {
            return true;
        }
    }
    return false;
}

//! function that returns true if edge_2d e is an edge in the side-view
bool Object_3d::is_side_edge(std::vector<vertex_2d> S_vertices, std::vector<edge_2d> S_edges, edge_2d e)
{
    // when projection of edge e in the side view is a point
    if(S_vertices[e.f] == S_vertices[e.s])
        return true;
    for(int i=0; i<S_edges.size(); i++)
    {
        if(e.f == S_edges[i].f && e.s == S_edges[i].s)
        {
            return true;
        }
        if(e.s == S_edges[i].f && e.f == S_edges[i].s)
        {
            return true;
        }
    }
    return false;
}

//! function that returns true if two edge_3d in the 3D_object are collinear
bool Object_3d::is_collinear(edge_3d e1, edge_3d e2)
{
    // As vertex_3d is a 3x1 vector
    vertex_3d a(v3d_list[e1.f].x - v3d_list[e1.s].x,
                v3d_list[e1.f].y - v3d_list[e1.s].y,
                v3d_list[e1.f].z - v3d_list[e1.s].z);

    vertex_3d b(v3d_list[e2.f].x - v3d_list[e2.s].x,
                v3d_list[e2.f].y - v3d_list[e2.s].y,
                v3d_list[e2.f].z - v3d_list[e2.s].z);

    vertex_3d c(v3d_list[e1.f].x - v3d_list[e2.s].x,
                v3d_list[e1.f].y - v3d_list[e2.s].y,
                v3d_list[e1.f].z - v3d_list[e2.s].z);

    vertex_3d zero(0,0,0);

    if(zero == cross_product(a,b) && zero == cross_product(b,c))
    {
        return true;
    }
    return false;
}

//! function to check if edge e overlaps with any one of the edges of E
bool Object_3d::is_overlapping(std::vector<edge_3d> E, edge_3d e)
{
    float dot_pro;
    for(int i=0; i<E.size(); i++)
    {
        edge_3d a(0,0);
        a = E[i];
        vertex_3d p1(	v3d_list[a.f].x - v3d_list[e.f].x,
                        v3d_list[a.f].y - v3d_list[e.f].y,
                        v3d_list[a.f].z - v3d_list[e.f].z);

        vertex_3d p2(	v3d_list[a.f].x - v3d_list[e.s].x,
                        v3d_list[a.f].y - v3d_list[e.s].y,
                        v3d_list[a.f].z - v3d_list[e.s].z);

        dot_pro = dot_product(p1,p2);
        if( dot_pro <= 0 || std::abs(dot_pro) < epsilon) {return true;}

        vertex_3d p11(	v3d_list[a.s].x - v3d_list[e.f].x,
                        v3d_list[a.s].y - v3d_list[e.f].y,
                        v3d_list[a.s].z - v3d_list[e.f].z);

        vertex_3d p21(	v3d_list[a.s].x - v3d_list[e.s].x,
                        v3d_list[a.s].y - v3d_list[e.s].y,
                        v3d_list[a.s].z - v3d_list[e.s].z);

        dot_pro = dot_product(p11,p21);
        if( dot_pro <= 0 || std::abs(dot_pro) < epsilon) {return true;}

        vertex_3d p12(	v3d_list[e.f].x - v3d_list[a.f].x,
                        v3d_list[e.f].y - v3d_list[a.f].y,
                        v3d_list[e.f].z - v3d_list[a.f].z);

        vertex_3d p22(	v3d_list[e.f].x - v3d_list[a.s].x,
                        v3d_list[e.f].y - v3d_list[a.s].y,
                        v3d_list[e.f].z - v3d_list[a.s].z);

        dot_pro = dot_product(p12,p22);
        if( dot_pro <= 0 || std::abs(dot_pro) < epsilon) {return true;}

        vertex_3d p13(	v3d_list[e.s].x - v3d_list[a.f].x,
                        v3d_list[e.s].y - v3d_list[a.f].y,
                        v3d_list[e.s].z - v3d_list[a.f].z);

        vertex_3d p23(	v3d_list[e.s].x - v3d_list[a.s].x,
                        v3d_list[e.s].y - v3d_list[a.s].y,
                        v3d_list[e.s].z - v3d_list[a.s].z);

        dot_pro = dot_product(p13,p23);
        if( dot_pro <= 0 || std::abs(dot_pro) < epsilon) {return true;}
    }
    return false;
}

//! Redundant Edges Removal procedure
void Object_3d::RER()
{
    std::vector<bool> examined(e3d_list.size(), false);

    std::vector<edge_3d> E;
    std::vector<int> indices; // indices of edges added in E

    // this_while
    while(1)
    {
        bool end_this_while = true;
        for(int i=0; i<e3d_list.size(); i++)
        {
            if(!examined[i])
            {
                E.push_back(e3d_list[i]); indices.push_back(i); examined[i] = true;
                end_this_while = false;	break;
            }
        }
        if(end_this_while) { break; }

        bool end_it = false;
        while(!end_it)
        {
            end_it = true;
            for(int i=0; i<e3d_list.size(); i++)
            {
                if(!examined[i] && is_collinear(E[0], e3d_list[i]))
                {
                    if(is_overlapping(E, e3d_list[i]))
                    {
                        E.push_back(e3d_list[i]); indices.push_back(i);
                        examined[i] = 1; end_it = false;
                    }
                }
            }
        }
        if(E.size() == 1)
        {
            E.clear(); indices.clear(); continue;
        }

        E.clear();

        std::sort(indices.begin(), indices.end());

        std::vector<int> vertices;
        std::vector<edge_3d> new_e3d_list;
        std::vector<bool> new_examined;

        for(int i=0; i<indices.size(); i++)
        {
            int j = indices[i];
            vertices.push_back( e3d_list[j].f );
            vertices.push_back( e3d_list[j].s );
        }

        int ptr = 0;

        for(int i=0; i < e3d_list.size(); i++)
        {
            if(ptr >= indices.size())
            {
                while(i < e3d_list.size())
                {
                    new_e3d_list.push_back(e3d_list[i]);
                    new_examined.push_back(examined[i]);
                    i++;
                }
            }
            while(indices[ptr] != i && i < e3d_list.size())
            {
                new_e3d_list.push_back(e3d_list[i]);
                new_examined.push_back(examined[i]);
                i++;
            }
            ptr++;
        }

        e3d_list = new_e3d_list;
        examined = new_examined;
        new_examined.clear();
        new_e3d_list.clear();

        sort_vertices(vertices);

        for(int i=0; i<vertices.size()-1; i++)
        {
            edge_3d tmp_edge(vertices[i], vertices[i+1]);
            e3d_list.push_back(tmp_edge);
            examined.push_back(true);
        }
    }

}

//! function to sort vertex of collinear edges
void Object_3d::sort_vertices(std::vector<int> &vertices)
{
    // int a[] = {5,5,5,5,5,5};
    // std::sort(a, a+6, custom_comparator);
    std::vector< std::pair<int,vertex_3d> > v;
    std::set<int> set_tmp(vertices.begin(), vertices.end());
    cout<<"vertices in sort_vertices\n";
    for(auto z : set_tmp)
    {
        cout<<z<<' ';
        v.push_back({z,v3d_list[z]});
    }
    cout<<endl;
    std::sort(v.begin(), v.end(), [](pair<int,vertex_3d> lhs, pair<int,vertex_3d> rhs){ return lhs.second < rhs.second; });
    vertices.clear();
    for(auto z : v)
    {
        vertices.push_back(z.first);
    }
}
