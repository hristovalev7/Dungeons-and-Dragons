#ifndef DUNGEONS_AND_DRAGONS_MATRIX_HPP
#define DUNGEONS_AND_DRAGONS_MATRIX_HPP

#include <cstddef>

class Matrix
{
private:
    char** elements;
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

    void print() const;

    void fillMatrix(char c);

    [[nodiscard]] size_t getRows() const;

    [[nodiscard]] size_t getColumns() const;
};


#endif //DUNGEONS_AND_DRAGONS_MATRIX_HPP
