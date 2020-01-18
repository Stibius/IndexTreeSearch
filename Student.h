#pragma once

#include <string>

#include "Date.h"

//class representing a student record
class Student
{
private:

	std::string m_ID;
	std::string m_firstName;
	std::string m_lastName;
	Date m_birth;
	std::string m_major;
	float m_GPA;

public:

	Student() = default;

	Student(const std::string& ID, const std::string& firstName, const std::string& lastName, const Date& birth, const std::string& major, float GPA);

	//comparison operator for the Student class
	//Student object with a smaller ID is considered smaller
	//used for sorting the student records by ID 
	bool operator<(const Student& student) const;

	void setID(const std::string& ID);

	void setFirstName(const std::string& firstName);

	void setLastName(const std::string& lastName);

	void setBirth(const Date& birth);

	void setMajor(const std::string& major);

	void setGPA(float GPA);

	const std::string& getID() const;

	const std::string& getFirstName() const;

	const std::string& getLastName() const;

	const Date& getBirth() const;

	const std::string& getMajor() const;

	float getGPA() const;

	//returns the entire student record in a string format ready for printing
	std::string getRecord() const;
};


