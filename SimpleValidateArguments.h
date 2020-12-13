#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <iostream>

namespace simple
{

using Strings = std::vector<std::string>;

enum class ReturnCode
{
    Invalid = -1,
    Ok = 0,
    Help = 1
};

class ValidateArguments
{
public:
    int validate(const Strings& args);
};
};
