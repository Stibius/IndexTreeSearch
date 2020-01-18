#include "search.h"
#include "IndexTree.h"
#include "fileIO.h"

SearchResult::SearchResult(const Student* student, int accesses)
	: m_student(student), m_accesses(accesses) 
{
}

bool SearchResult::operator<(const SearchResult& searchResult) const
{
	return m_student == nullptr || m_student < searchResult.m_student;
}

void binarySearchID(const ArrayList<Student>& students, int first, int last, const std::string& ID, SearchResult& result)
{
	if (first > last)
	{
		return;
	}

	int index = (last + first) / 2;
	const Student& student = students[index];
	result.m_accesses++;

	if (ID == student.getID())
	{
		result.m_student = &student;
		return;
	}
	else if (ID < student.getID())
	{
		binarySearchID(students, first, index - 1, ID, result);
	}
	else
	{
		binarySearchID(students, index + 1, last, ID, result);
	}
}

SearchResult binarySearchID(const ArrayList<Student>& students, const std::string& ID)
{
	SearchResult result;

	binarySearchID(students, 0, students.getSize() - 1, ID, result);

	return result;
}

void binaryRangeSearchID(const ArrayList<Student>& students, int first, int last, const std::string& ID1, const std::string& ID2, ArrayList<SearchResult>& results, int& accesses)
{
	if (first > last)
	{
		return;
	}

	int index = (last + first) / 2;
	const Student& student = students[index];
	accesses++;

	if (student.getID() >= ID1 && student.getID() <= ID2)
	{
		results.insert(SearchResult(&student, accesses));

		//search for other matching values to the left of the found value
		for (int i = index - 1; i >= 0; --i)
		{
			accesses++;

			if (students[i].getID() >= ID1 && students[i].getID() <= ID2)
			{
				results.insert(SearchResult(&(students[i]), accesses));
			}
			else
			{
				break;
			}
		}

		//search for other matching values to the right of the found value
		for (int i = index + 1; i < students.getSize(); ++i)
		{
			accesses++;

			if (students[i].getID() >= ID1 && students[i].getID() <= ID2)
			{
				results.insert(SearchResult(&(students[i]), accesses));
			}
			else
			{
				break;
			}
		}
	}
	else if (ID1 < student.getID())
	{
		binaryRangeSearchID(students, first, index - 1, ID1, ID2, results, accesses);
	}
	else
	{
		binaryRangeSearchID(students, index + 1, last, ID1, ID2, results, accesses);
	}
}

ArrayList<SearchResult> binaryRangeSearchID(const ArrayList<Student>& students, const std::string& ID1, const std::string& ID2, int& accesses)
{
	ArrayList<SearchResult> results;
	accesses = 0;

	binaryRangeSearchID(students, 0, students.getSize() - 1, ID1, ID2, results, accesses);

	results.sort();

	return results;
}

ArrayList<SearchResult> sequentialSearch(const ArrayList<Student>& students, const std::string& label, const std::string& key, int& accesses)
{
	accesses = 0;

	ArrayList<SearchResult> results;

	for (const Student& student : students)
	{
		accesses++;

		if (label == "FIRSTNAME")
		{
			if (student.getFirstName() == key)
			{
				results.insert(SearchResult(&(student), accesses));
			}
		}
		else if (label == "LASTNAME")
		{
			if (student.getLastName() == key)
			{
				results.insert(SearchResult(&(student), accesses));
			}
		}
		else if (label == "DOB")
		{
			Date date = Date(key);

			if (student.getBirth() == date)
			{
				results.insert(SearchResult(&(student), accesses));
			}
		}
		else if (label == "MAJOR")
		{
			if (student.getMajor() == key)
			{
				results.insert(SearchResult(&(student), accesses));
			}
		}
		else if (label == "GPA")
		{
			if (student.getGPA() == stof(key))
			{
				results.insert(SearchResult(&(student), accesses));
			}
		}
	}

	return results;
}

ArrayList<SearchResult> sequentialRangeSearch(const ArrayList<Student>& students, const std::string& label, const std::string& key1, const std::string& key2, int& accesses)
{
	accesses = 0;

	ArrayList<SearchResult> results;

	for (const Student& student : students)
	{
		accesses++;

		if (label == "FIRSTNAME")
		{
			if (student.getFirstName() >= key1 && student.getFirstName() <= key2)
			{
				results.insert(SearchResult(&student, accesses));
			}
		}
		else if (label == "LASTNAME")
		{
			if (student.getLastName() >= key1 && student.getLastName() <= key2)
			{
				results.insert(SearchResult(&student, accesses));
			}
		}
		else if (label == "DOB")
		{
			Date date1 = Date(key1);
			Date date2 = Date(key2);

			if (student.getBirth() >= date1 && student.getBirth() <= date2)
			{
				results.insert(SearchResult(&student, accesses));
			}
		}
		else if (label == "MAJOR")
		{
			if (student.getMajor() >= key1 && student.getMajor() <= key2)
			{
				results.insert(SearchResult(&student, accesses));
			}
		}
		else if (label == "GPA")
		{
			if (student.getGPA() >= stof(key1) && student.getGPA() <= stof(key2))
			{
				results.insert(SearchResult(&student, accesses));
			}
		}
	}

	return results;
}

void findKeys(const std::string& keyFilename, const std::string& outputFilename, const ArrayList<Student>& students)
{
	//build AVL index trees for all fields

	IndexTree<std::string> FNTree;
	IndexTree<std::string> LNTree;
	IndexTree<Date> birthTree;
	IndexTree<std::string> majorTree;
	IndexTree<float> GPATree;

	for (int i = 0; i < students.getSize(); ++i)
	{
		FNTree.insert(students[i].getFirstName(), i);
		LNTree.insert(students[i].getLastName(), i);
		birthTree.insert(students[i].getBirth(), i);
		majorTree.insert(students[i].getMajor(), i);
		GPATree.insert(students[i].getGPA(), i);
	}

	//read keys

	ArrayList<KeyInfo> keyInfos = readKeys(keyFilename);

	//for each key or key range
	for (const KeyInfo& keyInfo : keyInfos)
	{
		//search is for ID: binary search
		if (keyInfo.m_label == "ID")
		{
			//it is not a range search
			if (keyInfo.m_key2 == "")
			{
				SearchResult result = binarySearchID(students, keyInfo.m_key1);

				//print results
				printBinarySearchResult(outputFilename, keyInfo, result);
			}
			//it is a range search
			else
			{
				int accesses = 0;
				ArrayList<SearchResult> results = binaryRangeSearchID(students, keyInfo.m_key1, keyInfo.m_key2, accesses);

				//print results
				printBinaryRangeSearchResults(outputFilename, keyInfo, results, accesses);
			}
		}
		//search is not for ID, sequential and AVL index tree search
		else
		{
			//it is not a range search
			if (keyInfo.m_key2 == "")
			{
				ArrayList<SearchResult> sequentialResults;
				int sequentialAccesses = 0;
				IndexSearchResult indexResults;

				if (keyInfo.m_label == "FIRSTNAME")
				{
					sequentialResults = sequentialSearch(students, keyInfo.m_label, keyInfo.m_key1, sequentialAccesses);
					indexResults = FNTree.search(keyInfo.m_key1);
				}
				else if (keyInfo.m_label == "LASTNAME")
				{
					sequentialResults = sequentialSearch(students, keyInfo.m_label, keyInfo.m_key1, sequentialAccesses);
					indexResults = LNTree.search(keyInfo.m_key1);
				}
				else if (keyInfo.m_label == "DOB")
				{
					Date date = Date(keyInfo.m_key1);

					sequentialResults = sequentialSearch(students, keyInfo.m_label, keyInfo.m_key1, sequentialAccesses);
					indexResults = birthTree.search(date);
				}
				else if (keyInfo.m_label == "MAJOR")
				{
					sequentialResults = sequentialSearch(students, keyInfo.m_label, keyInfo.m_key1, sequentialAccesses);
					indexResults = majorTree.search(keyInfo.m_key1);
				}
				else if (keyInfo.m_label == "GPA")
				{
					sequentialResults = sequentialSearch(students, keyInfo.m_label, keyInfo.m_key1, sequentialAccesses);
					indexResults = GPATree.search(stof(keyInfo.m_key1));
				}

				//print results
				printIndexSearchResults(outputFilename, keyInfo, sequentialResults, sequentialAccesses, indexResults, students);
			}
			//it is a range search
			else
			{
				ArrayList<SearchResult> sequentialResults;
				ArrayList<IndexSearchResult> indexResults;
				int sequentialAccesses = 0;
				int indexAccesses = 0;

				if (keyInfo.m_label == "FIRSTNAME")
				{
					sequentialResults = sequentialRangeSearch(students, keyInfo.m_label, keyInfo.m_key1, keyInfo.m_key2, sequentialAccesses);
					indexResults = FNTree.searchRange(keyInfo.m_key1, keyInfo.m_key2, indexAccesses);
				}
				else if (keyInfo.m_label == "LASTNAME")
				{
					sequentialResults = sequentialRangeSearch(students, keyInfo.m_label, keyInfo.m_key1, keyInfo.m_key2, sequentialAccesses);
					indexResults = LNTree.searchRange(keyInfo.m_key1, keyInfo.m_key2, indexAccesses);
				}
				else if (keyInfo.m_label == "DOB")
				{
					Date date1 = Date(keyInfo.m_key1);
					Date date2 = Date(keyInfo.m_key2);

					sequentialResults = sequentialRangeSearch(students, keyInfo.m_label, keyInfo.m_key1, keyInfo.m_key2, sequentialAccesses);
					indexResults = birthTree.searchRange(date1, date2, indexAccesses);
				}
				else if (keyInfo.m_label == "MAJOR")
				{
					sequentialResults = sequentialRangeSearch(students, keyInfo.m_label, keyInfo.m_key1, keyInfo.m_key2, sequentialAccesses);
					indexResults = majorTree.searchRange(keyInfo.m_key1, keyInfo.m_key2, indexAccesses);
				}
				else if (keyInfo.m_label == "GPA")
				{
					sequentialResults = sequentialRangeSearch(students, keyInfo.m_label, keyInfo.m_key1, keyInfo.m_key2, sequentialAccesses);
					indexResults = GPATree.searchRange(stof(keyInfo.m_key1), stof(keyInfo.m_key2), indexAccesses);
				}

				//print results
				printIndexRangeSearchResults(outputFilename, keyInfo, sequentialResults, sequentialAccesses, indexResults, indexAccesses, students);
			}
		}
	}
}
