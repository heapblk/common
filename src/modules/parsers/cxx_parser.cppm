module;

#include <print>

#ifdef __unix__
#define EOL '\n'
#elif _WIN32
#define EOL '\r\n'
#endif

#define BLOCK_COMMENT_END   "*/"
#define LINE_COMMENT        "//"

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
        m_buffer = std::move(buffer);
        bool success = true;
        bool block_comment = false;
        size_t line_start = 0;
        size_t line_count = 1;

        while (line_start < m_buffer.size())
        {
            // Find end of line
            size_t line_end = m_buffer.find(EOL, line_start);
            if (line_end == std::string::npos)
                line_end = m_buffer.size();

            std::string_view line(m_buffer.data() + line_start, line_end - line_start);
            size_t i = 0;
            bool line_has_code = false; // or anything but comments

            while (i < line.size())
            {
                if (block_comment)
                {
                    size_t current_line_end = line.find(BLOCK_COMMENT_END, i);
                    if (current_line_end == std::string_view::npos)
                    {
                        // rest of line is inside block comment
                        i = line.size();
                        break;
                    }
                    block_comment = false;
                    i = current_line_end + 2; // move index beyond the found '*/'
                }
                else
                {
                    if (line[i] == '/' && i + 1 < line.size())
                    {
                        if (line[i + 1] == '/')
                            break; // rest is line comment
                        if (line[i + 1] == '*')
                        {
                            // start block comment
                            block_comment = true;
                            i += 2;
                            continue;
                        }
                    }
                    if (!std::isspace(line[i]))
                    {
                        line_has_code = true;
                    }
                    ++i;
                }
            }

            if (line_has_code)
            {
                success = false;
                std::println("Error: Line {} contains uncommented tokens", line_count);
            }

            line_start = line_end + 1;
            ++line_count;
        }

        if (block_comment)
        {
            std::println("Error: file ends inside a non-closed block comment");
            success = false;
        }

        if (success)
        {
            // insert a nice compiler message at the top
            std::string comp_message = "/*THIS WAS COMPILED WITH COMMON*/\n";
            m_buffer.insert(m_buffer.begin(), comp_message.begin(), comp_message.end());
        }

        return success;
    };

    // returns internal buffer
    [[nodiscard]] std::string get_buffer() override
    {
        return m_buffer;
    }

private:
    std::string m_buffer;
};