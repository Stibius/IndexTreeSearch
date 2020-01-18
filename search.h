#pragma once

#include "ArrayList.h"
#include "Student.h"

//represents one result of a sequential or binary search on an arraylist of Student objects 
//contains a pointer to the found Student object and number of accesses necessary to find that Student
//if nothing was found, the pointer is nullptr
struct SearchResult
{
	const Student* m_student = nullptr;
	int m_accesses = 0;

	SearchResult(const Student* student = nullptr, int accesses = 0);

	//a comparison operator for sorting purposes
	bool operator<(const SearchResult& searchResult) const;
};

//performs binary search on the input arraylist between the first and last positions inclusive
//searches for ID
//the result is saved in the result variable
void binarySearchID(const ArrayList<Student>& students, int first, int last, const std::string& ID, SearchResult& result);

//performs binary search on the input arraylist
//searches for ID
//returns the result
SearchResult binarySearchID(const ArrayList<Student>& students, const std::string& ID);

//performs binary range search on the input arraylist between the first and last positions inclusive
//searches for all IDs between ID1 and ID2 inclusive
//the results are saved in the results arraylist
//accesses: for counting the total number of accesses even if the arraylist of results is empty
void binaryRangeSearchID(const ArrayList<Student>& students, int first, int last, const std::string& ID1, const std::string& ID2, ArrayList<SearchResult>& results, int& accesses);

//performs binary range search on the input arraylist
//searches for all IDs between ID1 and ID2 inclusive
//returns the results
//accesses: for counting the total number of accesses even if the arraylist of results is empty
ArrayList<SearchResult> binaryRangeSearchID(const ArrayList<Student>& students, const std::string& ID1, const std::string& ID2, int& accesses);

//performs sequential search on the input arraylist 
//searches for all records that have a value of the field given by label equal to key
//returns the results
//accesses: for counting the total number of accesses even if the arraylist of results is empty
ArrayList<SearchResult> sequentialSearch(const ArrayList<Student>& students, const std::string& label, const std::string& key, int& accesses);

//performs sequential range search on the input arraylist 
//searches for all records that have a value of the field given by label between key1 and key2 inclusive
//returns the results
//accesses: for counting the total number of accesses even if the arraylist of results is empty
ArrayList<SearchResult> sequentialRangeSearch(const ArrayList<Student>& students, const std::string& label, const std::string& key1, const std::string& key2, int& accesses);

//keyFilename: the file with the keys to retrieve
//outputFilename: the file where the results are going to be saved
//students: arraylist of student records on which the search is going to be performed
void findKeys(const std::string& keyFilename, const std::string& outputFilename, const ArrayList<Student>& students);





