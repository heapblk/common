module;

#include <filesystem>
#include <fstream>
#include <print>
#include <utility>

export module FileIOModule;

export class FileIO final
{
public:
    explicit FileIO(std::string filename) : m_filename(std::move(filename))
    {
    };

    ~FileIO() = default;

    // read into the internal buffer
    [[nodiscard]] bool read()
    {
        std::ifstream file(m_filename);
        if (!file)
            return false;

        m_content.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        return true;
    };

    // write the internal buffer to a file
    [[nodiscard]] bool write() const
    {
        std::ofstream file(m_out_filename.empty() ? m_filename + ".com" : m_out_filename);
        if (!file)
            return false;

        file.write(m_content.data(), m_content.size());

        return true;
    };

    void set_out_filename(const std::string &out_filename)
    {
        m_out_filename = out_filename;
    }

    void set_filename(const std::string &filename)
    {
        m_filename = filename;
    }

    void set_content(const std::string &content)
    {
        m_content = content;
    }

    [[nodiscard]] std::string get_content() const
    {
        return m_content;
    }

private:
    std::string m_filename;
    std::string m_out_filename;
    std::string m_content;
};
