#pragma once
#include <vector>
#include <string>

bool validName(std::string s);
bool validID(int i);
bool isNumber(std::string s);
bool validClass(std::string s);
std::vector<std::string> SplitCommand(const std::string& command);
std::vector<std::vector<int>> primMST(const std::vector<std::vector<int>>& MST, int location);