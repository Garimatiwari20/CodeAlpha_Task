#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

struct Course {
    string name;
    double grade;
    int creditHours;
};

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    vector<Course> courses(numCourses);
    double totalGradePoints = 0;
    int totalCredits = 0;

    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << ":\n";
        cout << "Enter course name: ";
        cin.ignore();  // to handle newline from previous input
        getline(cin, courses[i].name);
        cout << "Enter grade (on 10-point scale): ";
        cin >> courses[i].grade;
        cout << "Enter credit hours: ";
        cin >> courses[i].creditHours;

        totalGradePoints += courses[i].grade * courses[i].creditHours;
        totalCredits += courses[i].creditHours;
    }

    double cgpa = (totalCredits > 0) ? (totalGradePoints / totalCredits) : 0;

    cout << "\n--------- Course Grades ---------\n";
    cout << left << setw(20) << "Course Name" 
         << setw(10) << "Grade" 
         << setw(15) << "Credit Hours" << endl;

    for (const auto& course : courses) {
        cout << left << setw(20) << course.name 
             << setw(10) << course.grade 
             << setw(15) << course.creditHours << endl;
    }

    cout << "\nTotal Credits: " << totalCredits;
    cout << "\nTotal Grade Points: " << totalGradePoints;
    cout << fixed << setprecision(2);
    cout << "\nFinal CGPA: " << cgpa << endl;

    return 0;
}
