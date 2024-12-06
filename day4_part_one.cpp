#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 

using namespace std;

const string substring = "XMAS";


uint findNumberOfHorizontalOccurences(const vector<string>& lines, uint x, uint y) {
   uint count = 0;

    // Check if substring fits to the right
    if (x + substring.size() <= lines[0].size()) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y][x + i] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    // Check if substring fits to the left
    if (x >= substring.size() - 1) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y][x - i] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    return count;}

uint findNumberOfVerticalOccurences(const vector<string>& lines, uint x, uint y) {
 uint count = 0;

    // Check if substring fits downwards
    if (y + substring.size() <= lines.size()) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y + i][x] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    // Check if substring fits upwards
    if (y >= substring.size() - 1) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y - i][x] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    return count;}

uint findNumberOfDiagonalOccurences(const vector<string>& lines, uint x, uint y) {
    uint count = 0;

    // Check diagonally down-right
    if (x + substring.size() <= lines[0].size() && y + substring.size() <= lines.size()) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y + i][x + i] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    // Check diagonally down-left
    if (x >= substring.size() - 1 && y + substring.size() <= lines.size()) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y + i][x - i] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    // Check diagonally up-right
    if (x + substring.size() <= lines[0].size() && y >= substring.size() - 1) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y - i][x + i] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    // Check diagonally up-left
    if (x >= substring.size() - 1 && y >= substring.size() - 1) {
        bool match = true;
        for (uint i = 0; i < substring.size(); i++) {
            if (lines[y - i][x - i] != substring[i]) {
                match = false;
                break;
            }
        }
        if (match) count++;
    }

    return count;
}


uint findNumberOfOccurences(const vector<string>& lines, uint x, uint y) {
    return findNumberOfHorizontalOccurences(lines, x, y) +
           findNumberOfVerticalOccurences(lines, x, y) +
           findNumberOfDiagonalOccurences(lines, x, y);
}


int main() {
    ifstream inputFile ("day4_input.txt");

    if (!inputFile.is_open()) {
        cout << "Unable to open file";
        return 1;     
    }

    vector<string> lines;
    string line;
 
    while(getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    uint substringCounter = 0;
    for (int x = 0; x < lines[0].size(); x++) {
        for (int y = 0; y < lines.size(); y++) {
            if (lines[y][x] == substring[0]) {
                substringCounter += findNumberOfOccurences(lines, x, y);
            }
        }   
    }

    cout << substringCounter << endl;

    return 0;
}
