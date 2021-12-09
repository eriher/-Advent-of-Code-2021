#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <unordered_map>
#include <sstream>
#include <list>
#include <algorithm>

int task1(std::unordered_map<int,int>& freq){
    std::vector<int> costs(freq.size(),0);
    int i = 0;
    for(auto& kv: freq){
        int j = 0;
        for(auto& kv2:freq){
            if(i != j){
                costs[j] += abs(kv.first - kv2.first)*kv.second;
            }
            j++;
        }
        i++;
    }
    return *std::min_element(costs.begin(),costs.end());
}

int task2(std::unordered_map<int,int>& freq){
    int min = (*freq.begin()).first;
    int end = (*freq.end()).first;
    std::cout << min << "," << end << std::endl;
    std::vector<int> costs(end-min+1,0);
    for(auto& kv: freq){
        for(int i = min; i <= end; i++){
            if(kv.first == i)
                continue;
            int val = abs(kv.first - i);
            val = ((val*(val+1))/2);
            costs[i] += val*kv.second;
        }
    }
    return *std::min_element(costs.begin(),costs.end());
}

int main() {
    auto data = readInts("input.txt");
    std::unordered_map<int, int> freq;
    for(int i = 0; i < data.size(); i++)
        freq[data[i]]++;

    std::cout << task1(freq) << std::endl;
    std::cout << task2(freq) << std::endl;
}