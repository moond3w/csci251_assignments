#ifndef DISPLAYMAPS_H
#define DISPLAYMAPS_H

#include <string>
#include "processConfig.h"

void displayGrid(string display);
string getCityDisplay(int track_x, int track_y);
string getCPIndexDisplay(int track_x, int track_y, CloudPressureType * cloudPressureArrayPtr);
string getCPLMHDisplay(int track_x, int track_y, CloudPressureType * cloudPressureArrayPtr);
string getCPDisplayByID (int track_x, int track_y, int city_id, CloudPressureType * cloudPressureArrayPtr);
void displayGridByCity(string);

#endif