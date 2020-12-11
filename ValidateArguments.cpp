#include "ValidateArguments.h"
#include <algorithm>

namespace old
{
class HelpArgument : public Argument
{
public:
    std::string getName() override
    {
        return name;
    }

    int getNumberOfParameters() override
    {
        return parameters;
    }

    ReturnCode validate(const Strings&) override
    {
        return ReturnCode::Help;
    }

private:
    const std::string name = "--help";
    const int parameters = 0;
};

class NameArgument : public Argument
{
public:
    std::string getName() override
    {
        return name;
    }

    int getNumberOfParameters() override
    {
        return parameters;
    }

    ReturnCode validate(const Strings& params) override
    {
        auto str = params[0];
        if (str.length() < 3 or str.length() > 10)
        {
            return ReturnCode::Invalid;
        }
        return ReturnCode::Ok;
    }

private:
    const std::string name = "--name";
    const int parameters = 1;
};

class CountArgument : public Argument
{
public:
    std::string getName() override
    {
        return name;
    }

    int getNumberOfParameters() override
    {
        return parameters;
    }

    ReturnCode validate(const Strings& params) override try
    {
        auto value = std::stoi(params[0]);

        if (value < 10 or value > 100)
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
    const std::string name = "--count";
    const int parameters = 1;
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

std::string ValidateArguments::toLowercase(const std::string& arg)
{
    std::string output;
    std::transform(arg.begin(), arg.end(), std::back_inserter(output), [](const auto& c){return std::tolower(c);});
    return output;
}

int ValidateArguments::validate(const std::vector<std::string>& args)
{
    auto result = ReturnCode::Ok;

    if (args.empty())
    {
        return static_cast<int>(ReturnCode::Invalid);
    }

    auto it = args.begin();
    while (it != args.end())
    {
        auto name = toLowercase(*it);
        auto argValidator = arguments.find(name);
        if (argValidator == arguments.end())
        {
            // invalid argument
            return static_cast<int>(ReturnCode::Invalid);
        }
        ++it;

        auto parametersNeeded = argValidator->second->getNumberOfParameters();
        if (std::distance(it, args.end()) < parametersNeeded)
        {
            // not enough parameters
            return static_cast<int>(ReturnCode::Invalid);
        }

        Strings partial{};
        for (int i=0; i<parametersNeeded; ++i)
        {
            partial.push_back(*it);
            ++it;
        }
        auto partialResult = argValidator->second->validate(partial);
        if (partialResult == ReturnCode::Invalid)
        {
            return static_cast<int>(partialResult);
        }
        if (partialResult == ReturnCode::Help)
        {
            result = partialResult;
        }
    }

    return static_cast<int>(result);
}
}
