#include <iostream>
#include <fstream>
#include "JSONParser.h"
#include "Model.h"

static const std::string getTestFolderPath() {
    return std::string("Resources");
}

int main(int argc, const char* argv[]) {
    //std::fstream theJSONFile(getTestFolderPath() + "/classroom.json");
    std::fstream theJSONFile("Resources/classroom.json");
    ECE141::JSONParser parser(theJSONFile);
    ECE141::Model theModel;
    parser.parse(&theModel);

    return 0;
}