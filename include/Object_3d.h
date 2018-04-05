#ifndef OBJECT_3D_H
#define OBJECT_3D_H

#include "structs.h"
#include <vector>
#include "object_2d.h"
using namespace std;

// class object_2d;

/*! \mainpage COP290 - Orthographic views of a solid and Reconstruction of Solid from given orthographic projections - Documentation
 *
 * \section intro_sec INTRODUCTION
 *
 * The objective of this project is to design and implement a software package which reconstructs a 3-D object from its given orthographic views and from the given 3-D object
 * gives its projections on a given cutting plane and its orthographic views(top, front, right side
 * view). This document mainly talks about the mathematical model involved in this project
 * and the algorithms to achieve the same. In this project we are considering only polyhedron
 * 3-D objects which have flat polygon faces. For reconstruction of any polyhedron object, 3
 * orthographic views are sufficient and 2 orthographic views are necessary as some symmetric
 * polyhedron objects can be uniquely reconstructed from 2 orthographic views.
 *
 \section assumption_sec ASSUMPTIONS
  \subsection subsection1 3D to 2D Transformation -
  The projected views provided in the input are top view, front view and right side view of the object.
  Hidden lines are also treated as solid lines.
  \subsection subsection2 2D to 3D Transformation -
  Hidden lines also being shown as solid lines. The information provided about the object forms a valid 3D object. Provided projection forms a valid object.
 */



/*! \class Object3d
    \brief class for representation of a 3D object
*/
class Object_3d
{
    public :
        std::vector<vertex_3d> v3d_list;  //!< vector of 3d vertices

        std::vector<edge_3d> e3d_list; //!< vector of 3d edges

        std::vector< std::vector<int> > surface_list; //!< vector of surfaces, one surface is vector of 3d edges
                                                          //!<

        //! Constructor
        Object_3d(std::vector<vertex_3d> v3d_list,
         std::vector<edge_3d> e3d_list, std::vector<std::vector<int> > surface_list);

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
        Object_3d(object_2d o);

        Object_3d();

        // **************** how to generate surfaces ?? ***********

        //! function to add a vertex in the vector of vertices
        void add_vertex(vertex_3d v);

        //! function to add an edge in the vector of edges
        void add_edge(edge_3d e);

        //! function to remove an edge in the vector of edges
        void remove_edge(edge_3d e);

    private:

        //! function to add vertices_3d form T,F,S 2d coordinate
        void add_vertices(std::vector<vertex_2d> T_vertices, std::vector<vertex_2d> F_vertices,
            std::vector<vertex_2d> S_vertices);

        //! function to add edges_3d corresponding to the edges in top, front and side view
        void decision_tree(object_2d o);

        //! function that returns true if edge_2d e is an edge in the front-view
        bool is_front_edge(std::vector<vertex_2d> F_vertices, std::vector<edge_2d> F_edges, edge_2d e);

        //! function that returns true if edge_2d e is an edge in the side-view
        bool is_side_edge(std::vector<vertex_2d> S_vertices, std::vector<edge_2d> S_edges, edge_2d e);

        //! function that returns true if two edge_3d in the 3D_object are collinear
        bool is_collinear(edge_3d e1, edge_3d e2);

        //! function to check if edge e overlaps with any one of the edges of E
        bool is_overlapping(std::vector<edge_3d> E, edge_3d e);

        //! Redundant Edges Removal procedure
        void RER();

        //! function to sort vertex of collinear edges
        void sort_vertices(std::vector<int> &vertices);
};

#endif
