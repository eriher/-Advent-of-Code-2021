#include <iostream>
#include <vector>
#include <iterator>
#include "../utils/filereader.h"
#include <sstream>



int task1(std::vector<std::pair<std::string,int>>& data){
    int x = 0, y = 0;
    for(auto& pair:data){
        if(pair.first == "forward") {
            x += pair.second;
        } else if(pair.first == "up"){
            y = std::max(0,y-pair.second);
        } else {
            y += pair.second;
        }
    }
    return x*y;
}

int task2(std::vector<std::pair<std::string,int>>& data){
    int x,y,aim;
    for(auto& pair:data){
        if(pair.first == "forward"){
            x += pair.second;
            y = std::max(0,y+pair.second*aim);
        } else {
            if(pair.first == "up"){
                aim -= pair.second;
            } else {
                aim += pair.second;
            }
        }
    }
    return x * y;
}

int main() {
    std::vector<std::pair<std::string,int>> data = readPairs<std::string,int>("input.txt");
    std::cout << task1(data) << std::endl;
    std::cout << task2(data) << std::endl;
}