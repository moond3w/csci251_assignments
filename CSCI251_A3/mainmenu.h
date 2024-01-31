#ifndef MAINMENU_H
#define MAINMENU_H

#include <vector>
#include <string>

using namespace std;

// Functions for processing input file
string verifyInputFileName(string);
void processInputFile();
void processUniqueData();
vector<string> splitString (string, string);

// Functions for menu display
void displayMainMenu();
void displayFilterMenu();
void displaySortCriteriaMenu();
void displaySortOrderMenu();

// Functions for program run
void returnToMenu();
bool isInteger(string);
string verifyInput(string);

// Functions for menu options
// in_array used in selectFilterCriteria()
void selectFilterCriteria();
bool in_array(const string &, const vector<string> &);

void selectSortCriteria();
void selectSortOrder();

// sortData used in viewData and storeData
void viewData();
void storeData();
void sortData(string, string, string);
string verifyOutputFileName(string);


#endif