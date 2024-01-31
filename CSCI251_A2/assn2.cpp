/* =====================================
   To compile for testing : g++ -std=c++11 twoDShapes.o assn2.cpp -o csci251_a2.exe
   =====================================
   To run     : ./csci251_a2.exe
   =====================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "twoDShapes.h"
#include "assn2.h"

using namespace std;

// Initialize array to store ShapeTwoD pointers
vector<ShapeTwoD*> shapeTwoDArr;

int main()
{
    // Initialization for program run
    int counter = 0; // keep track of shapeTwoDArr
    bool runProgram = true;
    string userInput;
    int menuInput;

    string shapeName = "";
    string shapeType = "";

    // Start of program
    while (runProgram)
    {
        displayMenu();
        cout << "Please enter your choice: ";
        getline(cin, userInput);
        cout << endl;

        // If user does not enter integer, loop until user does
        while (!isInteger(userInput))
        {
            cout << "Invalid choice." << endl;
            cout << "Please enter an integer to proceed." << endl;
            cout << endl;
            returnToMenu();
            displayMenu();
            cout << "Please enter your choice: ";
            getline(cin, userInput);
            cout << endl;
        }

        menuInput = stoi(userInput);

        switch (menuInput) {
            case 1:
                cout << "[ Input Sensor Data ]" << endl;
                cout << endl;

                // Retrieve basic information
                cout << "Please enter name of shape : ";
                getline(cin, shapeName);
                cout << "Please enter special type (NS / WS) : ";
                getline (cin, shapeType);
                cout << endl;

                // Create and store shape
                counter = inputSensorData(shapeName, shapeType, counter);
                break;

            case 2:
                cout << "[ Compute Area (for all records) ]" << endl;
                cout << endl;
                computeAllArea(counter);
                cout << "Computation completed! ( " << counter << " record(s) were updated )" << endl;
                cout << endl;
                break;

            case 3:
                cout << "[ Print Shapes Report ]" << endl;
                cout << endl;
                cout << "Total no. of records available = " << counter << endl;
                cout << endl;
                displayShapeArr(counter);
                returnToMenu();
                break;

            case 4:
                cout << "[ Sort Shape Data ]" << endl;
                cout << endl;
                processSubMenu(counter);
                break;

            case 5:
                cout << "Thank you for using the Assignment 2 Program." << endl;
                cout << "[ Exiting Program... ]" << endl;
                cout << endl;
                runProgram = false;
                break;

            default:
                cout << "Invalid choice." << endl;
                cout << "Please enter an integer within the menu range. (0 - 5)" << endl;
                cout << endl;
                returnToMenu();
        }
    }

    return (0);
}

// Process submenu for option 4 in program : Sort shapes data
void processSubMenu(int counter)
{
    bool runSubProgram = true;
    string userInput = "";

    while (runSubProgram)
    {
        displaySubMenu();
        cout << endl;
        cout << "Please select sort option ('q' to return) : ";
        getline(cin, userInput);
        cout << endl;

        if (userInput == "a")
        {
            // Sort by area ascending
            cout << "Sort by area (smallest to largest) ... " << endl;
            cout << endl;
            sortByAreaAscend();
            displayShapeArr(counter);
            returnToMenu();
        }
        else if (userInput == "b")
        {
            // Sort by area descending
            cout << "Sort by area (largest to smallest) ... " << endl;
            cout << endl;
            sortByAreaDescend();
            displayShapeArr(counter);
            returnToMenu();
        }
        else if (userInput == "c")
        {
            // Sort by special type and area
            cout << "Sort by special type (WS to NS) ... " << endl;
            cout << "Sort by area (smallest to largest) ... " << endl;
            cout << endl;
            sortBySpecThenArea();
            displayShapeArr(counter);
            returnToMenu();
        }
        else if (userInput == "q")
        {
            runSubProgram = false;
            cout << "Returning to main menu..." << endl;
            cout << endl;
        }
        else
        {
            cout << "Invalid input. Please select one of the options." << endl;
            cout << endl;
        }
    }
}

int inputSensorData(string shapeName, string shapeType, int counter)
{
    bool warpSpace;
    bool validWS = false;
    bool shapeCreated = false;

    if (shapeType == "WS")
    {
        warpSpace = true;
        validWS = true;
    }
    else if (shapeType == "NS")
    {
        warpSpace = false;
        validWS = true;
    }
    else
    {
        cout << "Invalid Special Type. Please try again." << endl;
        cout << "Going back to main menu..." << endl;
        cout << endl;
    }
    
    if (validWS)
    {
        if (shapeName == "Cross")
        {
            shapeTwoDArr.push_back(new Cross(shapeName, warpSpace, counter));
            shapeTwoDArr.back()->setVertexes();
            shapeCreated = true;
        }
        else if (shapeName == "Rectangle")
        {
            shapeTwoDArr.push_back(new Rectangle(shapeName, warpSpace, counter));
            shapeTwoDArr.back()->setVertexes();
            shapeCreated = true;
        }
        else if (shapeName == "Square")
        {
            shapeTwoDArr.push_back(new Square(shapeName, warpSpace, counter));
            shapeTwoDArr.back()->setVertexes();
            shapeCreated = true;
        }
        else if (shapeName == "Circle")
        {
            shapeTwoDArr.push_back(new Circle(shapeName, warpSpace, counter));
            shapeTwoDArr.back()->setVertexes();
            shapeCreated = true;
        }
        else
        {
            cout << "Invalid Shape Name. Please try again." << endl;
            cout << "Going back to main menu..." << endl;
            cout << endl;
        }
    }

    if (shapeCreated)
    {
        counter = counter += 1;
        cout << "Record successfully stored. Going back to main menu..." << endl;
        cout << endl;
    }

    return counter;
}

// Compute area for all objects created
void computeAllArea(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        ShapeTwoD* temp = shapeTwoDArr[i];
        temp->setArea();
        
        shapeTwoDArr[i] = temp;
    }
}

// Retrieve string of points on perimeter of shape
string displayPointsOnShape(ShapeTwoD* myShape)
{
    ostringstream oss;

    int maxX = myShape->maxX;
    int minX = myShape->minX;
    int maxY = myShape->maxY;
    int minY = myShape->minY;

    for (int i = minX; i <= maxX; i++)
    {
        for (int j = minY; j <= maxY; j++)
        {
            if (myShape->isPointOnShape(i, j))
            {
                oss << "(" << i << "," << j << "), ";
            }
        }
    }

    string output = oss.str();

    if (output.empty())
        output = "none!";
    else
        // remove last ", "
        output = output.substr(0, output.size()-2);
    
    return output;
}

// Retrieve string of points within shape
string displayPointsInShape(ShapeTwoD* myShape)
{
    ostringstream oss;

    int maxX = myShape->maxX;
    int minX = myShape->minX;
    int maxY = myShape->maxY;
    int minY = myShape->minY;

    for (int i = minX; i <= maxX; i++)
    {
        for (int j = minY; j <= maxY; j++)
        {
            if (myShape->isPointInShape(i, j))
            {
                oss << "(" << i << "," << j << "), ";
            }
        }
    }

    string output = oss.str();

    if (output.empty())
        output = "none!";
    else
        // remove last ", "
        output = output.substr(0, output.size()-2);
    
    return output;
}

// Display all ShapeTwoD objects in shapeTwoDArr
void displayShapeArr(int counter)
{
    for (int i = 0; i < counter; i++)
    {
        ShapeTwoD* temp = shapeTwoDArr[i];
        // Display shape details
        cout << "Shape [" << temp->id << "]" << endl;
        cout << temp->toString() << endl;

        // Display points on shape and points in shape
        string pointsOnShape = displayPointsOnShape(temp);
        string pointsInShape = displayPointsInShape(temp);

        cout << "Points on perimeter : " << pointsOnShape << endl;
        cout << endl;
        cout << "Points within shape : " << pointsInShape << endl;
        cout << endl;
    }
}

bool orderByAreaAscend(ShapeTwoD* lhs, ShapeTwoD* rhs)
{
  return (lhs->getArea() < rhs->getArea());
}

bool orderByAreaDescend(ShapeTwoD* lhs, ShapeTwoD* rhs)
{
  return (lhs->getArea() > rhs->getArea());
}

bool orderBySThenArea(ShapeTwoD* lhs, ShapeTwoD* rhs)
{
    int leftVal = 0;
    int rightVal = 0;
    // Set true = 1 and false = 0
    if (lhs->getContainsWarpSpace())
        leftVal = 1;
    
    if (rhs->getContainsWarpSpace())
        rightVal = 1;

    // Set comparison for special type
    if (leftVal < rightVal)
        return false;
    
    if (rightVal < leftVal)
        return true;

    // If special type for lhs = rhs
    if (lhs->getArea() < rhs->getArea())
        return true;

    if (lhs->getArea() > rhs->getArea())
        return false; 
    
    return false;
}

void sortByAreaAscend()
{
    sort(shapeTwoDArr.begin(), shapeTwoDArr.end(), orderByAreaAscend);
}

void sortByAreaDescend()
{
    sort(shapeTwoDArr.begin(), shapeTwoDArr.end(), orderByAreaDescend);
}

void sortBySpecThenArea()
{
    sort(shapeTwoDArr.begin(), shapeTwoDArr.end(), orderBySThenArea);
}

// Display Main Menu screen
void displayMenu()
{
    cout << "Student ID   : 7910939" << endl;
    cout << "Student Name : Chai Guo Liang" << endl;
    cout << "==============================" << endl;
    cout << "Welcome to Assignment 2 Program!" << endl;
    cout << endl;
    cout << "1)   Input Sensor Data" << endl;
    cout << "2)   Compute Area (for all records)" << endl;
    cout << "3)   Print Shapes Report" << endl;
    cout << "4)   Sort Shape Data" << endl;
    cout << "5)   Quit Program" << endl;
    cout << endl;
}

// Prompt user to input <enter> to return to main menu
void returnToMenu()
{
    string userInput;
    // Loop until empty string detected (<enter>)
    while (true)
    {
        cout << "Press <enter> to go back to main menu..." << endl;
        getline(cin, userInput);
        if (userInput.empty())
        {
            break;
        }
    }
}

void displaySubMenu()
{
    cout << "   a) Sort by Area (Ascending)" << endl;
    cout << "   b) Sort by Area (Descending)" << endl;
    cout << "   c) Sort by Special Type and Area" << endl;
}