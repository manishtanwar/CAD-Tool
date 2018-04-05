#include "include/planar_graph_generator.h"
#include "include/general_methods.h"
#include<iostream>

#define epsilon 0.000001

//! function that generates and retunrs planes
    std::vector< Full_plane > planar_graph_generator(std::vector<vertex_3d> v3d_list,
        std::vector<edge_3d> &e3d_list){
        std::vector< std::vector<int> > adj_list = get_adj_list(e3d_list, v3d_list.size());

        std::vector<plane> planes_list = construct_planes(v3d_list, e3d_list, adj_list);

        planes_list =  eliminate_duplicate_planes(planes_list);

        std::vector< Full_plane > ans;
        for(int i=0; i<planes_list.size(); i++){
            Full_plane f1(planes_list[i], v3d_list, e3d_list);
            if(check_legality(f1,adj_list))
                ans.push_back(f1);
        }
        remove_single_plane_edges(ans,e3d_list);
        return ans;
    }

    //! function that constructs plane equations
    std::vector< plane > construct_planes(std::vector<vertex_3d> v3d_list,
        std::vector<edge_3d> e3d_list, std::vector< std::vector<int> > adj_list){
        std::vector<plane> planes_list;
        for(int i=0; i<adj_list.size(); i++){

            for(int j=0; j<adj_list[i].size(); j++){
                for(int k=j+1; k<adj_list[i].size(); k++){
                    int p1,p2; p1= adj_list[i][j];
                    p2= adj_list[i][k]; vertex_3d v1,v2;
                    v1 = v3d_list[i]; v1.shift_it(v3d_list[p1]);
                    v2 = v3d_list[i]; v2.shift_it(v3d_list[p2]);
                    v1 = cross_product(v1,v2);
                    v2 = v3d_list[p2];
                    float d = dot_product(v1,v2);
                    planes_list.push_back(plane (v1.x,v1.y,v1.z,d));
                }
            }
        }
        return planes_list;
    }

    //! function that returns adjacency edges list of the vertex_3d list
    std::vector< std::vector<int> > get_adj_list(std::vector<edge_3d> e3d_list, int no_of_vertices){
        std::vector< std::vector<int> > v(no_of_vertices);
        for(auto z : e3d_list)
            v[z.f].push_back(z.s), v[z.s].push_back(z.f);
        return v;
    }

    //! function that eliminates duplicate formed planes
    std::vector< plane > eliminate_duplicate_planes(std::vector< plane > planes){
        int n = planes.size();
        std::vector<bool> useful(n,true);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                // condition
                float diff,a,b,c,d;
                a = planes[i].a - planes[j].a;
                b = planes[i].b - planes[j].b;
                c = planes[i].c - planes[j].c;
                d = planes[i].d - planes[j].d;
                diff = a*a + b*b + c*c + d*d;
                if(diff < epsilon)
                    {useful[i]=false; break;}
            }
        }
        std::vector<plane> ans;
        for(int i=0;i<n;i++)
            if(useful[i]) ans.push_back(planes[i]);
        return ans;
    }

    //! function returns true if planar graph is legal
    bool check_legality(Full_plane &f, std::vector< std::vector<int> > adj_list){
        if(f.edges_on_it.size() <= 2) return false;

        remove_dangling(f, adj_list);
        if(f.edges_on_it.size() == 0)
            return false;
        return true;
    }

    //! function that removes dangling and isolated edges on the planar graph using dfs
    void remove_dangling(Full_plane &f, std::vector< std::vector<int> > adj_list){
        bool end_it;
        while(true)
        {
            end_it=true;
            for(int j=0; j<f.vertices_on_it.size(); j++){
                int cnt=0; int z = f.vertices_on_it[j];
                for(auto zz : adj_list[z]){
                    for(auto y : f.vertices_on_it){
                        if(zz == y) {cnt++; break;}
                    }
                }
                if(cnt < 2){
                    f.vertices_on_it.erase(f.vertices_on_it.begin()+j);
                    j--;
                    end_it = false;
                }
            }
            if(end_it) break;
        }
        for(int j=0; j<f.edges_on_it.size(); j++){
            int k,l; k = f.edges_on_it[j].f; l = f.edges_on_it[j].s;
            bool k1,l1; k1=l1= false;
            for(auto z : f.vertices_on_it){
                if(z == k) k1 = true;
                if(z == l) l1 = true;
            }
            if(!(k1 && l1)) f.edges_on_it.erase(f.edges_on_it.begin()+j), j--;
        }
    }

    void remove_single_plane_edges(std::vector<Full_plane > &f_list, std::vector<edge_3d> &e3d_list)
    {
        std::vector<int> remove_these;

        for(int i=0;i<e3d_list.size(); i++)
        {
            int cnt = 0;
            for(auto z : f_list)
            {
                int j=0;
                for(auto zz : z.edges_on_it)
                {
                    if(zz == e3d_list[i])
                        cnt++;
                    j++;
                }
            }
            if(cnt < 2){
                remove_these.push_back(i);
                int ple=0;
                for(auto z : f_list){
                    for(int j=z.edges_on_it.size()-1; j>=0;j--){
                        if(e3d_list[i] == z.edges_on_it[j])
                        {
                            f_list[ple].edges_on_it.erase(f_list[ple].edges_on_it.begin()+j);
                        }
                    }
                    ple++;
                }
            }
        }
        for(int i=remove_these.size()-1 ; i>=0; i--)
        {
            e3d_list.erase(e3d_list.begin()+remove_these[i]);
        }
    }

