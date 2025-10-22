#include <vector>
#include <print>

// import Parser;
import FileIOModule;
import FlagParserModule;

int main(const int argc, char *argv[])
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
    if (!file.read())
    {
        std::println("Error: couldn't read file: {}", _v_arg.at(1));
        return EXIT_FAILURE;
    }

    // parse with parser flags
    if (!FlagParser::m_output.empty())
        file.set_out_filename(FlagParser::m_output);

    if (!file.write())
    {
        std::println("Error: couldn't write file: {}", FlagParser::m_output);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


