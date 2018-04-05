
#include "include/faceloop_generator.h"
#include "include/general_methods.h"
#include "include/planar_graph_generator.h"
#include "include/body_loop.h"
#define epsil 0.000001
#define PI 3.14159265
#include <cmath>
#include <algorithm>
#include <iostream>
#include <map>


body_loop :: body_loop(std::vector<face_loop> face_loop_list)
{
    for(auto z : face_loop_list)
    {
        this->face_loop_list.push_back(z);
    }
}

body_loop :: body_loop()
{

}

void body_loop :: add_face_loop(face_loop fl, bool side)
{
    face_loop_list.push_back(fl);
    side_of_face_loop.push_back(side);
}

std::vector< body_loop > generate_body_loop(std::vector< face_loop > face_loop_list,
        std::vector<vertex_3d> v3d_list)
{
    std::vector< body_loop > ans;
    // F => '+'(0), S => '-'(1)
    // cout<<face_loop_list.size()<<'\n';
    std::vector< pair<bool,bool> > side_used(face_loop_list.size());
    initialize_side_used(side_used);

    pair<int,bool> curr_fl;
    while(1)
    {
        // cout<<"ii lo\n";
        std::map< pair<int,bool>, int > mp;
        int unex_in_mp=0;

        curr_fl.F = -1;
        for(int i=0;i<side_used.size();i++){
            if(side_used[i].F == false){
                curr_fl.F=i; curr_fl.S = 0;
                side_used[i].F = true; break;
            }
            if(side_used[i].S == false){
                curr_fl.F=i; curr_fl.S = 1;
                side_used[i].S = true; break;
            }
        }
        // basic_loop search ends here
        if(curr_fl.F == -1) break;

        // cout<<curr_fl.F<<' '<<curr_fl.S<<"\n";

        mp[curr_fl]=1;
        unex_in_mp++;
        while(unex_in_mp>0){
            for(auto z : mp){
                if(z.S == 1){
                    curr_fl = z.F;
                    break;
                }
            }
            // cout<<"%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%\n";
            // cout<<"curr_fl "<<curr_fl.F<<' '<<curr_fl.S<<'\n';

            for(auto z : face_loop_list[curr_fl.F].basic_loop_list){
                for(auto zz : z.edge_list){
                    // cout<<"\n";
                    // cout<<"edge: "<<zz.f<<' '<<zz.s<<"\n";
                    pair<int,bool> succ_fl = successive_face_loop(face_loop_list, face_loop_list[curr_fl.F], curr_fl.F, curr_fl.S, zz, v3d_list, z.inner);

                    // cout<<succ_fl.F<<' '<<succ_fl.S<<"\n";

                    if(mp[succ_fl] > 0) continue;
                    mp[succ_fl] = 1;
                    unex_in_mp++;
                    if(succ_fl.S == false)	side_used[succ_fl.F].F=true;
                    else	side_used[succ_fl.F].S=true;
                }
            }
            mp[curr_fl]=2;
            unex_in_mp--;
        }

        body_loop bl;
        for(auto z : mp)
        {
            bl.add_face_loop(face_loop_list[z.F.F],z.F.S);
        }
        // cout<<bl.face_loop_list.size()<<"\n";

        // if(check_legality(bl) && inner_outer(bl,v3d_list)) ans.pb(bl);
        ans.pb(bl);

//        cout<<"one finished\n";
    }
    return ans;
}

pair<int,bool> successive_face_loop(std::vector< face_loop > face_loop_list,
        face_loop fl, int fl_int, bool side, edge_3d e,
        std::vector<vertex_3d> v3d_list, bool inner_basic)
{
    edge_3d reverse_e(e.s,e.f);
    // if(!side)
    // cout<<"search at edge: "<<e.f<<' '<<e.s<<'\n';
    // else
    // cout<<"search at edge: "<<e.s<<' '<<e.f<<'\n';
    bool done = false;

    pair<int,bool> ans;
    for(int i=0;i<face_loop_list.size();i++){
        if(i== fl_int) continue; done=false;
        for(auto z : face_loop_list[i].basic_loop_list){
            for(auto zz : z.edge_list){
                if((reverse_e == zz && side == false) || (e == zz && side == true)){
                    // cout<<"mila1 :"<<zz.f<<' '<<zz.s<<'\n';
                    ans.F = i; ans.S = false; done=true;
                    if(inner_basic) {ans.S = !ans.S;}
                    if(z.inner) {ans.S = !ans.S;}
                    break;
                }
                else if((e == zz && side == false) || (reverse_e == zz && side == true)){
                    // cout<<"mila2 :"<<zz.f<<' '<<zz.s<<'\n';
                    ans.F = i; ans.S = true;done=true;
                    if(inner_basic) {ans.S = !ans.S;}
                    if(z.inner) {ans.S = !ans.S;}
                    break;
                }
            }
            // edge_3d poi(8,9);
            // if(ans.F == 5){ cout<<fl_int<<" "<<inner_basic<<" 789789 \n"; }

            if(done) break;
        }
        if(done) break;
    }
    return ans;
}

void initialize_side_used(std::vector< pair<bool,bool> > &side_used )
{
    for(int i=0;i<side_used.size();i++){
        side_used[i].first = false;
        side_used[i].second = false;
    }
}

bool check_legality(body_loop bl)
{

    std::map< pair<int,int>,int > mp;
    for(auto z : bl.face_loop_list){
        for(auto zz : z.basic_loop_list){
            for(auto z1 : zz.edge_list){
                int a[2]; a[0] = z1.f; a[1] = z1.s; std::sort(a,a+2);
                pair<int,int> p(a[0],a[1]);
                mp[p]++;
            }
        }
    }
    bool legal = true;
    for(auto z : mp){
        if(z.S != 2) {	legal = false;	break; }
    }
    return legal;
}

bool inner_outer(body_loop bp,std::vector<vertex_3d> v3d_list)
{
    //returns true if inner
    // lets assume all loops are inner
    return true;
}

std::vector<float> get_ray_l(plane p1, plane p2, bool s1, bool s2)
{

}


