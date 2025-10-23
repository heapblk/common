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
    [[nodiscard]] bool parse(std::string content) override
    {
        m_content = "THIS WAS COMPILED WITH COMMON\n" + std::move(content);
        bool success = true;

        // check for block comments
        if (m_content.at(0) != '/' && m_content.at(1) != '*' && !m_content.ends_with("*/"))
        {
            std::println("Error: CXXParser: could not parse file: failed at block comment check");
            success = false;
        }

        return success;
    };

    [[nodiscard]] std::string get_content() override
    {
        return m_content;
    }

private:
    std::string m_content;
};