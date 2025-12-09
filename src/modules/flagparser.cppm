module;

#include <print>
#include <string>
#include <vector>

export module FlagParserModule;

import IParserModule;
import CXXParserModule;
import PythonParserModule;
import PowerShellParserModule;

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
    int arg_index = 0;
    // skip first argument, because it doesn't need to be parsed
    for (auto it = flags.begin() + 1; it != flags.end(); ++it, arg_index++)
    {
        if (const auto next = std::next(it); arg_index == 0 && *it == "--help" || *it == "-h")
        {
            std::println(R"(common - Compiler for the esoteric programming language where everything is a comment!

USAGE:
    common <input_file> [OPTIONS]

ARGUMENTS:
    <input_file>    Source file to compile (any file extension)

OPTIONS:
    -h, --help         This help message
    -o, --output       Specify output file
    --parser=<parser>  Comment parser to use (default: c)
                       Available parsers:
                         c          - C/C++ style comments (// and /* */)
                         python     - Python style comments (#)
                         powershell - PowerShell style comments (# and <# #>)

DESCRIPTION:
    Compiles source files written in the 'common' programming language to .com files.
    By default, parses C-style comments (//, /* */). Output file will have the same
    name as input with .com extension.

EXAMPLES:
    # Compile with default C/C++ style comments
    $ common common_test.txt
    
    # Compile with Python style comments
    $ common --parser=py common_python_test.txt)");
            // this isn't best practice, but we can exit right here after the help message is printed
            std::exit(EXIT_SUCCESS);
        }

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
                m_parser = new PythonParser('#', "\"\"\"");
                success = true;
            }
            else if (parser_name == "powershell" || parser_name == "ps")
            {
                m_parser = new PowerShellParser('#', "<#", "#>");
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
