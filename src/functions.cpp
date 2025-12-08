#include "functions.h"
#include <vector>
#include <limits>
#include <sstream>


/*UFIDs are strictly eight digits long and must be unique.
Names must include only alphabets from [a-z, A-Z, and spaces]
A students total classes must be between 1 to 6 (inclusive)
Class Codes must have 3 capital letters [A-Z] followed by 4 digits [0-9]
Any invalid or misspelled commands must be ignored with an “unsuccessful” message followed by executing the next command.*/
bool validName(std::string s) {
    for (char c : s) {
        if (!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return true;
}
bool validID(std::string i) {
    if (i.length()!=8) {
        return false;
    }
    return true;
}
bool isNumber(std::string s) {
    if (s.empty()) {
        return false;
    }
    for (char c : s) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
bool validClass(std::string s) {
    if (s.length()!=7) {
        return false;
    }
    for (int i = 0; i < 7; i++) {
        if (i < 3 && (!isalpha(s[i]) || !isupper(s[i]))) {
            return false;
        }
        if (i>=3 && !isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<int>> primMST(const std::vector<std::vector<int>>& MST, int location) {
    int n = MST.size();

    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));

    std::vector<int> key(n, std::numeric_limits<int>::max());
    std::vector<bool> inMST(n, false);
    std::vector<int> parent(n, -1);

    key[location] = 0;

    for (int count = 0; count < n - 1; count++) {


        int u = -1;
        int minVal = std::numeric_limits<int>::max();

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && key[v] < minVal) {
                minVal = key[v];
                u = v;
            }
        }
        if (u == -1) {
            break;
        }
        inMST[u] = true;

        for (int v = 0; v < n; v++) {
            int weight = MST[u][v];

            if (weight > 0 && !inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (parent[i] != -1) {
            int u = parent[i];
            int v = i;
            int w = MST[u][v];
            result[u][v] = w;
            result[v][u] = w;
        }
    }

    return result;
}

std::vector<std::string> SplitCommand(const std::string& command) {
    std::vector<std::string> word;
    std::istringstream iss(command);
    std::string token;

    while (iss >> token) {
        word.push_back(token);
        if (token.find('\"') != std::string::npos && token.substr(1).find('\"')==std::string::npos) {
            iss>>token;
            word[word.size()-1] += " " + token;
            while (token.find('\"') == std::string::npos) {
                iss>>token;
                word[word.size()-1] += " " + token;
            }
        }
    }

    return word;
}