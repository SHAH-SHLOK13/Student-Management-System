// Shared input utilities for the Student Management System
// Contains: clearCin, trimString, isValidName, readRoll, readMarks

#ifndef UTILS_H
#define UTILS_H

#include <string>

// Clears cin error state and discards buffered input up to the next newline.
void clearCin();

// Removes leading and trailing whitespace (spaces and tabs) from s in-place.
void trimString(std::string& s);

// Replaces tabs with spaces and collapses multiple consecutive spaces into a single space.
void normalizeSpaces(std::string& s);

// Returns true if s, after trimming, is non-empty, <= 50 chars,
// and contains at least one alphabetic character.
bool isValidName(const std::string& s, bool verbose = true);

// Reads a roll number from stdin into 'roll'.
// Returns true on success; false and prints an error if input is non-numeric
// or outside the range [1, 9999].
bool readRoll(int& roll);

// Reads a marks value from stdin into 'marks'.
// Returns true on success; false and prints an error if input is non-numeric,
// non-finite, or outside the range [0.0, 100.0].
bool readMarks(float& marks);

// Prompts the user and repeatedly loops until a valid name is entered or EOF is encountered.
bool promptValidName(std::string& name, const std::string& promptText = "Enter Name: ");

// Prompts the user and repeatedly loops until a valid marks value is entered or EOF is encountered.
bool promptValidMarks(float& marks, const std::string& promptText = "Enter Marks (0 - 100): ");

// Prompts the user and repeatedly loops until a valid roll number is entered or EOF is encountered.
bool promptValidRoll(int& roll, const std::string& promptText = "Enter Roll Number (1 - 9999): ");

#endif // UTILS_H
