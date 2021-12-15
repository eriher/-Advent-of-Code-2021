#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <unordered_set>

std::unordered_map<std::string,std::vector<std::string>> adjecencies;

void parseLines(std::vector<std::string>& lines,char splitter){
    for(auto& line:lines){
        std::istringstream ss(line);
        std::string l;
        std::string r;
        for(char c; ss >> c;){
            if(c == splitter)
                break;
            l += c;
        }
        ss >> r;
        adjecencies[l].push_back(r);
        adjecencies[r].push_back(l);
    }
}

int task1(std::vector<std::string>& path, std::unordered_set<std::string>& visited) {
    auto node = path.back();
    int result = 0;
    if(node == "end")
    {
        return 1;
    }
    for(auto& adj:adjecencies[node]){
        if(!visited.count(adj)){
            path.push_back(adj);
            if(std::islower(adj[0])){
                visited.insert(adj);
            }
            result += task1(path,visited);
            if(std::islower(adj[0])){
                visited.erase(adj);
            }
            path.pop_back();
        }
    }
    return result;
}

int task2(std::vector<std::string>& path, std::unordered_set<std::string>& visited) {
    auto node = path.back();
    if(node == "end")
    {
        return 1;
    }
    int result = 0;
    for(auto& adj:adjecencies[node]){
        if(adj != "start"){
            path.push_back(adj);
            if(visited.count(adj)){
                result += task1(path,visited);
            } else {
                if(std::islower(adj[0])){
                    visited.insert(adj);
                }
                result += task2(path,visited);
                if(std::islower(adj[0])){
                    visited.erase(adj);
                }
            }
            path.pop_back();
        }
    }
    return result;
}

int main() {
    auto lines = readLines("input.txt");
    parseLines(lines, '-');
    std::vector<std::string> path{"start"};
    std::unordered_set<std::string> visited{"start"};
    std::cout << task1(path,visited) << std::endl;
    std::cout << task2(path,visited) << std::endl;
}