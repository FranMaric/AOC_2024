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
// 3. At most one level can be unsafe for the whole report to be safe
//
bool isReportSafe(vector<int> report) {
    bool isGloballyIncreasing = true;
    bool hadUnsafeLevel = false;

    for (auto it = report.begin(); it != report.end(); ) {
        if (*it == *(it + 1) || abs(*it - *(it + 1)) > 3) {
            if (hadUnsafeLevel) {
                return false;
            } else {
                hadUnsafeLevel = true;
                report.erase(it);
                continue;
            }
        }

        bool isLocallyIncreasing = (*it - *(it + 1)) > 0;

        if (it == report.begin()) {
            isGloballyIncreasing = isLocallyIncreasing; 
        } else if (isGloballyIncreasing != isLocallyIncreasing) {
             if (hadUnsafeLevel) {
                return false;
            } else {
                hadUnsafeLevel = true;
                report.erase(it);
                continue;
            }
        }

        ++it;
    }

    return true;
}

bool isReportSafeWithOneRemoval(const vector<int>& report) {
    for (size_t i = 0; i < report.size(); ++i) {
        // Create a new report with the current level removed.
        vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i);

        // Check if the new report is safe.
        if (isReportSafe(modifiedReport)) {
            return true;
        }
    }
    return false;
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
        if (isReportSafeWithOneRemoval(report)) {
            safeReportCounter++;
        }
    }

    cout << safeReportCounter << endl;

    return 0;
}
