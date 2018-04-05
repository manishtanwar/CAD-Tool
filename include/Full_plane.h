
#ifndef FULL_PLANE_H
#define FULL_PLANE_H

#include<vector>
#include "structs.h"

using namespace std;


/*! \class edge_2d
    \brief class for an edge_2d
*/
class Full_plane{
    public:
        plane p; //!< equation of plane i.e (a,b,c,d) for ax + by + cz + d = 0

        std::vector<int> vertices_on_it; //!< vector of enum of vertices which are on this plane

        std::vector<edge_3d> edges_on_it; //!< vector of edges which are on this plane


        //! Constructor
        Full_plane(plane p, std::vector<vertex_3d> v3d_list,
            std::vector<edge_3d> e3d_list);

        //! Constructor
        Full_plane(plane p);

        //! function to check if the vertex v is on this plane or not
        bool v_on_this_plane(vertex_3d v);

        //! function to check if the edge e is on this plane or not
        bool e_on_this_plane(vertex_3d v1,vertex_3d v2);

        //! function to add the vertices which are on this plane
        /*!
          \param v_list vertex list of 3D object
        */
        void add_vertices(std::vector<vertex_3d> v3d_list);

        //! function to add the edges which are on this plane
        /*!
          \param e_list edge list of 3D object
        */
        void add_edges(std::vector<edge_3d> e3d_list, std::vector<vertex_3d> v3d_list);
};

#endif
