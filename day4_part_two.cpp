#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 

using namespace std;



// Only works with this substring, expected substring length is 3
const string substring = "MAS";


uint findNumberOfOccurences(const vector<string>& lines, uint x, uint y) {
    if (x - 1 < 0 || y - 1 < 0 || x + 1 >= lines[0].size() || y + 1 >= lines.size()) {
        return 0;
    }

    bool checkFirstDiagonal = lines[y - 1][x - 1] == substring[0] && lines[y + 1][x + 1] == substring[2] ||
                              lines[y - 1][x - 1] == substring[2] && lines[y + 1][x + 1] == substring[0];
    bool checkSecondDiagonal = lines[y - 1][x + 1] == substring[0] && lines[y + 1][x - 1] == substring[2] ||
                              lines[y - 1][x + 1] == substring[2] && lines[y + 1][x - 1] == substring[0];
    
    if (checkFirstDiagonal && checkSecondDiagonal) {
        return 1;
    }

    return 0;    
}


int main() {
    ifstream inputFile ("day4_input.txt");

    if (!inputFile.is_open()) {
        cout << "Unable to open file" << endl;
        return 1;     
    }

    vector<string> lines;
    string line;
 
    while(getline(inputFile, line)) {
        lines.push_back(line);
    }

    inputFile.close();

    uint xCounter = 0;
    for (int x = 1; x < lines[0].size() - 1; x++) {
        for (int y = 1; y < lines.size() - 1; y++) {
            if (lines[y][x] == substring[1]) {
                xCounter += findNumberOfOccurences(lines, x, y);
            }
        }   
    }

    cout << xCounter << endl;

    return 0;
}
