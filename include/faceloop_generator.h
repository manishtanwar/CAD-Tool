#ifndef FACELOOP_GENERATOR_H
#define FACELOOP_GENERATOR_H

#include "structs.h"
#include "Full_plane.h"
// #include "Object_3D.h"
#include <vector>
using namespace std;

/*! \class basic_loop
*/
class basic_loop{
public:

    std::vector<edge_3d> edge_list;  //!< vector of edges included in the loop
    bool inner;					//!< bool is true if loop is inner

    //! Constructor
    basic_loop(std::vector<edge_3d> loop, bool inner);
};


/*! \class face_loop
*/
class face_loop
{
public:

    std::vector< basic_loop > basic_loop_list; //!< vector of basic_loop included in the faceloop
    plane p; //!< equation of plane on which faceloop is

    //! Constructor
    face_loop(std::vector< basic_loop > basic_loop_list, plane p);

    //! function that adds basic loop in the basic_loop_list
    void add_basic_loop(basic_loop bl);
};

    //! \fn function to generate face loops
        /*!
          \param p plane for which face_loops are being calculated
          \param edges_on_the_plane vector of the edges which are on this plane
          \param v3d_list vertex list of the 3d object
        */
    std::vector< face_loop > generate_face_loops(plane p, std::vector<int> vertices_on_the_plane,
        std::vector<edge_3d> &edges_on_the_plane, std::vector<vertex_3d> v3d_list);

    //! function to generate ordered adj_list in clockwise direction
    std::vector< std::vector<int> > generate_ordered_adj_list(std::vector<edge_3d> edges_on_the_plane, std::vector<int> vertices_on_the_plane, std::vector<vertex_3d> v3d_list);

    //! function that generates basic loops
    std::vector< basic_loop > basic_loop_generator(std::vector<edge_3d> &edges_on_the_plane,
        std::vector< vector<int> > ordered_adj_list);

    // https://www.geeksforgeeks.org/how-to-check-if-a-given-point-lies-inside-a-polygon/
    //! function to generate inclusion matrix
    std::vector< std::vector<bool> > generate_inclusion_matrix(std::vector< basic_loop > basic_loop_list,
        std::vector<vertex_3d> v3d_list);

#endif
