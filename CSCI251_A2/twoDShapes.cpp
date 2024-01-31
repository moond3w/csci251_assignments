/* =====================================
   To compile for testing : g++ -std=c++11 twoDShapes.cpp -o twoDShapes.exe
   =====================================
   To compile : g++ -c twoDShapes.cpp
   =====================================
   To run     : ./twoDShapes.exe
   =====================================
*/

#include <string>
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include "twoDShapes.h"

using namespace std;

/* ===============================
        SHAPETWOD METHODS
================================*/

// Generate default constructor for ShapeTwoD
ShapeTwoD :: ShapeTwoD()
{
    name = "";
    containsWarpSpace = false;

    minX = 0;
    maxX = 0;
    minY = 0;
    maxY = 0;

    id = -1;
}

// Generate non-default constructor for ShapeTwoD
ShapeTwoD :: ShapeTwoD(string name, bool containsWarpSpace, int id)
{
    this->name = name;
    this->containsWarpSpace = containsWarpSpace;
    this->id = id;

    minX = 0;
    maxX = 0;
    minY = 0;
    maxY = 0;
}

// Set methods for both name, containsWarpSpace
void ShapeTwoD :: setName(string name)
{
    this->name = name;
}

void ShapeTwoD :: setContainsWarpSpace(bool containsWarpSpace)
{
    this->containsWarpSpace = containsWarpSpace;
}

// Overloaded operator
ostream& operator<<(ostream &out,const ShapeTwoD &aShapeTwoD)
{
    string warpSpace;
    if (aShapeTwoD.containsWarpSpace)
        warpSpace = "WS";
    else
        warpSpace = "NS";

    out << "Name : " << aShapeTwoD.name 
        << "\nSpecial Type : " << warpSpace;

    return out;
}

// return string of ShapeTwoD data
string ShapeTwoD :: toString()
{
    ostringstream oss;
    oss << (*this);
    return oss.str();
}

// To be overloaded in subclasses
double ShapeTwoD :: computeArea()
{
    return (0.0);
}

// To be overloaded in subclasses
bool ShapeTwoD :: isPointInShape(int x, int y)
{
    return false;
}

// To be overloaded in subclasses
bool ShapeTwoD :: isPointOnShape(int x, int y)
{
    return false;
}

// To be overloaded in subclasses
void ShapeTwoD :: setArea()
{
    cout << "In ShapeTwoD" << endl;
}

// To be overloaded in subclasses
double ShapeTwoD :: getArea() const
{
    return (0.0);
}

// To be overloaded in subclasses
void ShapeTwoD :: setVertexes()
{
    cout << "In ShapeTwoD" << endl;
}

// self-explanatory
bool ShapeTwoD :: getContainsWarpSpace() const
{
    return containsWarpSpace;
}

/* ===============================
        CROSS METHODS
================================*/
// Generate default constructor for Cross
Cross :: Cross()
: ShapeTwoD()
{
    // Initialize Cross Vertex Array
    for (int i = 0; i < Cross::ROWS; i++)
    {
        for (int j = 0; j < Cross::COLS; j++)
        {
            coordinates[i][j] = 0;
        }
    }

    // Initialize area
    area = 0.0;
}

// Generate non-default constructor for Cross
Cross :: Cross(string name, bool containsWarpSpace, int id)
: ShapeTwoD(name, containsWarpSpace, id)
{
    // Initialize Cross Vertex Array
    for (int i = 0; i < Cross::ROWS; i++)
    {
        for (int j = 0; j < Cross::COLS; j++)
        {
            coordinates[i][j] = 0;
        }
    }

    // Initialize area
    area = 0.0;
}

// Overload insertion operator
ostream& operator<<(ostream &out, const Cross &aCross)
{
    string warpSpace;
    string displayVertex;

    if (aCross.ShapeTwoD::containsWarpSpace)
        warpSpace = "WS";
    else
        warpSpace = "NS";
    
    displayVertex = aCross.Cross::displayVertexes();

    out << "Name : " << aCross.ShapeTwoD::name 
        << "\nSpecial Type : " << warpSpace
        << "\nArea : " << aCross.area << " unit square"
        << "\nVertices : \n" << displayVertex;

    return out;
}

string Cross :: toString()
{
    ostringstream oss;
    oss << (*this);
    return oss.str();
}

// Compute area of a cross
// reference: https://www.mathopenref.com/coordpolygonarea.html
double Cross :: computeArea()
{
    double area = 0.0;
    int x1,x2,y1,y2;

    for (int x = 1; x <= Cross::ROWS; x++)
    {
        if (x < Cross::ROWS)
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            x2 = coordinates[x][0];
            y2 = coordinates[x][1];
        }
        // For last coordinate where x = 12
        else
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            int reset_x = x % Cross::ROWS;
            x2 = coordinates[reset_x][0];
            y2 = coordinates[reset_x][1];
        }

        area = area + ((x1*y2) - (y1*x2));
    }
    area = abs(area/2);
    return (area);
}

// Determines if given point (x, y) is in Cross 
bool Cross :: isPointInShape(int x, int y)
{
    bool pointInShape = false;

    // Determine the two points with largest Y 
    // x values will determine range
    int maxY = Cross::maxY;
    int minY = Cross::minY;
    int countY = 0;
    int startX;
    int endX;

    // Determine the two points with largest X
    // y values will determine range
    int maxX = Cross::maxX;
    int minX = Cross::minX;
    int countX = 0;
    int startY;
    int endY;

    for (int i = 1; i <= Cross::ROWS; i++)
    {
        if ((coordinates[i][1] == maxY) && (countY == 0))
        {
            startX = coordinates[i][0];
            countY = countY + 1;
        }

        if ((coordinates[i][1] == maxY) && (countY == 1))
        {
            endX = coordinates[i][0];
        }
        
        if ((coordinates[i][0] == maxX) && (countX == 0))
        {
            startY = coordinates[i][1];
            countX = countX + 1;
        } 

        if ((coordinates[i][0] == maxX) && (countX == 1))
        {
            endY = coordinates[i][1];
        } 
    }

    int temp;
    // Swap values if needed so startXY < endXY
    if (startX > endX)
    {
        temp = endX;
        endX = startX;
        startX = temp;
    }

    // Swap values if needed so startXY < endXY
    if (startY > endY)
    {
        temp = endY;
        endY = startY;
        startY = temp;
    }

    // Comparison if in x or y in range, point is in shape.
    if ((x > startX) && (x < endX))
    {
        if ((y > minY) && (y < maxY))
        {
            pointInShape = true;
            return pointInShape;
        }
    }
    
    if ((y > startY) && (y < endY))
    {
        if ((x > minX) && (x < maxX))
        {
            pointInShape = true;
            return pointInShape;
        }
    }
    
    return pointInShape;
}

// Determines if given point (x, y) is in Cross 
bool Cross :: isPointOnShape(int myX, int myY)
{
    bool pointOnShape = false;
    int x1,x2,y1,y2;

    // Retrieve two continuous points to form line
    for (int x = 1; x <= Cross::ROWS; x++)
    {
        // For first 11 coordinates
        if (x < Cross::ROWS)
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            x2 = coordinates[x][0];
            y2 = coordinates[x][1];
        }
        // For last coordinate where x loops back 0
        else
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            int reset_x = x % Cross::ROWS;
            x2 = coordinates[reset_x][0];
            y2 = coordinates[reset_x][1];
        }

        // Test if on horizontal line
        if ((y1 == y2) && (y1 == myY))
        {
            // Scenario 1: x1 < x < x2
            // Scenario 2: x2 < x < x1
            if ((myX > x1 && myX < x2) || (myX > x2 && myX < x1))
            {
                pointOnShape = true;
                break;
            }
        }
    
        // Test if on vertical line
        if ((x1 == x2) && (x1== myX))
        {
            // Scenario 1: y1 < y < y2
            // Scenario 2: y2 < y < y1
            if ((myY > y1 && myY < y2) || (myY > y2 && myY < y1))
            {
                pointOnShape = true;
                break;
            }
        }
    }

    return pointOnShape;
}

// Set coordinates for every vertex in Cross
void Cross :: setVertexes()
{
    string inputX;
    string inputY;
    int x_coord, y_coord;

    for (int i = 0; i < Cross::ROWS; i++)
    {
        for (int j = 0; j < Cross::COLS; j++)
        {
            if (j == 0)
            {
                cout << "Please enter x-coordinate of pt." << i << " : ";
                getline(cin, inputX);
                x_coord = checkIntegerInput(inputX, "Please enter x-coordinate of pt.", i);
                coordinates[i][j] = x_coord;

                // to determine scope of y coordinates
                if (x_coord > ShapeTwoD::maxX)
                    ShapeTwoD::maxX = x_coord;
                
                if (x_coord < ShapeTwoD::minX)
                    ShapeTwoD::minX = x_coord;
            }
            else
            {
                cout << "Please enter y-coordinate of pt." << i << " : ";
                getline(cin, inputY);
                y_coord = checkIntegerInput(inputY, "Please enter y-coordinate of pt.", i);
                coordinates[i][j] = y_coord;

                // to determine scope of y coordinates
                if (y_coord > ShapeTwoD::maxY)
                    ShapeTwoD::maxY = y_coord;
                
                if (y_coord < ShapeTwoD::minY)
                    ShapeTwoD::minY = y_coord;
            }
        }
        cout << endl;
    }
}

// Set area of Cross
void Cross :: setArea()
{
    this->area = computeArea();
}

// Get area of Cross
double Cross :: getArea() const
{
    return area;
}

// Display vertex list in string format
string Cross :: displayVertexes() const
{
    ostringstream oss;

    for (int i = 0; i < Cross::ROWS; i++)
    {
        oss << "Point[" << i << "] : (" << coordinates[i][0]
                << ", " << coordinates[i][1] << ")\n";
    }

    return oss.str();
}

/* ===============================
        RECTANGLE METHODS
================================*/
// Generate default constructor for Rectangle
Rectangle :: Rectangle()
: ShapeTwoD()
{
    // Initialize Rectangle Vertex Array
    for (int i = 0; i < Rectangle::ROWS; i++)
    {
        for (int j = 0; j < Rectangle::COLS; j++)
        {
            coordinates[i][j] = 0;
        }
    }

    // Initialize area
    area = 0.0;
}

// Generate non default constructor for Rectangle
Rectangle :: Rectangle(string name, bool containsWarpSpace, int id)
: ShapeTwoD(name, containsWarpSpace, id)
{
    // Initialize Rectangle Vertex Array
    for (int i = 0; i < Rectangle::ROWS; i++)
    {
        for (int j = 0; j < Rectangle::COLS; j++)
        {
            coordinates[i][j] = 0;
        }
    }

    // Initialize area
    area = 0.0;
}

// Overload insertion operator for Rectangle
ostream& operator<<(ostream &out, const Rectangle &aRectangle)
{
    string warpSpace;
    string displayVertex;

    if (aRectangle.ShapeTwoD::containsWarpSpace)
        warpSpace = "WS";
    else
        warpSpace = "NS";
    
    displayVertex = aRectangle.Rectangle::displayVertexes();

    out << "Name : " << aRectangle.ShapeTwoD::name 
        << "\nSpecial Type : " << warpSpace
        << "\nArea : " << aRectangle.area << " unit square"
        << "\nVertices : \n" << displayVertex;

    return out;
}

// Display Rectangle object in string
string Rectangle :: toString()
{
    ostringstream oss;
    oss << (*this);
    return oss.str();
}

// Compute and return area of rectangle
double Rectangle :: computeArea()
{
    int x1, y1, x2, y2, x3, y3;
    double length, breadth;
    double area;

    x1 = coordinates[0][0];
    y1 = coordinates[0][1];

    x2 = coordinates[1][0];
    y2 = coordinates[1][1];

    x3 = coordinates[2][0];
    y3 = coordinates[2][1];
    // Compute length by using two consecutive coordinates
    length = sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));

    // Compute breadth by getting next consecutive coordinate
    breadth = sqrt(((x3 - x2)*(x3 - x2)) + ((y3 - y2)*(y3 - y2)));

    // Compute area with length * breadth
    area = length * breadth;

    return (area);
}

// Check if (x, y) is in Rectangle
bool Rectangle :: isPointInShape(int x, int y)
{
    bool pointInShape = false;
    bool withinX = false;
    bool withinY = false;

    int x1, x3, y1, y3;
    // First and third point will always be on opposite ends
    x1 = coordinates[0][0];
    y1 = coordinates[0][1];

    x3 = coordinates[2][0];
    y3 = coordinates[2][1];

    // Find minX, maxX, minY, maxY
    int maxX = max(x1, x3);
    int minX = min(x1, x3);
    int maxY = max(y1, y3);
    int minY = min(y1, y3);

    // Determine if x and y is within min and max
    if (x > minX && x < maxX)
        withinX = true;

    if (y > minY && y < maxY)
        withinY = true;

    if (withinX && withinY)
        pointInShape = true;
    
    return (pointInShape);
}

// Check if (x, y) is on Rectangle perimeter
bool Rectangle :: isPointOnShape(int myX, int myY)
{
    bool pointOnShape = false;

    int x1,x2,y1,y2;

    // Retrieve two continuous points to form line
    for (int x = 1; x <= Rectangle::ROWS; x++)
    {
        // For first 3 coordinates
        if (x < Rectangle::ROWS)
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            x2 = coordinates[x][0];
            y2 = coordinates[x][1];
        }
        // For last coordinate where x loops back 0
        else
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            int reset_x = x % Rectangle::ROWS;
            x2 = coordinates[reset_x][0];
            y2 = coordinates[reset_x][1];
        }

        // Test if on horizontal line
        if ((y1 == y2) && (y1 == myY))
        {
            // Scenario 1: x1 < x < x2
            // Scenario 2: x2 < x < x1
            if ((myX > x1 && myX < x2) || (myX > x2 && myX < x1))
            {
                pointOnShape = true;
                break;
            }
        }
    
        // Test if on vertical line
        if ((x1 == x2) && (x1== myX))
        {
            // Scenario 1: y1 < y < y2
            // Scenario 2: y2 < y < y1
            if ((myY > y1 && myY < y2) || (myY > y2 && myY < y1))
            {
                pointOnShape = true;
                break;
            }
        }
    }

    return (pointOnShape);
}

// Set vertex for Rectangle
void Rectangle :: setVertexes()
{
    string inputX;
    string inputY;
    int x_coord, y_coord;

    for (int i = 0; i < Rectangle::ROWS; i++)
    {
        for (int j = 0; j < Rectangle::COLS; j++)
        {
            if (j == 0)
            {
                cout << "Please enter x-coordinate of pt." << i << " : ";
                getline(cin, inputX);
                x_coord = checkIntegerInput(inputX, "Please enter x-coordinate of pt.", i);
                coordinates[i][j] = x_coord;

                // to determine scope of x coordinates
                if (x_coord > ShapeTwoD::maxX)
                    ShapeTwoD::maxX = x_coord;
                
                if (x_coord < ShapeTwoD::minX)
                    ShapeTwoD::minX = x_coord;
            }
            else
            {
                cout << "Please enter y-coordinate of pt." << i << " : ";
                getline(cin, inputY);
                y_coord = checkIntegerInput(inputY, "Please enter y-coordinate of pt.", i);
                coordinates[i][j] = y_coord;

                // to determine scope of y coordinates
                if (y_coord > ShapeTwoD::maxY)
                    ShapeTwoD::maxY = y_coord;
                
                if (y_coord < ShapeTwoD::minY)
                    ShapeTwoD::minY = y_coord;                
            }
        }
        cout << endl;
    }
}

// Set area for Rectangle with computeArea
void Rectangle :: setArea()
{
    this->area = computeArea();
}

// Get area of Rectangle
double Rectangle :: getArea() const
{
    return area;
}

// Return string of vertices in Rectangle
string Rectangle :: displayVertexes() const
{
    ostringstream oss;

    for (int i = 0; i < Rectangle::ROWS; i++)
    {
        oss << "Point[" << i << "] : (" << coordinates[i][0]
                << ", " << coordinates[i][1] << ")\n";
    }

    return oss.str();
}

/* ===============================
        SQUARE METHODS
================================*/

// Generate default constructor for Square
Square :: Square()
: ShapeTwoD()
{
    // Initialize Square Vertex Array
    for (int i = 0; i < Square::ROWS; i++)
    {
        for (int j = 0; j < Square::COLS; j++)
        {
            coordinates[i][j] = 0;
        }
    }

    // Initialize area
    area = 0.0;
}

// Generate non default constructor for Square
Square :: Square(string name, bool containsWarpSpace, int id)
: ShapeTwoD(name, containsWarpSpace, id)
{
    // Initialize Square Vertex Array
    for (int i = 0; i < Square::ROWS; i++)
    {
        for (int j = 0; j < Square::COLS; j++)
        {
            coordinates[i][j] = 0;
        }
    }

    // Initialize area
    area = 0.0;
}

// Overload insertion operator for Square
ostream& operator<<(ostream &out, const Square &aSquare)
{
    string warpSpace;
    string displayVertex;

    if (aSquare.ShapeTwoD::containsWarpSpace)
        warpSpace = "WS";
    else
        warpSpace = "NS";
    
    displayVertex = aSquare.Square::displayVertexes();

    out << "Name : " << aSquare.ShapeTwoD::name 
        << "\nSpecial Type : " << warpSpace
        << "\nArea : " << aSquare.area << " unit square"
        << "\nVertices : \n" << displayVertex;

    return out;
}

// Display Square object in string
string Square :: toString()
{
    ostringstream oss;
    oss << (*this);
    return oss.str();
}

// Compute and return area of Square
double Square :: computeArea()
{
    int x1, y1, x2, y2;
    double length, breadth;
    double area;

    x1 = coordinates[0][0];
    y1 = coordinates[0][1];

    x2 = coordinates[1][0];
    y2 = coordinates[1][1];

    // Compute length by using two consecutive coordinates
    length = sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));

    // Compute area with length * length
    area = length * length;

    return (area);
}

// Check if (x, y) is in Square
bool Square :: isPointInShape(int x, int y)
{
    bool pointInShape = false;
    bool withinX = false;
    bool withinY = false;

    int x1, x3, y1, y3;
    // First and third point will always be on opposite ends
    x1 = coordinates[0][0];
    y1 = coordinates[0][1];

    x3 = coordinates[2][0];
    y3 = coordinates[2][1];

    // Find minX, maxX, minY, maxY
    int maxX = max(x1, x3);
    int minX = min(x1, x3);
    int maxY = max(y1, y3);
    int minY = min(y1, y3);

    // Determine if x and y is within min and max
    if (x > minX && x < maxX)
        withinX = true;

    if (y > minY && y < maxY)
        withinY = true;

    if (withinX && withinY)
        pointInShape = true;
    
    return (pointInShape);
}

// Check if (x, y) is on Square perimeter
bool Square :: isPointOnShape(int myX, int myY)
{
    bool pointOnShape = false;

    int x1,x2,y1,y2;

    // Retrieve two continuous points to form line
    for (int x = 1; x <= Square::ROWS; x++)
    {
        // For first 3 coordinates
        if (x < Square::ROWS)
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            x2 = coordinates[x][0];
            y2 = coordinates[x][1];
        }
        // For last line where x loops back 0
        else
        {
            x1 = coordinates[x-1][0];
            y1 = coordinates[x-1][1];

            int reset_x = x % Square::ROWS;
            x2 = coordinates[reset_x][0];
            y2 = coordinates[reset_x][1];
        }

        // Test if on horizontal line
        if ((y1 == y2) && (y1 == myY))
        {
            // Scenario 1: x1 < x < x2
            // Scenario 2: x2 < x < x1
            if ((myX > x1 && myX < x2) || (myX > x2 && myX < x1))
            {
                pointOnShape = true;
                break;
            }
        }
    
        // Test if on vertical line
        if ((x1 == x2) && (x1== myX))
        {
            // Scenario 1: y1 < y < y2
            // Scenario 2: y2 < y < y1
            if ((myY > y1 && myY < y2) || (myY > y2 && myY < y1))
            {
                pointOnShape = true;
                break;
            }
        }
    }

    return (pointOnShape);
}

// Set vertex for Square
void Square :: setVertexes()
{
    string inputX;
    string inputY;
    int x_coord, y_coord;

    for (int i = 0; i < Square::ROWS; i++)
    {
        for (int j = 0; j < Square::COLS; j++)
        {
            if (j == 0)
            {
                cout << "Please enter x-coordinate of pt." << i << " : ";
                getline(cin, inputX);
                x_coord = checkIntegerInput(inputX, "Please enter x-coordinate of pt.", i);
                coordinates[i][j] = x_coord;

                // to determine scope of x coordinates
                if (x_coord > ShapeTwoD::maxX)
                    ShapeTwoD::maxX = x_coord;
                
                if (x_coord < ShapeTwoD::minX)
                    ShapeTwoD::minX = x_coord;
            }
            else
            {
                cout << "Please enter y-coordinate of pt." << i << " : ";
                getline(cin, inputY);
                y_coord = checkIntegerInput(inputY, "Please enter y-coordinate of pt.", i);
                coordinates[i][j] = y_coord;

                // to determine scope of y coordinates
                if (y_coord > ShapeTwoD::maxY)
                    ShapeTwoD::maxY = y_coord;
                
                if (y_coord < ShapeTwoD::minY)
                    ShapeTwoD::minY = y_coord;
            }
        }
        cout << endl;
    }
}

// Set area for Square through computeArea
void Square :: setArea()
{
    this->area = computeArea();
}

// Get area of square
double Square :: getArea() const
{
    return area;
}

// Return string of vertex array details
string Square :: displayVertexes() const
{
    ostringstream oss;

    for (int i = 0; i < Square::ROWS; i++)
    {
        oss << "Point[" << i << "] : (" << coordinates[i][0]
                << ", " << coordinates[i][1] << ")\n";
    }

    return oss.str();
}

/* ===============================
        CIRCLE METHODS
================================*/

// Generate default constructor for Circle
Circle :: Circle()
: ShapeTwoD()
{
    // Initialize Circle center coordinate array
    for (int i = 0; i < Circle::ROWS; i++)
    {
        center[i] = 0;
    }

    // Initialize area
    area = 0.0;

    // Initialize radius
    radius = 1;
}

// Generate non default constructor for Circle
Circle :: Circle(string name, bool containsWarpSpace, int id)
: ShapeTwoD(name, containsWarpSpace, id)
{
    // Initialize Circle center coordinate array
    for (int i = 0; i < Circle::ROWS; i++)
    {
        center[i] = 0;
    }

    // Initialize area
    area = 0.0;

    // Initialize radius
    radius = 1;
}

// Overload insertion operator for Circle
ostream& operator<<(ostream &out, const Circle &aCircle)
{
    string warpSpace;
    string displayVertex;

    if (aCircle.ShapeTwoD::containsWarpSpace)
        warpSpace = "WS";
    else
        warpSpace = "NS";
    
    displayVertex = aCircle.Circle::displayVertexes();

    out << "Name : " << aCircle.ShapeTwoD::name 
        << "\nSpecial Type : " << warpSpace
        << "\nArea : " << fixed << setprecision(2) << aCircle.area << " unit square"
        << "\nRadius : " << aCircle.radius
        << "\nCenter Point : " << displayVertex;

    return out;
}

// Display Circle object in string
string Circle :: toString()
{
    ostringstream oss;
    oss << (*this);
    return oss.str();
}

// Compute and return area of Circle
double Circle :: computeArea()
{
    double area;

    // Compute area with PI * r * r
    area = M_PI * radius * radius;

    return (area);
}

// Check if (x, y) is in Circle
bool Circle :: isPointInShape(int x, int y)
{
    bool pointInShape = false;

    int centerX, centerY;
    double distFromCenter = 0.0;

    // Retrieve center coordinates
    centerX = center[0];
    centerY = center[1];

    // Calculate distance between (x,y) and (centerX, centerY)
    distFromCenter = sqrt(((x - centerX)*(x - centerX)) + ((y - centerY)*(y - centerY)));

    // Determine if distance is smaller than radius
    if ((distFromCenter < radius) && (distFromCenter != 0))
        pointInShape = true;

    return (pointInShape);
}

// Only requirement is to determine if myX and myY is NSEW of center
bool Circle :: isPointOnShape(int myX, int myY)
{
    bool pointOnShape = false;

    int centerX, centerY;
    double distFromCenter = 0.0;

    // Retrieve center coordinates
    centerX = center[0];
    centerY = center[1];

    // North
    if ((centerX == myX) && ((centerY + radius) == myY))
        pointOnShape = true;

    // South
    if ((centerX == myX) && ((centerY - radius) == myY))
        pointOnShape = true;

    // East
    if ((centerY == myY) && ((centerX + radius) == myX))
        pointOnShape = true;

    // West
    if ((centerY == myY) && ((centerX - radius) == myX))
        pointOnShape = true;

    return (pointOnShape);
}

// Set vertex for Circle
void Circle :: setVertexes()
{
    string inputX;
    string inputY;
    string inputRad;
    int x_coord, y_coord;

    // Set x coordinate
    cout << "Please enter x-coordinate of center : ";
    getline(cin, inputX);
    x_coord = checkIntegerInput(inputX, "Please enter x-coordinate of center");
    center[0] = x_coord;

    // Set y coordinate
    cout << "Please enter y-coordinate of center : ";
    getline(cin, inputY);
    y_coord = checkIntegerInput(inputY, "Please enter y-coordinate of center");
    center[1] = y_coord;

    // Set radius
    cout << "Please enter radius (units) : ";
    getline(cin, inputRad);
    radius = checkIntegerInput(inputRad, "Please enter radius (units)");

    cout << endl;

    //Set values to determine scope for minX etc.
    ShapeTwoD::maxX = x_coord + radius;
    ShapeTwoD::minX = x_coord - radius;
    ShapeTwoD::maxY = y_coord + radius;
    ShapeTwoD::minY = y_coord - radius;
}

// Set area for Circle through computeArea
void Circle :: setArea()
{
    this->area = computeArea();
}

double Circle :: getArea() const
{
    return area;
}

// Return string of center coordinate
string Circle :: displayVertexes() const
{
    ostringstream oss;

    oss << "(" << center[0] << ", " << center[1] << ")\n";

    return oss.str();
}


/* ===============================
        OTHER METHODS
================================*/

// Check user input for setVertex and ensure is integer
int checkIntegerInput(string userInput, string message, int point)
{
    int coordinate;
    // If user does not enter integer, loop until user does
    while (!isInteger(userInput))
    {
        cout << "Invalid coordinate." << endl;
        cout << message << point << " : ";
        getline(cin, userInput);
    }

    coordinate = stoi(userInput);
    return coordinate;
}

// Check user input for Circle and ensure is integer
int checkIntegerInput(string userInput, string message)
{
    int val;
    // If user does not enter integer, loop until user does
    while (!isInteger(userInput))
    {
        cout << "Invalid value. Please enter an integer." << endl;
        cout << message << " : ";
        getline(cin, userInput);
    }

    val = stoi(userInput);
    return val;
}

// Check if user input is integer
bool isInteger(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (isdigit(input[i]) == false) {
            return false;
        }
    }
    
    // If user inputs empty string also return false
    if (input.empty())
        {
            return false;
        }
    return true;
}
