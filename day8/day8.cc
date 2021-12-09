#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <map>
#include <sstream>
#include <list>
#include <algorithm>
#include <unordered_map>
#include <cmath>

//convert string to key
int stok(std::string& s){
    int k = 0;
    for(auto&c:s){
        k += std::pow(2,c - 'a');
    }
    return k;
}

int task2(std::vector<std::string>& signals, std::vector<std::string>& digits){
    std::vector<std::string> lookup(10);
    std::vector<std::string> fives;
    std::vector<std::string> sixes;
    //unique signals can be deduced from the start
    //signals with 5 and 6 segments must be deduced
    for(auto& d: signals){
        switch (d.size())
        {
        case 2:
            lookup[1] = d;
            break;
        case 3:
            lookup[7] = d;
            break;
        case 4:
            lookup[4] = d;
            break;
        case 7:
            lookup[8] = d;
            break;
        case 5:
            fives.push_back(d);
            break;
        case 6:
            sixes.push_back(d);
            break;
        default:
            break;
        }
    }
    //from the sixes: 1 can be used to deduce 6. 4 can be used to deduce 9. remaining is 0.
    //1 will only have 1 common section with 6 etc..
    for(int i = 0; i < sixes.size(); i++){
        std::unordered_map<char,int> freq;
        for(auto& c: sixes[i])
            freq[c]++;
        
        if(!lookup[6].size()){
            auto one = lookup[1];
            for(auto& c: one){
                if(freq.count(c) == 0){
                    //the 6 is found
                    lookup[6] = sixes[i];
                    break;
                }
            }
            if(lookup[6].size())
                continue;
        }
        if(!lookup[0].size()){
            auto four = lookup[4];
            for(auto& c: four){
                if(freq.count(c) == 0){
                    //the 0 is found
                    lookup[0] = sixes[i];
                    break;
                }
            }
            if(lookup[0].size())
                continue;
        }
        lookup[9] = sixes[i];
    }

    for(int i = 0; i < fives.size(); i++){
        std::unordered_map<char,int> freq;
        for(auto& c: fives[i])
            freq[c]++;
        
        if(!lookup[3].size()){
            auto one = lookup[1];
            bool match = true;
            for(auto& c: one){
                if(freq.count(c) == 0){
                    match = false;
                    break;
                }
            }
            if(match){
                lookup[3] = fives[i];
                continue;
            } 
        } 
        auto four = lookup[4];
        int count = 0;
        for(auto& c: four){
            if(freq.count(c)){
                count++;
            }
        }
        if(count == 2){
            lookup[2] = fives[i];
        } else {
            lookup[5] = fives[i];
        }
    }

    std::unordered_map<int,int> m;
    for(int i = 0; i < lookup.size(); i++)
        m[stok(lookup[i])] = i;
    
    //process the digits using the generated map
    int result = 0;
    for(auto& query:digits){
        result *= 10;
        result +=m[stok(query)];
    }
    return result;
}

int task1(std::vector<std::vector<std::string>>& digits){
    int count = 0;
    for(auto& vec: digits){
        for(auto& line:vec){
            int size = line.size();
            if((size >= 2 && size <= 4) || size == 7)
                count++;
        }
    }
    return count;
}

int main() {
    auto data = readLines("input.txt");
    
    std::vector<std::vector<std::string>> signals;
    std::vector<std::vector<std::string>> outputs;
    for(auto& line:data){
        std::istringstream ss(line);
        {
            std::vector<std::string> vec;
            for(std::string s; ss >> s;){
                if(s == "|")
                    break;
                vec.push_back(s);
            }
            signals.push_back(vec);
        }
        {
            std::vector<std::string> vec;
            for(std::string s; ss >> s;)
                vec.push_back(s);
            outputs.push_back(vec);
        }
    }
    //task1
    std::cout << task1(outputs) << std::endl;

    //task2
    int result = 0;
    for(int i = 0; i < signals.size(); i++){
        result += task2(signals[i], outputs[i]);
    }
    std::cout << result << std::endl;
}