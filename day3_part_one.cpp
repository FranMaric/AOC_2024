#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

int main() {
    std::string fileName = "day3_input.txt";

    std::ifstream inputFile(fileName);
    if (!inputFile) {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return 1;
    }

    std::string input((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
    inputFile.close();
    
    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

    auto begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto end = std::sregex_iterator();

    int result = 0;
    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;

        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());
        result += x * y;
    }

    std::cout << result << std::endl;
    
    return 0;
}
