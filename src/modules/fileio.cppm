module;

#include <filesystem>
#include <fstream>
#include <print>

export module FileIOModule;

export class FileIO final
{
public:
    explicit FileIO(const std::string &filename)
        : m_filename(filename),
          m_file(filename)
    {
        if (m_file.good())
        {
            try
            {
                m_file.open(m_filename);
            }
            catch (std::filesystem::filesystem_error const &e)
            {
                //std::println(e.what());
            }
        }
    };

    ~FileIO()
    {
        m_file.close();
    };

    // read into the internal buffer
    void read()
    {
        if (m_file.is_open())
        {
            // read file
        }
    };

    // write the internal buffer to a file
    void write()
    {
        if (m_file.is_open())
        {
            if (not m_out_filename.empty())
            {
                // write to out_filename
            }
            else
            {
                // write to m_filename
            }
        }
    };

    void set_out_filename(const std::string &out_filename)
    {
        m_out_filename = out_filename;
    }

    void set_content(const std::string &content)
    {
        m_content = content;
    }

    std::string get_content() const
    {
        return m_content;
    }

private:
    std::string m_filename;
    std::string m_out_filename;
    std::string m_content;
    std::ifstream m_file;
};
