#include <print>
#include <vector>

import FileIOModule;
import FlagParserModule;

int main(const int argc, char *argv[])
{
    std::vector<std::string> _v_arg(argv, argv + argc);

    // check if we have any possible flags
    if (_v_arg.size() > 1)
    {
        if (!FlagParser::parse(_v_arg))
            return EXIT_FAILURE;
    }
    else
    {
        std::println("Error: No arguments were given, try '--help' or '-h' for usage info");
        return EXIT_FAILURE;
    }

    FileIO file(_v_arg.at(1));
    if (!file.read())
    {
        std::println("Error: couldn't read file: {}", _v_arg.at(1));
        return EXIT_FAILURE;
    }

    if (!FlagParser::m_parser->parse(file.get_content()))
        return EXIT_FAILURE;

    file.set_content(FlagParser::m_parser->get_buffer());

    if (!FlagParser::m_output.empty())
        file.set_out_filename(FlagParser::m_output);

    if (!file.write())
    {
        std::println("Error: couldn't write file: {}", FlagParser::m_output);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
