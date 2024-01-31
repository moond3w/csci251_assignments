#ifndef ASSN2_H
#define ASSN2_H

#include <iostream>
#include <string>
#include "twoDShapes.h"

using namespace std;

int inputSensorData(string shapeName, string shapeType, int counter);

void computeAllArea(int counter);

string displayPointsOnShape(ShapeTwoD* myShape);
string displayPointsInShape(ShapeTwoD* myShape);
void displayShapeArr(int counter);

void displaySubMenu();
void processSubMenu(int counter);
inline bool orderByAreaAscend(ShapeTwoD* lhs, ShapeTwoD* rhs);
inline bool orderByAreaDescend(ShapeTwoD* lhs, ShapeTwoD* rhs);
inline bool orderBySThenArea(ShapeTwoD* lhs, ShapeTwoD* rhs);
void sortByAreaAscend();
void sortByAreaDescend();
void sortBySpecThenArea();

void displayMenu();
void returnToMenu();

#endif