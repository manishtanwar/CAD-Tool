#ifndef STRUCTS_H
#define STRUCTS_H
#define F first
#define S second
#define pb push_back

/*! \class vertex_2d
    \brief class for a vertex_2d
*/
class vertex_2d{
    public:
        float x; //!< x-coordinate of the vertex
        float y; //!< y-coordinate of the vertex

        //! Constructor
        vertex_2d(float x, float y);

        //! Constructor
        vertex_2d();

        //! bool operator == for vertex_2d
        bool operator == (const vertex_2d& rhs);

        //! bool operator < for vertex_2d
        bool operator < (const vertex_2d& rhs);

        //! function to shift a vertex wrt to a reference vertex
        /*!
          \param ref_vertex reference vertex chosen as origin
        */
        void shift_it(vertex_2d ref_vertex);
};


/*! \class edge_2d
    \brief class for an edge_2d
*/
class edge_2d{
    public:
        int f; //!< position of first end-point of the edge in v_list
        int s; //!< position of second end-point of the edge in v_list
        bool dash;   //!< boolean for if edge is dash or solid

        //! Constructor
        edge_2d(int f, int s);
};

/*! \class edge_2d_v2v
    \brief class for an edge_2d_v2v
*/
class edge_2d_v2v{
    public:
        vertex_2d f; //!< first end-point
        vertex_2d s; //!< second end-point
        bool dash;   //!< boolean for if edge is dash or solid

        //! Constructor
        edge_2d_v2v(vertex_2d f, vertex_2d s);
};

/*! \class vertex_3d
    \brief class for a vertex_3d
*/
class vertex_3d{
    public:
        float x; //!< x-coordinate of the vertex
        float y; //!< y-coordinate of the vertex
        float z; //!< z-coordinate of the vertex

        vertex_3d();

        //! Constructor
        vertex_3d(float x, float y, float z);

        //! bool operator == for vertex_3d
        bool operator == (const vertex_3d& rhs);

        //! bool operator < for vertex_3d
        bool operator < (const vertex_3d& rhs);

        //! function to shift a vertex wrt to a reference vertex
        /*!
          \param ref_vertex reference vertex chosen as origin
        */
        void shift_it(vertex_3d ref_vertex);

        //!print();
        void printit();

        //! length of a vector
        float length_of_it();
};

/*! \class edge_3d
    \brief class for an edge_3d
*/
class edge_3d{
    public:
        int f; //!< position of first end-point of the edge in v_list
        int s; //!< position of second end-point of the edge in v_list

        //! Constructor
        edge_3d(int f, int s);

        //! bool operator == for edge_3d
        bool operator == (const edge_3d& rhs);
};

/*! \class plane
    \brief class for a plane
    plane represented as (a,b,c,d) corresponding to the equation ax + by + cz  = d
*/
class plane{
    public:
        float a;
        float b;
        float c;
        float d;

        //! constructor for a plane
        /*!
          This constructor edits (a,b,c,d) as following -
          if d is non-zero (a',b',c',d') = (a/d,b/d,c/d,1)
          else
            if c is non-zero (a',b',c',0) = (a/c,b/c,1,0)
            else
                if b is non-zero (a',b',0,0) = (a/b,1,0,0)
                else
                    (a'0,0,0) = (1,0,0,0)
        */
        plane(float a, float b, float c, float d);

        //! constructor for a plane
        plane();

        //!print();
        void printit();
};

#endif
