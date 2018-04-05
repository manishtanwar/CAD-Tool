#ifndef BODY_loop_H
#define BODY_loop_H

#include "structs.h"
#include "faceloop_generator.h"
#include <vector>
#include <utility>
using namespace std;

class body_loop
{
public:
    std::vector<face_loop> face_loop_list;  //!< vector of face loops included in a particular body part
    std::vector<bool> side_of_face_loop; //!< vector of side of corresponding face loops list

    //! Constructor
    body_loop(std::vector<face_loop> face_loop_list);

    //! Constructor
    body_loop();

    //! function that adds face loop in the face_loop_list
    void add_face_loop(face_loop fl, bool side);

};


    //! \fn function to generate body parts
    /*!
      \param face_loop_list list of all face loops generated for the reconstruction
      \param v3d_list vector of the 3d-vertices of the 3D object
    */
    std::vector< body_loop > generate_body_loop(std::vector< face_loop > face_loop_list,
        std::vector<vertex_3d> v3d_list);
    // std::vector< pair<int,bool> > S;
    // std::vector<bool> side_used[2];
    // for both + and - side
    // bool side => side = 0 = '+' and side = 1 = '-'

    //! \fn function to find successive face loop for a face loop at a particular edge
    /*!
      \param face_loop_list list of all face loops of the object
      \param fl face loop for which successive face loop is being found
      \param side side of the face loop (i.e + or -)
      \param e edge of the face loop fl at which successive face loop has to be found
      \param e_vector 3*1 vector for direction of the edge e
      \return the index of successive face loop and its side
    */
    pair<int,bool> successive_face_loop(std::vector< face_loop > face_loop_list,
        face_loop fl, int fl_int, bool side, edge_3d e, std::vector<vertex_3d> v3d_list, bool inner_basic);

    //! function that initializes side_used for both sides + and - for every body loop
    void initialize_side_used(std::vector< pair<bool,bool> > &side_used );

    //! function that checks that if a body part generated is legal or not
    bool check_legality(body_loop bp);

    //! function that determines if give body loop is inner or outer
    bool inner_outer(body_loop bp,std::vector<vertex_3d> v3d_list);

    //algo to think => how to determine if a ray intersects with any surface of a body loop

    //! function that determines vector along ray l = @n1/|n1| + @n2/|n2|, where @ is the corresponding side
    std::vector<float> get_ray_l(plane p1, plane p2, bool s1, bool s2);

#endif


