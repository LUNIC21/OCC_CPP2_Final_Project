/*
	Lee, Jiseob

	Project: Grade Report
	CS A250
	Fall 2023
*/

#ifndef COURSE_H
#define COURSE_H

#include <iostream>

class Course
{
public:
	// Default constructor
	Course() :
		coursePrefix("N/A"), courseNumber(0), courseUnits(0) {};

	void setCourseInfo(const std::string&, int, int);

	std::string getCoursePrefix() const;
	int getCourseNumber() const;
	int getCourseUnits() const;

	bool operator<(const Course&) const;

	~Course() {}

private:
	std::string coursePrefix;
	int courseNumber;
	int courseUnits;
};

#endif