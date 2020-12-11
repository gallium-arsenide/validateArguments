#include "BetterValidateArguments.h"
#include <algorithm>

namespace better
{

class ArgumentBase : public Argument
{
public:
    ArgumentBase(std::string name, size_t numberOfparameters)
        : name{std::move(name)}, numberOfparameters{numberOfparameters}
    {}

    virtual std::string getName() override
    {
        return name;
    }

    Result validate(Strings::const_iterator begin, Strings::const_iterator end) override
    {
        if (not hasEnoughParameters(begin, end))
        {
            return {ReturnCode::Invalid, end};
        }
        auto code = validateSpecific(begin, begin + numberOfparameters);
        auto next = begin + numberOfparameters;
        return {code, next};
    }

protected:
    virtual ReturnCode validateSpecific(Strings::const_iterator begin, Strings::const_iterator end) = 0;

private:
    bool hasEnoughParameters(Strings::const_iterator first, Strings::const_iterator last)
    {
        size_t size = std::distance(first, last);
        return size >= numberOfparameters;
    }

    const std::string name;
    const size_t numberOfparameters;
};

class HelpArgument : public ArgumentBase
{
public:
    HelpArgument() : ArgumentBase{"--help", 0}
    {}

protected:
    ReturnCode validateSpecific(Strings::const_iterator, Strings::const_iterator) override
    {
        return ReturnCode::Help;
    }
};

class NameArgument : public ArgumentBase
{
public:
    NameArgument() : ArgumentBase{"--name", 1}
    {}

protected:
    ReturnCode validateSpecific(Strings::const_iterator first, Strings::const_iterator) override
    {
        if (not hasGoodLength(*first))
        {
            return ReturnCode::Invalid;
        }
        return ReturnCode::Ok;
    }

private:
    bool hasGoodLength(const std::string& str)
    {
        return str.length() >= 3 and str.length() <= 10;
    }
};

class CountArgument : public ArgumentBase
{
public:
    CountArgument() : ArgumentBase{"--count", 1}
    {}

protected:
    ReturnCode validateSpecific(Strings::const_iterator first, Strings::const_iterator) override try
    {
        auto value = std::stoi(*first);
        if (not isInRange(value))
        {
            return ReturnCode::Invalid;
        }
        return ReturnCode::Ok;
    }
    catch (const std::exception& e)
    {
        return ReturnCode::Invalid;
    }

private:
    bool isInRange(int value)
    {
        return value >= 10 and value <= 100;
    }
};

ValidateArguments::ValidateArguments()
{
    registerArgument(std::make_unique<HelpArgument>());
    registerArgument(std::make_unique<NameArgument>());
    registerArgument(std::make_unique<CountArgument>());
}

void ValidateArguments::registerArgument(std::unique_ptr<Argument> arg)
{
    arguments[arg->getName()] = std::move(arg);
}

std::string ValidateArguments::toLowercase(const std::string& str)
{
    std::string output;
    std::transform(str.begin(), str.end(), std::back_inserter(output), [](const auto& c){return std::tolower(c);});
    return output;
}

int ValidateArguments::validate(const Strings& args)
{
    auto result = ReturnCode::Ok;

    if (args.empty())
    {
        return static_cast<int>(ReturnCode::Invalid);
    }

    auto it = args.begin();
    auto last = args.end();
    while (it != last and not isCritical(result))
    {
        auto name = toLowercase(*it);
        auto validatorIt = arguments.find(name);
        if (validatorIt == arguments.end())
        {
            return static_cast<int>(ReturnCode::Invalid);
        }

        auto& validator = *(validatorIt->second);
        auto partialResult = validator.validate(it + 1, last);

        result = getWithHigherPriority(result, partialResult.returnCode);
        it = partialResult.nextIterator;
    }

    return static_cast<int>(result);
}

bool ValidateArguments::isCritical(ReturnCode code)
{
    return code == ReturnCode::Invalid;
}

ReturnCode ValidateArguments::getWithHigherPriority(ReturnCode first, ReturnCode second)
{
    if (priority[first] > priority[second])
    {
        return first;
    }
    return second;
}

}
