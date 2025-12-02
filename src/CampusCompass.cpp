#include "CampusCompass.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

#include "functions.h"

using namespace std;

std::unordered_map<std::string, int> AllClasses;
std::unordered_map<int, std::string> Locations;

CampusCompass::CampusCompass() {}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    std::ifstream edges(edges_filepath);
    std::ifstream classes(classes_filepath);

    if (!edges.is_open()) {
        std::cerr << "Failed to open edges: " << edges_filepath << std::endl;
        return false;
    }
    if (!classes.is_open()) {
        std::cerr << "Failed to open edges: " << classes_filepath << std::endl;
        return false;
    }

    std::string line1;
    int max = 0;
    while (std::getline(edges, line1)) {
        std::vector<std::string> row;
        std::stringstream ss(line1);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }

        //first loc id and second loc id
        int pos1 = std::stoi(row[0]);
        int pos2 = std::stoi(row[1]);

        //resize vector if needed
        if (max<pos1) {
            max=pos1;
            for (size_t i = 0; i < map.size(); i++) {
                map[i].resize(max,-1);
                open[i].resize(max,false);
            }
            map.resize(max,std::vector<int>(max,-1));
            open.resize(max,std::vector<bool>(max,false));
        }
        if (max<pos2) {
            max=pos2;
            for (size_t i = 0; i < map.size(); i++) {
                map[i].resize(max,-1);
                open[i].resize(max,false);
            }
            map.resize(max,std::vector<int>(max,-1));
            open.resize(max,std::vector<bool>(max,false));
        }

        map[pos1][pos2]=std::stoi(row[4]);
        map[pos2][pos1]=std::stoi(row[4]);
        open[pos2][pos1]=true;
        open[pos1][pos2]=true;
        Locations[pos1]=row[2];
        Locations[pos2]=row[3];
    }
    edges.close();

    std::string line2;
    while (std::getline(classes, line2)) {
        std::vector<std::string> row;
        std::stringstream ss(line2);
        std::string cell;

        while (std::getline(ss, cell, ',')) {
            row.push_back(cell);
        }
        AllClasses[row[0]]=std::stoi(row[1]);
    }
    classes.close();
    return true;
}

bool CampusCompass::ParseCommand(const string &command) {
    std::vector<std::string> words = SplitCommand(command);
    if (words.empty()){
        std::cout<<"unsuccessful"<<std::endl;
        return false;
    }
    if (words[0]=="insert") {
        if (words.size()<6 || !isNumber(words[2]) || !isNumber(words[3]) || !isNumber(words[4]) || (int)words.size()-4!=std::stoi(words[4])) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        std::vector <std::string> c;
        for (size_t i = 5; i < words.size(); i++) {
            c.push_back(words[i]);
        }
        return insert(words[1],std::stoi(words[2]),std::stoi(words[3]),c);
    }
    if (words[0]=="remove") {
        if (words.size()!=2 || !isNumber(words[1]) || !validID(std::stoi(words[1]))) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        return remove(std::stoi(words[1]));
    }
    if (words[0]=="dropClass") {
        if (words.size()!=3 || !isNumber(words[1]) || !validID(std::stoi(words[1]))) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        return drop(std::stoi(words[1]),words[2]);
    }
    if (words[0]=="replaceClass") {
        if (words.size()!=4 || !isNumber(words[1]) || !validID(std::stoi(words[1]))) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        return replace(std::stoi(words[1]),words[2],words[3]);
    }
    if (words[0]=="removeClass") {
        if (words.size()!=2) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        std::cout<<removeClass(words[1])<<std::endl;
        return true;
    }
    if (words[0]=="toggleEdgesClosure") {
        if (words.size()<2 || !isNumber(words[1]) || (int)words.size()-2!=std::stoi(words[1])) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        std::vector<int> edges;
        for (size_t i = 2; i < words.size(); i++) {
            edges.push_back(std::stoi(words[i]));
        }
        toggleEdge(edges);
        std::cout<<"successful"<<std::endl;
        return true;
    }
    if (words[0]=="checkEdgeStatus") {
        if (words.size()!=3 || !isNumber(words[1]) || !isNumber(words[2])) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        std::cout<<checkEdge(std::stoi(words[1]),std::stoi(words[2]))<<std::endl;
        return true;
    }
    if (words[0]=="isConnected") {
        if (words.size()!=3 || !isNumber(words[1]) || !isNumber(words[2])) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        isConnected(std::stoi(words[1]),std::stoi(words[2]));
        return true;
    }
    if (words[0]=="printShortestEdges") {
        if (words.size()!=2 || !isNumber(words[1]) ||!validID(std::stoi(words[1]))) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        std::map<std::string,int> e = shortestEdges(std::stoi(words[1]));
        for (auto it = e.begin(); it != e.end(); ++it) {
            std::cout<<it->first<<" | Total Time: "<<it->second<<std::endl;
        }
        return true;
    }
    if (words[0]=="printStudentZone") {
        if (words.size()!=2 || !isNumber(words[1]) ||!validID(std::stoi(words[1]))) {
            std::cout<<"unsuccessful"<<std::endl;
            return false;
        }
        std::cout<<studentZone(std::stoi(words[1]))<<std::endl;
        return true;
    }
    return false;
}

bool CampusCompass::insert(std::string n, int id, int residence, std::vector<std::string> c) {
    if (!validID(id) || !validName(n) || students.count(id) || c.empty() || c.size()>6) {
        std::cout<<"unsuccessful"<<std::endl;
        return false;
    }
    students[id]=new Student(n,id,residence);
    for (std::string s : c) {
        students[id]->classes.insert(s);
    }
    std::cout<<"successful"<<std::endl;
    return true;
}
bool CampusCompass::remove(int id) {
    if (!students.count(id)) {
        std::cout<<"unsuccessful"<<std::endl;
        return false;
    }
    delete students[id];
    students.erase(id);
    std::cout<<"successful"<<std::endl;
    return true;
}

bool CampusCompass::drop(int id,std::string className) {
    if (!students.count(id) || !students[id]->classes.count(className) || !AllClasses.count(className)) {
        std::cout<<"unsuccessful"<<std::endl;
        return false;
    }
    students[id]->classes.erase(className);
    if (students[id]->classes.empty()) {
        remove(id);
    }
    std::cout<<"successful"<<std::endl;
    return true;
}
bool CampusCompass::replace(int id, std::string class1, std::string class2) {
    if (!students.count(id) || !students[id]->classes.count(class1) || students[id]->classes.count(class2) || !AllClasses.count(class2)) {
        std::cout<<"unsuccessful"<<std::endl;
        return false;
    }
    students[id]->classes.erase(class1);
    students[id]->classes.insert(class2);
    std::cout<<"successful"<<std::endl;
    return true;
}
int CampusCompass::removeClass(std::string className) {
    int count=0;
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->second->classes.count(className)) {
            drop(it->first,className);
            count++;
        }
    }
    return count;
}

void CampusCompass::toggleEdge(std::vector<int> edges) {
    for (size_t i = 0; i < edges.size()-1; i+=2) {
        if (open[edges[i]][edges[i+1]]==true) {
            open[edges[i]][edges[i+1]]=false;
            open[edges[i+1]][edges[i]]=false;
        }
        else {
            open[edges[i]][edges[i+1]]=true;
            open[edges[i+1]][edges[i]]=true;
        }
    }
}
std::string CampusCompass::checkEdge(int p1, int p2) {
    if (map[p1][p2]==-1) {
        return "DNE";
    }
    if (open[p1][p2]==false) {
        return "closed";
    }
    return "open";
}
bool CampusCompass::isConnected(int p1, int p2) {
    std::unordered_set<int> visited;
    std::queue<int> q;
    q.push(p1);
    visited.insert(p1);
    while (!q.empty()) {
        int temp = q.front();
        q.pop();
        for (size_t i = 0; i < map[temp].size(); i++) {
            if (open[temp][i]) {
                if ((int)i==p2) {
                    std::cout<<"successful"<<std::endl;
                    return true;
                }
                if (!visited.count(i)) {
                    visited.insert(i);
                    q.emplace(i);
                }
            }
        }
    }
    std::cout<<"unsuccessful"<<std::endl;
    return false;
}
std::map<std::string,int> CampusCompass::shortestEdges(int id) {
    //stores return times
    std::map<std::string,int> times;
    //location id -> distance
    std::unordered_map<int,int> distances;
    std::unordered_set<int> visited;

    //store locations of students classes
    std::unordered_set<int> classLocation;
    for (auto it = students[id]->classes.begin(); it != students[id]->classes.end(); ++it) {
        classLocation.emplace(AllClasses[*it]);
        times[*it]=-1;
    }

    distances[students[id]->residence]=0;
    while (!distances.empty()) {
        //pick value with the smallest distance
        int smallest = distances[0];
        int temp = 0;
        for (const auto& pair : distances) {
            if (pair.second>smallest) {
                smallest = pair.second;
                temp = pair.first;
            }
        }

        //if next removed is a class location store it
        if (classLocation.count(temp)) {
            times[Locations[temp]]=smallest;
        }

        //remove from distances and add to visited
        distances.erase(temp);
        visited.insert(temp);

        //check edges and adjust distances
        for (size_t i = 0; i < map[temp].size(); i++) {
            if (open[temp][i] && !visited.count(i)) {
                if (!distances.count(i) || smallest+map[temp][i]<distances[i]) {
                    distances[i]=smallest+map[temp][i];
                }
            }
        }
    }

    return times;
}

int CampusCompass::studentZone(int id) {
    //dikstras finds shortest paths for classes
    std::unordered_set<int> visited;
    std::unordered_map<int,int> distances;
    //visited->parent
    std::map<int,int> parents;


    parents[students[id]->residence]=-1;
    distances[students[id]->residence]=0;
    while (!distances.empty()) {
        //pick value with the smallest distance
        int smallest = distances[0];
        int temp = 0;
        for (const auto& pair : distances) {
            if (pair.second>smallest) {
                smallest = pair.second;
                temp = pair.first;
            }
        }

        //remove from distances and add to visited
        distances.erase(temp);
        visited.insert(temp);

        //check edges and adjust distances
        for (size_t i = 0; i < map[temp].size(); i++) {
            if (open[temp][i] && !visited.count(i)) {
                if (!distances.count(i) || smallest+map[temp][i]<distances[i]) {
                    distances[i]=smallest+map[temp][i];
                    parents[i]=temp;
                }
            }
        }
    }




    //from dikstras develop nodes needed make second graph and delete edges that connect to only 1 thing
    visited.clear();
    for (auto it = students[id]->classes.begin(); it != students[id]->classes.end(); ++it) {
        int temp = AllClasses[*it];
        while (parents[temp]!=-1) {
            visited.insert(parents[temp]);
            temp = parents[temp];
        }
    }

    std::vector<std::vector<int>> MST;
    MST.resize(map.size());
    for (auto it = visited.begin(); it != visited.end(); ++it) {
        for (auto it2 = it; it2 != visited.end(); ++it2) {
            if (map[*it][*it2]>0 && open[*it2][*it]) {
                MST[*it][*it2]=map[*it][*it2];
                MST[*it2][*it]=map[*it][*it2];
            }
        }
    }

    //prims finds MST
    MST = primMST(MST, students[id]->residence);
    //find cost of MST
    int sum = 0;
    for (size_t i = 0; i < MST.size(); i++) {
        for (size_t j = 0; j < MST[i].size(); j++) {
            sum += MST[i][j];
        }
    }
    sum/=2;
    return sum;

}


