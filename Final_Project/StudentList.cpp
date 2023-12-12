/*
	Lee, Jiseob

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"

#include <iostream>
#include <iomanip>

using namespace std;

void StudentList::addStudent(const Student& newStudent)
{
	Node* newNode = new Node(newStudent, nullptr);
	if (count == 0)
	{
		first = newNode;
		last = newNode;
	}
	else
	{
		last->setNext(newNode);
		last = newNode;
	}
	++count;
}

int StudentList::getNoOfStudents() const
{
	return count;
}

void StudentList::printStudentByID(int idNumber, 
	double tuitionRate) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr && !found)
	{
		if (current->getStudent().getID() == idNumber)
		{
			current->getStudent().printStudentInfo(tuitionRate);
			found = !found;
		}
		current = current->getNext();
	}

	if (!found)
	{
		cout << "No students with ID " << idNumber 
			<< " found in the list." << endl << endl;
	}
}

void StudentList::printStudentByName(const string& lastName) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr)
	{
		if (current->getStudent().getLastName() == lastName)
		{
			found = true;
			current->getStudent().printStudent();
		}

		current = current->getNext();
	}

	if (!found)
	{
		cout << "No student with last name " << lastName 
			<< " is on the list." << endl << endl;
	}
}

void StudentList::printStudentsByCourse(const std::string& coursePrefix, 
	int courseNumber) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr)
	{
		if (current->getStudent().isCourseCompleted(coursePrefix, 
			courseNumber))
		{
			found = true;
			current->getStudent().printStudent();
		}

		current = current->getNext();
	}

	if (!found)
	{
		cout << "No students enrolled in " << coursePrefix 
			<< " " << courseNumber << endl << endl;
	}
}

void StudentList::printAllStudents(double tuitionRate)const
{
	Node* current = first;

	while (current != nullptr)
	{
		current->getStudent().printStudentInfo(tuitionRate);

		current = current->getNext();
	}
}

void StudentList::clearStudentList()
{
	Node* current = first;
	Node* nextNode = nullptr;

	while (current != nullptr)
	{
		nextNode = current->getNext();
		delete current;
		current = nextNode;
	}

	first = nullptr;
	last = nullptr;
	count = 0;
}

StudentList::~StudentList()
{
	if (count > 0)
	{
		clearStudentList();
	}
	
}

void StudentList::printStudentsToFile(ostream& outputFile, 
	double tuitionRate) const
{
	Node* current = first;

	while (current != nullptr)
	{
		const Student& currentStudent = current->getStudent();

		outputFile << "Student Name: " << currentStudent.getLastName()
			<< ", " << currentStudent.getFirstName() << endl;
		outputFile << "Student ID: " << currentStudent.getID() << endl;
		outputFile << "Number of courses completed: " 
			<< currentStudent.getNumberOfCourses() << endl << endl;
		outputFile << "CourseNo  Units  Grade" << endl;

		const multimap<Course, char>& coursesCompleted = currentStudent.getCoursesCompleted();

		for (const auto& iter : coursesCompleted)
		{
			const Course& course = iter.first;

			outputFile << setw(6) << left << course.getCoursePrefix() << setw(6) << left
				<< course.getCourseNumber() << setw(7) << left
				<< course.getCourseUnits() << iter.second << endl;
		}

		outputFile << endl << "Total number of credit hours: " 
			<< currentStudent.getUnitsCompleted() << endl;

		if (currentStudent.isTuitionPaid())
			outputFile << "Current Term GPA: " << setprecision(2) << fixed 
			<< currentStudent.calculateGPA() << endl << endl;
		else
		{
			double tuitionCost = currentStudent.billingAmount(tuitionRate);
			outputFile << "*** Grades are being held for not paying the tuition. ***\n";
			outputFile << "Amount Due: $" << setprecision(2) << fixed 
				<< tuitionCost << endl << endl;
		}

		outputFile << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" 
			<< endl << endl;
		current = current->getNext();
	}
}

void StudentList::printStudentsOnHold(double tuitionRate) const
{
	Node* current = first;
	bool found = false;
	
	while (current != nullptr)
	{
		const Student& currentStudent = current->getStudent();
		if (!currentStudent.isTuitionPaid())
		{
			cout << currentStudent.getID() << " - "
				<< currentStudent.getFirstName() << ", "
				<< currentStudent.getLastName() << endl
				<< "      " << "Amount Due: "
				<< "$" << setprecision(2) << fixed
				<< currentStudent.getNumberOfCourses() * tuitionRate << endl << endl;
		}

		current = current->getNext();
	}

	if (!found)
	{
		cout << "There are no students on hold." << endl << endl;
	}
}

// Project Part D Additional Selection (3)
void StudentList::changeCourseNumber
(const string& coursePrefix, int courseNumber, int newNumber)
{
    Node* current = first;
    while (current != nullptr)
    {
		multimap<Course, char> tempCourses;

		Student currentStudent = current->getStudent();
		multimap<Course, char> currentCourses = currentStudent.getCoursesCompleted();
		auto iter = currentCourses.begin();
		bool found = false;
		while (iter != currentCourses.end())
		{
			if (iter->first.getCoursePrefix() == coursePrefix &&
				iter->first.getCourseNumber() == courseNumber)
			{
				Course newCourse;
				newCourse.setCourseInfo(coursePrefix, newNumber, 
					iter->first.getCourseUnits());
				tempCourses.insert(make_pair(newCourse, iter->second));
			}
			else
			{
				tempCourses.insert(make_pair(iter->first, iter->second));
			}
			++iter;
		}
		
		//Updating the courses
		Student newStudent;
		newStudent.setStudentInfo(
			currentStudent.getID(), currentStudent.getFirstName(),
			currentStudent.getLastName(), currentStudent.isTuitionPaid(), 
			tempCourses);

		current->setStudent(newStudent);
		current = current->getNext();
    }
}