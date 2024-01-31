/* ===============================
    Compile: g++ -c Point2D.cpp
   ===============================*/

#include <iostream>
#include <string>
#include <cmath>

#include "Point2D.h"

using namespace std;

ostream& operator<< (ostream& out, const Point2D& my2DPoint)
{
    out << "["; 
    out.width(4);
    out << my2DPoint.getX() << ", ";
    out.width(4);
    out << my2DPoint.getY() << "]";
    out << "   ";
    out.precision(3); 
    out << std::fixed << my2DPoint.getScalarValue();

    return out;
}

Point2D :: Point2D()
{
    this->x = 0;
    this->y = 0;

    setDistFrOrigin(); // should remain 0
}

Point2D :: Point2D(int x, int y)
{
    this->x = x;
    this->y = y;

    setDistFrOrigin();
}

// Calculate distance of point from origin (0,0)
void Point2D :: setDistFrOrigin()
{
    this->distFrOrigin = sqrt((this->x * this->x) + (this->y * this->y));
}

int Point2D :: getX() const
{
    return this->x;
}

int Point2D :: getY() const
{
    return this->y;
}

double Point2D :: getScalarValue() const
{
    return this->distFrOrigin;
}

void Point2D :: setX(int x)
{
    this->x = x;
}

void Point2D :: setY(int y)
{
    this->y = y;
}

bool Point2D :: operator== (const Point2D & my2DPoint)
{
    return ((this->x == my2DPoint.getX()) && 
            (this->y == my2DPoint.getY()));
}

// Sort by x ascending, then y ascending
bool Point2D :: compareXAsc(Point2D lhs, Point2D rhs)
{
    if (lhs.getX() < rhs.getX())
        return true;
    if (lhs.getX() > rhs.getX())
        return false;
    
    // if lhs x == rhs x
    if (lhs.getY() < rhs.getY())
        return true;
    if (lhs.getY() > rhs.getY())
        return false; 

    return false;
}

// Sort by x descending, then y descending
bool Point2D :: compareXDsc(Point2D lhs, Point2D rhs)
{
    if (lhs.getX() > rhs.getX())
        return true;
    if (lhs.getX() < rhs.getX())
        return false;
    
    // if lhs x == rhs x
    if (lhs.getY() > rhs.getY())
        return true;
    if (lhs.getY() < rhs.getY())
        return false; 

    return false;
}

// Sort by y ascending, then x ascending
bool Point2D :: compareYAsc(Point2D lhs, Point2D rhs)
{
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

// Sort by y descending, then x descending
bool Point2D :: compareYDsc(Point2D lhs, Point2D rhs)
{
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

// Sort by scalar ascending
bool Point2D :: compareScalarAsc(Point2D lhs, Point2D rhs)
{
    return (lhs.getScalarValue() < rhs.getScalarValue());
}

// Sort by scalar descending
bool Point2D :: compareScalarDsc(Point2D lhs, Point2D rhs)
{
    return (lhs.getScalarValue() > rhs.getScalarValue());
}

