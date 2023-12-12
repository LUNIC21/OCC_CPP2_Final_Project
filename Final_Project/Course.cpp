/*
    Lee, Jiseob

    Project: Grade Report
    CS A250
    Fall 2023
*/

#include "Course.h"
#include "Student.h"

#include <iostream>
#include <map>

using namespace std;

void Course::setCourseInfo(const string& newCoursePrefix, 
    int newCourseNumber, int newCourseUnits)
{
	coursePrefix = newCoursePrefix;
	courseNumber = newCourseNumber;
	courseUnits = newCourseUnits;
}

string Course::getCoursePrefix() const
{
	return coursePrefix;
}

int Course::getCourseNumber() const
{
	return courseNumber;
}

int Course::getCourseUnits() const
{
	return courseUnits;
}


bool Course::operator<(const Course& other) const
{
    if (courseUnits < other.courseUnits)
        return true;
    else if (courseUnits > other.courseUnits)
        return false;

    // If courseUnits are equal, compare coursePrefix
    if (coursePrefix < other.coursePrefix)
        return true;
    else if (coursePrefix > other.coursePrefix)
        return false;

    // If coursePrefix is also equal, compare courseNumber
    return courseNumber < other.courseNumber;

}