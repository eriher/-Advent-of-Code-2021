#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <stack>
#include <unordered_map>
#include <algorithm>
#include <sstream>
#include <unordered_set>



std::vector<std::vector<char>> parseData(std::vector<std::string>& data){
    std::vector<std::vector<char>> result;
    int rows = 0, cols = 0;
    for(auto& line:data){
        std::istringstream ss(line);
        int x,y;
        char c;
        ss >> x;
        ss >> c;
        ss >> y;
        if(y >= rows){            
            result.resize(y+1);
            for(int i = rows; i < y+1; i++){
                result[i].resize(cols,'.');
            }
            rows = y+1;
        }
        if(x >= cols){
            cols = x+1;
            for(auto&vec:result)
                vec.resize(cols,'.');
        }
        result[y][x] = '#';
    }
    return result;
}

std::vector<std::pair<char,int>> parseInstructions(std::vector<std::string>& data){
    std::vector<std::pair<char,int>> result;
    auto it = data.back().find_first_of("=");
    while(it != std::string::npos){
        char dim = data.back()[it-1];
        int num = std::stoi(data.back().substr(it+1,data.back().size()-it));
        result.push_back({dim,num});
        data.pop_back();
        it = data.back().find_first_of("=");
    }
    return result;
}

std::vector<std::vector<char>> fold(const std::pair<char,int>& instr,const std::vector<std::vector<char>>&  paper){
    std::vector<std::vector<char>> result;

    if(instr.first == 'y'){
        int b = paper.size()-1;

        while(b > 2*instr.second){
            result.push_back(paper[b]);
            b--;
        }
        int midToEnd = 2*instr.second - paper.size();
        int a = 0;

        while(a <= midToEnd){
            result.push_back(paper[a]);
            a++;
        }

        while(a != instr.second && b != instr.second){
            std::vector<char> vec;
            for(int j = 0; j < paper[0].size(); j++){
                if(paper[a][j] == '#' || paper[b][j] == '#')
                    vec.push_back('#');
                else
                    vec.push_back('.');
            }
            result.push_back(vec);
            a++;
            b--;
        }
    } else {
        for(int i = 0; i < paper.size(); i++){
            std::vector<char> vec;
            int b = paper[0].size()-1;

            while(b > 2*instr.second){
                vec.push_back(paper[i][b]);
                b--;
            }

            int a = 0;
            int midToEnd = 2*instr.second - paper[0].size();
            while(a <= midToEnd){
                vec.push_back(paper[i][a]);
                a++;
            }

            while(a != instr.second && b != instr.second){
                if(paper[i][a] == '#' || paper[i][b] == '#')
                    vec.push_back('#');
                else
                    vec.push_back('.');
                a++;
                b--;
            }
            
            result.push_back(vec);
        }
    }
    return result;
}

int main() {
    auto lines = readLines("input.txt");
    auto instructions = parseInstructions(lines);
    auto paper = parseData(lines);

    paper = fold(instructions.back(),paper);
    instructions.pop_back();
    int task1 = 0;
    for(auto &vec:paper){
        for(auto& c: vec){
            if(c == '#')
                task1++;
        }
    }
    while(instructions.size()){
        paper = fold(instructions.back(),paper);
        instructions.pop_back();
    }
    std::cout << task1 << std::endl;
    for(auto &vec:paper){
        for(auto& c: vec){
            std::cout << c;
        }
        std::cout << std::endl;
    }

}