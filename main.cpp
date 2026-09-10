// Student Management System — main entry point

#include <iostream>
#include <vector>
#include <iomanip>

#include "Student.h"
#include "StudentManager.h"
#include "FileHandler.h"
#include "Utils.h"

using namespace std;

// Prints the menu.
static void printMenu() {
    cout << "\n==============================\n";
    cout << "   Student Management System  \n";
    cout << "==============================\n";
    cout << " 1. Add Student\n";
    cout << " 2. Display All Students\n";
    cout << " 3. Search Student\n";
    cout << " 4. Delete Student\n";
    cout << " 5. Sort by Name (A-Z)\n";
    cout << " 6. Sort by Marks (High-Low)\n";
    cout << " 7. Edit Student\n";
    cout << " 8. Student Count\n";
    cout << " 9. Update Marks\n";
    cout << "10. Exit\n";
    cout << "------------------------------\n";
    cout << "Enter Choice: ";
}

// ── Main ─────────────────────────────────────────────────────────────────────

int main() {
    vector<Student> students;
    loadFromFile(students);

    int choice = 0;

    do {
        printMenu();

        string choiceStr;
        if (!getline(cin, choiceStr)) {
            clearCin();
            continue;
        }
        trimString(choiceStr);
        
        if (choiceStr.empty() || choiceStr.length() > 2) {
            cout << "Error: Please enter a number between 1 and 10.\n";
            continue;
        }
        
        bool validChoice = true;
        for (char c : choiceStr) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                validChoice = false;
                break;
            }
        }
        
        if (!validChoice) {
            cout << "Error: Please enter a number between 1 and 10.\n";
            continue;
        }
        
        try {
            choice = stoi(choiceStr);
        } catch (...) {
            cout << "Error: Please enter a number between 1 and 10.\n";
            continue;
        }

        switch (choice) {

            // ── 1. Add Student ──────────────────────────────────────────────
            case 1:
                addStudent(students);
                saveToFile(students);   // auto-save after mutation
                break;

            // ── 2. Display All Students ─────────────────────────────────────
            case 2:
                displayStudents(students);
                break;

            // ── 3. Search Student ───────────────────────────────────────────
            case 3: {
                int roll = 0;
                if (!promptValidRoll(roll, "Enter Roll Number: ")) break;

                const Student* s = searchStudent(students, roll);
                if (s) {
                    cout << "Student found:\n";
                    displayStudent(*s);
                } else {
                    cout << "Error: No student with roll number " << roll << " found.\n";
                }
                break;
            }

            // ── 4. Delete Student ───────────────────────────────────────────
            case 4: {
                int roll = 0;
                if (!promptValidRoll(roll, "Enter Roll Number to Delete: ")) break;

                deleteStudent(students, roll);
                saveToFile(students);   // auto-save after mutation
                break;
            }

            // ── 5. Sort by Name ─────────────────────────────────────────────
            case 5:
                if (students.empty()) {
                    cout << "No students to sort.\n";
                    break;
                }
                sortByNameAscending(students);
                cout << "Sorted by name (A-Z).\n";
                break;

            // ── 6. Sort by Marks ─────────────────────────────────────────────
            case 6:
                if (students.empty()) {
                    cout << "No students to sort.\n";
                    break;
                }
                sortByMarksDescending(students);
                cout << "Sorted by marks (highest first).\n";
                break;

            // ── 7. Edit Student ──────────────────────────────────────────────
            case 7: {
                int roll = 0;
                if (!promptValidRoll(roll, "Enter Roll Number to Edit: ")) break;

                Student* s = searchStudent(students, roll);
                if (!s) {
                    cout << "Error: No student with roll number " << roll << " found.\n";
                    break;
                }

                cout << "Current record:\n";
                displayStudent(*s);
                cout << "\nEnter new details:\n";

                // Name
                string new_name;
                if (!promptValidName(new_name, "Enter Name: ")) break;

                // Marks
                float new_marks = 0.0f;
                if (!promptValidMarks(new_marks, "Enter Marks (0 - 100): ")) break;

                // Roll Number
                int new_roll = 0;
                while (true) {
                    if (!promptValidRoll(new_roll, "Enter Roll Number (1 - 9999): ")) break;

                    Student* conflict = searchStudent(students, new_roll);
                    if (conflict && conflict != s) {
                        cout << "Error: Roll number " << new_roll << " is already taken. Please enter a different roll number.\n";
                        continue;
                    }
                    break;
                }
                if (cin.eof()) break;

                s->editStudent(new_name, new_marks, new_roll);
                cout << "Student updated successfully.\n";
                saveToFile(students);   // auto-save after mutation
                break;
            }

            // ── 8. Student Count ─────────────────────────────────────────────
            case 8:
                cout << "Total students: " << students.size() << "\n";
                break;

            // ── 9. Update Marks ───────────────────────────────────────────────
            case 9: {
                int roll = 0;
                if (!promptValidRoll(roll, "Enter Roll Number: ")) break;

                Student* s = searchStudent(students, roll);
                if (!s) {
                    cout << "Error: No student with roll number " << roll << " found.\n";
                    break;
                }

                cout << "Current marks: " << fixed << setprecision(2) << s->getMarks() << "\n";
                float new_marks = 0.0f;
                if (!promptValidMarks(new_marks, "Enter new Marks (0 - 100): ")) break;

                s->updateMarks(new_marks);
                cout << "Marks updated successfully.\n";
                saveToFile(students);   // auto-save after mutation
                break;
            }

            // ── 10. Exit ──────────────────────────────────────────────────────
            case 10:
                saveToFile(students);
                cout << "Data saved. Goodbye!\n";
                break;

            default:
                cout << "Error: Choice must be between 1 and 10.\n";
                break;
        }

    } while (choice != 10);

    return 0;
}