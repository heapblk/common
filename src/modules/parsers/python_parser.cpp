module;

#include <print>

export module PythonParserModule;

import IParserModule;

export class PythonParser final : public IParser
{
  public:
    explicit PythonParser(char line_delim, const std::string &block_delim)
    {
        IParser::set_line_delim(std::move(line_delim));
        IParser::set_block_delim(block_delim, block_delim);
    };

    ~PythonParser() override = default;
};
