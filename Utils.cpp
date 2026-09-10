// Shared input utilities for the Student Management System

#include "Utils.h"

#include <iostream>
#include <limits>
#include <cmath>
#include <cctype>
#include <algorithm>

using namespace std;

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void trimString(string& s) {
    // Trim leading whitespace
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) {
        s.clear();
        return;
    }
    // Trim trailing whitespace
    size_t end = s.find_last_not_of(" \t\r\n");
    s = s.substr(start, end - start + 1);
}

void normalizeSpaces(string& s) {
    string out;
    bool inSpace = false;
    for (char c : s) {
        if (isspace(static_cast<unsigned char>(c))) {
            if (!inSpace) {
                out += ' ';
                inSpace = true;
            }
        } else {
            out += c;
            inSpace = false;
        }
    }
    s = out;
    trimString(s);
}

bool isValidName(const string& s, bool verbose) {
    if (s.length() < 2 || s.length() > 50) {
        if (verbose) cout << "Error: Name length must be between 2 and 50 characters.\n";
        return false;
    }
    
    int alphaCount = 0;
    char prev = '\0';
    
    for (char c : s) {
        if (isalpha(static_cast<unsigned char>(c))) {
            alphaCount++;
        } else if (c == ' ' || c == '-' || c == '\'' || c == '.') {
            // Consecutive punctuation/spaces not allowed
            if (prev == ' ' || prev == '-' || prev == '\'' || prev == '.') {
                if (verbose) cout << "Error: Name cannot contain consecutive spaces or punctuation.\n";
                return false;
            }
        } else {
            if (verbose) cout << "Error: Name contains invalid character '" << c << "'. Only letters, spaces, hyphens, apostrophes, and periods are allowed.\n";
            return false;
        }
        prev = c;
    }
    
    if (alphaCount < 2) {
        if (verbose) cout << "Error: Name must contain at least 2 letters.\n";
        return false;
    }
    
    // Check boundaries
    char first = s.front();
    char last = s.back();
    if (first == ' ' || first == '-' || first == '\'' || first == '.' ||
        last == ' ' || last == '-' || last == '\'' || last == '.') {
        if (verbose) cout << "Error: Name cannot start or end with a space or punctuation.\n";
        return false;
    }
    
    return true;
}

bool readRoll(int& roll) {
    string line;
    if (!getline(cin, line)) {
        clearCin();
        return false;
    }
    trimString(line);
    
    if (line.empty() || line.length() > 4) {
        cout << "Error: Please enter a valid integer between 1 and 9999.\n";
        return false;
    }
    
    for (char c : line) {
        if (!isdigit(static_cast<unsigned char>(c))) {
            cout << "Error: Roll number must contain only digits.\n";
            return false;
        }
    }
    
    try {
        roll = stoi(line);
    } catch (...) {
        cout << "Error: Invalid roll number.\n";
        return false;
    }
    
    if (roll < 1 || roll > 9999) {
        cout << "Error: Roll number must be between 1 and 9999.\n";
        return false;
    }
    return true;
}

bool readMarks(float& marks) {
    string line;
    if (!getline(cin, line)) {
        clearCin();
        return false;
    }
    trimString(line);
    
    if (line.empty()) {
        cout << "Error: Please enter a valid number.\n";
        return false;
    }
    
    int dotCount = 0;
    for (char c : line) {
        if (c == '.') {
            dotCount++;
            if (dotCount > 1) {
                cout << "Error: Invalid decimal format.\n";
                return false;
            }
        } else if (!isdigit(static_cast<unsigned char>(c))) {
            cout << "Error: Marks must contain only digits and at most one decimal point.\n";
            return false;
        }
    }
    
    try {
        marks = stof(line);
    } catch (...) {
        cout << "Error: Invalid marks format.\n";
        return false;
    }
    
    if (!isfinite(marks)) {
        cout << "Error: Marks must be a finite number.\n";
        return false;
    }
    if (marks < 0.0f || marks > 100.0f) {
        cout << "Error: Marks must be between 0 and 100.\n";
        return false;
    }
    return true;
}

bool promptValidName(string& name, const string& promptText) {
    while (true) {
        cout << promptText;
        if (!getline(cin, name)) {
            if (cin.eof()) return false;
            clearCin();
            continue;
        }
        normalizeSpaces(name);
        if (isValidName(name, true)) {
            return true;
        }
        if (cin.eof()) return false;
    }
}

bool promptValidMarks(float& marks, const string& promptText) {
    while (true) {
        cout << promptText;
        if (readMarks(marks)) {
            return true;
        }
        if (cin.eof()) return false;
    }
}

bool promptValidRoll(int& roll, const string& promptText) {
    while (true) {
        cout << promptText;
        if (readRoll(roll)) {
            return true;
        }
        if (cin.eof()) return false;
    }
}
