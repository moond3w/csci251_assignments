/* ===============================
    Compile: g++ -c Line2D.cpp
   ===============================*/

#include <cmath>
#include <iostream>

#include "Point2D.h"
#include "Line2D.h"

using namespace std;

// overloaded insertion for output
ostream& operator<< (ostream& out, const Line2D& my2DLine)
{
    out << "["; 
    out.width(4);
    out << my2DLine.getPt1().getX() << ", ";
    out.width(4);
    out << my2DLine.getPt1().getY() << "]";
    out << "   ["; 
    out.width(4);
    out << my2DLine.getPt2().getX() << ", ";
    out.width(4);
    out << my2DLine.getPt2().getY() << "]";
    out << "   ";
    out.precision(3); 
    out << std::fixed << my2DLine.getScalarValue();

    return out;
}

// default constructor
Line2D :: Line2D()
{
    this->pt1 = Point2D();
    this->pt2 = Point2D();
    
    setLength();
}

// non-default constructor
Line2D :: Line2D(Point2D pt1, Point2D pt2)
{
    this->pt1 = pt1;
    this->pt2 = pt2;

    setLength();
}

Point2D Line2D :: getPt1() const
{
    return this->pt1;
}

Point2D Line2D :: getPt2() const
{
    return this->pt2;
}

double Line2D :: getScalarValue() const
{
    return this->length;
}

void Line2D :: setPt1(Point2D pt1)
{
    this->pt1 = pt1;
}

void Line2D :: setPt2(Point2D pt2)
{
    this->pt2 = pt2;
}

void Line2D :: setLength()
{
    int pt1X = this->pt1.getX();
    int pt1Y = this->pt1.getY();
    int pt2X = this->pt2.getX();
    int pt2Y = this->pt2.getY();

    this->length = sqrt(((pt1X - pt2X) * (pt1X - pt2X)) + 
                        ((pt1Y - pt2Y) * (pt1Y - pt2Y)));
}

bool Line2D :: operator== (const Line2D & a2DLine)
{
    return (pt1 == a2DLine.getPt1() && 
            pt2 == a2DLine.getPt2());
}

// Sort by x ascending, then y ascending for pt1
bool Line2D :: compareXYAscPt1(Line2D lhs, Line2D rhs)
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

    return false;
}

// Sort by x descending, then y descending for pt1
bool Line2D :: compareXYDscPt1(Line2D lhs, Line2D rhs)
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

    return false;
}

// Sort by x ascending, then y ascending for pt2
bool Line2D :: compareXYAscPt2(Line2D lhs, Line2D rhs)
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

    return false;
}

// Sort by x descending, then y descending for pt2
bool Line2D :: compareXYDscPt2(Line2D lhs, Line2D rhs)
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

    return false;
}

// Sort by scalar value ascending
bool Line2D :: compareScalarAsc(Line2D lhs, Line2D rhs)
{
    return (lhs.getScalarValue() < rhs.getScalarValue());
}

// Sort by scalar value descending
bool Line2D :: compareScalarDsc(Line2D lhs, Line2D rhs)
{
    return (lhs.getScalarValue() > rhs.getScalarValue());
}