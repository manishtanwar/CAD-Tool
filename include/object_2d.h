#ifndef OBJECT_2D_H
#define OBJECT_2D_H

#include "structs.h"
#include <vector>
using namespace std;

/*! \class object_2d
    \brief representation of object_2d
*/
class object_2d{
    public:
        // Used vector for vertices as in our algorithm there is no need to delete a vertex
        std::vector<vertex_2d> T_vertices; //!< vector of co-ordinates of vertices in top-view
        std::vector<vertex_2d> F_vertices; //!< vector of co-ordinates of vertices in front-view
        std::vector<vertex_2d> S_vertices; //!< vector of co-ordinates of vertices in side-view
        std::vector<edge_2d> T_edges; //!< vector of edges in top-view
        std::vector<edge_2d> F_edges; //!< vector of edges in front-view
        std::vector<edge_2d> S_edges; //!< vector of edges in side-view

        //! Constructor
        object_2d(std::vector<vertex_2d> T_vertices, std::vector<vertex_2d> F_vertices,
            std::vector<vertex_2d> S_vertices, std::vector<edge_2d_v2v> T_edges,
            std::vector<edge_2d_v2v> F_edges, std::vector<edge_2d_v2v> S_edges);


        //! \fn Constructor which process the 3D object and returns a 2D object
        /*!
         *This constructor consists -
         *1. Converting the 3D vertex into its projected vertex
         *2. Adding the obtained projected vertex in top, front and side vertex list
         *3. There should not be an edge between overlapping points
         *4. Adding edges to the front, top and side edge list if it is an egde in the solid
         *5. On the basis of checker result edge is added in the edgelist of 2D object
        */
        object_2d(std::vector<vertex_3d> v3d_list,
         std::vector<edge_3d> e3d_list, std::vector< std::vector<edge_3d> > surface_list);

        //! function to add a vertex in the vector of vertices of Top-view
        void add_T_vertex(vertex_2d v);

        //! function to add a vertex in the vector of vertices of Front-view
        void add_F_vertex(vertex_2d v);

        //! function to add a vertex in the vector of vertices of Side-view
        void add_S_vertex(vertex_2d v);

        //! function to add an edge in the vector of edges of Top-view
        void add_T_edge(edge_2d e);

        //! function to add an edge in the vector of edges of Front-view
        void add_F_edge(edge_2d e);

        //! function to add an edge in the vector of edges of Side-view
        void add_S_edge(edge_2d e);

        //! function to convert 3D vertex to 2D vertex and returns in the form of (v_T,v_F,v_S)
        std::vector<vertex_2d> converter(vertex_3d v);

        //! function to check that an edge in 3D is also an edge in top ,front and side views
        std::vector<bool> checker(edge_3d e);


};


#endif
