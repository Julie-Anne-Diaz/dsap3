#pragma once
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <unordered_set>
using namespace std;

//classcode -> locationID
extern std::unordered_map<std::string, int> endTimes;
extern std::unordered_map<std::string,int> startTimes;
extern std::unordered_map<std::string, int> AllClasses;
//locationID -> location name
extern std::unordered_map<int, std::string> Locations;

struct Student {
    std::string name;
    std::string ID;
    int residence;
    std::unordered_set<std::string> classes;
    Student(){}
    Student(std::string n, std::string id, int l){name=n; ID=id; residence=l;}
};


class CampusCompass {
private:
    //adjacency matrix
    std::vector<std::vector<int>> map;
    //matrix of what paths are open
    std::vector<std::vector<bool>> open;
    //student id -> Student class pointer
    std::unordered_map<std::string,Student*> students;

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool insert(std::string n, std::string id, int residence, std::vector<std::string> c);
    bool remove(std::string id);
    bool drop(std::string id,std::string className);
    bool replace(std::string id, std::string class1, std::string class2);
    int removeClass(std::string className);
    void toggleEdge(std::vector<int> edges);
    std::string checkEdge(int p1, int p2);
    bool isConnected(int p1, int p2);
    std::map<std::string,int> shortestEdges(std::string id);
    int studentZone(std::string id);
    int shortestPath(int startLocation, int endLocation);
    std::string verifySchedule(std::string ID);
    std::string ParseCommand(const string &command);
};
