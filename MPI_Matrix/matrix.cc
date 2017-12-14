#include "matrix.h"

#include <stdexcept>
#include <iostream>
#include <fstream>
#include <utility>

namespace la{

    void Matrix::init_matrix(const size_t &row, const size_t &col, const double &init_val){
        size_t num = col * row;
        m_rows = row;
        m_cols = col;
        for (size_t i = 0; i < num; i++){
            m_data.push_back(init_val);
        }
    }

    Matrix::Matrix(const size_t &row, const size_t &col, const double &init_val){
        if (row > 0 && col > 0){
            init_matrix(row, col, init_val);
        }
        else{
            throw std::range_error("The size of Matrix must >= 1 * 1");
        }
    }

    Matrix::Matrix(const Matrix::m_size &sz, const double &init_val){
        size_t row = sz.first;
        size_t col = sz.second;
        if (row > 0 && col > 0){
            init_matrix(row, col, init_val);
        }
        else{
            throw std::range_error("The size of Matrix must >= 1 * 1");
        }    
    }
    
    Matrix::Matrix(const std::string & file_name){
        std::ifstream input;
        input.open(file_name);
        if (input.is_open()){
            input >> m_rows >> m_cols;
            double temp;
            while(input >> temp){
                m_data.push_back(temp);
            }
            size_t len = m_rows * m_cols;
            if (m_data.size() != len){
                throw std::invalid_argument("Please check if the format of \
                the matrix in the file is with correct format!");
            }
        }
        else{
            throw std::invalid_argument(file_name + " cannot be opened correctly!");
        }
        input.close();
    }

    size_t Matrix::pos2seq(const Matrix::m_size &sz){
        size_t r = sz.first;
        size_t c = sz.second;
        size_t seq = r * m_cols + c;
    }

    size_t Matrix::pos2seq(const size_t &r, const size_t &c){
        size_t seq = r * m_cols + c;
    }

    Matrix::m_size Matrix::seq2pos(const size_t &i){
        size_t r = i / m_cols;
        size_t c = i % m_cols;
        return Matrix::m_size(r,c);
    }

    void Matrix::print(bool with_size) const{
        if(with_size == true){
            std::cout << "n_rows: " << m_rows << ", n_cols: " << m_cols << std::endl;
        }
        size_t counter = 0;
        for (size_t i = 0; i < m_data.size(); i++){
            std::cout << m_data[i] << " " << std::flush;
            counter++;
            if (counter >= m_cols){
                std::cout << std::endl;
                counter = 0;
            }
        }      
    }

    template <typename T>
    void Matrix::print_vector(const std::vector<T> & current_vec) const{
        size_t sz = current_vec.size();
        if (sz >= 2){
            std::cout << "[" << current_vec[0] << ", " << std::flush;
            for (size_t i = 1; i < sz - 1; i++){
                std::cout << current_vec[i] << ", " << std::flush;           
            }
            std::cout << current_vec[sz - 1] << "]" << std::endl;
        }
        else if(sz == 1){
            std::cout << "[" << current_vec[0] << "]" << std::endl;
        }
        else{
            std::cout << "[ ]" << std::endl;
        }
    }

    double Matrix::get_val(const size_t &r, const size_t &c) const{
        size_t addr = r * m_cols + c;
        return m_data[addr];
    }

    double Matrix::get_val(const size_t &i) const{
        return m_data[i];
    }

    void Matrix::set_val(const size_t &r, const size_t &c, const double &val){
        size_t addr = r * m_cols + c;
        m_data[addr] = val;
    }

    void Matrix::set_val(const size_t &i, const double &val){
        m_data[i] = val;
    }

    Matrix::m_size Matrix::size() const{
        m_size sz(m_rows, m_cols);
        return sz;
    }

    size_t Matrix::get_n_rows() const{
        return m_rows;
    }

    size_t Matrix::get_n_cols() const{
        return m_cols;
    }

    std::vector<double> Matrix::operator[](const size_t &r_coor) const{
        std::vector<double> vec;
        for (size_t i=0; i < m_cols; i++){
            vec.push_back(get_val(r_coor, i));
        }
        return vec;
    }

    Matrix operator+(const Matrix &lhs, const Matrix &rhs){
        Matrix m(lhs.size());
        if (lhs.size() == rhs.size()){
            size_t len = lhs.get_n_rows() * lhs.get_n_cols();
            for (size_t i = 0; i < len; i++){
                Matrix::m_size pos = m.seq2pos(i);
                size_t cur_row = pos.first;
                size_t cur_col = pos.second;
                double temp = lhs[cur_row][cur_col] + rhs[cur_row][cur_col];
                m.set_val(i, temp);
            }
        }
        else{
            throw std::logic_error("Cannot sum up these \
            two matrice because of different size!");
        }
        return m;
    }

    Matrix operator*(const Matrix &lhs, const Matrix &rhs){

        size_t a = lhs.get_n_rows();
        size_t b1 = lhs.get_n_cols();
        size_t b2 = rhs.get_n_rows();
        size_t c = rhs.get_n_cols();
        Matrix m(a, c);

        if (b1 == b2){
            size_t b = b1;
            size_t len = a * c;
            for (size_t i = 0; i < len; i++){
                Matrix::m_size pos = m.seq2pos(i);
                size_t cur_row = pos.first;
                size_t cur_col = pos.second;
                double temp = 0;
                for (size_t k = 0; k < b; k++){
                    temp += (lhs[cur_row][k] * rhs[k][cur_col]);
                }
                m.set_val(cur_row, cur_col, temp);
            }
        }
        else{
            throw std::logic_error("Cannot multiply these two matrice \
            because the n_cols of lhs must be equal to n_rows of rhs!");
        }
        return m;
    }
}