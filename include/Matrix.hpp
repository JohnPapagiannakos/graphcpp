#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <array>

template <typename T, std::size_t rows, std::size_t columns>
class Matrix
{
    protected:
    const std::array<size_t, 2> _Dimensions;

    std::size_t _Rows;

    std::size_t _Cols;

    std::array<std::array<T, columns>, rows> Data;

    public:
    Matrix() : _Dimensions({rows,columns}), _Rows(rows), _Cols(columns) {}

    inline T &operator()(size_t i, size_t j) { 
        if( (i>=0) && (i<_Rows) && (j>=0) && (j<_Cols) ) 
        {
            return Data[i][j]; 
        }
        else
        {
            std::cerr << "Out of bounds!" << std::endl;
            return Data[0][0];
        }
    }

    Matrix &operator=(const Matrix &M)
    {
        if (this == &M)
        {
            return *this;
        }

        if (_Rows != M._Rows || _Cols != M._Cols_)
        {
           std::cerr << "_Rows != M._Rows || _Cols != M._Cols_" << std::endl;
        }

        for (size_t row = 0; row < _Rows; row++)
        {
            for (size_t col = 0; col < _Cols; col++)
            {
                Data[row][col] = M.Data[row][col];
            }
        }
        return *this;
    }

    void setConstant(int value_type)
    {
        for (size_t row = 0; row < _Rows; row++)
        {
            for (size_t col = 0; col < _Cols; col++)
            {
                Data[row][col] = value_type;
            }
        }
    }

    void Print(void)
    {
        for (size_t row = 0; row < _Rows; row++)
        {
            for (size_t col = 0; col < _Cols; col++)
            {
                std::cout << Data[row][col] << "\t";
            }
            std::cout << std::endl;
        }
    }

    ~Matrix(){ }
};

template <std::size_t rows, std::size_t columns>
class AdjacencyMatrix : public Matrix<int, rows, columns>
{
    public:
    AdjacencyMatrix() : Matrix<int, rows, columns>() {setZero();}

    void setZero(void)
    {
        Matrix<int, rows, columns>::setConstant(0);
    }

    void setOnes(void)
    {
        Matrix<int, rows, columns>::setConstant(1);
    }
};

#endif