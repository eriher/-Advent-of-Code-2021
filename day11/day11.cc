#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <sstream>

using Grid = std::vector<std::vector<int>>;

Grid parseLines(std::vector<std::string>& lines){
    Grid result;

    for(auto& line:lines){
        std::vector<int> vec;
        std::istringstream ss(line);
        for(char c; ss>>c;)
            vec.push_back(c-'0');
        result.push_back(vec);
    }

    return result;
}

int steps(Grid& data, int steps){
    int result = 0;
    while(steps > 0){
        std::vector<std::pair<int,int>> bloomers;
        for(int i = 0; i < data.size(); i++){
            for(int j = 0; j < data[i].size(); j++){
                data[i][j]++;
                if(data[i][j]==10){
                    bloomers.push_back({i,j});
                }
            }
        }

        while(bloomers.size()){
            auto coord = bloomers.back();
            bloomers.pop_back();
            for(int i = -1; i < 2; i++){
                for(int j = -1; j < 2; j++){
                    if(i==0 && j == 0)
                        continue;
                    int x = i + coord.first;
                    int y = j + coord.second;
                    if(x >= 0 && x < data.size() && y >= 0 && y < data[0].size()){
                        data[x][y]++;
                        if(data[x][y]==10){
                            bloomers.push_back({x,y});
                        }
                    }
                }
            }
        }
   
        for(int i = 0; i < data.size(); i++){
            for(int j = 0; j < data[i].size(); j++){
                if(data[i][j] > 9){
                    data[i][j] = 0;
                    result++;
                }
            }
        }
        steps--;
    }
    return result;
}

int sumGrid(Grid& data){
    int sum = 0;
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[0].size(); j++){
            sum += data[i][j];
        }
    }
    return sum;
}

int main() {
    auto lines = readLines("input.txt");
    auto data = parseLines(lines);

    std::cout << steps(data,100) << std::endl;
    int n = 0;
    while(sumGrid(data) != 0){
        steps(data,1);
        n++;
    }
    std::cout << n+100 << std::endl;
}