#ifndef PROCESSREPORT_H
#define PROCESSREPORT_H

#include <string>
#include "processConfig.h"

bool isAdjacent(int x, int y, int city_id);
float calcCloudPressure(int city_id, CloudPressureType * cloudPressureArrayPtr);
string calcCloudPressureLMH(float cloudPressure);
float calcProbOfRain(string avgPressure, string avgCloudCover);
void displayProbOfRain(float probOfRain);
void displaySummaryReport();
void getUniqueCityID();
string getCityName(int city_id);
void safelyDeallocateMemory(int arraySize, int * intArr);

#endif