module;

#include <cctype>
#include <print>
#include <string>
#include <vector>

export module FlagParserModule;

import IParserModule;
import CXXParserModule;
import PythonParserModule;

namespace
{
const std::string c_parser_prefix = "--parser=";
};

// checks if all flags that are set have been set correctly (e.g. -o needs an argument)
export namespace FlagParser // wanted to try a pattern that works well with cxx modules here
{
std::string m_output;
IParser *m_parser = new CXXParser(); // default is the cxx parser

bool parse(std::vector<std::string> &flags)
{
    bool success = true;
    // skip first two arguments, we already know that we have at least 3
    for (auto it = flags.begin() + 2; it != flags.end(); ++it)
    {
        if (*it == "-o" or *it == "--output")
        {
            if (const auto next = std::next(it); next == flags.end() or next->empty())
            {
                std::println("Error: -o/--output takes one argument");
                success = false;
            }
            else
            {
                m_output = *next;
                success = true;

                // skip next argument
                ++it;
            }
        }
        else if (it->contains(c_parser_prefix))
        {
            std::string parser_name =
                static_cast<std::string>(*it).substr(c_parser_prefix.size(), static_cast<std::string>(*it).size());
            std::transform(parser_name.begin(), parser_name.end(), parser_name.begin(),
                           [](unsigned char c) { return std::tolower(c); });

            if (parser_name == "cxx" || parser_name == "c")
            {
                m_parser = new CXXParser();
                success = true;
            }
            else if (parser_name == "python" || parser_name == "py")
            {
                m_parser = new PythonParser();
                success = true;
            }
            else
            {
                std::println("Error: no such parser exists");
                success = false;
            }
        }
        else
        {
            // first and second args should be ignored here when returning an error
            std::println("Error: no such flag");
            success = false;
        }
    }
    return success;
}
} // namespace FlagParser
