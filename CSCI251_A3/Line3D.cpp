/* ===============================
    Compile: g++ -c Line3D.cpp
   ===============================*/

#include <iostream>
#include <cmath>
#include <string>

#include "Point3D.h"
#include "Line3D.h"
#include "Line2D.h"

using namespace std;

// overloaded insertion for output
ostream& operator<< (ostream& out, const Line3D& my3DLine)
{
    out << "["; 
    out.width(4);
    out << my3DLine.getPt1().getX() << ", ";
    out.width(4);
    out << my3DLine.getPt1().getY() << ", ";
    out.width(4);
    out << my3DLine.getPt1().getZ() << "]";
    out << "   ["; 
    out.width(4);
    out << my3DLine.getPt2().getX() << ", ";
    out.width(4);
    out << my3DLine.getPt2().getY() << ", ";
    out.width(4);
    out << my3DLine.getPt2().getZ() << "]";
    out << "   ";
    out.precision(3); 
    out << std::fixed << my3DLine.getScalarValue();

    return out;
}

Line3D :: Line3D()
{
    this->pt1 = Point3D();
    this->pt2 = Point3D();

    setLength();
}

Line3D :: Line3D(Point3D pt1, Point3D pt2)
{
    this->pt1 = pt1;
    this->pt2 = pt2;

    setLength();
}

Point3D Line3D :: getPt1() const
{
    return this->pt1;
}

Point3D Line3D :: getPt2() const
{
    return this-> pt2;
}

void Line3D :: setPt1(Point3D pt1)
{
    this->pt1 = pt1;
}

void Line3D :: setPt2(Point3D pt2)
{
    this->pt2 = pt2;
}

void Line3D :: setLength()
{
    // For easier formating
    int pt1X = this->pt1.getX();
    int pt1Y = this->pt1.getY();
    int pt1Z = this->pt1.getZ();
    int pt2X = this->pt2.getX();
    int pt2Y = this->pt2.getY();
    int pt2Z = this->pt2.getZ();
    
    this->length = sqrt(((pt1X - pt2X) * (pt1X - pt2X)) + 
                        ((pt1Y - pt2Y) * (pt1Y - pt2Y)) + 
                        ((pt1Z - pt2Z) * (pt1Z - pt2Z)));
}

bool Line3D :: operator== (const Line3D & a3DLine)
{
    return (pt1 == a3DLine.getPt1() && 
            pt2 == a3DLine.getPt2());
}

// Sort by x ascending, then y ascending, then z ascending for pt1
bool Line3D :: compareXYZAscPt1(Line3D lhs, Line3D rhs)
{
    if (lhs.getPt1().getX() < rhs.getPt1().getX())
        return true;
    if (lhs.getPt1().getX() > rhs.getPt1().getX())
        return false;
    
    // if lhs x == rhs x
    if (lhs.getPt1().getY() < rhs.getPt1().getY())
        return true;
    if (lhs.getPt1().getY() > rhs.getPt1().getY())
        return false;
    
    // if lhs y == rhs y
    if (lhs.getPt1().getZ() < rhs.getPt1().getZ())
        return true;
    if (lhs.getPt1().getZ() > rhs.getPt1().getZ())
        return false; 

    return false;
}

// Sort by x descending, then y descending, then z descending for pt1
bool Line3D :: compareXYZDscPt1(Line3D lhs, Line3D rhs)
{
    if (lhs.getPt1().getX() > rhs.getPt1().getX())
        return true;
    if (lhs.getPt1().getX() < rhs.getPt1().getX())
        return false;
    
    // if lhs x == rhs x
    if (lhs.getPt1().getY() > rhs.getPt1().getY())
        return true;
    if (lhs.getPt1().getY() < rhs.getPt1().getY())
        return false; 
    
    // if lhs y == rhs y
    if (lhs.getPt1().getZ() > rhs.getPt1().getZ())
        return true;
    if (lhs.getPt1().getZ() < rhs.getPt1().getZ())
        return false; 

    return false;
}

// Sort by x ascending, then y ascending, then z ascending for pt2
bool Line3D :: compareXYZAscPt2(Line3D lhs, Line3D rhs)
{
    if (lhs.getPt2().getX() < rhs.getPt2().getX())
        return true;
    if (lhs.getPt2().getX() > rhs.getPt2().getX())
        return false;
    
    // if lhs x == rhs x
    if (lhs.getPt2().getY() < rhs.getPt2().getY())
        return true;
    if (lhs.getPt2().getY() > rhs.getPt2().getY())
        return false;
    
    // if lhs y == rhs y
    if (lhs.getPt2().getZ() < rhs.getPt2().getZ())
        return true;
    if (lhs.getPt2().getZ() > rhs.getPt2().getZ())
        return false; 

    return false;
}

// Sort by x descending, then y descending, then z descending for pt2
bool Line3D :: compareXYZDscPt2(Line3D lhs, Line3D rhs)
{
    if (lhs.getPt2().getX() > rhs.getPt2().getX())
        return true;
    if (lhs.getPt2().getX() < rhs.getPt2().getX())
        return false;
    
    // if lhs x == rhs x
    if (lhs.getPt2().getY() > rhs.getPt2().getY())
        return true;
    if (lhs.getPt2().getY() < rhs.getPt2().getY())
        return false;
    
    // if lhs y == rhs y
    if (lhs.getPt2().getZ() > rhs.getPt2().getZ())
        return true;
    if (lhs.getPt2().getZ() < rhs.getPt2().getZ())
        return false; 

    return false;
}