#include <iostream>
#include <fstream>
#include "JSONParser.h"
#include "Model.h"
#include "AutoGrader.h"

// STUDENT: Be sure to update this path if necessary (should point to the repo directory)
inline std::string getWorkingDirectoryPath() {
    return ".";
}

int main(int argc, const char* argv[]) {
    ECE141::AutoGrader autoGrader(getWorkingDirectoryPath());
    autoGrader.runTest("BasicTest");

    std::string test = "select(test again)";
    ECE141::StringIterator it(test);
    std::cout << "Matches 'select': " << (it.matchesKeyword("select") ? "true" : "false") << "\n";
    std::cout << "(" << it.extractValueFromParenthesis() << ")\n";

    return 0;
}