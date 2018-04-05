#ifndef PLANAR_GRAPH_GENERATOR_H
#define PLANAR_GRAPH_GENERATOR_H

#include "structs.h"
#include "Full_plane.h"
#include <vector>


using namespace std;

    //! function that generates and retunrs planes
    std::vector< Full_plane > planar_graph_generator(std::vector<vertex_3d> v3d_list,
        std::vector<edge_3d> &e3d_list);

    //! function that constructs plane equations
    std::vector< plane > construct_planes(std::vector<vertex_3d> v3d_list,
        std::vector<edge_3d> e3d_list, std::vector< std::vector<int> > adj_list);

    //! function that returns adjacency edges list of the vertex_3d list
    std::vector< std::vector<int> > get_adj_list(std::vector<edge_3d> e3d_list,int no_of_vertices);

    //! function that eliminates duplicate formed planes
    std::vector< plane > eliminate_duplicate_planes(std::vector< plane > planes);

    //! function returns true if planar graph is legal
    bool check_legality(Full_plane &f, std::vector< std::vector<int> > adj_list);

    //! function that removes dangling and isolated edges on the planar graph using dfs
    void remove_dangling(Full_plane &f, std::vector< std::vector<int> > adj_list);

    //! function that removes those edges which belongs only to one planner graph
    void remove_single_plane_edges(std::vector<Full_plane > &f_list, std::vector<edge_3d> &e3d_list);

#endif
