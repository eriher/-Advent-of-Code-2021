#include <iostream>
#include <vector>
#include <iterator>
#include "../utils/filereader.h"

template<typename Iterator>
int compare(Iterator start, Iterator end, int i){
    int count = 0;
    while(start+i != end){
        if(*start < *(start+i))
            count++;
        start++;
    }
    return count;
}

int main(){
    std::vector<int> data;
    readInput("input.txt",data);
    std::cout << compare(data.begin(), data.end(),1) << std::endl;
    std::cout << compare(data.begin(), data.end(),3) << std::endl;
}