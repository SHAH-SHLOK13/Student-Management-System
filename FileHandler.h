// Declares file I/O functions for saving and loading student records

#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <vector>
#include "Student.h"

// Saves all student records to students.txt (overwrites existing file).
void saveToFile(const std::vector<Student>& students);

// Loads student records from students.txt into the provided vector.
// Clears the vector first. Skips and warns about corrupt rows.
void loadFromFile(std::vector<Student>& students);

#endif // FILEHANDLER_H