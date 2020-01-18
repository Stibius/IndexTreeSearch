#pragma once

#include <string>

#include "ArrayList.h"
#include "IndexTree.h"
#include "Student.h"

struct SearchResult;

//represents one record from the file with search keys
struct KeyInfo
{
	std::string m_label; //label to search for
	std::string m_key1;  //value to search for, in case of ranged search, this is the lower bound
	std::string m_key2;  //in case of ranged search, this is the upper bound
};

//reads a list of student records from an input file
//returns an arraylist of Student objects
ArrayList<Student> readStudents(const std::string& inputFilename);

//reads a list of search keys from an input file
//returns an array list of KeyInfo objects
ArrayList<KeyInfo> readKeys(const std::string& keyFilename);

//prints the result of a binary search
void printBinarySearchResult(const std::string& outputFilename, const KeyInfo& keyInfo, const SearchResult& result);

//prints the results of a ranged binary search
//accesses: number of accesses in the case that nothing was found
void printBinaryRangeSearchResults(const std::string& outputFilename, const KeyInfo& keyInfo, const ArrayList<SearchResult>& results, int accesses);

//prints the results of a sequential and index tree search
//sequentialAccesses: number of sequential search accesses in the case that nothing was found
void printIndexSearchResults(const std::string& outputFilename, const KeyInfo& keyInfo, const ArrayList<SearchResult>& sequentialResults, int sequentialAccesses, const IndexSearchResult& indexResults, const ArrayList<Student>& students);

//prints the results of a sequential and index tree search
//sequentialAccesses: number of sequential search accesses in the case that nothing was found
//indexAccesses: number of index search accesses in the case that nothing was found
void printIndexRangeSearchResults(const std::string& outputFilename, const KeyInfo& keyInfo, const ArrayList<SearchResult>& sequentialResults, int sequentialAccesses, const ArrayList<IndexSearchResult>& indexResults, int indexAccesses, const ArrayList<Student>& students);