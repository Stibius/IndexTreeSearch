#include "Student.h"

Student::Student(const std::string& ID, const std::string& firstName, const std::string& lastName, const Date& birth, const std::string& major, float GPA)
	: m_ID(ID), m_firstName(firstName), m_lastName(lastName), m_birth(birth), m_major(major), m_GPA(GPA)
{
}

bool Student::operator<(const Student& student) const
{
	return m_ID < student.m_ID;
}

void Student::setID(const std::string& ID)
{
	m_ID = ID;
}

void Student::setFirstName(const std::string& firstName)
{
	m_firstName = firstName;
}

void Student::setLastName(const std::string& lastName)
{
	m_lastName = lastName;
}

void Student::setBirth(const Date& birth)
{
	m_birth = birth;
}

void Student::setMajor(const std::string& major)
{
	m_major = major;
}

void Student::setGPA(float GPA)
{
	m_GPA = GPA;
}

const std::string& Student::getID() const
{
	return m_ID;
}

const std::string& Student::getFirstName() const
{
	return m_firstName;
}

const std::string& Student::getLastName() const
{
	return m_lastName;
}

const Date& Student::getBirth() const
{
	return m_birth;
}

const std::string& Student::getMajor() const
{
	return m_major;
}

float Student::getGPA() const
{
	return m_GPA;
}

std::string Student::getRecord() const
{
	//convert birth date to string
	std::string birthS = m_birth.toString();

	//convert GPA to string
	std::string GPAS = std::to_string(m_GPA);
	int pos = GPAS.find('.');
	//make sure there are only 2 decimal digits
	GPAS.erase(pos + 3);

	//create the string record
	std::string record =
		m_ID + ", " +
		m_firstName + ", " +
		m_lastName + ", " +
		birthS + ", " +
		m_major + ", " +
		GPAS;

	return record;
}
