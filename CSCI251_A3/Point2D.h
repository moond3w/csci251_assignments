#ifndef POINT2D_H
#define POINT2D_H

using namespace std;

class Point2D
{
    friend ostream& operator<< (ostream&, const Point2D&);
    
    protected:
        int x;
        int y;
        double distFrOrigin;

        void setDistFrOrigin();

    public:
        Point2D();
        Point2D(int, int);

        int getX() const;
        int getY() const;
        double getScalarValue() const;

        void setX(int);
        void setY(int);

        // Overload comparator operators
        bool operator== (const Point2D &);

        // For comparator in sort
        static bool compareXAsc(Point2D, Point2D);
        static bool compareXDsc(Point2D, Point2D);
        static bool compareYAsc(Point2D, Point2D);
        static bool compareYDsc(Point2D, Point2D);
        static bool compareScalarAsc(Point2D, Point2D);
        static bool compareScalarDsc(Point2D, Point2D);
};

#endif