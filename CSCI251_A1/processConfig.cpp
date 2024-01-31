/* =====================================
   To compile : g++ -c processConfig.cpp
   =====================================
   To test    : ./processConfig.exe
   =====================================
*/

#include <iostream>
#include <string>
#include <fstream>

#include <vector>
#include <sstream>
#include "processConfig.h"

using namespace std;

// global variables
int mapArraySize;
int cityArraySize;
CityLocationType * cityLocationArrayPtr = nullptr;
CloudPressureType * cloudCoverArrayPtr = nullptr;
CloudPressureType * atmPressureArrayPtr = nullptr;
GridIdx GridX_IdxRange, GridY_IdxRange;

// Take in input file for processing map information
void processConfig()
{
    // declaration
    string inputFileName;
    ifstream inData;
    ofstream outData;

	bool gridXFound = false;
	bool gridYFound = false;
	bool arrayNotInit = true;

	/* dataCount to keep track of what txt file is being processed
	   since file name is not fixed
	   0 = citylocation, 1 = cloudcover, 2 = pressure
	*/
	int dataCount = 0;

	string delim;
	vector<string> dataItems;
	vector<string> startEndRange;

    cout << "Please enter config filename : ";
    cin >> inputFileName;
	cout << endl;
	
    inData.open(inputFileName);

    string aLine;

    while (getline(inData, aLine))
    {
		// Checks for and ignores comments
		if (aLine.substr(0,2) != "//")
		{
			// Check for and determine x-axis index
			size_t pos = aLine.find("GridX_IdxRange");
			
			if (pos != string::npos)
			{
				gridXFound = true;

				delim = "=";
				dataItems = splitString(aLine, delim);

				// Further split dataItems to get <start>, <end>
				delim = "-";
				startEndRange = splitString(dataItems[1], delim);

				GridX_IdxRange.start = stoi(startEndRange[0]);
				GridX_IdxRange.end = stoi(startEndRange[1]);

				cout << "Reading in GridX_IdxRange : " << GridX_IdxRange.start << "-" << GridX_IdxRange.end << "... done!" << endl;

				continue;
			}

			// Check for and determine y-axis index
			pos = aLine.find("GridY_IdxRange");
			if (pos != string::npos)
			{
				gridYFound = true;

				delim = "=";
				dataItems = splitString(aLine, delim);

				// Further split dataItems to get <start>, <end>
				delim = "-";
				startEndRange = splitString(dataItems[1], delim);

				GridY_IdxRange.start = stoi(startEndRange[0]);
				GridY_IdxRange.end = stoi(startEndRange[1]);

				cout << "Reading in GridY_IdxRange : " << GridY_IdxRange.start << "-" << GridY_IdxRange.end << "... done!" << endl;

				continue;
			}

			// Generate and initialize data arrays after array size known
			if (gridXFound && gridYFound && arrayNotInit)
			{
				cout << endl;
				cout << "Storing data from input file: " << endl;

				// Calculate and allocate new arrays based on IdxRange
				mapArraySize = (GridX_IdxRange.end - GridX_IdxRange.start + 1)
							* (GridY_IdxRange.end - GridY_IdxRange.start + 1);

				cloudCoverArrayPtr = new CloudPressureType[mapArraySize];
				atmPressureArrayPtr = new CloudPressureType[mapArraySize];
				
				// prevent array from initializing multiple times
				arrayNotInit = false;

				continue;
			}

			// Check and processes textfiles
			pos = aLine.find(".txt");

			if (pos != string::npos)
			{
				readAndProcessFile (aLine, dataCount);
				dataCount = dataCount + 1;
			}
		}

	}
	inData.close();

	cout << endl;
	
	// If all data found and added
	if (dataCount == 3)
		cout << "All records succesfully stored. Returning to main menu... "<< endl;
	else
		cout << "Records are missing. Please check the config file name and try again!" << endl;
}

void readAndProcessFile (string filename, int dataCount)
{
	if (dataCount == 0)
	{
		cityArraySize = getCityArraySize(filename);
		cityLocationArrayPtr = new CityLocationType[cityArraySize];
		processCityLocation(filename, cityArraySize, cityLocationArrayPtr);
	}
	else if (dataCount == 1)
		processCloudPressure(filename, mapArraySize, cloudCoverArrayPtr);
	else if (dataCount == 2)
		processCloudPressure(filename, mapArraySize, atmPressureArrayPtr);
	else
		cout << "Something is wrong in readAndProcessFile: " << dataCount << endl;

	cout << filename << "... done!" << endl;
}

int getCityArraySize(string filename)
{
// Determine size of array by reading file once
	cityArraySize = 0;

	// Reading .txt file content - [x, y]-id-string
    fstream inputFile (filename.c_str(), fstream::in);

	string aLine;

	while (getline (inputFile, aLine))
    {
		cityArraySize = cityArraySize + 1;
	}

	cityArraySize = cityArraySize - 1; // remove last empty line
	inputFile.close();

	return cityArraySize;
}

void processCityLocation(string filename, int cityArraySize, CityLocationType* cityInfoArrayPtr)
{

	// Reading .txt file content - [x, y]-id-string
    fstream inputFile (filename.c_str(), fstream::in);

	// Read file to store city location information
	string aLine;
	string delim = "-";

	// counter to track array
	int i = 0;

    while (getline (inputFile, aLine) && i < cityArraySize)
    {
		// initialize temp CityLocationType struct object
		CityLocationType temp;
		vector<string> dataItems = splitString(aLine, delim);

		// Currently : dataItems {[x, y], int, string}
		string s = dataItems[0];
		temp.city_id = stoi(dataItems[1]);
		temp.city_name = dataItems[2];

		// extract coordinates from string [x, y]
    	char c;
    	istringstream ss(s);
    	ss >> c >> temp.coord.x >> c >> temp.coord.y >> c;

		cityInfoArrayPtr[i] = temp;
		i = i + 1;
	}

	inputFile.close();
}

void processCloudPressure (string filename, int mapArraySize, CloudPressureType* cloudPressureArrayPtr)
{
	// Reading .txt file content - [x,y]-int
    fstream inputFile (filename.c_str(), fstream::in);

	string aLine;
	string delim;

	delim = "-";
	// counter to track array
	int i = 0;

    while (getline (inputFile, aLine) && i < mapArraySize)
    {
		// initialize temp CloudPressure struct object
		CloudPressureType temp;
		vector<string> dataItems = splitString(aLine, delim);

		// Currently : dataItems {[x, y], int}
		string s = dataItems[0];
		temp.cloud_pressure = stoi(dataItems[1]);
		temp.cp_index = convertToIndex(temp.cloud_pressure);
		temp.lmh = convertToLMH(temp.cloud_pressure);

		// extract coordinates from string [x, y]
    	char c;
    	istringstream ss(s);
    	ss >> c >> temp.coord.x >> c >> temp.coord.y >> c;

		cloudPressureArrayPtr[i] = temp;
		i = i + 1;
	}
	inputFile.close();
}

// split string into array with delim
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

// Convert to index with inclusion of numbers > 99
string convertToIndex (int x)
{
	int index;
	string idx_str;

	index = (x / 10) % 10;
	if (index >= 10)
		idx_str = "?";
	else
		idx_str = to_string(index);
	
	return idx_str;
}

// Convert to LMH Symbols with inclusion of numbers > 99
string convertToLMH (int x)
{
	if (x < 35)
		return "L";
	else if (x < 65)
		return "M";
	else if (x < 100)
		return "H";
	else
		return "?";
}

void safelyDeallocateMemory(int arraySize, CityLocationType * cityLocationArrayPtr)
{
	if (arraySize <= 0)
		return;
	
	delete [] cityLocationArrayPtr;
}

void safelyDeallocateMemory (int arraySize, CloudPressureType * cloudPressureArrayPtr)
{
	if (arraySize <= 0)
		return;
	
	delete [] cloudPressureArrayPtr;
}

