#ifndef PROCESSCONFIG_H
#define PROCESSCONFIG_H

#include <string>
#include <vector>

using namespace std;

struct GridIdx
{
    int start;
    int end;
};

struct Coordinate
{
    int x;
    int y;
};

struct CityLocation
{
    Coordinate coord;
    int city_id;
    string city_name;
};

// Structure to contain information about cloud cover OR atmospheric pressure
struct CloudPressure
{
    int cloud_pressure;
    string cp_index;
    string lmh;
    Coordinate coord;
};

typedef struct CityLocation CityLocationType;
typedef struct CloudPressure CloudPressureType;

void processConfig();
int getCityArraySize(string filename);
void readAndProcessFile(string fileName, int data_count);
void processCityLocation(string filename, int cityArraySize, CityLocationType * cityInfoArrayPtr);
void processCloudPressure(string fileName, int mapArraySize, CloudPressureType * cloudPressureArrayPtr);
vector<string> splitString (string str, string delim);
string convertToIndex (int x);
string convertToLMH (int x);
void safelyDeallocateMemory(int, CityLocationType * cityLocationArrayPtr);
void safelyDeallocateMemory(int, CloudPressureType * cloudPressureArrayPtr);

#endif