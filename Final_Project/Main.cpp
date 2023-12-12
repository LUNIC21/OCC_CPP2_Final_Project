/*
	Lee, Jiseob

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"
#include "InputHandler.h"
#include "OutputHandler.h"

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

const string FILE_NAME = "student_data.txt";

void displayMenu();
void processChoice(StudentList& theList, double tuitionRate);

int main()
{
	StudentList theList;
	double tuitionRate = 350.0;

	readStudentData(FILE_NAME, theList, tuitionRate);
	processChoice(theList, tuitionRate);
}

void displayMenu()
{
	// Display Menu
	cout << "*** MAIN MENU ***" << endl << endl;
	cout << "Select one of the following:" << endl << endl;
	cout << "    1: Print all students" << endl;
	cout << "    2: Print student information" << endl;
	cout << "    3: Search student by last name" << endl;
	cout << "    4: Print students by course" << endl;
	cout << "    5: Print students on hold" << endl;
	cout << "    6: Print students to file" << endl;
	cout << "    7: Change the course number" << endl;
	cout << "    8: To exit" << endl << endl;
}

void processChoice(StudentList& theList, double tuitionRate)
{
	int choice = 0;

	while (choice != 8)
	{
		displayMenu();
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1: // Print all Students
		{
			theList.printAllStudents(tuitionRate);
			system("pause");
			break;
		}
		case 2: // Print student information
		{
			int studentID = 0;
			cout << "Enter the student ID: ";
			cin >> studentID;

			if (cin.fail())
			{
				cout << "Invalid entry.";
				system("pause");
				break;
			}
			theList.printStudentByID(studentID, tuitionRate);
			system("pause");
			break;
		}
		case 3: // Search student by last name
		{
			string studentName;
			cout << "Enter the student name: ";
			cin >> studentName;

			if (cin.fail())
			{
				cout << "Invalid entry.";
				system("pause");
				break;
			}
			theList.printStudentByName(studentName);
			system("pause");
			break;
		}
		case 4: // Print students by course
		{
			string coursePrefix;
			int courseNumber = 0;

			cout << "Enter the course prefix: ";
			cin >> coursePrefix;
			cout << "Enter the course number: ";
			cin >> courseNumber;

			if (cin.fail())
			{
				cout << "Invalid entry.";
				system("pause");
				break;
			}
			theList.printStudentsByCourse(coursePrefix, courseNumber);
			system("pause");
			break;
		}
		case 5: // Print students on hold;
		{
			theList.printStudentsOnHold(tuitionRate);
			system("pause");
			break;
		}
		case 6: // Print students to file;
		{
			string fileName;

			cout << "Enter a name for a new file to write on " <<
				"(include extension.txt) :\n";
			cin >> fileName;

			if (fileName.empty())
			{
				cerr << "Empty name" << endl;
			}
			else
			{
				if (fileName.length() < 4 ||
					fileName.substr(fileName.length() - 4) != ".txt")
				{
					fileName += ".txt";
				}
				ofstream outputFile(fileName);
				theList.printStudentsToFile(outputFile, tuitionRate);
			}
			system("pause");
			break;
		}
		case 7:
		{
			string coursePrefix;
			int courseNumber = 0;
			int newCourseNumber = 0;

			cout << "Enter the course prefix: ";
			cin >> coursePrefix;

			if (cin.fail())
			{
				cout << "Invalid entry. ";
				system("pause");
				break;
			}

			cout << "Enter the course number: ";
			cin >> courseNumber;

			if (cin.fail())
			{
				cout << "Invalid entry. ";
				system("pause");
				break;
			}

			cout << "Enter a new course number: ";
			cin >> newCourseNumber;

			if (cin.fail())
			{
				cout << "Invalid entry.";
				system("pause");
				break;
			}

			theList.changeCourseNumber(coursePrefix, courseNumber, newCourseNumber);
			cout << "\nUpdated student list:\n";
			theList.printStudentsByCourse(coursePrefix, newCourseNumber);
			cout << "\n";
			system("pause");

			break;
		}
		case 8: // exit
		{
			cout << "\nThank you for using the OCC Gradebook. Good-bye!\n\n";
			system("pause");
			break;
		}
		default:
		{
			cout << "Sorry. That is not a selection." << endl;
			system("pause");
			break;
		}
		}
	}
}