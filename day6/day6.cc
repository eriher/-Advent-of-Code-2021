#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <map>
#include <sstream>
#include <list>
#include <algorithm>

std::map<std::pair<int,int>,long long int> lookup;
long long int helper(int n, int days){
    auto key = std::make_pair(n,days);
    if(lookup.count(key) > 0)
        return lookup[key];
    long long int count = 1;
    if(n > days)
        return 1;
    int day = n+1;
    while(day <= days)
    {
        count += helper(8,days-day);
        day += 7;
    }
    lookup[key] = count;
    return count;
}

int main() {
    auto data = readInts("input.txt");
    
    long long int task1 = 0;
    long long int task2 = 0;
    for(auto& d:data){
        task1 += helper(d,80);
    }
    
    for(auto& d:data){
        task2 += helper(d,256);
    }

    std::cout << task1 << std::endl;
    std::cout << task2 << std::endl;
    
}