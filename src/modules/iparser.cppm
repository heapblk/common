module;

#include <string>

export module IParserModule;

// CONSIDER:
// currently only one parser at a time is allowed,
// it would be cool if multiple at once are allowed
//
// also the way the parser interface is designed is
// really not scalable
export class IParser
{
public:
    virtual ~IParser() = default;

    // parse the read file content by the rules of a parser
    virtual bool parse(std::string) = 0;

    // get the parsed content
    virtual std::string get_content() = 0;
};
