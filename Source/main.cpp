#include <iostream>
#include <fstream>
#include <functional>
#include <map>
#include "JSONParser.h"
#include "AutoGrader.h"
#include "Testable.h"

// STUDENT: Be sure to update this path if necessary (should point to the repo directory)
inline std::string getWorkingDirectoryPath() {
    return ".";
}

bool runAutograderTest(const std::string& aPath, const std::string& aTestName) {
    ECE141::AutoGrader autoGrader(aPath);
    return autoGrader.runTest(aTestName);
}

bool runBasicTest(const std::string& aPath) {
    return runAutograderTest(aPath, "BasicTest");
}

bool runAdvancedTest(const std::string& aPath) {
    return runAutograderTest(aPath, "AdvancedTest");
}

int runTest(const int argc, const char* argv[]) {
    const std::string thePath = argc > 2 ? argv[2] : getWorkingDirectoryPath();
    const std::string theTest = argv[1];

    std::map<std::string, std::function<bool(const std::string&)>> theTestFunctions {
        { "compile", [](const std::string&) { return true; } },
        { "query", ECE141::runModelQueryTest },
        { "basic", runBasicTest },
        { "advanced", runAdvancedTest }
    };

    if (theTestFunctions.count(theTest) == 0) {
        std::clog << "Unkown test '" << theTest << "'\n";
        return 1;
    }

    const bool hasPassed = theTestFunctions[theTest](thePath);
    std::cout << "Test '" << theTest << "' " << (hasPassed ? "PASSED" : "FAILED") << "\n";
    return !hasPassed;
}

int main(const int argc, const char* argv[]) {
    if (argc > 1)
        return runTest(argc, argv);

    return 0;
}