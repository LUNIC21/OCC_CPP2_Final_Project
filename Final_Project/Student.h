/*
	Lee, Jiseob

	Project: Grade Report
	CS A250
	Fall 2023
*/

#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"

#include <iostream>
#include <map>
#include <string>

class Student
{
public:
	// Default constructor
	Student() :studentID(0), firstName("N/A"), lastName("N/A"), 
		numberOfCourses(0), tuitionWasPaid(false) {};

	void setStudent(const Student&);
	void setStudentInfo(int, const std::string&, const std::string&,
		bool, const std::multimap<Course, char>&);

	int getID() const;
	const std::string& getFirstName() const;
	const std::string& getLastName() const;
	void getName(std::string&, std::string&) const;
	int getNumberOfCourses() const;
	int getUnitsCompleted() const;
	std::multimap<Course, char> getCoursesCompleted() const;

	bool isTuitionPaid() const;
	bool isCourseCompleted(const std::string&, int) const;
	double calculateGPA() const;
	double billingAmount(double) const;

	void printStudent() const;
	void printStudentInfo(double) const;

	~Student() {}

private:
	int studentID;
	std::string firstName;
	std::string lastName;
	int numberOfCourses;
	bool tuitionWasPaid;
	std::multimap<Course, char> coursesCompleted;
};

#endif