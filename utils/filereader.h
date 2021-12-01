#include <fstream>
#include <string>
#include <vector>
#include <iterator>


template <typename T>
static void readInput(std::string path, std::vector<T>& data){
    std::ifstream fs("input.txt");
    if(!fs){
        std::cout << "File not found" << std::endl;
        return;
    }
    std::copy(std::istream_iterator<T>(fs),
        std::istream_iterator<T>(),
        std::back_inserter(data));
}