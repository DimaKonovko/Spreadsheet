#include "FileProcessing.h"

#include <windows.h>

using namespace std;

// Implementation
vector< vector<string> > ParseSpreadsheetTxt(const wchar_t* pathToFile)
{
	vector< vector<string> > vector2d;
	vector<string> lines;
	string line;
	ifstream file(pathToFile, ios_base::in);
	
	if (!file.is_open()) { return vector2d; }

	while (getline(file, line)) {
		lines.push_back(line);
	}

	for (int i = 0; i < lines.size(); i++) {
		vector<string> emptyVector;
		vector2d.push_back(emptyVector);

		static int delimiter_pos;
		static string substr;
		while ((delimiter_pos = lines[i].find(";")) != string::npos) {
			substr = lines[i].substr(0, delimiter_pos);
			vector2d[i].push_back(substr);
			lines[i].erase(0, delimiter_pos + 1);
		}
	}

	if (!file.is_open()) { return vector2d; }
	return vector2d;
}
