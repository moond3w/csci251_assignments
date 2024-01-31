/* ===============================
    Compile: g++ -c Point3D.cpp 
   ===============================*/

#include <iostream>
#include <cmath>

#include "Point3D.h"

using namespace std;

ostream& operator<< (ostream& out, const Point3D& my3DPoint)
{
    out << "["; 
    out.width(4);
    out << my3DPoint.getX() << ", ";
    out.width(4);
    out << my3DPoint.getY() << ", ";
    out.width(4);
    out << my3DPoint.getZ() << "]";
    out << "   ";
    out.precision(3); 
    out << std::fixed << my3DPoint.getScalarValue();

    return out;
}

// default constructor
Point3D :: Point3D()
: Point2D()
{
    this->z = 0;

    setDistFrOrigin();
}

// non-default constructor
Point3D :: Point3D(int x, int y, int z)
: Point2D(x, y)
{
    this->z = z;

    setDistFrOrigin();
}

// calculate distance from origin (0, 0, 0)
void Point3D :: setDistFrOrigin()
{
    this->distFrOrigin = sqrt((this->x * this->x) + 
    (this->y * this->y) + (this->z * this->z));
}

int Point3D :: getZ() const
{
    return this->z;
}

void Point3D :: setZ(int z)
{
    this->z = z;
}

bool Point3D :: operator== (const Point3D & my3DPoint)
{
    return ((this->getX() == my3DPoint.getX()) && 
            (this->getY() == my3DPoint.getY()) && 
            (this->getZ() == my3DPoint.getZ()));
}

// Sort by z ascending, then y ascending, then x ascending
bool Point3D :: compareZAsc(Point3D lhs, Point3D rhs)
{
    if (lhs.getZ() < rhs.getZ())
        return true;
    if (lhs.getZ() > rhs.getZ())
        return false;
    
    // if lhs z == rhs z
    if (lhs.getY() < rhs.getY())
        return true;
    if (lhs.getY() > rhs.getY())
        return false;
    
    // if lhs y == rhs y
    if (lhs.getX() < rhs.getX())
        return true;
    if (lhs.getX() > rhs.getX())
        return false;

    return false;
}

// Sort by x descending, then y descending, then x descending
bool Point3D :: compareZDsc(Point3D lhs, Point3D rhs)
{
    if (lhs.getZ() > rhs.getZ())
        return true;
    if (lhs.getZ() < rhs.getZ())
        return false;
    
    // if lhs z == rhs z
    if (lhs.getY() > rhs.getY())
        return true;
    if (lhs.getY() < rhs.getY())
        return false; 

    // if lhs y == rhs y
    if (lhs.getX() > rhs.getX())
        return true;
    if (lhs.getX() < rhs.getX())
        return false;

    return false;
}
