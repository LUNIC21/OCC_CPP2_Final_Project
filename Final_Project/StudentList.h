/*
    Lee, Jiseob

    Project: Grade Report
    CS A250
    Fall 2023
*/

#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "Student.h"

#include <iostream>
#include <map>

class Node
{
public:
    // Overloaded constructor
    Node(Student newData, Node* newNext)
        : student(newData), next(newNext) {}
    // Function getNext returns the address of the next node.
    Node* getNext() const { return next; }
    // Function getData returns the int value stored in 
    // the node.
    Student getStudent() const { return student; }
    // Function setNext overwrites the address stored in 
    // the node with a given address.
    void setNext(Node* newNext)
    {
        next = newNext;
    }
    // Function setData overwrites the int value stored in 
    // the node with a given value.
    void setStudent(Student newData) { student = newData; }
    // Destructor
    ~Node() {}
private:
    // Student object stored in the node.
    Student student;
    // A pointer storing the address of the next node.
    Node* next;
};

class StudentList
{
public:
    // Default Constructor
    StudentList() : first(nullptr), last(nullptr), count(0) {};
    // Copy Consctructor
    StudentList(const StudentList&);
    //Copy assignment operator
    StudentList& operator=(const StudentList&);

    void addStudent(const Student& newStudent);

    int getNoOfStudents() const;

    void printStudentByID(int, double) const;
    void printStudentByName(const std::string&) const;
    void printStudentsByCourse(const std::string&, int) const;
    void printAllStudents(double)const;
    void printStudentsToFile(std::ostream&, double) const;
    void printStudentsOnHold(double) const;

    // Project Part D Additional Selection (3)
    void changeCourseNumber(const std::string&, int, int);

    void clearStudentList();
    ~StudentList();

private:
    Node* first;
    Node* last;
    int count;

    void copyCallingObjIsEmpty(const StudentList&);
    void copyObjectsSameLength(const StudentList&);
    void copyCallingObjLonger(const StudentList&);
    void copyCallingObjShorter(const StudentList&);
};


#endif