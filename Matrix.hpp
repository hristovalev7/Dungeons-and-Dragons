#ifndef DUNGEONS_AND_DRAGONS_MATRIX_HPP
#define DUNGEONS_AND_DRAGONS_MATRIX_HPP

#include <iostream>
#include <cstddef>
#include "Direction.hpp"
#include "Cell.hpp"

template<typename T>
class Matrix
{
private:
    T** elements;
    size_t rows;
    size_t columns;

    void deallocate();

    void allocate(size_t _rows, size_t _columns);

    void copy(const Matrix& other);

public:
    Matrix();

    Matrix(size_t _rows, size_t _columns);

    Matrix(const Matrix& other);

    Matrix& operator=(const Matrix& other);

    ~Matrix();

    virtual void print() const;

    void fillMatrix(const char& c);

    [[nodiscard]] size_t getRows() const;

    [[nodiscard]] size_t getColumns() const;

    T getElement(unsigned int i, unsigned int j) const;

    void setElement(unsigned int i, unsigned int j, const T& element);

    void resize(size_t _rows, size_t _columns);

    [[nodiscard]] std::pair<unsigned int, unsigned int> getNeighbor(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const;

    [[nodiscard]] bool inBounds(std::pair<unsigned int, unsigned int> cell) const;
};


template<typename T>
void Matrix<T>::deallocate()
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

template<typename T>
void Matrix<T>::allocate(size_t _rows, size_t _columns)
{
    elements = new T* [_rows]{};
    for (int i{0}; i < _rows; ++i)
    {
        elements[i] = new T[_columns]{};
    }
    rows = _rows;
    columns = _columns;
}

template<typename T>
void Matrix<T>::copy(const Matrix<T>& other)
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

template<typename T>
Matrix<T>::Matrix() : elements(nullptr), rows(0), columns(0)
{}

template<typename T>
Matrix<T>::Matrix(size_t _rows, size_t _columns) : elements(new T* [_rows]{}), rows(_rows), columns(_columns)
{
    for (int i{0}; i < _rows; ++i)
    {
        elements[i] = new T[_columns]{};
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& other) : elements(nullptr), rows(other.rows), columns(other.columns)
{
    allocate(other.rows, other.columns);
    copy(other);
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other)
{
    if (this != &other)
    {
        deallocate();
        allocate(other.rows, other.columns);
        copy(other);
    }
    return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
    deallocate();
}

template<typename T>
void Matrix<T>::print() const
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

template<typename T>
void Matrix<T>::fillMatrix(const char& c)
{
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < columns; ++j)
        {
            elements[i][j] = c;
        }
    }
}

template<typename T>
size_t Matrix<T>::getRows() const
{
    return rows;
}

template<typename T>
size_t Matrix<T>::getColumns() const
{
    return columns;
}

template<typename T>
T Matrix<T>::getElement(unsigned int i, unsigned int j) const
{
    return elements[i][j];
}

template<typename T>
void Matrix<T>::setElement(unsigned int i, unsigned int j, const T& element)
{
    elements[i][j] = element;
}

template<typename T>
void Matrix<T>::resize(size_t _rows, size_t _columns)
{
    Matrix<T> matrix(_rows, _columns);
    *this = matrix;
}

template<typename T>
std::pair<unsigned int, unsigned int> Matrix<T>::getNeighbor(const std::pair<unsigned int, unsigned int>& cell, const Direction& direction) const
{
    std::pair<unsigned int, unsigned int> result{0, 0};
    switch (direction)
    {
        case Up:
            result = std::make_pair(cell.first - 1, cell.second);
            break;
        case Down:
            result = std::make_pair(cell.first + 1, cell.second);
            break;
        case Left:
            result = std::make_pair(cell.first, cell.second - 1);
            break;
        case Right:
            result = std::make_pair(cell.first, cell.second + 1);
            break;
        case Invalid:
            throw std::logic_error("Invalid direction given to Matrix::getNeighbor()\n");
    }
    return result;
}

template<typename T>
bool Matrix<T>::inBounds(std::pair<unsigned int, unsigned int> cell) const
{
    return cell.first < rows && cell.second < columns;
}

#endif //DUNGEONS_AND_DRAGONS_MATRIX_HPP
