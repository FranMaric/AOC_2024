#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <vector> 


using namespace std;


void printReports(const vector<vector<int>>& reports) {
    for (const vector<int>& report : reports) {
        for (size_t i = 0; i < report.size(); ++i) {
            cout << report[i];
            if (i != report.size() - 1)
                cout << ',';
        }
        cout << '\n';
    }
}

// Rules
//
// 1. The levels are either all increasing or all decreasing.
// 2. Any two adjacent levels differ by at least one and at most three.
//
bool isReportSafe(const vector<int>& report) {
    bool isGloballyIncreasing = true;

    for (int i = 0; i < report.size() - 1; i++) {
        if (report[i] == report[i + 1]) {
            return false;
        }
        if (abs(report[i] - report[i + 1]) > 3) {
            return false;
        }

        // Check are all increasing or all decreasing
        bool isLocallyIncreasing = (report[i] - report[i + 1]) > 0;

        if (i == 0) {
            isGloballyIncreasing = isLocallyIncreasing; 
        } else if (isGloballyIncreasing != isLocallyIncreasing) {
            return false;
        }
    }

    return true;
}

int main() {
    ifstream inputFile ("day2_input.txt");

    if (!inputFile.is_open()) {
        cout << "Unable to open file";
        return 1;     
    }

    vector<vector<int>> reports;
    string line;
 
    while(getline(inputFile, line)) {
        stringstream iss(line);
        vector<int> levels;
        int number;
        while (iss >> number)
            levels.push_back(number);
        reports.push_back(levels);
    }

    inputFile.close();

    uint safeReportCounter = 0;
    for (const vector<int>& report: reports) {
        if (isReportSafe(report)) {
            safeReportCounter++;
        }
    }

    cout << safeReportCounter << endl;

    return 0;
}
