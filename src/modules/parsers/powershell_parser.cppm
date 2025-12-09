module;

#include <print>

export module PowerShellParserModule;

import IParserModule;

export class PowerShellParser final : public IParser
{
  public:
    explicit PowerShellParser(char line_delim, const std::string &right_block_delim,
                              const std::string &left_block_delim)
    {
        IParser::set_line_delim(std::move(line_delim));
        IParser::set_block_delim(left_block_delim, right_block_delim);
    };

    ~PowerShellParser() override = default;
};
