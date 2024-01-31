/* =====================================
   To compile for testing : g++ -std=c++11 processConfig.o processReport.cpp -o processReport.exe
   =====================================
   To compile : g++ -c processReport.cpp
   =====================================
   To run     : ./processReport.exe
   =====================================
*/

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "processConfig.h"
#include "processReport.h"

using namespace std;

// Extern var from processConfig.cpp
extern GridIdx GridX_IdxRange, GridY_IdxRange;
extern int mapArraySize;
extern int cityArraySize;
extern CityLocationType * cityLocationArrayPtr; 
extern CloudPressureType * cloudCoverArrayPtr;
extern CloudPressureType * atmPressureArrayPtr;

int * uniqueCityArr;
int uniqueCitySize = 10;

// Check if grid square is adjacent or in city
/* To determine adjacency:
    abs(x - x) and abs(y - y) must = 1 or 0
*/
bool isAdjacent(int x, int y, int city_id)
{
    bool isAdjacent = false;
    int x_diff;
    int y_diff;

    for (int i = 0; i < cityArraySize; i++)
    {
        CityLocationType city = cityLocationArrayPtr[i];
        // Identify city
        if (city.city_id == city_id)
        {
            x_diff = abs(city.coord.x - x);
            y_diff = abs(city.coord.y - y);

            if ((x_diff == 0 || x_diff == 1) && (y_diff == 0 || y_diff == 1))
            {
                isAdjacent = true;
            }
        }
    }

    return isAdjacent;
}

// Calculate and return average cloud cover or average atmospheric pressure given a city_id
float calcCloudPressure(int city_id, CloudPressureType * cloudPressureArrayPtr)
{
    float totalCloudPressure = 0;
    float averageCloudPressure = 0;
    int counter = 0;

    for (int i = 0; i < mapArraySize; i++)
    {
        CloudPressureType temp = cloudPressureArrayPtr[i];
        if (isAdjacent(temp.coord.x, temp.coord.y, city_id))
        {
            totalCloudPressure = totalCloudPressure + temp.cloud_pressure;
            counter = counter + 1;
        }
    }

    averageCloudPressure = totalCloudPressure / counter;
    return averageCloudPressure;
}

// Calculate and return cloud cover or average atmospheric pressure in LMH Symbol
string calcCloudPressureLMH(float cloudPressure)
{
    if (cloudPressure < 35)
		return "L";
	else if (cloudPressure < 65)
		return "M";
	else if (cloudPressure < 100)
		return "H";
	else
		return "?";
}

// Calculate and return probability of rain
float calcProbOfRain(string avgPressure, string avgCloudCover)
{
    float probOfRain = 0.0;
    if (avgPressure == "L")
    {
        if (avgCloudCover == "H")
            probOfRain = 90.0;
        else if (avgCloudCover == "M")
            probOfRain = 80.0;
        else if (avgCloudCover == "L")
            probOfRain = 70.0;
    }

    else if (avgPressure == "M")
    {
        if (avgCloudCover == "H")
            probOfRain = 60.0;
        else if (avgCloudCover == "M")
            probOfRain = 50.0;
        else if (avgCloudCover == "L")
            probOfRain = 40.0;
    }

    else if (avgPressure == "H")
    {
        if (avgCloudCover == "H")
            probOfRain = 30.0;
        else if (avgCloudCover == "M")
            probOfRain = 20.0;
        else if (avgCloudCover == "L")
            probOfRain = 10.0;
    }

    return probOfRain;
}

// Display ASCII print of probability of rain
void displayProbOfRain(float probOfRain)
{
    if (probOfRain < 20)
    {
        cout << "~" << endl;
        cout << "~~" << endl;
    }
    else if (probOfRain < 30)
    {
        cout << "~~" << endl;
        cout << "~~~" << endl;
    }
    else if (probOfRain < 40)
    {
        cout << "~~~" << endl;
        cout << "~~~~" << endl;
    }
    else if (probOfRain < 50)
    {
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
    }
    else if (probOfRain < 60)
    {
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "    \\ " << endl;
    }
    else if (probOfRain < 70)
    {
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "   \\\\ " << endl;
    }
    else if (probOfRain < 80)
    {
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "  \\\\\\ " << endl;
    }
    else if (probOfRain < 90)
    {
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << " \\\\\\\\ " << endl;
    }
    else if (probOfRain < 100)
    {
        cout << "~~~~" << endl;
        cout << "~~~~~" << endl;
        cout << "\\\\\\\\\\ " << endl;
    }
}

// Get array of unique city ID
void getUniqueCityID()
{
    // Maximum number of unique city ID = 10
    uniqueCityArr = new int[uniqueCitySize];

    // Counter to keep track of unique city_id
    int counter = 0;
    bool isUnique;
    // For each element in cityLocation array, loop through uniqueCityArr 
    for (int i = 0; i < cityArraySize; i++)
    {
        isUnique = true;
        CityLocationType temp = cityLocationArrayPtr[i];
        for (int j = 0; j < uniqueCitySize; j++)
        {
            // if id matches any element in uniqueCityArr
            if (temp.city_id == uniqueCityArr[j])
            {
                isUnique = false;
            }
        }

        // if no matches
        if (isUnique)
        {
            uniqueCityArr[counter] = temp.city_id;
            counter = counter + 1;
        }
    }
}

// Retrieve string city_name given city_id
string getCityName(int city_id)
{
    string cityName;
    for (int i = 0; i < cityArraySize; i++)
    {
        CityLocationType temp = cityLocationArrayPtr[i];
        if (temp.city_id == city_id)
        {
            cityName = temp.city_name;
            break;
        }
    }
    return cityName;
}

// Display overall summary report
void displaySummaryReport()
{
    cout << endl;
    cout << "Weather Forecast Summary Report" << endl;
    cout << "-------------------------------" << endl;

    // Have to retrieve unique cities
    getUniqueCityID();
    for (int i = 0; i < uniqueCitySize; i++)
    {
        // To retrieve valid unique id from uniqueCityArr
        // uniqueCityArr may include garbage values if not full
        if (uniqueCityArr[i] > 0 && uniqueCityArr[i] < 10)
        {
            int uniqueCityId = uniqueCityArr[i];

            // Initialize each value
            string cityName = "";
            float avgCloudCover = 0.0;
            float avgPressure = 0.0;
            string accLMH = "";
            string apLMH = "";
            float probOfRain = 0.0;

            // Calculate each value
            cityName = getCityName(uniqueCityId);
            avgCloudCover = calcCloudPressure(uniqueCityId, cloudCoverArrayPtr);
            avgPressure = calcCloudPressure(uniqueCityId, atmPressureArrayPtr);
            accLMH = calcCloudPressureLMH(avgCloudCover);
            apLMH = calcCloudPressureLMH(avgPressure);
            probOfRain = calcProbOfRain(apLMH, accLMH);
            
            cout << "City Name : " << cityName << endl;
            cout << "City ID   : " << uniqueCityId << endl;
            cout << "Ave. Cloud Cloud (ACC)   : " << fixed << setprecision(2) << avgCloudCover << " (" << accLMH << ")" << endl;
            cout << "Ave. Pressure    (AP)    : " << fixed << setprecision(2) << avgPressure << " (" << apLMH << ")" << endl;
            cout << "Probability of Rain (%)  : " << fixed << setprecision(2) << probOfRain << endl;
            displayProbOfRain(probOfRain);
            cout << endl;
        }
    }

}

void safelyDeallocateMemory(int arraySize, int * intArr)
{
    if (arraySize <= 0)
        return;
    
    delete [] intArr;
}