
#include "ArgumentManager.h"

void ArgumentManager::parse(const std::string& rawArguments, char delimiter)
{
    std::stringstream currentArgumentName;
    std::stringstream currentArgumentValue;
    bool argumentNameFinished = false;

    for (unsigned int i = 0; i <= rawArguments.length(); ++i)
    {
        if (i == rawArguments.length() || rawArguments[i] == delimiter)
        {
            if (currentArgumentName.str() != "")
            {
                m_argumentMap[currentArgumentName.str()] = currentArgumentValue.str();
            }
            //reset
            currentArgumentName.str("");
            currentArgumentValue.str("");
            argumentNameFinished = false;
        }
        else if (rawArguments[i] == '=')
        {
            argumentNameFinished = true;
        }
        else
        {
            if (argumentNameFinished)
            {
                currentArgumentValue << rawArguments[i];
            }
            else
            {
                //ignore any spaces in argument names. 
                if (rawArguments[i] == ' ')
                    continue;
                currentArgumentName << rawArguments[i];
            }
        }
    }
}

void ArgumentManager::parse(int argc, char* argv[], char delimiter)
{
    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            parse(argv[i], delimiter);
        }
    }
}

ArgumentManager::ArgumentManager(int argc, char* argv[], char delimiter)
{
    parse(argc, argv, delimiter);
}

ArgumentManager::ArgumentManager(const std::string& rawArguments, char delimiter)
{
    parse(rawArguments, delimiter);
}

std::string ArgumentManager::get(const std::string& argumentName)
{
    std::map<std::string, std::string>::iterator iter = m_argumentMap.find(argumentName);

    //If the argument is not found, return a blank string.
    if (iter == m_argumentMap.end())
    {
        return "";
    }
    else
    {
        return iter->second;
    }
}

std::string ArgumentManager::toString()
{
    std::stringstream ss;
    for (std::map<std::string, std::string>::iterator iter = m_argumentMap.begin(); iter != m_argumentMap.end(); ++iter)
    {
        ss << "Argument name: " << iter->first << std::endl;
        ss << "Argument value: " << iter->second << std::endl;
    }
    return ss.str();
}

std::ostream& operator<<(std::ostream& out, ArgumentManager& am)
{
    out << am.toString();
    return out;
}
