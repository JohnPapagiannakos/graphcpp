#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <array>
#include <cassert>
template <typename T>
class Matrix
{
    protected:
    const std::array<size_t, 2> _Dimensions;

    std::size_t _Rows;

    std::size_t _Cols;

    T **Data;

    public:
    Matrix(std::size_t rows, std::size_t columns) : _Dimensions({rows,columns}), _Rows(rows), _Cols(columns) { allocate();}
    Matrix() : _Dimensions({1,1}), _Rows(1), _Cols(1) {allocate();}

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

        if (_Rows != M._Rows || _Cols != M._Cols)
        {
           std::cerr << "_Rows != M._Rows || _Cols != M._Cols" << std::endl;
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

    size_t Rows()
    {
        return _Rows;
    }

    size_t Cols()
    {
        return _Cols;
    }

    void allocate(void)
    {
        Data = new T *[_Rows];
        for (size_t row = 0; row < _Rows; ++row)
        {
            Data[row] = new T[_Cols];
            assert(Data[row]);
        }
    }

    void deallocate(void)
    {
        // for (size_t row = 0; row < _Rows; row++)
        // {
        //     delete[] Data[row];
        // }
        // delete[] Data;
        delete[] Data[0];
        delete[] Data;
        Data = nullptr;
    }

    // ~Matrix()
    // {
    //     deallocate();
    // }
};

class AdjacencyMatrix : public Matrix<int>
{
    public:
    AdjacencyMatrix(std::size_t rows, std::size_t columns) : Matrix(rows, columns) { Matrix<int>::allocate(); setZero();}
    AdjacencyMatrix() : Matrix() { Matrix<int>::allocate(); setZero(); }

    void setZero(void)
    {
        Matrix<int>::setConstant(0);
    }

    void setOnes(void)
    {
        Matrix<int>::setConstant(1);
    }

    AdjacencyMatrix transpose(void)
    {
        AdjacencyMatrix M(_Cols, _Rows);
        for (size_t row = 0; row < Matrix<int>::_Rows; row++)
        {
            for (size_t col = 0; col < Matrix<int>::_Cols; col++)
            {
                M(col, row) = Matrix<int>::Data[row][col];
            }
        }
        return M;
    }

    // ~AdjacencyMatrix()
    // {
    //     // Matrix<int>::deallocate();
    // }
};

#endif