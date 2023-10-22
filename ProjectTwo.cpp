//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Matthew R. Leclerc
// Version     : 1.0
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

// Define a Course structure to store course information.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Function to load data from the file into the data structure. (Big Thanks to StackOverflow to understand the loading bool setup)
bool loadDataStructure(map<string, Course>& courseMap, const string& fileName) {
    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Error: Unable to open file " << fileName << endl;
        return false;
    }

    string line;
    while (getline(inputFile, line)) {
        // Parse the line and extract course information.
        stringstream ss(line);
        string courseNumber, courseTitle, prerequisite;
        getline(ss, courseNumber, ',');
        getline(ss, courseTitle, ',');

        Course course;
        course.courseNumber = courseNumber;
        course.courseTitle = courseTitle;

        while (getline(ss, prerequisite, ',')) {
            course.prerequisites.push_back(prerequisite);
        }

        courseMap[courseNumber] = course; // Add course information to the data structure.
    }

    inputFile.close();
    return true;
}

// Function to print an alphanumeric list of courses in the Computer Science department.
void printCourseList(const map<string, Course>& courseMap) {
    cout << "Here is a list of Computer Science courses:" << endl;
    for (const auto& pair : courseMap) {
        const Course& course = pair.second;
        // Check if the course is in the Computer Science department (adjust as needed).
        // If it is, print the course information.
        cout << course.courseNumber << ", " << course.courseTitle << endl;
    }
}

// Function to print course information by course number.
void printCourseInfo(const map<string, Course>& courseMap) {
    string courseNumber;
    cout << "Enter the course number: ";
    cin >> courseNumber;

    // Check if the course exists in the data structure.
    if (courseMap.find(courseNumber) != courseMap.end()) {
        const Course& course = courseMap.at(courseNumber);
        cout << course.courseNumber << ", " << course.courseTitle << endl;
        cout << "Prerequisites:";

        // Check if there are prerequisites for the course.
        if (course.prerequisites.empty()) {
            cout << " None";
        }
        else {
            for (const string& prereq : course.prerequisites) {
                cout << " " << prereq;
            }
        }
        cout << endl;
    }
    else {
        cerr << "Error: Course not found." << endl;
    }
}

int main() {
    map<string, Course> courseMap; // Data structure to store courses.

    cout << "Welcome to the course planner." << endl;
    int choice;
    string defaultFileName = "Course_Information.txt"; // Default file name.

    do {
        cout << "1. Load Data Structure." << endl;
        cout << "2. Print Course List." << endl;
        cout << "3. Print Course." << endl;
        cout << "9. Exit" << endl;
        cout << "What would you like to do? ";

        // Validate user input to ensure it's an integer.
        if (!(cin >> choice)) {
            cin.clear(); // Clear error state.
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input.
            cout << "Invalid input. Please enter a valid option." << endl;
            continue; // Go back to the beginning of the loop.
        }

        // Switch statement to handle user menu choice.
        switch (choice) {
            // Case 1: Load Data Structure.
        case 1: {
            // Attempt to load course data from a file into the data structure.
            bool success = loadDataStructure(courseMap, defaultFileName);
            if (success) {
                cout << "Data loaded successfully from " << defaultFileName << "." << endl;
            }
            else {
                cerr << "Error: Failed to load data from " << defaultFileName << "." << endl;
            }
            break;
        }
              // Case 2: Print Course List.
        case 2:
            // Display an alphanumeric list of Computer Science courses.
            printCourseList(courseMap);
            break;
            // Case 3: Print Course Information.
        case 3:
            // Prompt the user for a course number and display its information.
            printCourseInfo(courseMap);
            break;
            // Case 9: Exit the program.
        case 9:
            // Display a thank you message and exit the program.
            cout << "Thank you for using the course planner!" << endl;
            break;
            // Default case: Handle invalid input.
        default:
            // Display an error message for invalid menu choices.
            cout << choice << " is not a valid option." << endl;
            break;
        }
    } while (choice != 9);

    return 0;
}
