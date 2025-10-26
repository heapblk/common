module;

#include <print>

#ifdef __unix__
#define EOL '\n'
#elif _WIN32
#define EOL '\r\n'
#endif

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
        bool success = false;
        m_buffer = std::move(buffer);

        if (!m_buffer.starts_with("//") && !m_buffer.starts_with("/*"))
        {
            std::println("Error: CXXParser: Line 1: no '/*' or '//' at the beginning of buffer");
            return false;
        }
        else if (m_buffer.ends_with("*/" + EOL))
        {
            success = true;
        }

        if (!success)
            success = parse_internal();

        // insert a nice compiler message at the top
        std::string comp_message = "/*THIS WAS COMPILED WITH COMMON*/\n";
        m_buffer.insert(m_buffer.begin(), comp_message.begin(), comp_message.end());

        return success;
    };

    // returns internal buffer
    [[nodiscard]] std::string get_buffer() override
    {
        return m_buffer;
    }

private:
    bool parse_internal()
    {
        bool success = true;
        bool line_comment = false;
        bool block_comment = false;
        int count = 1;

        for (auto it = m_buffer.begin(); it != m_buffer.end(); ++it)
        {
            auto next = std::next(it);

            switch (*it)
            {
            case '/':
                if (*next == '*')
                    block_comment = true;
                break;
            case '*':
                if (*next == '/')
                {
                    if (block_comment)
                        block_comment = false; // block comment ends here
                }
                break;
            case EOL:
                count++;
                if (!block_comment)
                {
                    line_comment = false;

                    if (*next == '/' && *(next + 1) == '/')
                        line_comment = true;

                    if (next != m_buffer.end() && !line_comment)
                    {
                        std::println("current char: {}", *it);
                        std::println("next char: {}", *next);
                        std::println("nextnext char: {}", *(next + 1));
                        std::println("Error: Line {}", count);
                    }
                }
                break;
            default:
                if (!block_comment && !line_comment)
                {
                    success &= false;
                }
                else
                    success &= true;
            }
        }
        return success;
    }

    std::string m_buffer;
};