
#include <string>
#include "ArgumentManager.h"
#include "Student.h"
#include "ArrayList.h"
#include "search.h"
#include "fileIO.h"

int main(int argc, char* argv[])
{
	ArgumentManager argManager;
	argManager.parse(argc, argv);
	std::string inputFilename1 = argManager.get("A");
	std::string inputFilename2 = argManager.get("B");
	std::string outputFilename = argManager.get("C");

	ArrayList<Student> students = readStudents(inputFilename1);

	students.sort();

	findKeys(inputFilename2, outputFilename, students);

	return 0;
}