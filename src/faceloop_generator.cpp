#include "include/faceloop_generator.h"
#include "include/general_methods.h"
#include "include/planar_graph_generator.h"
#define epsil 0.000001
#include <cmath>
#include <algorithm>
#include <iostream>

basic_loop :: basic_loop(std::vector<edge_3d> loop, bool inner)
{
    this->inner = inner;
    for(auto z : loop)
    {
        edge_list.push_back(z);
    }
}

face_loop :: face_loop(std::vector< basic_loop > basic_loop_list, plane p)
{
    this->p.a = p.a;
    this->p.b = p.b;
    this->p.c = p.c;
    this->p.d = p.d;

    for(auto z : basic_loop_list)
    {
        this->basic_loop_list.push_back(z);
    }
}

void face_loop :: add_basic_loop(basic_loop bl)
{
    basic_loop_list.push_back(bl);
}

std::vector< face_loop > generate_face_loops(plane p, std::vector<int> vertices_on_the_plane,
        std::vector<edge_3d> &edges_on_the_plane, std::vector<vertex_3d> v3d_list)
{
    // cout<<"1\n";
    std::vector< std::vector<int> > ordered_adj_list = generate_ordered_adj_list(edges_on_the_plane,
     vertices_on_the_plane, v3d_list);
    // cout<<"2\n";int y=0;
    // for(auto z : ordered_adj_list){
    // 	cout<<++y<<" -> ";
    // 	for(auto zz : z) cout<<zz+1<<' ';
    // 	cout<<"\n";
    // }
    std::vector< basic_loop > basic_loop_list = basic_loop_generator(edges_on_the_plane, ordered_adj_list);
    // cout<<"3\n"; int ind=0;
    // for(auto z : basic_loop_list){
    // 	cout<<"Basic Loop: #"<<ind++<<'\n';
    // 	for(auto zzzz : z.edge_list){
    // 		cout<<"edge"<<' '<<zzzz.f<<' '<<zzzz.s<<"\n";
    // 	}
    // }
    std::vector< std::vector<bool> > inclusion_matrix = generate_inclusion_matrix(basic_loop_list, v3d_list);
    // cout<<"4\n";
    std::vector< face_loop > ans;
    std::vector< bool > done(basic_loop_list.size(),false);
    int count=done.size();

    // int i=0;
    // for(auto zzz : basic_loop_list){i++;
    // 	cout<<"Basic Loop: #"<<i<<'\n';
    // 	for(auto zzzz : zzz.edge_list){
    // 		cout<<"edge"<<' '<<zzzz.f<<' '<<zzzz.s<<"\n";
    // 	}
    // }
    // cout<<"<<\n";
    // for(auto z : inclusion_matrix){
    // 	for(auto zz : z)cout<<zz<<' ';cout<<'\n';
    // }
    // cout<<">>\n";


    while(count > 0){
        std::vector<basic_loop> curr_basic_loop_list;
        for(int i=0;i<done.size();i++){ if(done[i]) continue;
            int included_by=0;
            for(int j=0;j<done.size();j++){
                if(inclusion_matrix[j][i]) {included_by++;break;}
            }
            if(included_by==0){
                // cout<<"YAHPPPPPPPPPPPPPPPPPPPPPP\n";
                curr_basic_loop_list.pb(basic_loop_list[i]); count--;
                done[i]=true;
                for(int j=0;j<done.size();j++){ if(done[j]) continue;
                    if(inclusion_matrix[i][j]){
                    basic_loop_list[j].inner = true;
                    // cout<<"INNER HAI Be\n";
                    // cout<<basic_loop_list[j].inner<<"\n";
                    curr_basic_loop_list.pb(basic_loop_list[j]);
                    count--; done[j]=true;
                    }
                }
            }
        }
        face_loop curr(curr_basic_loop_list,p);
        ans.pb(curr);
    }
    // cout<<"3\n"; int ind=0;
    // for(auto z : basic_loop_list){
    // 	cout<<"Basic Loop: #"<<ind++<<'\n';
    // 	for(auto zzzz : z.edge_list){
    // 		cout<<"edge"<<' '<<zzzz.f<<' '<<zzzz.s<<"\n";
    // 	}
    // }
    return ans;
}

bool compare_angles(std::pair< int,std::pair<float,bool> > lhs,
 std::pair< int,std::pair<float,bool> > rhs)
{
    if(lhs.S.S == false && rhs.S.S == false) return (lhs.S.F > rhs.S.F);
    if(lhs.S.S == true && rhs.S.S == true)   return (lhs.S.F < rhs.S.F);
    if(lhs.S.S == true  && rhs.S.S == false) return true;
    if(lhs.S.S == false && rhs.S.S == true)  return false;
}

// sort the edges on the basis of clockwise direction
void sort_edges(std::vector<int> &v,int i, std::vector<vertex_3d> v3d_list)
{
    if(v.size() <= 1) return ;
    vertex_3d v1,v2,v3,v4;
    v1 = v3d_list[v[0]];
    v1.shift_it(v3d_list[i]);
    // pair<f,s> f = angle b/w v1 and v[j]-v[i], s = up or down
    v2 = v3d_list[v[1]];
    v2.shift_it(v3d_list[i]);
    v2 = cross_product(v1,v2);
    std::vector< std::pair< int,std::pair<float,bool> > > vec;
    // v2 is reference cross product for upper or lower halver distinguising
    for(auto z : v){
        std::pair< int,std::pair<float,bool> > ele;
        v3 = v3d_list[z];
        v3.shift_it(v3d_list[i]);
        ele.second.first = dot_product(v3,v1);
        ele.second.first /= v1.length_of_it() * v3.length_of_it();
        v3 = cross_product(v1,v3);
        float dir = dot_product(v2,v3);
        if(dir >= 0) ele.second.second = true;
        else ele.second.second = false;
        ele.first = z;
        vec.push_back(ele);
    }
    std::sort(vec.begin(),vec.end(),compare_angles);

    v.clear();
    for(auto z : vec) v.pb(z.F);
}

std::vector< std::vector<int> > generate_ordered_adj_list(std::vector<edge_3d> edges_on_the_plane, std::vector<int> vertices_on_the_plane, std::vector<vertex_3d> v3d_list)
{
    std::vector< std::vector<int> > adj_list = get_adj_list(edges_on_the_plane,v3d_list.size());
    // get_adj_list is called from planar_graph_generator

    for(auto z : vertices_on_the_plane)
    {
        sort_edges(adj_list[z],z,v3d_list);
        // sort the adjacent list at z index as z is referenced from main v3d list
    }

    return adj_list;

}


std::vector< basic_loop > basic_loop_generator(std::vector<edge_3d> &edges_on_the_plane,
        std::vector< vector<int> > ordered_adj_list)
{
    std::vector<bool> visited(edges_on_the_plane.size(),false);
    int Vstart,Vend,Vnext,Vstart_prev;
    std::vector< basic_loop > ans;
    std::vector< edge_3d > loop;
    while(1){
        loop.clear();
        int j=-1;
        for(int i=0;i<visited.size();i++){
            if(!visited[i]) {j=i;break;}
        }
        if(j==-1) break; int k; visited[j]=true;

        // cout<<"edges_on_the_plane \n";
        // for(auto z : edges_on_the_plane) cout<<z.f<<' '<<z.s<<'\n';
        // cout<<"end\n";

        Vstart = edges_on_the_plane[j].f;
        Vend = edges_on_the_plane[j].s;
        // cout<<"Vstart "<<Vstart<<' '<<Vend<<"\n";
        loop.pb(edge_3d (Vend,Vstart));
        Vstart_prev = Vend;
        while(Vstart != Vend){
            for(int i=0;i<ordered_adj_list[Vstart].size();i++){
                if(ordered_adj_list[Vstart][i] == Vstart_prev){
                    k=i; break;
                }
            }
            if(k == ordered_adj_list[Vstart].size()-1) Vnext = ordered_adj_list[Vstart][0];
            else Vnext = ordered_adj_list[Vstart][k+1];
            edge_3d eNext(Vstart,Vnext); edge_3d eNext1(Vnext,Vstart);
            Vstart_prev = Vstart;
            Vstart = Vnext;
            // cout<<Vstart<<"\n";
            // cout<<eNext.f<<' '<<eNext.s<<"\n";
            // cout<<eNext1.f<<' '<<eNext1.s<<"\n";
            loop.pb(eNext);
            for(int i=0;i<edges_on_the_plane.size();i++){
                if(edges_on_the_plane[i] == eNext) {visited[i]=true;j=i;break;}
                if(edges_on_the_plane[i] == eNext1) {visited[i]=true;j=i;break;}
            }

        }
        // cout<<"loop =>\n";
        // for(auto z : loop) cout<<z.f<<' '<<z.s<<"\n";
        // cout<<"loop done\n";
        ans.pb(basic_loop (loop,false));
    }
    // cout<<"done\n";
    return ans;
}

bool is_in_it(vertex_3d v1, basic_loop b, std::vector<vertex_3d> v3d_list){
    bool final_ans = true;
    for(int wq=0;wq<b.edge_list.size();wq++){
        vertex_3d v2,v3,v4,e,f,g,e1,v5,v6; v2 = v3d_list[b.edge_list[wq].f];
        int cnt=0; e = v1; e.shift_it(v2);
        float a,h,k;
        std::vector<vertex_3d> intersections_list;
        // cout<<"here we go \n";
        // v1.printit(); cout<<'\n';
        // v2.printit(); cout<<'\n';
        for(auto z : b.edge_list){
            e = v1; e.shift_it(v2);
            v3 = v3d_list[z.f]; v4 = v3d_list[z.s];
            // v3.printit(); cout<<' '; v4.printit(); cout<<'\n';
            f = v3; f.shift_it(v4);
            g = v1; g.shift_it(v3);
            // e.printit(); cout<<'\n'; f.printit(); cout<<'\n'; g.printit(); cout<<'\n';
            g = cross_product(e,g);
            e1 = e;
            e = cross_product(e,f);
            // g.printit(); cout<<' '; e.printit(); cout<<'\n';
            a = dot_product(e,g);
            h = g.length_of_it();k = e.length_of_it();
            //if(std::abs(h) < epsil || std::abs(k) < epsil) continue;
            // cout<<a<<' '<<h<<' '<<k<<"\n";
            if(std::abs(k) < epsil) continue;
            h /= k; if(a > 0) h = -h;
            f.x *= h; f.y *= h; f.z *= h;
            v3.shift_it(f);
            // v3 is the intersection


            v5 = v3; v6 = v3;
            v5.shift_it(v3d_list[z.f]); v6.shift_it(v3d_list[z.s]);
            float lets_decide = dot_product(v5,v6);
            if(lets_decide <= 0)
            intersections_list.pb(v3);
            else continue;
            // cout<<"The inetersection :"; v3.printit(); cout<<'\n';
        }
        // cout<<"done\n\n";
        // v1.printit(); cout<<' '; v2.printit(); cout<<'\n';
        // cout<<"intersections_list"<<'\n';
        // for(auto z : intersections_list) z.printit(), cout<<' ';
        // cout<<"\n end of intersections_list \n";
        if(intersections_list.size() < 2) return false;
        // removed this part as a vertex should be counted twice
        std::vector<bool> remove_them(intersections_list.size(), false);
        for(int i=0;i<intersections_list.size();i++){
            for(int j=i+1;j<intersections_list.size();j++){
                float x,y,z,x1,y1,z1;
                x  = intersections_list[i].x; y  = intersections_list[i].y; z = intersections_list[i].z;
                x1 = intersections_list[j].x; y1 = intersections_list[j].y; z1 = intersections_list[j].z;
                x -= x1; y-=y1; z-=z1; x*=x; y*=y; z*=z;
                x += y+z;
                if(x < epsil){
                    remove_them[i]=true; break;
                }
            }
        }
        for(int i=remove_them.size()-1;i>=0;i--){
            if(remove_them[i]) intersections_list.erase(intersections_list.begin()+i);
        }
        v2 = intersections_list[0]; v2.shift_it(v1);
        if(intersections_list.size() < 2) return false;
        for(int i=1;i<intersections_list.size();i++){
            v3=intersections_list[i]; v3.shift_it(v1);
            a = dot_product(v2,v3);
            if(a > 0) cnt++;
        }
        cnt++;
        if(cnt%2) final_ans = final_ans & true;
        else final_ans = final_ans & false;
    }
    return final_ans;



    // old--> jo shi chal rha tha
    // vertex_3d v2,v3,v4,e,f,g,e1,v5,v6; v2 = v3d_list[b.edge_list[0].f];
    // int cnt=0; e = v1; e.shift_it(v2);
    // float a,h,k;
    // std::vector<vertex_3d> intersections_list;
    // // cout<<"here we go \n";
    // // v1.printit(); cout<<'\n';
    // // v2.printit(); cout<<'\n';
    // for(auto z : b.edge_list){
    // 	e = v1; e.shift_it(v2);
    // 	v3 = v3d_list[z.f]; v4 = v3d_list[z.s];
    // 	// v3.printit(); cout<<' '; v4.printit(); cout<<'\n';
    // 	f = v3; f.shift_it(v4);
    // 	g = v1; g.shift_it(v3);
    // 	// e.printit(); cout<<'\n'; f.printit(); cout<<'\n'; g.printit(); cout<<'\n';
    // 	g = cross_product(e,g);
    // 	e1 = e;
    // 	e = cross_product(e,f);
    // 	// g.printit(); cout<<' '; e.printit(); cout<<'\n';
    // 	a = dot_product(e,g);
    // 	h = g.length_of_it();k = e.length_of_it();
    // 	//if(std::abs(h) < epsil || std::abs(k) < epsil) continue;
    // 	// cout<<a<<' '<<h<<' '<<k<<"\n";
    // 	if(std::abs(k) < epsil) continue;
    // 	h /= k; if(a > 0) h = -h;
    // 	f.x *= h; f.y *= h; f.z *= h;
    // 	v3.shift_it(f);
    // 	// v3 is the intersection


    // 	v5 = v3; v6 = v3;
    // 	v5.shift_it(v3d_list[z.f]); v6.shift_it(v3d_list[z.s]);
    // 	float lets_decide = dot_product(v5,v6);
    // 	if(lets_decide <= 0)
    // 	intersections_list.pb(v3);
    // 	else continue;
    // 	// cout<<"The inetersection :"; v3.printit(); cout<<'\n';
    // }
    // // cout<<"done\n\n";
    // // v1.printit(); cout<<' '; v2.printit(); cout<<'\n';
    // // cout<<"intersections_list"<<'\n';
    // // for(auto z : intersections_list) z.printit(), cout<<' ';
    // // cout<<"\n end of intersections_list \n";
    // if(intersections_list.size() < 2) return false;
    // // removed this part as a vertex should be counted twice
    // std::vector<bool> remove_them(intersections_list.size(), false);
    // for(int i=0;i<intersections_list.size();i++){
    // 	for(int j=i+1;j<intersections_list.size();j++){
    // 		float x,y,z,x1,y1,z1;
    // 		x  = intersections_list[i].x; y  = intersections_list[i].y; z = intersections_list[i].z;
    // 		x1 = intersections_list[j].x; y1 = intersections_list[j].y; z1 = intersections_list[j].z;
    // 		x -= x1; y-=y1; z-=z1; x*=x; y*=y; z*=z;
    // 		x += y+z;
    // 		if(x < epsil){
    // 			remove_them[i]=true; break;
    // 		}
    // 	}
    // }
    // for(int i=remove_them.size()-1;i>=0;i--){
    // 	if(remove_them[i]) intersections_list.erase(intersections_list.begin()+i);
    // }
    // v2 = intersections_list[0]; v2.shift_it(v1);
    // if(intersections_list.size() < 2) return false;
    // for(int i=1;i<intersections_list.size();i++){
    // 	v3=intersections_list[i]; v3.shift_it(v1);
    // 	a = dot_product(v2,v3);
    // 	if(a > 0) cnt++;
    // }
    // cnt++;

    // // v1.printit();cout<<' '<<cnt<<'\n';
    // if(cnt%2) return true;
    // return false;
}

bool included(basic_loop b1, basic_loop b2, std::vector<vertex_3d> v3d_list){
    bool ans = true; vertex_3d a,b;
    for(auto z : b2.edge_list){
        a = v3d_list[z.f]; b = v3d_list[z.s];
        // cout<<"included"<<"\n";
        // a.printit(); cout<<' ';
        // b.printit(); cout<<'\n';
        if((!(is_in_it(a,b1,v3d_list))) || (!(is_in_it(b,b1,v3d_list))))
        {
            // cout<<(is_in_it(a,b1,v3d_list))<<"\n";
            // cout<<(is_in_it(b,b1,v3d_list))<<"\n";
            ans=false;break;
        }
    }
    return ans;
}

std::vector< std::vector<bool> > generate_inclusion_matrix(std::vector< basic_loop > basic_loop_list,
        std::vector<vertex_3d> v3d_list)
{
    std::vector< std::vector<bool> > ans(basic_loop_list.size());

    for(auto z : ans){
        for(int i=0;i<basic_loop_list.size();i++) z.pb(false);
    }
    for(int i=0;i<ans.size();i++){
        for(int j=0;j<ans.size();j++){
            if(i == j) {ans[i].pb(false);continue;}
            if( included(basic_loop_list[i], basic_loop_list[j], v3d_list)) {ans[i].pb(true);}
            else ans[i].pb(false);
        }
    }
    return ans;
}




