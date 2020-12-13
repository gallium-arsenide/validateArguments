#include "SimpleValidateArguments.h"

namespace simple
{

int ValidateArguments::validate(const simple::Strings &args)
{
    bool isHelp = false;

    if (args.empty())
    {
        return static_cast<int>(ReturnCode::Invalid);
    }

    auto it = args.begin();
    while(it != args.end())
    {
        std::string arg;
        std::transform(it->begin(), it->end(), std::back_inserter(arg),
                       [](const auto& c){return std::tolower(c);});

        if(arg == "--help")
        {
            isHelp = true;
        }
        else if (arg == "--name")
        {
            ++it;
            if (it == args.end())
            {
                return static_cast<int>(ReturnCode::Invalid);
            }
            auto name = *it;
            if (name.length() < 3 or name.length() > 10)
            {
                return static_cast<int>(ReturnCode::Invalid);
            }
        }
        else if (arg == "--count")
        {
            ++it;
            if(it == args.end())
            {
                return static_cast<int>(ReturnCode::Invalid);
            }

            int value = 0;
            try
            {
                value = std::stoi(*it);
            }
            catch (const std::exception& e)
            {
                return static_cast<int>(ReturnCode::Invalid);
            }

            if (value < 10 or value > 100)
            {
                return static_cast<int>(ReturnCode::Invalid);
            }
        }
        else
        {
            return static_cast<int>(ReturnCode::Invalid);
        }

        ++it;
    }

    if (isHelp)
    {
        return static_cast<int>(ReturnCode::Help);
    }
    return static_cast<int>(ReturnCode::Ok);
}
}
