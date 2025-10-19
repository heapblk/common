module;

#include <iostream>

import IParserModule;

export module CXXParserModule;

export class CXXParser final : public IParser
{
public:
    CXXParser() = default;

    ~CXXParser() override
    {
    };

    void parse() override
    {
        std::cout << "parse()" << std::endl;
    };

};