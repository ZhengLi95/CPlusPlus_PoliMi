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
    bool has_name(const std::string &);
    void err_has_no_such_name(const std::string &);
    std::string get_column_names(char= ' ');

    public:
    DataFrame(const std::string &);
    size_t size();
    void set_column(const std::string &, const std::vector<T> &);
    void set_element_at(const std::string &, const size_t &, const T &);
    double get_mean(const std::string &);
    DataFrame<T> select_equal(const std::string &, const T &);
    void print();
    
};

template <typename T>
size_t DataFrame<T>::size(){
    return n_rows;
}

template <typename T>
bool DataFrame<T>::has_name(const std::string & name){
    if (df_data.find(name) == df_data.end()){
        return false;
    }
    else{
        return true;
    }
}

template <typename T>
void DataFrame<T>::err_has_no_such_name(const std::string & name){
    std::cerr << "Cannot find key: " << name << " in this DataFrame object!" << std::endl;
}

template <typename T>
std::string DataFrame<T>::get_column_names(char s){
    std::string str = "";
    for(auto pair : df_data){
        str = str + pair.first + s;
    }
    str.erase(str.size() - 1, 1);
    return str;
}

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
    n_rows = 0;
    std::vector<std::string> names = split(s);
    for (std::string name : names){
        std::vector<T> current_col;
        df_data.insert(std::make_pair(name, current_col));
        n_rows++;
    }
}

template <typename T>
void DataFrame<T>::print(){
    for (df_column current_col : df_data){
        std::cout << current_col.first << ": ";
        size_t sz = current_col.second.size();
        if (sz >= 2){
            std::cout << "[" << current_col.second[0] << ", ";
            for (size_t i = 1; i < sz - 1; i++){
                std::cout << current_col.second[i] << ", ";           
            }
            std::cout << current_col.second[sz - 1] << "]" << std::endl;
        }
        else if(sz == 1){
            std::cout << "[" << current_col.second[0] << "]" << std::endl;
        }
        else{
            std::cout << "[ ]" << std::endl;
        }

    }
}

template <typename T>
void DataFrame<T>::set_column(const std::string& name, const std::vector<T>& new_value){
    if (has_name(name)){
        df_data[name] = new_value;
    }
    else{
        err_has_no_such_name(name);
    }
}

template <typename T>
void DataFrame<T>::set_element_at(const std::string& name, const size_t& pos, const T& val){
    if (has_name(name)){
        if (df_data[name].size() > pos){
            df_data[name][pos] = val;
        }
        else{
            std::cerr << "The position of the data: " << pos << " is not legal!" << std::endl;
        }
    }
    else{
        err_has_no_such_name(name);
    }
}

template <typename T>
double DataFrame<T>::get_mean(const std::string& name){
    if (has_name(name)){
        std::vector<T> current_vec = df_data[name];
        double avg = 0;
        for(T elem : current_vec){
            avg += elem;
        }
        avg /= current_vec.size();
        return avg;
    }
    else{
        this->err_has_no_such_name(name);
    }
}

template <typename T>
DataFrame<T> DataFrame<T>::select_equal(const std::string & name, const T & val){
    std::string names = get_column_names();
    DataFrame<T> current_df(names);
    if (has_name(name)){
        std::vector<T> current_vec = df_data[name];
        std::vector<size_t> positions;
        for(size_t i = 0; i < current_vec.size(); i++){
            if (current_vec[i] == val){
                positions.push_back(i);
            }
        }
        for(size_t pos : positions){
            for(df_column col : df_data){
                std::string col_name = col.first;
                std::vector<T> col_vals = col.second;
                std::cout << col_vals[pos] << std::endl;
                current_df.df_data[col_name].push_back(col_vals[pos]);
            }
        }
        std::cout << "size: " << current_df.size() << " " << current_df.df_data[name].size() << std::endl;
        current_df.print();
    }
    else{
        err_has_no_such_name(name);
    }
    return current_df;
}

#endif
