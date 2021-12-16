#include <iostream>
#include "../utils/filereader.h"
#include <unordered_map>
#include <algorithm>
#include <sstream>

std::unordered_map<std::string,char> polymers;

uint64_t takeSteps(std::string s, int steps){
    std::unordered_map<std::string,uint64_t> counts;
    for(int i = 1; i < s.size(); i++){
        counts[{s[i-1],s[i]}]++;
    }

    for(int i = 0; i < steps; i++){
        auto it = counts.begin();

        std::unordered_map<std::string,uint64_t> counts2;
        while(it != counts.end()){
            char a = (*it).first.front();
            char b = polymers[(*it).first];
            char c = (*it).first.back();
            auto count = (*it).second;            
            counts2[{a,b}] += count;
            counts2[{b,c}] += count;
            it++;
        }
        counts = counts2;
    }

    std::unordered_map<char,uint64_t> elems{{s.back(),1}};
    for(auto&kv:counts){
        elems[kv.first.front()] += kv.second;
    }

    auto max = *(std::max_element(elems.begin(), elems.end(),
            [](const auto& l, const auto& r) { return l.second < r.second; }));
    auto min = *(std::min_element(elems.begin(), elems.end(),
            [](const auto& l, const auto& r) { return l.second < r.second; }));
         
    return max.second - min.second;
    
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
    std::cout << takeSteps(poly,10) << std::endl;
    std::cout << takeSteps(poly,40) << std::endl;
}