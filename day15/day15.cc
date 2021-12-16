#include <iostream>
#include "../utils/filereader.h"
#include <queue>
int m , n;

using Node = std::pair<int,std::pair<int,int>>;

void dijkstra(std::vector<std::string> graph, std::pair<int,int> src)
{
    std::vector<std::vector<int>> dist(graph.size(),std::vector<int>(graph[0].size(),INT_MAX)); 
    std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;
    dist[src.first][src.second] = 0;
    pq.push({0,src});
    std::vector<std::pair<int,int>> directions = {{-1,0},{1,0},{0,-1},{0,1}};

    while(!pq.empty()){
        auto top = pq.top();
        pq.pop();
        auto u = top.second;
        if(u.first == graph.size()-1 && u.second == graph[0].size()-1){
            break;
        }
        for(auto& dir:directions){
            int x = dir.first + u.first;
            int y = dir.second + u.second;
            if(x >= 0 && x < graph.size() && y >= 0 && y < graph[0].size()){
                if (dist[x][y] > dist[u.first][u.second] + (graph[x][y]-'0')){
                    dist[x][y] = dist[u.first][u.second] + (graph[x][y]-'0');
                    pq.push({dist[x][y],{x,y}});
                }
            }
        }
    }

    std::cout << dist.back().back() << std::endl;
}

void genRow(std::string& s){
    auto end = s.size();
    for(int j = n; j > 0; j--){
        int val = s[end-j] - '1';
        val = '1' + ((val+1) % 9);
        s += val;
    }    
}

std::vector<std::string> task2(std::vector<std::string> s){
    for(int i = 0; i < 4; i++){
        for(int r = 0; r < n; r++){
            genRow(s[r]);        
        }
    }
    for(int i = 0; i < 4; i++){
        auto sz = s.size();
        for(int i = n; i > 0; i--){
            std::string line = {s[sz-i].begin()+n,s[sz-i].end()};
            genRow(line);
            s.push_back(line);
        }
    }
    dijkstra(s,{0,0});
    return s;
}

int main() {
    auto lines = readLines("input.txt");
    n = lines.size();
    m = lines[0].size();
    dijkstra(lines,{0,0});
    lines = task2(lines);
}