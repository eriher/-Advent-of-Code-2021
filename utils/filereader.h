#include <fstream>
#include <string>
#include <vector>

template <typename T>
static void readInput(std::string path, std::vector<T>& data){
    std::ifstream fs(path);
    if(!fs){
        std::cout << "File not found" << std::endl;
        return;
    }
    for(T v; fs >> v;)
        data.push_back(v);
}

template <typename T>
static std::vector<T> readInput(std::string path){
    std::ifstream fs(path);
    if(!fs){
        std::cout << "File not found" << std::endl;
        return {};
    }
    std::vector<T> data;
    for(T v; fs >> v;)
        data.push_back(v);
    return data;
}

static std::vector<std::string> readLines(std::string path){
    std::ifstream fs(path);
    if(!fs){
        std::cout << "File not found" << std::endl;
        return {};
    }
    std::vector<std::string> data;
    for(std::string s;getline(fs,s);)
    {
        if(s.size() > 0)
            data.push_back(s);
    }
    return data;
}

template<typename T1, typename T2>
static std::vector<std::pair<T1,T2>> readPairs(std::string path){
    std::ifstream fs(path);
    if(!fs){
        std::cout << "File not found" << std::endl;
        return {};
    }
    std::vector<std::pair<T1,T2>> data;
    while(fs && !fs.eof()){
        T1 s;
        T2 v;
        fs >> s;
        if(fs.eof())
            break;
        fs >> v;
        data.push_back(make_pair(s,v));
    }
        
    return data;
}

static std::vector<int> readInts(std::string path) {
    std::ifstream fs(path);
    if(!fs){
        std::cout << "File not found" << std::endl;
        return {};
    }
    std::vector<int> data;
    for(int i; fs >> i;){
        data.push_back(i);
        if(fs.eof())
            break;
        char c;
        fs >> c;
        if(c != ',')
            break;
    }
    return data;
}

// static std::vector<std::vector<int>> readGrid(std::string path){
//     std::ifstream fs(path);
//     if(!fs){
//         std::cout << "File not found" << std::endl;
//         return {};
//     }
//     std::vector<std::vector<int>> data;
//     for(int i; fs >> i;){
//         data.push_back(i);
//         if(fs.eof())
//             break;
//         char c;
//         fs >> c;
//         if(c != ',')
//             break;
//     }
//     return data;
// }