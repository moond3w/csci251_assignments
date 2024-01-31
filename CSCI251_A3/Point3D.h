#ifndef POINT3D_H
#define POINT3D_H

#include "Point2D.h"

class Point3D : public Point2D
{
    friend ostream& operator<< (ostream&, const Point3D&);
    
    protected:
        int z;

        void setDistFrOrigin();

    public:
        Point3D();
        Point3D(int, int, int);

        int getZ() const;
        void setZ(int);

        bool operator== (const Point3D &);

        // For comparator in sort
        static bool compareZAsc(Point3D, Point3D);
        static bool compareZDsc(Point3D, Point3D);
};

#endif