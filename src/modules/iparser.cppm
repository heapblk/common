module;

#include <print>
#include <string>

#ifdef __unix__
#define EOL '\n'
#elif _WIN32
#define EOL '\r\n'
#endif

export module IParserModule;

// CONSIDER:
// currently only one parser at a time is allowed,
// it would be cool if multiple at once are allowed

// interface for implementing a comment parser,
// a default parser is given,
// though it works for nearly all kinds of comment styles,
// some parsers can be implemented in a smarter way e.g. the CXXParser
// so overwriting is strongly encouraged
export class IParser
{
  public:
    virtual ~IParser() = default;

    // set the block comment delimiters
    virtual void set_block_delim(std::string open, std::string close)
    {
        m_open_block_delim = std::move(open);
        m_close_block_delim = std::move(close);
    };

    // set the line comment delimiter
    virtual void set_line_delim(char delim)
    {
        m_line_delim = delim;
    };

    // parse the read file content by the rules of a default parser
    // can be overwritten
    virtual bool parse(std::string buffer)
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
                    size_t current_line_end = line.find(m_open_block_delim, i);
                    if (current_line_end == std::string_view::npos)
                    {
                        // rest of line is inside block comment
                        i = line.size();
                        break;
                    }
                    block_comment = false;
                    i = current_line_end + m_open_block_delim.size();
                }
                else
                {
                    if (line[i] == m_line_delim && i + 1 < line.size())
                    {
                        break; // rest is line comment
                    }
                    if ((i + m_close_block_delim.size() - 1) < line.size() &&
                        line.substr(i, m_close_block_delim.size()) == m_close_block_delim)
                    {
                        // start block comment
                        block_comment = true;
                        i += m_close_block_delim.size();
                        continue;
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

    // get internal buffer
    virtual std::string get_buffer()
    {
        return m_buffer;
    };

  private:
    std::string m_buffer;

    std::string m_open_block_delim;
    std::string m_close_block_delim;
    char m_line_delim;
};
