#include "include/structs.h"
#include "include/object_2d.h"
#include "include/Object_3d.h"
#include "include/3d_to_2d.h"
#include "include/form.h"
#include <bits/stdc++.h>

#undef scroll
#include <QWidget>

using namespace std;


int three_d_to_two_d(string file)
{

    ifstream inFile;
    inFile.open(file);
    if(!inFile) return 1;

    int no_of_vertices;
    inFile>>no_of_vertices;

    std::vector<vertex_3d> v3d_list;
    std::vector<edge_3d> e3d_list;
    std::vector< std::vector<edge_3d> > surface_list;

    while(no_of_vertices--)
    {
        float a,b,c; vertex_3d v(0,0,0);
        inFile>>a>>b>>c;
        v.x = a; v.y = b; v.z = c;
        v3d_list.pb(v);
    }

    int no_of_edges;
    inFile>>no_of_edges;

    while(no_of_edges--)
    {
        int f,s;
        inFile>>f>>s;
        edge_3d e(f,s);
        e3d_list.pb(e);
    }


    object_2d obj(v3d_list,e3d_list,surface_list);

    std::vector<pair<float,float>> T, Fv,S,O;
    std::vector<pair<int,int>> Te,Fe,Se,Oe;
    int ai[2];

    for(int i=0;i<(int)obj.T_vertices.size();i++)
        T.pb({obj.T_vertices[i].x, obj.T_vertices[i].y});

    for(int i=0;i<(int)obj.T_edges.size();i++)
    {
        ai[0]=obj.T_edges[i].f;
        ai[1]=obj.T_edges[i].s;
        sort(ai,ai+2); Te.pb({ai[0],ai[1]});
    }

    for(int i=0;i<(int)obj.F_vertices.size();i++)
        Fv.pb({obj.F_vertices[i].x, obj.F_vertices[i].y});

    for(int i=0;i<(int)obj.F_edges.size();i++)
    {
        ai[0]=obj.F_edges[i].f;
        ai[1]=obj.F_edges[i].s;
        sort(ai,ai+2); Fe.pb({ai[0],ai[1]});
    }

    for(int i=0;i<(int)obj.S_vertices.size();i++)
        S.pb({obj.S_vertices[i].x, obj.S_vertices[i].y});


    for(int i=0;i<(int)obj.S_edges.size();i++)
    {
        ai[0]=obj.S_edges[i].f;
        ai[1]=obj.S_edges[i].s;
        sort(ai,ai+2); Se.pb({ai[0],ai[1]});
    }

    for(int i=0;i<v3d_list.size();i++){
        float q,w;
        float x,y,z;
        x = v3d_list[i].x;
        y = v3d_list[i].y;
        z = v3d_list[i].z;
        q = (x-z)/(sqrt(2));
        w = (x + 2*y + z)/(sqrt(6));
        v3d_list[i].x = q;
        v3d_list[i].y = w;
        v3d_list[i].z = 0;
    }

    for(auto z : v3d_list){
        O.pb({z.x,z.y});
    }

    for(int i=0;i<e3d_list.size();i++){
        int v1,v2;
        v1 = e3d_list[i].f;
        v2 = e3d_list[i].s;
        if(!(v3d_list[v1] == v3d_list[v2]))
        {
            ai[0] = v1; ai[1] = v2;
            sort(ai,ai+2); Oe.pb({ai[0],ai[1]});
        }
    }
    inFile.close();
//    Form *f1 = new Form(T, Fv,  S,  O, Te,  Fe,  Se,  Oe);
//    f1->show();
    return 0;
}
