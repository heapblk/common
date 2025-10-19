#include <iostream>
#include <vector>
#include <print>

// import Parser;
import FileIOModule;
import FlagParserModule;

int main(int argc, char **argv)
{
    std::vector<std::string> _v_arg(argv, argv + argc);

    // check if we have any possible flags
    if (_v_arg.size() >= 2)
    {
        if (!FlagParser::parse(_v_arg))
        {
            return EXIT_FAILURE;
        }
    }

    // parse file content
    FileIO file(_v_arg.at(1));
    file.read();

    // parse with parser flags
    if (!FlagParser::m_output.empty())
        file.set_out_filename(FlagParser::m_output);

    file.write();
}


