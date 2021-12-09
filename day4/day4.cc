#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <unordered_map>
#include "sstream"
#include <list>
struct Board {
    std::unordered_map<int,std::pair<int,int>> nums;
    std::vector<int> checks;
};

int sumBoard(Board& board){
    int sum = 0;
    for(auto kv: board.nums){
        sum += kv.first;
    }
    return sum;
}

std::list<Board> loadBoards(std::vector<std::string>& data){
    std::list<Board> boards;
    for(int i = 0; i*5+1 < data.size(); i++){
        Board board;
        board.checks.resize(5*2);
        for(int row = 0; row < 5; row++){
            std::istringstream ss(data[i*5+1+row]);
            for(int col = 0; col < 5; col++){
                int v;
                ss >> v;
                board.nums[v] = {row,col};
            }
        }
        boards.push_back(board);
    }
    return boards;
}

std::list<int> loadNumbers(std::vector<std::string>& data){
    std::list<int> drawNumbers;
    std::istringstream ss(data[0]);
    for(int i;ss >> i;){
        drawNumbers.push_back(i);
        ss.ignore(1);
    }
    return drawNumbers;
}

Board nextWinningBoard(std::list<Board>& boards, std::list<int>& nums){
    while(!nums.empty()){
        int v = nums.front();
        auto it = boards.begin();
        while(it != boards.end()){
            if((*it).nums.count(v) > 0){
                auto coord =  (*it).nums[v];
                (*it).nums.erase(v);
                int row = coord.first;
                int col = coord.second;
                (*it).checks[row]++;
                (*it).checks[col+5]++;
                if((*it).checks[row] == 5 || (*it).checks[5+col] == 5){
                    Board b =  *it;
                    boards.erase(it);
                    return b;
                }
            }
            it++;
        }
        nums.pop_front();
    }
}

int main() {
    auto data = readLines("input.txt");
    
    std::list<int> drawNumbers = loadNumbers(data);
    std::list<Board> boards = loadBoards(data);

    Board firstWinner = nextWinningBoard(boards,drawNumbers);
    std::cout << sumBoard(firstWinner)*drawNumbers.front()<<std::endl;
    Board lastBoard;
    while(boards.size()){
        lastBoard = nextWinningBoard(boards,drawNumbers);
    }
    std::cout << sumBoard(lastBoard)*drawNumbers.front()<<std::endl;
}