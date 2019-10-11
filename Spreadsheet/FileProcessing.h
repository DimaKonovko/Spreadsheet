#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector< vector<string> > ParseSpreadsheetTxt(const wchar_t* pathToFile);
