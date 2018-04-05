#include "include/structs.h"
#include "include/object_2d.h"
#include "include/Object_3d.h"
#include "include/2d_to_3d.h"
#include "form.h"
#include <bits/stdc++.h>

#undef scroll
#include <QWidget>

using namespace std;


int two_d_to_three_d(string file, string outfile)
{

    ifstream inFile;
    int na = outfile.length();
    if(na > 4)
    {
        string tmp = outfile.substr(na-4,4);
        if(tmp != ".obj")
            outfile += ".obj";
    }
    else
        outfile += ".obj";

    ofstream outFile(outfile);

    inFile.open(file);
    if(!inFile) return 1;

    int no_of_vertices;
        inFile>>no_of_vertices;


    std::vector<vertex_2d> T_vertices; //!< vector of co-ordinates of vertices in top-view
    std::vector<vertex_2d> F_vertices; //!< vector of co-ordinates of vertices in front-view
    std::vector<vertex_2d> S_vertices; //!< vector of co-ordinates of vertices in side-view
    std::vector<edge_2d_v2v> T_edges; //!< vector of edges in top-view
    std::vector<edge_2d_v2v> F_edges; //!< vector of edges in front-view
    std::vector<edge_2d_v2v> S_edges; //!< vector of edges in side-view
    //outFile<<no_of_vertices<<" oho "<<endl;
    while(no_of_vertices--)
    {
        float a,b; vertex_2d v(0,0);
        inFile>>a>>b;
        v.x = -b; v.y = a;
        T_vertices.pb(v);
        inFile>>a>>b;
        v.x = -b; v.y = a;
        F_vertices.pb(v);
        inFile>>a>>b;
        v.x = -b; v.y = a;
        S_vertices.pb(v);
    }

    int n;
    inFile>>n;
//    outFile<<n<<endl;
    while(n--)
    {
        int a,b;
        inFile>>a>>b;

        vertex_2d v1(0,0); v1.x = -b; v1.y = a;
        inFile>>a>>b;
        vertex_2d v2(0,0); v2.x = -b; v2.y = a;

        edge_2d_v2v e(v1,v2);
        T_edges.pb(e);
    }

    inFile>>n;
//    outFile<<n<<endl;
    while(n--)
    {
        int a,b;
        inFile>>a>>b;

        vertex_2d v1(0,0); v1.x = -b; v1.y = a;
        inFile>>a>>b;
        vertex_2d v2(0,0); v2.x = -b; v2.y = a;

        edge_2d_v2v e(v1,v2);
        F_edges.pb(e);
    }

    inFile>>n;
//    outFile<<n<<endl;
    while(n--)
    {
        int a,b;
        inFile>>a>>b;

        vertex_2d v1(0,0); v1.x = -b; v1.y = a;
        inFile>>a>>b;
        vertex_2d v2(0,0); v2.x = -b; v2.y = a;

        edge_2d_v2v e(v1,v2);
        S_edges.pb(e);
    }

    object_2d o(T_vertices, F_vertices, S_vertices, T_edges, F_edges, S_edges);

    Object_3d ans(o);
    outFile<<setprecision(7);
    for(auto z : ans.v3d_list){
        outFile<<"v "<<z.y<<' '<<(-z.x)<<' '<<z.z<<'\n';
    }
    for(auto z : ans.surface_list){
        outFile<<"f ";
        for(auto zz : z){
            outFile<<zz+1<<' ';
        }
        outFile<<"\n";
    }
    outFile.close();
    inFile.close();



//    Form *f1 = new Form(T, Fv,  S,  O, Te,  Fe,  Se,  Oe);
//    f1->show();
    return 0;
}

