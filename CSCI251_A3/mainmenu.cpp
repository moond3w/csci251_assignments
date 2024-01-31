/* =====================================================
 Compile : g++ -std=c++11 Point2D.o Point3D.o Line2D.o Line3D.o mainmenu.cpp -o csci251_a3.exe
 Run     : ./csci251_a3.exe
   ===================================================== */ 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "MyTemplates.h"
#include "Point2D.h"
#include "Point3D.h"
#include "Line2D.h"
#include "Line3D.h"
#include "mainmenu.h"

using namespace std;

// Global vectors to store all class objects
vector<Point2D> my2DPointArr;
vector<Point3D> my3DPointArr;
vector<Line2D> my2DLineArr;
vector<Line3D> my3DLineArr;

// Global vectors to store all unique class objects
vector<Point2D> my2DPointSet;
vector<Point3D> my3DPointSet;
vector<Line2D> my2DLineSet;
vector<Line3D> my3DLineSet;

// Keep track of total number of records
int counter;

// Keep track of current criteria
string filterCriteria;
string sortCriteria;
string sortOrder;

// Possible sorting criteria for each filter
vector<string> point2DSort = {"x-coordinate", "y-coordinate", "Length"};
vector<string> point3DSort = {"x-coordinate", "y-coordinate", "z-coordinate", "Length"};
vector<string> LineSort =    {"Pt. 1", "Pt. 2", "Length"};

int main()
{
    // Starting criteria
    filterCriteria = "Point2D";
    sortCriteria   = "x-coordinate";
    sortOrder      = "ASC";
    
    // Initialization for program run
    bool runProgram = true;
    string userInput;
    int menuInput;

    // Start of program
    while (runProgram)
    {
        displayMainMenu();
        cout << "Please enter your choice: ";
        getline(cin, userInput);
        cout << endl;

        userInput = verifyInput(userInput);
        menuInput = stoi(userInput);

        switch (menuInput) {
            case 1:
                processInputFile();
                break;
            
            case 2:
                cout << "[ Specifying filtering criteria (current : " << filterCriteria << ")]" << endl;
                selectFilterCriteria();
                break;
            
            case 3: 
                cout << "[ Specifying sorting criteria (current : " << sortCriteria << ")]" << endl;
                selectSortCriteria();
                break;

            case 4:
                cout << "[ Specifying sorting order (current : " << sortOrder << ")]" << endl;
                selectSortOrder();
                break;
            
            case 5:
                cout << "[View Data... ]" << endl;
                viewData();
                returnToMenu();
                break;

            case 6:
                storeData();
                break;
            
            case 7:
                cout << "Thank you for using the Assignment 3 Program." << endl;
                cout << "[ Exiting Program... ]" << endl;
                cout << endl;
                runProgram = false;
                break;
            
            default:
                cout << "Invalid choice." << endl;
                cout << "Please enter an integer within the menu range. (1 - 7)" << endl;
                cout << endl;
                returnToMenu();
        }
        //cin.ignore(80, '\n');
    }

    return 0;
}


// Read in and process .txt file entered by user
void processInputFile()
{
    // Initialize for file input
    string inputFile;
    ifstream inData;
    ofstream outData;

    string delim;
    string aLine;
	vector<string> dataItems;

    // Every new processInputFile resets count of records
    counter = 0;

    // Retrieve filename from user
    cout << "Please enter filename : ";
    getline(cin, inputFile);
	cout << endl;

    inputFile = verifyInputFileName(inputFile);
	
    inData.open(inputFile);

    while (getline(inData, aLine))
    {
        delim = ", ";
        dataItems = splitString(aLine, delim);
        
        // Processing data for "Point2D, [x, y]"
        if (dataItems[0] == "Point2D")
        {
            // remove [ and ] from strings "[x", "y]"
            dataItems[1].erase(0, 1);
            dataItems[2].erase(dataItems[2].size()-1);

            // convert to int and store as Point2D obj
            int i, j;
            i = stoi(dataItems[1]);
            j = stoi(dataItems[2]);

            Point2D temp = Point2D(i, j);
            my2DPointArr.push_back(temp);
        }

        // Processing data for "Point3D, [x, y, z]"
        if (dataItems[0] == "Point3D")
        {
            // remove [ and ] from strings "[x", "z]"
            dataItems[1].erase(0, 1);
            dataItems[3].erase(dataItems[3].size()-1);

            // convert to int and store as Point3D obj
            int i, j, k;
            i = stoi(dataItems[1]);
            j = stoi(dataItems[2]);
            k = stoi(dataItems[3]);

            Point3D temp = Point3D(i, j, k);
            my3DPointArr.push_back(temp);
        }

        // Processing data for "Line2D, [a, b], [x, y]"
        if (dataItems[0] == "Line2D")
        {
            // remove [ and ] from strings "[a", "b]", "[x", "y]"
            dataItems[1].erase(0, 1);
            dataItems[2].erase(dataItems[2].size()-1);
            dataItems[3].erase(0, 1);
            dataItems[4].erase(dataItems[4].size()-1);

            // convert to int
            int i, j, k, l;
            i = stoi(dataItems[1]);
            j = stoi(dataItems[2]);
            k = stoi(dataItems[3]);
            l = stoi(dataItems[4]);

            // store as Line2D obj
            Point2D pt1 = Point2D(i, j);
            Point2D pt2 = Point2D(k, l);
            Line2D temp = Line2D(pt1, pt2);
            my2DLineArr.push_back(temp);
        }

        // Processing data for "Line3D, [a, b, c], [x, y, z]"
        if (dataItems[0] == "Line3D")
        {
            // remove [ and ] from strings "[a,", "c]", "[x", "z]"
            dataItems[1].erase(0, 1);
            dataItems[3].erase(dataItems[3].size()-1);
            dataItems[4].erase(0, 1);
            dataItems[6].erase(dataItems[6].size()-1);

            // convert to int and store as Line3D obj
            int i, j, k, l, m, n;
            i = stoi(dataItems[1]);
            j = stoi(dataItems[2]);
            k = stoi(dataItems[3]);
            l = stoi(dataItems[4]);
            m = stoi(dataItems[5]);
            n = stoi(dataItems[6]);
    
            //store as Line3D obj
            Point3D pt1 = Point3D(i, j, k);
            Point3D pt2 = Point3D(l, m, n);
            Line3D temp = Line3D(pt1, pt2);
            my3DLineArr.push_back(temp);
        }
    }
	inData.close();

    // Process Arrays
    processUniqueData();

    // Output to prompt user number of records read
    cout << counter << " records read in successfully!" << endl;
	cout << endl;
    cout << "Going back to main menu... "<< endl;
    cout << endl;
}

// Function to split string into vector based on delim
vector<string> splitString (string str, string delim)
{
	// initial result is empty
	vector<string> result;
	size_t pos = 0;
	string token;

	while ((pos = str.find(delim)) != std::string::npos)
	{
		token = str.substr(0, pos);
		result.push_back(token);
		str.erase(0, pos+delim.length());
	}

	if (!str.empty())
		result.push_back(str);
	
	return (result);
}

// Filter through vectors to store unique data
void processUniqueData()
{
    // Filter unique Point2D objects by checking against unique vector
    for (Point2D newPoint : my2DPointArr)
    {
        bool isUnique = true;
        for (Point2D uniquePoint : my2DPointSet)
        {
            if (newPoint == uniquePoint)
                isUnique = false;
        }

        // If no copy found in my3DPointSet
        if (isUnique)
        {
            my2DPointSet.push_back(newPoint);
            counter++;
        }
    }
    
    // Filter unique Point3D objects by checking against unique vector
    for (Point3D newPoint : my3DPointArr)
    {
        bool isUnique = true;
        for (Point3D uniquePoint : my3DPointSet)
        {
            if (newPoint == uniquePoint)
                isUnique = false;
        }

        // If no copy found in my3DPointSet
        if (isUnique)
        {
            my3DPointSet.push_back(newPoint);
            counter++;
        }
    }

    // Filter unique Line2D objects by checking against unique vector
    for (Line2D newLine : my2DLineArr)
    {
        bool isUnique = true;
        for (Line2D uniqueLine : my2DLineSet)
        {
            if (newLine == uniqueLine)
                isUnique = false;
        }

        // If no copy found in my2DLineSet
        if (isUnique)
        {
            my2DLineSet.push_back(newLine);
            counter++;
        }
    }

    // Filter unique Line3D objects by checking against unique vector
    for (Line3D newLine : my3DLineArr)
    {
        bool isUnique = true;
        for (Line3D uniqueLine : my3DLineSet)
        {
            if (newLine == uniqueLine)
                isUnique = false;
        }

        // If no copy found in my2DLineSet
        if (isUnique)
        {
            my3DLineSet.push_back(newLine);
            counter++;
        }
    }

    // Clear arrays after filter
    my2DPointArr.clear();
    my3DPointArr.clear();
    my2DLineArr.clear();
    my3DLineArr.clear();
}

// Menu for main page
void displayMainMenu()
{
    cout << "Student ID   : 7910939"           << endl;
    cout << "Student Name : Chai Guo Liang"    << endl;
    cout << "-------------------------------"  << endl;
    cout << "Welcome to Assignment 3 Program!" << endl;
    cout << endl;
    cout << "1)   Read In Data" << endl;
    cout << "2)   Specify Filtering Criteria (Current: " << filterCriteria << ")" << endl;
    cout << "3)   Specify Sorting Criteria (Current: " << sortCriteria << ")"     << endl;
    cout << "4)   Specify Sorting Order (Current: " << sortOrder << ")"           << endl;
    cout << "5)   View Data"    << endl;
    cout << "6)   Store Data"   << endl;
    cout << "7)   Quit Program" << endl;
    cout << endl;
}

// Menu for filter criteria page
void displayFilterMenu()
{
    cout << "    a)    Point2D records" << endl;
    cout << "    b)    Point3D records" << endl;
    cout << "    c)    Line2D records"  << endl;
    cout << "    d)    Line3D records"  << endl;
    cout << endl;
}

// Menu for sort criteria page
void displaySortCriteriaMenu()
{
    if (filterCriteria == "Point2D")
    {
        cout << "    a)    X coordinate value"    << endl;
        cout << "    b)    Y coordinate value"    << endl;
        cout << "    c)    Dist. Fr Origin value" << endl;
    }
    if (filterCriteria == "Point3D")
    {
        cout << "    a)    X coordinate value"    << endl;
        cout << "    b)    Y coordinate value"    << endl;
        cout << "    c)    Z coordinate value"    << endl;
        cout << "    d)    Dist. Fr Origin value" << endl;
    }
    if ((filterCriteria == "Line2D") || (filterCriteria == "Line3D"))
    {
        cout << "    a)    Pt.1's (x, y) values" << endl;
        cout << "    b)    Pt.2's (x, y) values" << endl;
        cout << "    c)    Length value"         << endl;
    }
    cout << endl;
}

// Menu for sort order page
void displaySortOrderMenu()
{
    cout << "    a)    ASC (Ascending Order)"  << endl;
    cout << "    b)    DSC (Descending Order)" << endl;
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

// Verify and loops till a valid integer is entered.
string verifyInput (string userInput)
{
    // If user does not enter integer, loop until user does
    while (!isInteger(userInput))
    {
        cout << "Invalid choice." << endl;
        cout << "Please enter an integer to proceed." << endl;
        cout << endl;
        returnToMenu();
        displayMainMenu();
        cout << "Please enter your choice: ";
        getline(cin, userInput);
        cout << endl;
    }
    return userInput;
}

// Function to select filter criteria (Menu Option 2)
void selectFilterCriteria()
{
    string userInput;
    bool filterNotSet = true;

    while (filterNotSet)
    {
        displayFilterMenu();
        cout << "Please enter your criteria (a - d) : ";
        getline(cin, userInput);

        if (userInput == "a")
        {
            filterCriteria = "Point2D";

            // Ensure sortCriteria is valid - if not in point2DSort, set to default
            if (!(in_array(sortCriteria, point2DSort)))
                sortCriteria = point2DSort[0];

            filterNotSet = false;
        }
        else if (userInput == "b")
        {
            filterCriteria = "Point3D";

            // Ensure sortCriteria is valid - if not in point3DSort, set to default
            if (!(in_array(sortCriteria, point3DSort)))
                sortCriteria = point3DSort[0];

            filterNotSet = false;
        }
        else if (userInput == "c")
        {
            filterCriteria = "Line2D";

            // Ensure sortCriteria is valid - if not in LineSort, set to default
            if (!(in_array(sortCriteria, LineSort)))
                sortCriteria = LineSort[0];

            filterNotSet = false;
        }
        else if (userInput == "d")
        {
            filterCriteria = "Line3D";

            // Ensure sortCriteria is valid - if not in LineSort, set to default
            if (!(in_array(sortCriteria, LineSort)))
                sortCriteria = LineSort[0];

            filterNotSet = false;
        }
        else
        {
            cout << "Invalid Input! Please try again." << endl;
            cout << endl;
        }
    }

    cout << "Filter criteria successfully set to '" << filterCriteria << "'!" << endl;
    cout << endl;
}

// Function to select sorting criteria (Menu Option 3)
void selectSortCriteria()
{
    string userInput;
    bool sortNotSet = true;

    while (sortNotSet)
    {
        displaySortCriteriaMenu();
        if (filterCriteria == "Point2D")
        {
            cout << "Please enter your criteria (a - c) : ";
            getline(cin, userInput);
            // By x coordinate value
            if (userInput == "a")
            {
                sortCriteria = "x-coordinate";
                sortNotSet = false;
            }
            // By y coordinate value
            else if (userInput == "b")
            {
                sortCriteria = "y-coordinate";
                sortNotSet = false;
            }
            // By Dist Fr Origin value
            else if (userInput == "c")
            {
                sortCriteria = "Length";
                sortNotSet = false;
            }
            else
            {
                cout << "Invalid Input! Please try again." << endl;
                cout << endl;
            }
        }
        
        if (filterCriteria == "Point3D")
        {
            cout << "Please enter your criteria (a - d) : ";
            getline(cin, userInput);
            // By x coordinate value
            if (userInput == "a")
            {
                sortCriteria = "x-coordinate";
                sortNotSet = false;
            }
            // By y coordinate value
            else if (userInput == "b")
            {
                sortCriteria = "y-coordinate";
                sortNotSet = false;
            }
            // By z coordinate value
            else if (userInput == "c")
            {
                sortCriteria = "z-coordinate";
                sortNotSet = false;
            }
            // By Dist Fr Origin value
            else if (userInput == "d")
            {
                sortCriteria = "Length";
                sortNotSet = false;
            }
            else
            {
                cout << "Invalid Input! Please try again." << endl;
                cout << endl;
            }
        }

        if ((filterCriteria == "Line2D") || (filterCriteria == "Line3D"))
        {
            cout << "Please enter your criteria (a - c) : ";
            getline(cin, userInput);
            // By X and Y coordinate values of pt 1
            if (userInput == "a")
            {
                sortCriteria = "Pt. 1";
                sortNotSet = false;
            }
            // By X and Y coordinate values of pt 2
            else if (userInput == "b")
            {
                sortCriteria = "Pt. 2";
                sortNotSet = false;
            }
            // By Length value
            else if (userInput == "c")
            {
                sortCriteria = "Length";
                sortNotSet = false;
            }
            else
            {
                cout << "Invalid Input! Please try again." << endl;
                cout << endl;
            }
        }
    }

    cout << "Sorting criteria successfully set to '" << sortCriteria << "'!" << endl;
    cout << endl;
}

// Function to select sort order (Menu Option 4)
void selectSortOrder()
{
    string userInput;
    bool sortOrderNotSet = true;

    while (sortOrderNotSet)
    {
        displaySortOrderMenu();
        cout << "Please enter your criteria (a - b) : ";
        getline(cin, userInput);

        if (userInput == "a")
        {
            sortOrder = "ASC";
            sortOrderNotSet = false;
        }
        else if (userInput == "b")
        {
            sortOrder = "DSC";
            sortOrderNotSet = false;
        }
        else
        {
            cout << "Invalid Input! Please try again." << endl;
            cout << endl;
        }
    }

    cout << "Sorting order successfully set to '" << sortOrder << "'!" << endl;
    cout << endl;
}

// Function to view data (Menu Option 5)
void viewData()
{
    cout << " filtering criteria : " << filterCriteria << endl;
    cout << " sorting criteria   : " << sortCriteria   << endl;
    cout << " sorting order      : " << sortOrder      << endl;
    cout << endl;

    sortData(filterCriteria, sortCriteria, sortOrder);
    
    if (filterCriteria == "Point2D")
    {
        cout << "    X     Y    Dist. Fr Origin"        << endl;
        cout << "- - - - - - - - - - - - - - - - - - -" << endl;
        for (Point2D my2DPoint : my2DPointSet)
            cout << my2DPoint << endl;
    }

    if (filterCriteria == "Point3D")
    {
        cout << "    X     Y     Z    Dist. Fr Origin"        << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
        for (Point3D my3DPoint : my3DPointSet)
            cout << my3DPoint << endl;
    }

    if (filterCriteria == "Line2D")
    {
        cout << " P1-X  P1-Y     P2-X  P2-Y    Length"        << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
        for (Line2D my2DLine : my2DLineSet)
            cout << my2DLine << endl;
    }
    
    if (filterCriteria == "Line3D")
    {
        cout << " P1-X  P1-Y  P1-Z     P2-X  P2-Y  P2-Z    Length"        << endl;
        cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        for (Line3D my3DLine : my3DLineSet)
            cout << my3DLine << endl;
    }

    cout << endl;
}

// Function to store data to txt file (Menu Option 6)
void storeData()
{
    ofstream outData;
    string outputFileName;
    int counter; // keep track of number of records in output
    
    // Get text file name from user
    cout << "Please enter filename : ";
    getline(cin, outputFileName);

    // Check valid file name
    outputFileName = verifyOutputFileName(outputFileName);

    outData.open(outputFileName);

    outData << " filtering criteria : " << filterCriteria << endl;
    outData << " sorting criteria   : " << sortCriteria   << endl;
    outData << " sorting order      : " << sortOrder      << endl;
    outData << endl;

    sortData(filterCriteria, sortCriteria, sortOrder);
    
    if (filterCriteria == "Point2D")
    {
        outData << "    X     Y    Dist. Fr Origin"        << endl;
        outData << "- - - - - - - - - - - - - - - - - - -" << endl;
        for (Point2D my2DPoint : my2DPointSet)
            outData << my2DPoint << endl;
        
        counter = my2DPointSet.size();
    }

    if (filterCriteria == "Point3D")
    {
        outData << "    X     Y     Z    Dist. Fr Origin"        << endl;
        outData << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
        for (Point3D my3DPoint : my3DPointSet)
            outData << my3DPoint << endl;
        
        counter = my3DPointSet.size();
    }

    if (filterCriteria == "Line2D")
    {
        outData << " P1-X  P1-Y     P2-X  P2-Y    Length"        << endl;
        outData << "- - - - - - - - - - - - - - - - - - - - - -" << endl;
        for (Line2D my2DLine : my2DLineSet)
            outData << my2DLine << endl;
        
        counter = my2DLineSet.size();
    }
    
    if (filterCriteria == "Line3D")
    {
        outData << " P1-X  P1-Y  P1-Z     P2-X  P2-Y  P2-Z    Length"        << endl;
        outData << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
        for (Line3D my3DLine : my3DLineSet)
            outData << my3DLine << endl;
        
        counter = my3DLineSet.size();
    }

    outData.close();

    cout << endl;
    cout << counter << " records output successfully!" << endl;
    cout << endl;
    cout << "Going back to main menu ..." << endl;
    cout << endl;

}

void sortData(string filterCriteria, string sortCriteria, string sortOrder)
{
    // Sorting possibilities for Point3D
    if (filterCriteria == "Point2D")
    {
        if ((sortCriteria == "x-coordinate") && (sortOrder == "ASC"))
            sort(my2DPointSet.begin(), my2DPointSet.end(), Point2D::compareXAsc);
        
        if ((sortCriteria == "x-coordinate") && (sortOrder == "DSC"))
            sort(my2DPointSet.begin(), my2DPointSet.end(), Point2D::compareXDsc); 
        
        if ((sortCriteria == "y-coordinate") && (sortOrder == "ASC"))
            sort(my2DPointSet.begin(), my2DPointSet.end(), Point2D::compareYAsc);
        
        if ((sortCriteria == "y-coordinate") && (sortOrder == "DSC"))
            sort(my2DPointSet.begin(), my2DPointSet.end(), Point2D::compareYDsc); 
        
        if ((sortCriteria == "Length") && (sortOrder == "ASC"))
            sort(my2DPointSet.begin(), my2DPointSet.end(), Point2D::compareScalarAsc);
        
        if ((sortCriteria == "Length") && (sortOrder == "DSC"))
            sort(my2DPointSet.begin(), my2DPointSet.end(), Point2D::compareScalarDsc); 
        
    }

    // Sorting possibilities for Point3D
    if (filterCriteria == "Point3D")
    {
        if ((sortCriteria == "x-coordinate") && (sortOrder == "ASC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareXAsc);
        
        if ((sortCriteria == "x-coordinate") && (sortOrder == "DSC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareXDsc); 
        
        if ((sortCriteria == "y-coordinate") && (sortOrder == "ASC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareYAsc);
        
        if ((sortCriteria == "y-coordinate") && (sortOrder == "DSC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareYDsc);
        
        if ((sortCriteria == "z-coordinate") && (sortOrder == "ASC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareZAsc);
        
        if ((sortCriteria == "z-coordinate") && (sortOrder == "DSC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareZDsc); 
        
        if ((sortCriteria == "Length") && (sortOrder == "ASC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareScalarAsc);
        
        if ((sortCriteria == "Length") && (sortOrder == "DSC"))
            sort(my3DPointSet.begin(), my3DPointSet.end(), Point3D::compareScalarDsc); 
    }

    // Sorting possibilities for Line2D
    if (filterCriteria == "Line2D")
    {
        if ((sortCriteria == "Pt. 1") && (sortOrder == "ASC"))
            sort(my2DLineSet.begin(), my2DLineSet.end(), Line2D::compareXYAscPt1);
        
        if ((sortCriteria == "Pt. 1") && (sortOrder == "DSC"))
            sort(my2DLineSet.begin(), my2DLineSet.end(), Line2D::compareXYDscPt1); 
        
        if ((sortCriteria == "Pt. 2") && (sortOrder == "ASC"))
            sort(my2DLineSet.begin(), my2DLineSet.end(), Line2D::compareXYAscPt2);
        
        if ((sortCriteria == "Pt. 2") && (sortOrder == "DSC"))
            sort(my2DLineSet.begin(), my2DLineSet.end(), Line2D::compareXYDscPt2); 
        
        if ((sortCriteria == "Length") && (sortOrder == "ASC"))
            sort(my2DLineSet.begin(), my2DLineSet.end(), Line2D::compareScalarAsc); 
        
        if ((sortCriteria == "Length") && (sortOrder == "DSC"))
            sort(my2DLineSet.begin(), my2DLineSet.end(), Line2D::compareScalarDsc); 
    }

    // Sorting possibilities for Line3D
    if (filterCriteria == "Line3D")
    {
        if ((sortCriteria == "Pt. 1") && (sortOrder == "ASC"))
            sort(my3DLineSet.begin(), my3DLineSet.end(), Line3D::compareXYZAscPt1);
        
        if ((sortCriteria == "Pt. 1") && (sortOrder == "DSC"))
            sort(my3DLineSet.begin(), my3DLineSet.end(), Line3D::compareXYZDscPt1); 
        
        if ((sortCriteria == "Pt. 2") && (sortOrder == "ASC"))
            sort(my3DLineSet.begin(), my3DLineSet.end(), Line3D::compareXYZAscPt2);
        
        if ((sortCriteria == "Pt. 2") && (sortOrder == "DSC"))
            sort(my3DLineSet.begin(), my3DLineSet.end(), Line3D::compareXYZDscPt2); 
        
        if ((sortCriteria == "Length") && (sortOrder == "ASC"))
            sort(my3DLineSet.begin(), my3DLineSet.end(), Line3D::compareScalarAsc); 
        
        if ((sortCriteria == "Length") && (sortOrder == "DSC"))
            sort(my3DLineSet.begin(), my3DLineSet.end(), Line3D::compareScalarDsc); 
    }
}

// Check for string in array
bool in_array(const string &value, const vector<string> &array)
{
    return find(array.begin(), array.end(), value) != array.end();
}

// Ensure input filename entered is valid
string verifyInputFileName(string userInput)
{
    bool fileNameVerified = false;
    bool fileExists = false;
    while (!fileNameVerified)
    {
        //Check if userInput len > 4 to store a valid file name (a.txt)
        if (userInput.size() > 4)
        {
            // Check if last 4 char of userInput == ".txt"
            if (equal((userInput.begin() + userInput.size() - 4), userInput.end(), ".txt"))
            {
                fileNameVerified = true;
                break;
            }
        }

        // If userInput fails conditions
        cout << "Invalid file name." << endl;
        cout << "Filename must include at least 1 letter and end with '.txt'." << endl;
        cout << endl;
        cout << "Please enter filename : ";
        getline(cin, userInput);
    }

    while (!fileExists)
    {
        ifstream fs(userInput);
        // If file opens successfully == file exists
        if (fs.is_open()) 
        {
            fs.close();
            // file name is valid
            fileExists = true;
            break;
        }
        else 
        {
            cout << "Filename does not exists!" << endl;
            cout << "Filename must be a valid '.txt' file in the directory." << endl;
            cout << endl;
            cout << "Please enter filename : ";
            getline(cin, userInput);
        }
    }

    return userInput;
}

// Ensure output filename entered is valid
string verifyOutputFileName(string userInput)
{
    bool fileNameVerified = false;
    bool fileExists = true;

    while (!fileNameVerified)
    {
        //Check if userInput len > 4 to store a valid file name (a.txt)
        if (userInput.size() > 4)
        {
            // Check if last 4 char of userInput == ".txt"
            if (equal((userInput.begin() + userInput.size() - 4), userInput.end(), ".txt"))
            {
                fileNameVerified = true;
                break;
            }
        }

        // If userInput fails conditions
        cout << "Invalid file name." << endl;
        cout << "Filename must include at least 1 letter and end with '.txt'." << endl;
        cout << endl;
        cout << "Please enter filename : ";
        getline(cin, userInput);
    }

    // Check if filename entered exists in directory
    while (fileExists)
    {
        ifstream fs(userInput);
        // If file opens successfully == file exists
        if (fs.is_open()) 
        {
            fs.close();

            cout << "Filename already exists!" << endl;
            cout << "Filename must not share a name with an existing file." << endl;
            cout << endl;
            cout << "Please enter filename : ";
            getline(cin, userInput);
        }
        else 
        {
            fileExists = false;
            break;
        }
    }
    return userInput;
}