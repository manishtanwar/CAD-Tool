#include "include/structs.h"

#define epsilon 0.000001
#include <cmath> // for abs
#include <iostream>

vertex_2d::vertex_2d(float x, float y)
{
    this->x = x; this->y = y;
}

vertex_2d::vertex_2d()
{
    this->x = 0; this->y = 0;
}

bool vertex_2d::operator == (const vertex_2d& rhs)
{
    return ( std::abs(x-rhs.x) < epsilon ) && ( std::abs(y-rhs.y) < epsilon );
}

bool vertex_2d::operator < (const vertex_2d& rhs)
{
    if(std::abs(x-rhs.x) > epsilon)
    {
        return (x < rhs.x);
    }
    return (y < rhs.y);
}

void vertex_2d::shift_it(vertex_2d ref_vertex)
{
    x -= ref_vertex.x; y -= ref_vertex.y;
}

edge_2d::edge_2d(int f, int s)
{
    this->f = f; this->s = s; dash = 0;
}

edge_2d_v2v::edge_2d_v2v(vertex_2d f, vertex_2d s)
{
    this->f = f; this->s = s; dash = 0;
}

vertex_3d::vertex_3d(float x, float y, float z)
{
    this->x = x; this->y = y;	this->z = z;
}

vertex_3d::vertex_3d()
{
    this->x = 0; this->y = 0;	this->z = 0;
}

void vertex_3d::printit()
{
    std::cout<<"vertex_3d "<<x<<' '<<y<<' '<<z;
}

bool vertex_3d::operator == (const vertex_3d& rhs)
{
    return ( std::abs(x-rhs.x) < epsilon ) && ( std::abs(y-rhs.y) < epsilon ) && ( std::abs(z-rhs.z) < epsilon );
}


bool vertex_3d::operator < (const vertex_3d& rhs)
{
    if( std::abs(x-rhs.x) > epsilon && x < rhs.x) return true;
    if( std::abs(x-rhs.x) > epsilon && x > rhs.x) return false;
    if( std::abs(y-rhs.y) > epsilon && y < rhs.y) return true;
    if( std::abs(y-rhs.y) > epsilon && y > rhs.y) return false;
    if( std::abs(z-rhs.z) > epsilon && z < rhs.z) return true;
    return false;
}

void vertex_3d::shift_it(vertex_3d ref_vertex)
{
    x -= ref_vertex.x; y -= ref_vertex.y; z -= ref_vertex.z;
}

float vertex_3d::length_of_it()
{
    float r = (x*x + y*y + z*z);
    r = std::sqrt(r);
    return r;
}

edge_3d::edge_3d(int f, int s)
{
    this->f = f;	this->s = s;
}

bool edge_3d::operator == (const edge_3d& rhs)
{
    return ( f == rhs.f ) && ( s == rhs.s );
}

plane::plane()
{
    a = b = c = d = 0;
}

void plane::printit()
{
    std::cout<<"Plane -> "<<a<<' '<<b<<' '<<c<<' '<<d<<'\n';
}

plane::plane(float a, float b, float c, float d)
{
    if(std::abs(d) >= epsilon)
    {
        this->a = a/d;
        this->b = b/d;
        this->c = c/d;
        this->d = 1;
    }
    else
    {
        if(std::abs(c) >= epsilon)
        {
            this->a = a/c;
            this->b = b/c;
            this->c = 1;
            this->d = 0;
        }
        else
        {
            if(std::abs(b) >= epsilon)
            {
                this->a = a/b;
                this->b = 1;
                this->c = 0;
                this->d = 0;
            }
            else
            {
                this->a = 1;
                this->b = 0;
                this->c = 0;
                this->d = 0;
            }
        }
    }
}



