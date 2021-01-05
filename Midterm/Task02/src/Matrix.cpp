/**
 * Nicholas Colonna
 */
#include "Matrix.h"

Matrix::Matrix(int rows, int columns)
    : m_rows{ rows }
    , m_columns{ columns }
{
    m_data = vector<vector<int>>(m_rows, vector<int>(m_columns));
}

Matrix::Matrix(const vector<vector<int>>& data)
{
    m_data = data;
    m_rows = m_data.size();
    m_columns = m_data[0].size();
}

int Matrix::rows() const
{
    return m_rows;
}

int Matrix::columns() const
{
    return m_columns;
}

int& Matrix::position(int row, int column)
{
    if (0 > row && m_rows <= row && 0 > column && m_columns <= column)
        error("out of bounds");

    return m_data[row][column];
}

//Addition operator overload
Matrix Matrix::operator +(Matrix &second) {
    if (this->m_columns != second.columns() || this->m_rows != second.rows()) {       //if dimensions are different, give error and return 0s
        cout << "Cannot add matrices of different dimensions.\n";
        return Matrix(0, 0);
    }
    //else do the addition
    Matrix *result = new Matrix(this->m_rows, this->m_columns);         //create result matrix of correct size
    for (int i = 0; i < this->m_rows; ++i) {
        for (int j = 0; j < this->m_columns; ++j) {
            result->position(i, j) = this->position(i, j) + second.position(i, j);      //do addition for each position of matrix
        }
    }
    return *result;
}

//Multiplication operator overload
Matrix Matrix::operator *(Matrix &second){
    if (this->m_columns != second.rows() && this->m_rows != second.columns()) {       //if dimensions are different, give error and return 0s
        cout << "Cannot multiply these matrices because they do not share a dimension.\n";
        return Matrix(0, 0);
    }
    Matrix *result = new Matrix(this->m_rows, second.columns());
    for (int i = 0; i < result->rows(); ++i) {
        for (int j = 0; j < result->columns(); ++j) {
            for(int k=0; k < this->m_columns; ++k){
                result->position(i, j) += this->position(i, k) * second.position(k, j);
            }
        }
    }
    return *result;
}

ostream& operator<<(ostream& os, Matrix& m)
{
    for (int i = 0; i < m.rows(); ++i) {
        for (int j = 0; j < m.columns(); ++j) {
            os << m.position(i, j) << '\t';
        }
        if (i < m.rows() - 1) {
            os << '\n';
        }
    }

    return os;
}
