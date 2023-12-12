/*
	Lee, Jiseob

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"

#include <iostream>

using namespace std;

StudentList::StudentList(const StudentList& otherList) : 
	first(nullptr), last(nullptr), count(0)
{
	Node* currentOther = otherList.first;
	while (currentOther != nullptr)
	{
		addStudent(currentOther->getStudent());
		currentOther = currentOther->getNext();
	}
}

StudentList& StudentList::operator=(const StudentList& otherList)
{
	if (&otherList == this) 
		cerr << "Attempted assignment to itself." << endl;
	else if (otherList.count == 0) 
		clearStudentList();
	else if (count == 0) 
		copyCallingObjIsEmpty(otherList);
	else if (count == otherList.count) 
		copyObjectsSameLength(otherList);
	else if (count > otherList.count) 
		copyCallingObjLonger(otherList);
	else if (count < otherList.count) 
		copyCallingObjShorter(otherList);

	return *this;
}

void StudentList::copyCallingObjIsEmpty(const StudentList& otherList)
{
	Node* current = otherList.first;
	while (current != nullptr)
	{
		addStudent(current->getStudent());
		current = current->getNext();
	}
}

void StudentList::copyObjectsSameLength(const StudentList& otherList)
{
	Node* current = first;
	Node* currentOther = otherList.first;

	while (current != nullptr)
	{
		current->setStudent(currentOther->getStudent());
		current = current->getNext();
		currentOther = currentOther->getNext();
	}
}

void StudentList::copyCallingObjLonger(const StudentList& otherList)
{
	Node* current = first;
	Node* currentOther = otherList.first;

	while (currentOther != nullptr)
	{
		current->setStudent(currentOther->getStudent());
		last = current;
		current = current->getNext();
		currentOther = currentOther->getNext();
	}

	while (current != nullptr)
	{
		Node* temp = current;
		current = current->getNext();
		delete temp;
		--count;
	}

	last->setNext(nullptr);
}

void StudentList::copyCallingObjShorter(const StudentList& otherList)
{
	Node* current = first;
	Node* currentOther = otherList.first;

	while (current != nullptr)
	{
		current->setStudent(currentOther->getStudent());
		current = current->getNext();
		currentOther = currentOther->getNext();
	}

	while (currentOther != nullptr)
	{
		Node* newNode = new Node(currentOther->getStudent(), nullptr);
		last->setNext(newNode);
		last = newNode;
		current = newNode;

		currentOther = currentOther->getNext();
		++count;
	}
}