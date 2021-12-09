#include <iostream>
#include <vector>
#include "../utils/filereader.h"
#include <algorithm>

template <typename Comparator>
char commonBit(std::vector<std::string>& bits, int bit, Comparator comp){
        int c0 = 0, c1 = 0;
        for(int j = 0; j < bits.size(); j++){
            if(bits[j][bit] == '0')
                c0++;
            else
                c1++;
        }
        std::cout << c0 << "," << c1 << std::endl;
        if(c0 > 0 && comp(c0,c1))
            return '0';
        else
            return '1';
}

template <typename Comparator>
int commonBits(std::vector<std::string>& bits, Comparator comp){
    std::string result;
    for(int i = 0; i < bits[0].size() ; i++){
        result += commonBit(bits,i,comp);
    }
    return std::stoi(result, nullptr, 2);
}

template <typename Comparator>
int filterBits(std::vector<std::string> bits, Comparator comp){
    int numBits = bits[0].size();
    //consider the first bit first
    for(int i = 0; i < numBits ; i++){
        //find the bit matching criteria
        char c = commonBit(bits,i,comp);
        std::cout << c << std::endl;
        bits.erase(std::remove_if(bits.begin(), bits.end(), [&](std::string& s){return s[i] != c;}),bits.end());
        std::cout << bits.size() << std::endl;
        if(bits.size() == 1)
            break;
    }
    std::cout << bits.size() << std::endl;
    std::cout << bits.back() << std::endl;
    return std::stoi(bits.back(), nullptr, 2);
}

int main() {
    auto data = readLines("input.txt");
    //task 1
    //auto gammaRating = commonBits(data,std::greater<int>());
    //auto epsilonRating = commonBits(data,std::less<int>());
    //std::cout << gammaRating*epsilonRating << std::endl;
    //task 2
    //start with the full list of binary numbers
    std::greater<char> pred;
    std::cout << "pred: " << pred(114,151) << std::endl;
    auto oxygenRating = filterBits(data,std::greater<int>());
    auto co2Rating = filterBits(data,std::less_equal<int>());
    std::cout << oxygenRating << std::endl;
    std::cout << co2Rating << std::endl;
    std::cout << oxygenRating*co2Rating << std::endl;

}