#ifndef LINE2D_H
#define LINE2D_H

#include <iostream>

#include "Point2D.h"

using namespace std;

class Line2D
{
    friend ostream& operator<< (ostream&, const Line2D&);
    
    public:
        Line2D();
        Line2D(Point2D, Point2D);

        Point2D getPt1() const;
        Point2D getPt2() const;

        double getScalarValue() const;

        void setPt1(Point2D);
        void setPt2(Point2D);

        bool operator== (const Line2D &);

        // For comparator in sort
        static bool compareXYAscPt1(Line2D, Line2D);
        static bool compareXYDscPt1(Line2D, Line2D);
        static bool compareXYAscPt2(Line2D, Line2D);
        static bool compareXYDscPt2(Line2D, Line2D);
        static bool compareScalarAsc(Line2D, Line2D);
        static bool compareScalarDsc(Line2D, Line2D);
    
    protected:
        double length;
        void setLength();
    
    private:
        Point2D pt1;
        Point2D pt2;
};

#endif