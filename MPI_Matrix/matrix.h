#include <string>
#include <vector>
#include <utility>

namespace la{

    class Matrix{

        // In this Matrix Class I use an 1 dimensional vector to simulate the structure of 2 dimensional
        // matrix. However, I suggest to use vector<vector<double>>, or there will be some troubles while
        // overloading the [] operator.

        friend Matrix operator*(const Matrix &lhs, const Matrix &rhs);
        friend Matrix operator+(const Matrix &lhs, const Matrix &rhs);

        public:
        
        typedef std::pair<size_t, size_t> m_size;

        private:

        std::vector<double> m_data;
        size_t m_rows;
        size_t m_cols;

        template <typename T>
        void print_vector(const std::vector<T> &) const;
        void print_dashline(unsigned) const;
        void init_matrix(const size_t &, const size_t &, const double & = 0.);
        double find_max() const;
        unsigned cal_highest_pos(double) const;

        std::vector<double> operator[](const size_t &r_coor) const;
        
        public:
        
        Matrix() = default;
        Matrix(const size_t &, const size_t &, const double & = 0.);
        Matrix(const m_size &, const double & = 0.);
        Matrix(const std::string &);

        void read(const std::string &);
        void print(bool with_size= false, bool with_dashline= true, unsigned dig= 2) const;

        double get_val(const size_t &, const size_t &) const;
        double get_val(const size_t &) const;
        void set_val(const size_t &, const size_t &, const double &);
        void set_val(const size_t &, const double &);

        m_size size() const;
        size_t get_n_rows() const;
        size_t get_n_cols() const;
        std::vector<double>::pointer get_data();
        std::vector<double>::const_pointer get_data() const;
        size_t pos2seq(const m_size &);
        size_t pos2seq(const size_t &, const size_t &);       
        m_size seq2pos(const size_t &);   
       
    };

    Matrix operator+(const Matrix &lhs, const Matrix &rhs);
    Matrix operator*(const Matrix &lhs, const Matrix &rhs);

}
