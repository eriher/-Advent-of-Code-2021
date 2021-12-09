#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <unordered_map>
#include <sstream>
#include <list>

using Range = std::pair<std::pair<int,int>,std::pair<int,int>>;

void resizeField(std::vector<std::vector<int>>& field, int rows, int cols){
    int prevSize = field.size();
    if(rows >= field.size())
        field.resize(rows+1, std::vector<int>(cols+1,0));
    if(field[0].size() <= cols)
        for(int i = 0; i < prevSize; i++)
            field[i].resize(cols+1);
}

std::vector<std::vector<int>> createField(std::vector<Range>& data, bool diag){
    std::vector<std::vector<int>> field;

    for(auto& d:data){
        int x1 = d.first.first, x2  = d.second.first, y1 = d.first.second, y2 = d.second.second;
        if(x1 == x2){
            int fixed = x1;
            int start = y1 < y2 ? y1 : y2;
            int end = y1 < y2 ? y2 : y1;

            resizeField(field, fixed, end);
            for(int i = start; i <= end; i++){
                field[fixed][i]++;
            }
        } else if(y1 == y2){

            int fixed = y1;
            int start = x1 < x2 ? x1 : x2;
            int end = x1 < x2 ? x2 : x1;

            resizeField(field, end, fixed);
            for(int i = start; i <= end; i++){
                field[i][fixed]++;
            }
        } else if(diag) {

            int xe = x1 < x2 ? x2 : x1;
            int ye = y1 < y2 ? y2 : y1;

            resizeField(field, xe, ye);
            std::pair<int,int> start;
            std::pair<int,int> end;
            if(d.first.first < d.second.first){
                start = d.first;
                end = d.second;
            } else {
                start = d.second;
                end = d.first;
            }
            int mod = 1;
            if(start.second > end.second)
                mod = -1;
            while(start.first <= end.first){
                field[start.first][start.second]++;
                start.first++;
                start.second += mod;
            }
        }
    }
    return field;
}

std::vector<Range> createData(std::vector<std::string>& lines){
    std::vector<Range> result;
    for(auto& line:lines){        
        std::istringstream ss(line);
        int x1, x2, y1, y2;
        ss >> x1;
        ss.ignore(1);
        ss >> y1;
        ss.ignore(4);
        ss >> x2;
        ss.ignore(1);
        ss>> y2;
        result.push_back({{x1,y1},{x2,y2}});
    }
    return result;
}

int main() {
    auto lines = readLines("input.txt");
    auto data = createData(lines);
    std::vector<std::vector<int>> field = createField(data,false);
    std::vector<std::vector<int>> field2 = createField(data,true);
    int task1 = 0;
    int task2 = 0;
    for(int i = 0; i < field.size(); i++){
        for(int j = 0; j < field[0].size(); j++){
            if(field[i][j] > 1)
                task1++;
            if(field2[i][j] > 1)
                task2++;                
        }
    }
    std::cout << task1 << std::endl;
    std::cout << task2 << std::endl;
}