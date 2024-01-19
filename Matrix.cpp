#include <iostream>
#include "Matrix.hpp"

void Matrix::deallocate()
{
    for (int i{0}; i < rows; ++i)
    {
        delete[] elements[i];
    }
    delete[] elements;
    elements = nullptr;
    rows = 0;
    columns = 0;
}

void Matrix::allocate(size_t _rows, size_t _columns)
{
    elements = new char* [_rows]{};
    for (int i{0}; i < _rows; ++i)
    {
        elements[i] = new char[_columns]{};
    }
    rows = _rows;
    columns = _columns;
}

void Matrix::copy(const Matrix& other)
{
    if (rows != other.rows || columns != other.columns)
    {
        deallocate();
        allocate(other.rows, other.columns);
    }
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < columns; ++j)
        {
            elements[i][j] = other.elements[i][j];
        }
    }
}

Matrix::Matrix() : elements(nullptr), rows(0), columns(0)
{}

Matrix::Matrix(size_t _rows, size_t _columns) : elements(new char* [_rows]{}), rows(_rows), columns(_columns)
{
    for (int i{0}; i < _rows; ++i)
    {
        elements[i] = new char[_columns]{};
    }
}

Matrix::Matrix(const Matrix& other) : elements(nullptr), rows(other.rows), columns(other.columns)
{
    allocate(other.rows, other.columns);
    copy(other);
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        deallocate();
        allocate(other.rows, other.columns);
        copy(other);
    }
    return *this;
}

Matrix::~Matrix()
{
    deallocate();
}

void Matrix::print() const
{
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < columns; ++j)
        {
            std::cout << elements[i][j] << '\t';
        }
        std::cout << '\n';
    }
}

void Matrix::fillMatrix(char c)
{
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < columns; ++j)
        {
            elements[i][j] = c;
        }
    }
}

size_t Matrix::getRows() const
{
    return rows;
}

size_t Matrix::getColumns() const
{
    return columns;
}

