#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <stack>
#include <unordered_map>
#include <algorithm>

std::unordered_map<char,int> task1Scores{{')',3},{']',57},{'}',1197},{'>',25137}};
std::unordered_map<char,int> task2Scores{{')',1},{']',2},{'}',3},{'>',4}};
std::unordered_map<char,char> matches{{')','('},{']','['},{'}','{'},{'>','<'},{'(',')'},{'[',']'},{'{','}'},{'<','>'}};

std::string::iterator checkCorrupt(std::string::iterator begin, std::string::iterator end){
    std::stack<char> hist;
    while(begin != end){
        char current = *begin;
        if(!task1Scores.count(current)){
            hist.push(current);
        } else {
            if(hist.empty() || hist.top() != matches[current]){
                return begin;
            }
            hist.pop();
        }
        begin++;
    }
    return end;
}

long long autoComplete(std::string::iterator begin, std::string::iterator end){
    std::stack<char> hist;
    while(begin != end){
        char current = *begin;
        if(!task1Scores.count(current)){
            hist.push(current);
        } else {
            if(hist.size())
                hist.pop();
        }
        begin++;
    }
    long long int result = 0;
    while(hist.size()){
        result *= 5;
        result += task2Scores[matches[hist.top()]];
        hist.pop();
    }
    return result;
}

int main() {
    auto lines = readLines("input.txt");
    int task1 = 0;
    std::vector<long long> task2;
    for(auto& line:lines){
        auto it = checkCorrupt(line.begin(),line.end());
        if(it != line.end())
            task1+=task1Scores[*it];
        else{
            auto t2 = autoComplete(line.begin(),line.end());
            if(t2 > 0)
                task2.push_back(t2);
        }
            
    }
    std::cout << task1 << std::endl;
    sort(task2.begin(),task2.end());
    std::cout << task2[task2.size()/2] << std::endl;
}