/*
	Lee, Jiseob

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "Student.h"

#include <iostream>
#include <map>
#include <iomanip>

using namespace std;

void Student::setStudent(const Student& otherStudent)
{
	studentID = otherStudent.studentID;
	firstName = otherStudent.firstName;
	lastName = otherStudent.lastName;
	numberOfCourses = otherStudent.numberOfCourses;
	tuitionWasPaid = otherStudent.tuitionWasPaid;
	coursesCompleted = otherStudent.coursesCompleted;
}

void Student::setStudentInfo(int newStudentID, 
	const string& newFirstName, 
	const string& newLastName, bool newTuitionWasPaid, 
	const multimap<Course, char>& newCoursesCompleted)
{
	studentID = newStudentID;
	firstName = newFirstName;
	lastName = newLastName;
	numberOfCourses = static_cast<int>(newCoursesCompleted.size());
	tuitionWasPaid = newTuitionWasPaid;
	coursesCompleted = newCoursesCompleted;
}

int Student::getID() const
{
	return studentID;
}

const string& Student::getFirstName() const
{
	return firstName;
}

const string& Student::getLastName() const
{
	return lastName;
}

void Student::getName(string& newFirstName, 
	string& newLastName) const
{
	newFirstName = firstName;
	newLastName = lastName;
}

int Student::getNumberOfCourses() const
{
	return numberOfCourses;
}

int Student::getUnitsCompleted() const
{
	int totalUnits = 0;

	for (const auto& iter : coursesCompleted)
	{
		totalUnits += iter.first.getCourseUnits();
	}

	return totalUnits;
}

multimap<Course, char> Student::getCoursesCompleted() const
{
	return coursesCompleted;
}

bool Student::isTuitionPaid() const
{
	return tuitionWasPaid;
}

bool Student::isCourseCompleted(const string& coursePrefix, 
	int courseNumber) const
{
	if (numberOfCourses == 0) return false;
	else
	{
		auto iter = coursesCompleted.begin();

		while (iter != coursesCompleted.end())
		{
			const Course& course = iter->first;
			if (course.getCoursePrefix() == coursePrefix && 
				course.getCourseNumber() == courseNumber)
			{
				return true;
			}
			++iter;
		}

		return false;
	}
}

double Student::calculateGPA() const
{
	int totalUnits = 0;
	double totalPoints = 0.0;

	for (auto& iter : coursesCompleted)
	{
		double letterGrade = 0.0;
		if (tolower(iter.second) == 'a') letterGrade = 4.0;
		else if (tolower(iter.second) == 'b') letterGrade = 3.0;
		else if (tolower(iter.second) == 'c') letterGrade = 2.0;
		else if (tolower(iter.second) == 'd') letterGrade = 1.0;

		totalUnits += iter.first.getCourseUnits();
		totalPoints += iter.first.getCourseUnits() * letterGrade;
	}

	return totalUnits != 0 ? totalPoints / totalUnits : 0.0;
}

double Student::billingAmount(double tuitionRate) const
{
	return tuitionRate * numberOfCourses;
}

void Student::printStudent() const
{
	cout << studentID << " - " << lastName 
		<< ", " << firstName << endl;
}

void Student::printStudentInfo(double tuitionRate) const
{
	cout << "Student Name: " << lastName << ", " 
		<< firstName << endl;
	cout << "Student ID: " << studentID << endl;
	cout << "Number of courses completed: " 
		<< numberOfCourses << endl << endl;
	cout << "CourseNo  Units  Grade" << endl;

	for (auto& iter : coursesCompleted)
	{
		cout << setw(6) << left << iter.first.getCoursePrefix() 
			<< setw(6) << left 
			<< iter.first.getCourseNumber() << setw(7) << left 
			<< iter.first.getCourseUnits() << iter.second << endl;
	}

	cout << endl << "Total number of credit hours: " 
		<< getUnitsCompleted() << endl;
	if (tuitionWasPaid)
		cout << "Current Term GPA: " << setprecision(2) << fixed 
		<< calculateGPA() << endl << endl;
	else
	{
		double tuitionCost = billingAmount(tuitionRate);
		cout << "*** Grades are being held for not paying the tuition. ***\n";
		cout << "Amount Due: $" << setprecision(2) << fixed 
			<< tuitionCost << endl << endl;
	}
	cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" 
		<< endl << endl;
}