// Handles reading and writing student records to/from students.txt

#include "FileHandler.h"
#include "Utils.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

static const char* FILE_NAME = "students.txt";

void saveToFile(const vector<Student>& students) {
    ofstream file(FILE_NAME);

    if (!file.is_open()) {
        cout << "Error: Could not open \"" << FILE_NAME << "\" for writing.\n";
        return;
    }

    for (const Student& s : students) {
        file << s.getName()      << ","
             << s.getRollNumber() << ","
             << s.getMarks()      << "\n";
    }

    file.close();
}

void loadFromFile(vector<Student>& students) {
    students.clear();
    ifstream file(FILE_NAME);

    if (!file.is_open()) {
        // File may simply not exist yet on first run — not an error
        return;
    }

    string line;
    int    lineNum   = 0;
    int    skipped   = 0;

    while (getline(file, line)) {
        ++lineNum;

        // Strip Windows CRLF
        if (!line.empty() && line.back() == '\r')
            line.pop_back();

        // Skip blank / whitespace-only lines
        if (line.find_first_not_of(" \t") == string::npos)
            continue;

        stringstream ss(line);
        string name, rollStr, marksStr;

        if (!(getline(ss, name, ',') &&
              getline(ss, rollStr, ',') &&
              getline(ss, marksStr))) {
            ++skipped;
            continue;
        }

        // Strip trailing CR from last field (extra safety)
        if (!marksStr.empty() && marksStr.back() == '\r')
            marksStr.pop_back();

        // Trim/Normalize fields
        normalizeSpaces(name);
        trimString(rollStr);
        trimString(marksStr);

        try {
            int   roll  = stoi(rollStr);
            float marks = stof(marksStr);

            // Validate ranges — reject corrupt data silently
            if (roll  < 1 || roll > 9999)            { ++skipped; continue; }
            if (!isfinite(marks))                     { ++skipped; continue; }
            if (marks < 0.0f || marks > 100.0f)       { ++skipped; continue; }
            if (!isValidName(name, false))            { ++skipped; continue; }

            students.emplace_back(name, marks, roll);

        } catch (const exception&) {
            ++skipped;
        }
    }

    file.close();

    if (skipped > 0)
        cout << "Warning: " << skipped << " corrupt record(s) were skipped while loading.\n";
}