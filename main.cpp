#include <iostream>
#include <vector>
#include <string>

#include "ValidateArguments.h"
#include "BetterValidateArguments.h"

void test(const std::vector<std::string>& args)
{
    auto val = old::ValidateArguments{};
    auto result = val.validate(args);

    auto val2 = better::ValidateArguments{};
    auto result2 = val2.validate(args);

    std::cout << "----------------------------------" << std::endl;
    std::cout << "Input:";
    for (const auto& arg : args)
    {
        std::cout << " \"" << arg <<"\"";
    }
    std::cout << std::endl;
    std::cout << "Output old: " << result << ", new: "<< result2 << std::endl;
    std::cout << "----------------------------------" << std::endl;
}


int main()
{
    test({});
    test({""});
    test({"--help"});
    test({"--hElP"});
    test({"--help invalid"});
    test({"--name"});
    test({"--name", "SOME_NAME"});
    test({"--name", "s"});
    test({"--name", "to long name so invalid"});
    test({"--count", "5"});
    test({"--count", "-2"});
    test({"--count", "13"});
    test({"--count", "invalid"});
    test({"--name", "SOME_NAME", "--count", "10"});
    test({"--name", "SOME_NAME", "--count", "10", "--help"});
    return 0;
}
