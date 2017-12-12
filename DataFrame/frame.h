#ifndef FRAME_H
#define FRAME_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <sstream>

template <typename T>
class DataFrame{

    typedef std::pair<std::string,std::vector<T>> df_column;
    typedef std::unordered_map<std::string, std::vector<T>> df_container;

    private:

    df_container df_data;
    bool first_column_added;
    size_t n_rows;
    int dummy;
    
    std::vector<std::string> split(const std::string &, char= ' ');

    public:
    DataFrame();
    DataFrame(const std::string &);
    void print();

};


template <typename T>
std::vector<std::string> DataFrame<T>::split(const std::string& s, char d){
    std::string word;
    std::vector<std::string> v;
    std::istringstream columns(s);
    while (std::getline (columns, word, d)) v.push_back (word);
    return v;
}

template <typename T>
DataFrame<T>::DataFrame(const std::string& s){
    std::vector<std::string> names = split(s);
    df_container df_data;
    for (std::string name : names){
        std::vector<T> current_col;
        auto ret = df_data.insert(std::make_pair(name, current_col));
        if (ret.second == true){
            std::cout << "SUCCESS" << std::endl;
        }
        else{
            std::cout << "FAIL" << std::endl;
        }
    }
    
    for (auto elem : df_data){
        std::cout << "AAAA" << std::endl;
    }
    
    df_data.insert(std::make_pair("test", std::vector<T>()));
    
    for (auto elem : df_data){
        std::cout << "CCCC" << std::endl;
    }
    
    for (auto current_col : df_data){
        std::cout << current_col.first << " : ";
        std::cout << "[";
        for (T elem : current_col.second){
            std::cout << elem << ",";
        }
        std::cout << "]" << std::endl;
    }
}

template <typename T>
void DataFrame<T>::print(){
    
    df_data.insert(std::make_pair("vaffanculo!", std::vector<T>()));

    for (const auto & elem : df_data){
        std::cout << "BBBB" << std::endl;
    }

    std::cout << "Almeno che il mio class funziona..." << std::endl;

    for (auto current_col : df_data){
        std::cout << current_col.first << " : ";
        std::cout << "[";
        for (T elem : current_col.second){
            std::cout << elem << ",";
        }
        std::cout << "]" << std::endl;
    }
}

#endif
