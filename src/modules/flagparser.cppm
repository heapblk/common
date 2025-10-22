module;

#include <vector>
#include <string>
#include <print>

import IParserModule;
import CXXParserModule;

export module FlagParserModule;

// checks if all flags that are set have been set correctly (e.g. -o needs an argument)
export namespace FlagParser // wanted to try a pattern that works well with cxx modules here
{
std::string m_output;
IParser *m_parser = new CXXParser(); // default is the cxx parser

bool parse(std::vector<std::string> &flags)
{
    bool success = false;
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
        else if (it->contains("--parser="))
        {
            // currently only the cxx parser is available
            if (*it == "--parser=cxx")
            {
                m_parser = new CXXParser();
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
}