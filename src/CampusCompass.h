#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//classcode -> locationID
extern std::unordered_map<std::string, int> AllClasses;
//locationID -> location name
extern std::unordered_map<int, std::string> Locations;

struct Student {
    std::string name;
    int ID;
    int residence;
    std::unordered_set<std::string> classes;
    Student(){}
    Student(std::string n, int id, int l){name=n; ID=id; residence=l;}
};


class CampusCompass {
private:
    //adjacency matrix
    std::vector<std::vector<int>> map;
    //matrix of what paths are open
    std::vector<std::vector<bool>> open;
    //student id -> Student class pointer
    std::unordered_map<int,Student*> students;

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool insert(std::string n, int id, int residence, std::vector<std::string> c);
    bool remove(int id);
    bool drop(int id,std::string className);
    bool replace(int id, std::string class1, std::string class2);
    int removeClass(std::string className);
    void toggleEdge(std::vector<int> edges);
    std::string checkEdge(int p1, int p2);
    bool isConnected(int p1, int p2);
    std::map<std::string,int> shortestEdges(int id);
    int studentZone(int id);

    bool ParseCommand(const string &command);
};
