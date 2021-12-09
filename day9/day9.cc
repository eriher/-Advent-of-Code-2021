#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <algorithm>
#include <cmath>
#include <queue>

//find lowpoints by checking neighbours
std::vector<std::pair<int,int>> findLowPoints(std::vector<std::string>& data){
    std::vector<std::pair<int,int>> result;
    std::vector<std::pair<int,int>> adj = {{-1,0},{1,0},{0,-1},{0,1}};
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[i].size(); j++){
            bool lowPoint = true;
            for(auto& a:adj){
                int x = i+a.first;
                int y = j+a.second;
                if(x >= 0 && x < data.size() && y >= 0 && y < data[i].size()){
                    if(data[i][j] >= data[x][y]){
                        lowPoint = false;
                        break;
                    }
                }
            }
            if(lowPoint)
            {
                result.push_back(std::make_pair(i,j));
            }
        }
    }
    return result;
}

//sum the lowpoints
int task1(std::vector<std::string> data, std::vector<std::pair<int,int>> lowPoints){
    int risk = 0;
    for(auto& lp: lowPoints){
        risk += (data[lp.first][lp.second] -'0')+1;
    }
    return risk;
}

//bfs from each lowpoint
int task2(std::vector<std::string>& data, std::vector<std::pair<int,int>>& lowPoints){    
    std::vector<std::vector<bool>> visited(data.size(),std::vector<bool>(data[0].size(),false));
    std::vector<int> sizes;
    std::vector<std::pair<int,int>> adj = {{-1,0},{1,0},{0,-1},{0,1}};
    for(auto& lp:lowPoints){
        int size = 0;
        std::queue<std::pair<int,int>> q;
        q.push(lp);
        visited[lp.first][lp.second] = true;
        while(q.size()){
            auto current = q.front();
            q.pop();
            int i = current.first;
            int j = current.second;
            for(auto& a:adj){
                int x = i+a.first;
                int y = j+a.second;
                if(x >= 0 && x < data.size() && y >= 0 && y < data[i].size()){
                    if(data[x][y] != '9' && !visited[x][y]){
                        visited[x][y] = true;
                        q.push(std::make_pair(x,y));
                    }
                }
            }
            size++;
        }
        sizes.push_back(size);
    }
    sort(sizes.begin(),sizes.end());
    int result = 1;
    for(int i = 0; i < 3; i++){
        result *= sizes.back();
        sizes.pop_back();
    }
    return result;
}

int main() {
    auto data = readLines("input.txt");
    auto lowPoints = findLowPoints(data);        
    std::cout << task1(data,lowPoints) << std::endl;
    std::cout << task2(data,lowPoints) << std::endl;
}