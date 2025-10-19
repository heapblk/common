module;

export module IParserModule;

export class IParser
{
public:
    virtual ~IParser() = default;

    virtual void parse() = 0;
};
