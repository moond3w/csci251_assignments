/* =====================================
   To compile for testing : g++ -std=c++11 processConfig.o displayMaps.cpp -o displayMaps.exe
   g++ -std=c++11 processConfig.o processReport.o mainmenu.o  displayMaps.cpp -o displayMaps.exe
   =====================================
   To compile : g++ -c displayMaps.cpp
   =====================================
   To run     : ./displayMaps.exe
   =====================================
*/

#include <iostream>
#include <string>
#include <sstream>
#include "displayMaps.h"
#include "processConfig.h"
#include "processReport.h"
#include "mainmenu.h"

using namespace std;

// Extern var from processConfig.cpp
extern GridIdx GridX_IdxRange, GridY_IdxRange;
extern int mapArraySize;
extern int cityArraySize;
extern CityLocationType * cityLocationArrayPtr; 
extern CloudPressureType * cloudCoverArrayPtr;
extern CloudPressureType * atmPressureArrayPtr;

extern int * uniqueCityArr;
extern int uniqueCitySize;

/*
Types of display: 
"city" - City location   
"cloud_index" - Cloud Cover as Index    "pressure_index" - Atm. Pressure as Index
"cloud_lmh"   - Cloud Cover as LMH      "pressure_lmh"   - Atm. Pressure as LMH
*/
void displayGrid(string display)
{
    int startX = GridX_IdxRange.start;
    int endX = GridX_IdxRange.end;
    int startY = GridY_IdxRange.start;
    int endY = GridY_IdxRange.end;
    
    // to display left border
    int y_axis = endY;

    // to track values of x and y on the grid from top left
    int track_x = startX;
    int track_y = endY;

    // determine length of border - +2 to include top and bot
    int borderX = endX - startX + 2;
    int borderY = endY - startY + 2;

    for (int row = 0; row <= borderY; row++)
    {
        // Display y_axis border
        if (row == 0 || row == borderY)
        {
            cout << "  ";
        }
        else
        {
            cout << y_axis << " ";
            y_axis = y_axis -1;
        }

        // Printing of border and grid
        for (int col = 0; col <= borderX; col++)
		{
            // Print top and bottom border
			if (row == 0 || row == borderY)
			{
				cout << "X ";
			}
            else
			{
                // Print left and right border
				if (col == 0 || col == borderX)
					cout << "X ";
                
                // Print Map
				else
                {
                    // Possible Types of maps:
                    string mapOutput;

                    if (display == "city")
                        mapOutput = getCityDisplay(track_x, track_y);
                    else if (display == "cloud_index")
                        mapOutput = getCPIndexDisplay(track_x, track_y, cloudCoverArrayPtr);
                    else if (display == "pressure_index")
                        mapOutput = getCPIndexDisplay(track_x, track_y, atmPressureArrayPtr);
                    else if (display == "cloud_lmh")
                        mapOutput = getCPLMHDisplay(track_x, track_y, cloudCoverArrayPtr);
                    else if (display == "pressure_lmh")
                        mapOutput = getCPLMHDisplay(track_x, track_y, atmPressureArrayPtr);
                    
                    cout << mapOutput;

                    // increment for track_x
                    track_x = track_x + 1;
                }
			}
        }
        cout << endl;

        // reset x y values for next row of grid if NOT border
        if (row != 0 && row != borderY)
		{
            track_y = track_y - 1;
            track_x = startX;
        }
    }

    // Display x-axis border heading
    cout << "    ";
    for (int x_axis = startX; x_axis <= endX; x_axis++)
    {
        cout << x_axis << " ";
    }

    cout << endl;
}


// get city id as string for display on map
string getCityDisplay(int track_x, int track_y)
{
    string city_str;
    ostringstream oss;
    bool cityInfoFound = false;

    // Loop through city location array to see if coordinates match track_x and track_y
    for (int i = 0; i < cityArraySize; i++)
    {
        CityLocationType temp = cityLocationArrayPtr[i];
        if (track_x == temp.coord.x && track_y == temp.coord.y)
        {
            oss << temp.city_id << " ";
            cityInfoFound = true;
            city_str = oss.str();
        }
    }
    if (!(cityInfoFound))
    {
        city_str = "  ";
    }

    return city_str;
}

// get cloud pressure index as string for display on map
string getCPIndexDisplay(int track_x, int track_y, CloudPressureType * cloudPressureArrayPtr)
{
    string idx_str;
    ostringstream oss;
    bool cloudPressureFound = false;

    for (int i = 0; i < mapArraySize; i++)
    {
        CloudPressureType temp = cloudPressureArrayPtr[i];
        if (track_x == temp.coord.x && track_y == temp.coord.y)
        {
            oss << temp.cp_index << " ";
            cloudPressureFound = true;
            idx_str = oss.str();
        }
    }
    if (!(cloudPressureFound))
    {
        idx_str = "  ";
    }
    return idx_str;
}

// get cloud pressure LMH as string for display on map
string getCPLMHDisplay(int track_x, int track_y, CloudPressureType * cloudPressureArrayPtr)
{
    string lmh_str;
    ostringstream oss;
    bool cloudPressureFound = false;

    for (int i = 0; i < mapArraySize; i++)
    {
        CloudPressureType temp = cloudPressureArrayPtr[i];
        if (track_x == temp.coord.x && track_y == temp.coord.y)
        {
            oss << temp.lmh << " ";
            cloudPressureFound = true;
            lmh_str = oss.str();
        }
    }
    if (!(cloudPressureFound))
    {
        lmh_str = "  ";
    }

    return lmh_str;
}

// Get Cloud Pressure LMH display for a specific city through city_id
string getCPDisplayByID (int track_x, int track_y, int city_id, CloudPressureType * cloudPressureArrayPtr)
{
    string lmh_str;
    ostringstream oss;
    bool cloudPressureFound = false;
    for (int i = 0; i < mapArraySize; i++)
    {
        CloudPressureType temp = cloudPressureArrayPtr[i];

        // Find desired coordinate first THEN check if it is adjacent to city_id
        if (track_x == temp.coord.x && track_y == temp.coord.y)
        {
            if (isAdjacent(temp.coord.x, temp.coord.y, city_id))
            {
                oss << temp.lmh << " ";
                cloudPressureFound = true;
                lmh_str = oss.str();
            }
        }
    }
    
    if (!(cloudPressureFound))
    {
        lmh_str = "  ";
    }

    return lmh_str;
}

/*
Types of display: 
"cloud_cover" - Cloud Cover as LMH    "pressure" - Atm. Pressure as LMH
*/
void displayGridByCity(string display)
{
    getUniqueCityID();
    for (int i = 0; i < uniqueCitySize; i++)
    {
        // To retrieve valid unique id from uniqueCityArr
        // uniqueCityArr may include garbage values if not full
        if (uniqueCityArr[i] > 0 && uniqueCityArr[i] < 10)
        {
            int uniqueCityId = uniqueCityArr[i];
            string cityName = getCityName(uniqueCityId);
            cout << endl;
            cout << "City: " << cityName << endl;
            cout << endl;

            int startX = GridX_IdxRange.start;
            int endX = GridX_IdxRange.end;
            int startY = GridY_IdxRange.start;
            int endY = GridY_IdxRange.end;
            
            // to display left border
            int y_axis = endY;

            // to track values of x and y on the grid from top left
            int track_x = startX;
            int track_y = endY;

            // determine length of border - +2 to include top and bot
            int borderX = endX - startX + 2;
            int borderY = endY - startY + 2;

            for (int row = 0; row <= borderY; row++)
            {
                // Display y_axis border
                if (row == 0 || row == borderY)
                {
                    cout << "  ";
                }
                else
                {
                    cout << y_axis << " ";
                    y_axis = y_axis -1;
                }

                // Printing of border and grid
                for (int col = 0; col <= borderX; col++)
                {
                    // Print top and bottom border
                    if (row == 0 || row == borderY)
                    {
                        cout << "X ";
                    }
                    else
                    {
                        // Print left and right border
                        if (col == 0 || col == borderX)
                            cout << "X ";
                        
                        // Print Map
                        else
                        {
                            // Possible Types of maps:
                            string mapOutput;

                            if (display == "cloud_cover")
                                mapOutput = getCPDisplayByID(track_x, track_y, uniqueCityId, cloudCoverArrayPtr);
                            else if (display == "pressure")
                                mapOutput = getCPDisplayByID(track_x, track_y, uniqueCityId, atmPressureArrayPtr);
                            
                            cout << mapOutput;

                            // increment for track_x
                            track_x = track_x + 1;
                        }
                    }
                }
                cout << endl;

                // reset x y values for next row of grid if NOT border
                if (row != 0 && row != borderY)
                {
                    track_y = track_y - 1;
                    track_x = startX;
                }
            }

            // Display x-axis border heading
            cout << "    ";
            for (int x_axis = startX; x_axis <= endX; x_axis++)
            {
                cout << x_axis << " ";
            }

            cout << endl;
        }
    }
}