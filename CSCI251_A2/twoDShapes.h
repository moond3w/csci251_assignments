#ifndef TWODSHAPES_H
#define TWODSHAPES_H

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

class ShapeTwoD
{
    friend ostream& operator<<(ostream &,const ShapeTwoD &); 

    public:
        // constructors
        ShapeTwoD();
        ShapeTwoD(string name, bool containsWarpSpace, int id);

        // functions
        virtual string toString();
        virtual double computeArea();
        virtual bool isPointInShape(int x, int y);
        virtual bool isPointOnShape(int x, int y);
        virtual void setArea();
        virtual double getArea() const;
        virtual void setVertexes();

        void setName(string name);
        void setContainsWarpSpace(bool containsWarpSpace);
        bool getContainsWarpSpace() const;

        // To determine "box" of coordinates where shape can contain
        int minX;
        int maxX;
        int minY;
        int maxY;

        int id;

    protected:
        string name;
        bool containsWarpSpace;
};

class Cross : public ShapeTwoD
{
    friend ostream& operator<<(ostream &, const Cross &);

    public:
        // constructors
        Cross();
        Cross(string name, bool containsWarpSpace, int id);

        // functions
        string toString();
        double computeArea();
        bool isPointInShape(int x, int y);
        bool isPointOnShape(int x, int y);

        void setVertexes();
        void setArea();
        virtual double getArea() const;
        string displayVertexes() const;
        
    private:
        // array to store vertex coordinates
        static const int ROWS = 12;
        static const int COLS = 2;
        int coordinates[ROWS][COLS];

        double area;
};

class Rectangle : public ShapeTwoD
{
    friend ostream& operator<<(ostream &, const Rectangle &);
    
    public:
        // constructors
        Rectangle();
        Rectangle(string name, bool containsWarpSpace, int id);

        // functions
        virtual string toString();
        virtual double computeArea();
        virtual bool isPointInShape(int x, int y);
        virtual bool isPointOnShape(int x, int y);

        void setVertexes();
        virtual void setArea();
        virtual double getArea() const;
        string displayVertexes() const;

    private:
        // array to store vertex coordinates
        static const int ROWS = 4;
        static const int COLS = 2;
        int coordinates[ROWS][COLS];

        double area;
};

class Square : public ShapeTwoD
{
    friend ostream& operator<<(ostream &, const Square &);
    
    public:
        // constructors
        Square();
        Square(string name, bool containsWarpSpace, int id);

        // functions
        virtual string toString();
        virtual double computeArea();
        virtual bool isPointInShape(int x, int y);
        virtual bool isPointOnShape(int x, int y);

        void setVertexes();
        virtual void setArea();
        virtual double getArea() const;
        string displayVertexes() const;

    private:
        // array to store vertex coordinates
        static const int ROWS = 4;
        static const int COLS = 2;
        int coordinates[ROWS][COLS];

        double area;
};

class Circle : public ShapeTwoD
{
    friend ostream& operator<<(ostream &, const Circle &);
    
    public:
        // constructors
        Circle();
        Circle(string name, bool containsWarpSpace, int id);

        // functions
        virtual string toString();
        virtual double computeArea();
        virtual bool isPointInShape(int x, int y);
        virtual bool isPointOnShape(int x, int y);

        virtual void setVertexes();
        virtual void setArea();
        virtual double getArea() const;
        string displayVertexes() const;

    private:
        // array to store center coordinate
        static const int ROWS = 2;
        int center[ROWS];

        int radius;
        double area;
};

int checkIntegerInput(string userInput, string message, int point);
int checkIntegerInput(string userInput, string message);
bool isInteger(string userInput);

#endif