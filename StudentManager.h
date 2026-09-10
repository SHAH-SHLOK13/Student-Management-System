// Contains declarations for all functions that operate on students

#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <string>
#include <vector>
#include "Student.h"

// Search
Student*       searchStudent(std::vector<Student>& students, int roll_number);
const Student* searchStudent(const std::vector<Student>& students, int roll_number);

// Comparators (used by sort)
bool compareByName(const Student& a, const Student& b);
bool compareByMarks(const Student& a, const Student& b);

// Validation helpers
bool isValidMarks(float marks);
bool isRollNumberUnique(const std::vector<Student>& students, int roll);

// Sort
void sortByNameAscending(std::vector<Student>& students);
void sortByMarksDescending(std::vector<Student>& students);

// Display
void displayStudent(const Student& s);
void displayStudents(const std::vector<Student>& students);

// Mutate
void addStudent(std::vector<Student>& students);
void deleteStudent(std::vector<Student>& students, int roll_num);

#endif // STUDENTMANAGER_H