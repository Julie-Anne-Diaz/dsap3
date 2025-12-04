#include <iostream>

#include "CampusCompass.h"

using namespace std;

int main() {
    // initialize your main project object
    CampusCompass compass;
    // ingest CSV data
    compass.ParseCSV("../data/edges.csv", "../data/classes.csv");
    // the below is example code for parsing commandline input
    int no_of_lines;
    string command;

    getline(cin, command);
    no_of_lines = stoi(command);
    std::string output;
    for (int i = 0; i < no_of_lines; i++) {
        getline(cin, command);
        // parse your commands however you see fit
        output+=compass.ParseCommand(command)+'\n';
    }
    std::cout << output;
}
