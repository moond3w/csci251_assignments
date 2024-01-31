/* =====================================
   To compile : g++ -std=c++11 processConfig.o displayMaps.o processReport.o mainmenu.cpp -o csci251_a1.exe
   =====================================
   To run     : ./csci251_a1.exe
   =====================================
*/

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

#include "processConfig.h"
#include "displayMaps.h"
#include "processReport.h"
#include "mainmenu.h"

using namespace std;

int main()
{
    // Initialization
    bool runProgram = true;
    string userInput;
    int menuInput;

    // Extern var from processConfig.o
    extern GridIdx GridX_IdxRange, GridY_IdxRange;
    extern int mapArraySize;
    extern int cityArraySize;
    extern CityLocationType * cityLocationArrayPtr; 
    extern CloudPressureType * cloudCoverArrayPtr;
    extern CloudPressureType * atmPressureArrayPtr;
    // Extern var from processReport.o
    extern int * uniqueCityArr;
    extern int uniqueCitySize;

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
                cout << "[ Read in and process a configuration file ]" << endl;
                cout << endl;
                processConfig();
                cin.ignore(80, '\n');
                cout << endl;
                break;

            case 2:
                cout << "[ Display City Map ]" << endl;
                cout << endl;
                displayGrid("city");
                cout << endl;
                returnToMenu();
                break;

            case 3:
                cout << "[ Display Cloud Coverage Map (Cloudiness Index) ]" << endl;
                cout << endl;
                displayGrid("cloud_index");
                cout << endl;
                returnToMenu();
                break;

            case 4:
                cout << "[ Display Cloud Coverage Map (LMH Symbols) ]" << endl;
                cout << endl;
                displayGrid("cloud_lmh");
                cout << endl;
                returnToMenu();
                break;

            case 5:
                cout << "[ Display Atmospheric Pressure Map (Pressure Index) ]" << endl;
                cout << endl;
                displayGrid("pressure_index");
                cout << endl;
                returnToMenu();
                break;

            case 6:
                cout << "[ Display Atmospheric Pressure Map (LMH Symbols) ]" << endl;
                cout << endl;
                displayGrid("pressure_lmh");
                cout << endl;
                returnToMenu();
                break;

            case 7:
                cout << "[ Display Cloud Coverage Map By City (LMH Symbols) ]" << endl;
                displayGridByCity("cloud_cover");
                returnToMenu();
                break;

            case 8:
                cout << "[ Display Atmospheric Pressure Map By City (LMH Symbols) ]" << endl;
                displayGridByCity("pressure");
                returnToMenu();
                break;
            
            case 9:
                cout << "[ Show Weather Forecast Summary Report ]" << endl;
                displaySummaryReport();
                returnToMenu();
                break;
            
            case 0:
                cout << "Thank you for using the Weather Information Processing System." << endl;
                cout << "[ Exiting Program... ]" << endl;
                cout << endl;
                runProgram = false;
                break;

            default:
                cout << "Invalid choice." << endl;
                cout << "Please enter an integer within the menu range. (0 - 9)" << endl;
                cout << endl;
                returnToMenu();
        }
    }

    // clear arrays
	safelyDeallocateMemory(cityArraySize, cityLocationArrayPtr);
	safelyDeallocateMemory(mapArraySize, cloudCoverArrayPtr);
	safelyDeallocateMemory(mapArraySize, atmPressureArrayPtr);
    safelyDeallocateMemory(uniqueCitySize, uniqueCityArr);

    return (0);
}

// Displays Main Menu screen
void displayMenu()
{
    cout << "Student ID   : 7910939" << endl;
    cout << "Student Name : Chai Guo Liang" << endl;
    cout << "==============================" << endl;
    cout << "Welcome to Weather Information Processing System!" << endl;
    cout << endl;
    cout << "1)   Read in and process a configuration file" << endl;
    cout << "2)   Display City Map" << endl;
    cout << "3)   Display Cloud Coverage Map (Cloudiness Index)" << endl;
    cout << "4)   Display Cloud Coverage Map (LMH Symbols)" << endl;
    cout << "5)   Display Atmospheric Pressure Map (Pressure Index)" << endl;
    cout << "6)   Display Atmospheric Pressure Map (LMH Symbols)" << endl;
    cout << "7)   Display Cloud Coverage Map By City (LMH Symbols)" << endl;
    cout << "8)   Display Atmospheric Pressure Map By City (LMH Symbols)" << endl;
    cout << "9)   Show Weather Forecast Summary Report" << endl;
    cout << "0)   Quit Program" << endl;
    cout << endl;
}

// Prompt user to input <enter> to return to main menu
void returnToMenu()
{
    string userInput;
    // Loop until empty string detected (<enter>)
    while (true)
    {
        cout << "Press <enter> to go back to main menu..." << endl << endl;
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
