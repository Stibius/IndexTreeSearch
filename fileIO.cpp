#include "fileIO.h"
#include "search.h"

#include <fstream>

ArrayList<Student> readStudents(const std::string& inputFilename)
{
	ArrayList<Student> students = ArrayList<Student>(5);

	std::ifstream ifs;
	ifs.open(inputFilename);
	if (!ifs.is_open()) return students;

	while (ifs)
	{
		std::string line;
		getline(ifs, line);
		if (line != "")
		{
			Student student;
			Date date;
			size_t pos1 = 0;
			size_t pos2 = 0;

			pos2 = line.find(',', pos1);
			if (pos2 == std::string::npos) break;
			student.setID(line.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 2;

			pos2 = line.find(',', pos1);
			if (pos2 == std::string::npos) break;
			student.setFirstName(line.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 2;

			pos2 = line.find(',', pos1);
			if (pos2 == std::string::npos) break;
			student.setLastName(line.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 2;

			pos2 = line.find('-', pos1);
			if (pos2 == std::string::npos) break;
			date.setYear(stoi(line.substr(pos1, pos2 - pos1)));
			pos1 = pos2 + 1;

			pos2 = line.find('-', pos1);
			if (pos2 == std::string::npos) break;
			date.setMonth(stoi(line.substr(pos1, pos2 - pos1)));
			pos1 = pos2 + 1;

			pos2 = line.find(',', pos1);
			if (pos2 == std::string::npos) break;
			date.setDay(stoi(line.substr(pos1, pos2 - pos1)));
			pos1 = pos2 + 2;

			student.setBirth(date);

			pos2 = line.find(',', pos1);
			if (pos2 == std::string::npos) break;
			student.setMajor(line.substr(pos1, pos2 - pos1));
			pos1 = pos2 + 2;

			student.setGPA(stof(line.substr(pos1)));

			students.insert(student);
		}
	}

	ifs.close();

	return students;
}

ArrayList<KeyInfo> readKeys(const std::string& keyFilename)
{
	//open the file

	std::ifstream ifs;
	ifs.open(keyFilename);
	if (!ifs.is_open())
	{
		return ArrayList<KeyInfo>();
	}

	ArrayList<KeyInfo> keyInfos;

	//go line by line in the input file

	while (ifs)
	{
		//get keys, if key2 is not empty it is a range search

		KeyInfo keyInfo;

		std::string line;
		getline(ifs, line);
		size_t pos1 = line.find(':');
		if (pos1 == std::string::npos) continue;
		keyInfo.m_label = line.substr(0, pos1);
		size_t pos2 = line.find('-', pos1);
		if (keyInfo.m_label == "DOB")
		{
			pos2 = line.find('-', pos2 + 1);
			pos2 = line.find('-', pos2 + 1);
		}
		pos1 += 2;
		if (pos2 == std::string::npos)
		{
			keyInfo.m_key1 = line.substr(pos1);
		}
		else
		{
			keyInfo.m_key1 = line.substr(pos1, pos2 - pos1);
			keyInfo.m_key2 = line.substr(pos2 + 1);
		}

		keyInfos.insert(keyInfo);
	}

	return keyInfos;
}

void printBinarySearchResult(const std::string& outputFilename, const KeyInfo& keyInfo, const SearchResult& result)
{
	std::ofstream ofs;
	ofs.open(outputFilename);
	if (!ofs.is_open())
	{
		return;
	}

	//print result
	if (result.m_student != nullptr)
	{
		ofs << result.m_student->getRecord() << "\n";
		ofs << "Without index: " << result.m_accesses + 1 << " accesses\n";
	}
	else
	{
		ofs << "No record found for " << keyInfo.m_label << " " << keyInfo.m_key1 << "\n";
		ofs << "Without index: " << result.m_accesses << " accesses\n";
	}

	ofs.close();
}

void printBinaryRangeSearchResults(const std::string& outputFilename, const KeyInfo& keyInfo, const ArrayList<SearchResult>& results, int accesses)
{
	std::ofstream ofs;
	ofs.open(outputFilename);
	if (!ofs.is_open())
	{
		return;
	}

	//print results
	if (results.getSize() != 0)
	{
		for (const SearchResult& result : results)
		{
			ofs << result.m_student->getRecord() << "\n";
			ofs << "Without index: " << result.m_accesses + 1 << " accesses\n\n";
		}
	}
	else
	{
		ofs << "No record found for " << keyInfo.m_label << " " << keyInfo.m_key1 << "-" << keyInfo.m_key2 << "\n";
		ofs << "Without index: " << accesses << " accesses\n";
	}

	ofs.close();
}

void printIndexSearchResults(const std::string& outputFilename, const KeyInfo& keyInfo, const ArrayList<SearchResult>& sequentialResults, int sequentialAccesses, const IndexSearchResult& indexResults, const ArrayList<Student>& students)
{
	std::ofstream ofs;
	ofs.open(outputFilename);
	if (!ofs.is_open())
	{
		return;
	}

	//print results
	if (indexResults.m_indexList == nullptr)
	{
		ofs << "No record found for " << keyInfo.m_label << " " << keyInfo.m_key1 << "\n";
		ofs << "Without index: " << sequentialAccesses << " accesses\n";
		ofs << "With index: " << indexResults.m_accesses + 1 << " accesses\n";
	}
	else
	{
		const IndexNode* current = indexResults.m_indexList;
		int i = 0;
		while (current != nullptr)
		{
			ofs << students[current->m_index].getRecord() << "\n";
			ofs << "Without index: " << sequentialResults[i].m_accesses << " accesses\n";
			ofs << "With index: " << indexResults.m_accesses + 1 << " accesses\n\n";
			current = current->m_next.get();
			i++;
		}
	}

	ofs.close();
}

void printIndexRangeSearchResults(const std::string& outputFilename, const KeyInfo& keyInfo, const ArrayList<SearchResult>& sequentialResults, int sequentialAccesses, const ArrayList<IndexSearchResult>& indexResults, int indexAccesses, const ArrayList<Student>& students)
{
	std::ofstream ofs;
	ofs.open(outputFilename);
	if (!ofs.is_open())
	{
		return;
	}

	//print results
	if (indexResults.getSize() == 0)
	{
		ofs << "No record found for " << keyInfo.m_label << " " << keyInfo.m_key1 << "-" << keyInfo.m_key2 << "\n";
		ofs << "Without index: " << sequentialAccesses << " accesses\n";
		ofs << "With index: " << indexAccesses + 1 << " accesses\n";
	}
	else
	{
		int j = 0;

		for (const IndexSearchResult& indexResult : indexResults)
		{
			const IndexNode* current = indexResult.m_indexList;
			while (current != nullptr)
			{
				ofs << students[current->m_index].getRecord() << "\n";
				ofs << "Without index: " << sequentialResults[j].m_accesses << " accesses\n";
				ofs << "With index: " << indexResult.m_accesses + 1 << " accesses\n\n";
				current = current->m_next.get();
				j++;
			}
		}
	}

	ofs.close();
}

