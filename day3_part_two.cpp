#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>


std::vector<size_t> findAllOccurrences(const std::string& str, const std::string& sub) {
    std::vector<size_t> indexes; // To store the indexes
    size_t pos = str.find(sub);  // Find the first occurrence

    while (pos != std::string::npos) {
        indexes.push_back(pos);  // Store the position
        pos = str.find(sub, pos + 1); // Find the next occurrence
    }

    return indexes;
}

struct Occurence {
    std::string substring;
    uint index;

    Occurence(const std::string& str, unsigned int idx)
        : substring(str), index(idx) {}
};


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

    const std::string doSubstring = "do()";   
    const std::string dontSubstring = "don't()";

    auto dontIndexes = findAllOccurrences(input, dontSubstring);
    auto doIndexes = findAllOccurrences(input, doSubstring);

    std::vector<Occurence> occurences;

    occurences.push_back( Occurence(doSubstring, 0) ); // Starts with do()

    uint size = dontIndexes.size() + doIndexes.size();

    for (int i = 0; i < size; i++) {
        if (dontIndexes.size() == 0) {
            occurences.push_back( Occurence(doSubstring, doIndexes[0]) );
            doIndexes.erase(doIndexes.begin());
        } else if (doIndexes.size() == 0) {
            occurences.push_back( Occurence(dontSubstring, dontIndexes[0]) );
            dontIndexes.erase(dontIndexes.begin());
        } else if (dontIndexes[0] < doIndexes[0]) {
            occurences.push_back( Occurence(dontSubstring, dontIndexes[0]) );
            dontIndexes.erase(dontIndexes.begin());
        } else {
            occurences.push_back( Occurence(doSubstring, doIndexes[0]) );
            doIndexes.erase(doIndexes.begin());
        }
    }

    auto begin = std::sregex_iterator(input.begin(), input.end(), pattern);
    auto end = std::sregex_iterator();

    int result = 0;
    for (std::sregex_iterator i = begin; i != end; ++i) {
        std::smatch match = *i;

        while (true) {
            if (occurences.size() == 1) { break; }
            if (occurences.size() > 1 && occurences[1].index > match.position()) { break; }
            occurences.erase(occurences.begin());
        }

        if (occurences[0].substring == dontSubstring) continue;

        int x = std::stoi(match[1].str());
        int y = std::stoi(match[2].str());
        result += x * y;
    }

    std::cout << result << std::endl;
    
    return 0;
}
