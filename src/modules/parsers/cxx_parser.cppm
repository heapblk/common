module;

#include <print>

export module CXXParserModule;

import IParserModule;

export class CXXParser final : public IParser
{
public:
    explicit CXXParser() = default;

    ~CXXParser() override = default;

    // parses the file content by the rules of the CXX parser
    [[nodiscard]] bool parse(std::string buffer) override
    {
        m_buffer = "THIS WAS COMPILED WITH COMMON\n" + std::move(buffer);
        bool success = true;

        // check for block comments at the beginning and end of the buffer
        if (m_buffer.at(0) != '/' && m_buffer.at(1) != '*' && !m_buffer.ends_with("*/"))
        {
            std::println("Error: CXXParser: could not parse file: failed at block comment check");
            return success;
        }

        return success;
    };

    // returns internal buffer
    [[nodiscard]] std::string get_buffer() override
    {
        return m_buffer;
    }

private:
    bool parse_line_comment(std::string buffer)
    {
        bool success = true;

        return success;
    }

    std::string m_buffer;
};