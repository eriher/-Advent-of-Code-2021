#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <unordered_set>

std::unordered_map<std::string,char> polymers;

std::string task1(char a, char b, int depth){    
    char c = polymers[{a,b}];
    if(depth < 2)
        return {a,c};
    return task1(a,c,depth-1)+task1(c,b,depth-1);    
}

int main() {
    auto lines = readLines("input.txt");
    while(lines.size() > 1)
    {
        std::istringstream ss(lines.back());
        std::string key;
        char val;
        ss >> key;
        ss.ignore(4);
        ss >> val;
        polymers[key] = val;
        lines.pop_back();
    }
    auto poly = lines.back();

    std::ostringstream result;
    for(int j = 1; j < poly.size(); j++){
        result << task1(poly[j-1],poly[j],15);
    }        
    result << poly.back();
    auto s = result.str();
    std::unordered_map<char,long long> freq;
    long long min = LLONG_MAX;
    long long max = 0;
    for(auto& c:s){
        freq[c]++;
    }
    for(auto&kv:freq){
        if(kv.second > max)
            max = kv.second;
        if(kv.second < min)
            min = kv.second;
    }
    std::cout << max-min << std::endl;
}