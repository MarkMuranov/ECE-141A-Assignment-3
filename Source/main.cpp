#include <iostream>
#include "Result.h"

int main(int argc, const char* argv[]) {
    {
        auto theResult1 = ECE141::Result<int>::newOk(4);
        auto theResult2 = ECE141::Result<int>::newError("Uh oh!");

        std::cout << "Value of result1: " << theResult1.unwrapOr(20) << "\n";
        std::cout << "Value of result2: " << theResult2.unwrapOr(20) << "\n";
    }

    {
        auto theResult1 = ECE141::Result<std::string>::newOk("my value");
        auto theResult2 = ECE141::Result<std::string>::newError("Uh oh!");

        std::cout << "Value of result1: " << theResult1.unwrapOr("yay!") << "\n";
        std::cout << "Value of result2: " << theResult2.unwrapOr("yay!") << "\n";
    }

    return 0;
}