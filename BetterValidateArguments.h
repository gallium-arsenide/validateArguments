#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

namespace better
{
using Strings = std::vector<std::string>;

enum class ReturnCode
{
    Invalid = -1,
    Ok = 0,
    Help = 1
};

class Argument
{
public:
    struct Result
    {
        ReturnCode returnCode;
        Strings::const_iterator nextIterator;
    };

    virtual ~Argument() = default;
    virtual std::string getName() = 0;
    virtual Result validate(Strings::const_iterator first, Strings::const_iterator last) = 0;
};

class ValidateArguments
{
public:
    ValidateArguments();
    int validate(const Strings& args);

private:
    void registerArgument(std::unique_ptr<Argument> arg);
    std::string toLowercase(const std::string& str);
    bool isCritical(ReturnCode);
    ReturnCode getWithHigherPriority(ReturnCode first, ReturnCode second);

    std::map<ReturnCode, int> priority{{ReturnCode::Ok, 1},
                                       {ReturnCode::Help, 2},
                                       {ReturnCode::Invalid, 3}};
    std::map<std::string, std::unique_ptr<Argument>> arguments;
};
}
