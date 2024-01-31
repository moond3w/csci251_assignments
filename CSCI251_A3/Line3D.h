#ifndef LINE3D_H
#define LINE3D_H

#include <iostream>

#include "Point3D.h"
#include "Line2D.h"

using namespace std;

class Line3D : public Line2D
{
    friend ostream& operator<< (ostream&, const Line3D&);
    
    public:
        Line3D();
        Line3D(Point3D, Point3D);

        Point3D getPt1() const;
        Point3D getPt2() const;

        void setPt1(Point3D);
        void setPt2(Point3D);

        bool operator== (const Line3D &);

        static bool compareXYZAscPt1(Line3D, Line3D);
        static bool compareXYZDscPt1(Line3D, Line3D);
        static bool compareXYZAscPt2(Line3D, Line3D);
        static bool compareXYZDscPt2(Line3D, Line3D);

    protected:
        void setLength();

    private:
        Point3D pt1;
        Point3D pt2;
};

#endif