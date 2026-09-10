// Contains all functions that operate on the student list

#include "StudentManager.h"
#include "Utils.h"

#include <iostream>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

// ── Search ──────────────────────────────────────────────────────────────────

Student* searchStudent(vector<Student>& students, int roll_number) {
    for (Student& s : students) {
        if (s.getRollNumber() == roll_number)
            return &s;
    }
    return nullptr;
}

const Student* searchStudent(const vector<Student>& students, int roll_number) {
    for (const Student& s : students) {
        if (s.getRollNumber() == roll_number)
            return &s;
    }
    return nullptr;
}

// ── Comparators ─────────────────────────────────────────────────────────────

bool compareByName(const Student& a, const Student& b) {
    return a.getName() < b.getName();
}

bool compareByMarks(const Student& a, const Student& b) {
    // Primary: marks descending. Tie-break: roll number ascending.
    if (a.getMarks() != b.getMarks())
        return a.getMarks() > b.getMarks();
    return a.getRollNumber() < b.getRollNumber();
}

// ── Validation ───────────────────────────────────────────────────────────────

bool isValidMarks(float marks) {
    return (marks >= 0.0f && marks <= 100.0f);
}

bool isRollNumberUnique(const vector<Student>& students, int roll) {
    return searchStudent(students, roll) == nullptr;
}

// ── Sort ─────────────────────────────────────────────────────────────────────

void sortByNameAscending(vector<Student>& students) {
    sort(students.begin(), students.end(), compareByName);
}

void sortByMarksDescending(vector<Student>& students) {
    sort(students.begin(), students.end(), compareByMarks);
}

// ── Display ──────────────────────────────────────────────────────────────────

void displayStudent(const Student& s) {
    cout << "\n-----------------------------\n";
    cout << "Name        : " << s.getName()      << "\n";
    cout << "Roll Number : " << s.getRollNumber() << "\n";
    cout << "Marks       : " << fixed << setprecision(2) << s.getMarks() << "\n";
}

void displayStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "\nNo students found.\n";
        return;
    }
    cout << "\nStudent Records (" << students.size() << " total):\n";
    for (const Student& s : students)
        displayStudent(s);
}

// ── Add Student ──────────────────────────────────────────────────────────────

void addStudent(vector<Student>& students) {
    string name;
    float  marks      = 0.0f;
    int    roll       = 0;

    // --- Name ---
    if (!promptValidName(name, "Enter Name: "))
        return;

    // --- Marks ---
    if (!promptValidMarks(marks, "Enter Marks (0 - 100): "))
        return;

    // --- Roll Number ---
    while (true) {
        if (!promptValidRoll(roll, "Enter Roll Number (1 - 9999): "))
            return;

        if (!isRollNumberUnique(students, roll)) {
            cout << "Error: Roll number " << roll << " already exists. Please enter a different roll number.\n";
            continue;
        }
        break;
    }

    students.emplace_back(name, marks, roll);
    cout << "Student added successfully.\n";
}

// ── Delete Student ───────────────────────────────────────────────────────────

void deleteStudent(vector<Student>& students, int roll_num) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getRollNumber() == roll_num) {
            students.erase(it);
            cout << "Student deleted successfully.\n";
            return;
        }
    }
    cout << "Error: No student with roll number " << roll_num << " found.\n";
}