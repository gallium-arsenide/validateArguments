#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

namespace old
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
    virtual ~Argument() = default;
    virtual std::string getName() = 0;
    virtual int getNumberOfParameters() = 0;
    virtual ReturnCode validate(const Strings& args) = 0;
};

class ValidateArguments
{
public:
    ValidateArguments();
    int validate(const Strings& args);

private:
    void registerArgument(std::unique_ptr<Argument> arg);
    std::string toLowercase(const std::string& arg);

    std::map<std::string, std::unique_ptr<Argument>> arguments;
};
};
