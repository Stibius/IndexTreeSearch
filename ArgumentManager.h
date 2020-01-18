#pragma once

#include <map>
#include <string>
#include <iostream>
#include <sstream>

//This is a class that can parse the commnad line arguments 
class ArgumentManager 
{
private:

    std::map<std::string, std::string> m_argumentMap;

public:

    ArgumentManager() { }

    ArgumentManager(int argc, char* argv[], char delimiter = ';');

    ArgumentManager(const std::string& rawArguments, char delimiter = ';');

    void parse(int argc, char* argv[], char delimiter = ';');

    void parse(const std::string& rawArguments, char delimiter = ';');

    std::string get(const std::string& argumentName);

    std::string toString();

    friend std::ostream& operator<<(std::ostream& out, ArgumentManager& am);
};