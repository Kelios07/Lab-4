#include <iostream>

using namespace std;

class Vector;
class Matrix
{
private:
    int** m_matrix; 
    int m_rows, m_cols;

public:
    Matrix(int rows, int cols) : m_rows(rows), m_cols(cols)
    {
        cout << "Constructing Matrix of size " << m_rows << "x" << m_cols << '\n';
        m_matrix = new int* [m_rows];
        for (int i = 0; i < m_rows; ++i)
        {
            m_matrix[i] = new int[m_cols]();
        }
    }

    ~Matrix()
    {
        cout << "Destructing Matrix\n";
        for (int i = 0; i < m_rows; ++i)
        {
            delete[] m_matrix[i];
        }
        delete[] m_matrix;
    }

    friend Vector multiply(const Matrix& matrix, const Vector& vector);

    Matrix operator*(int scalar) const
    {
        Matrix result(m_rows, m_cols);
        for (int i = 0; i < m_rows; ++i)
        {
            for (int j = 0; j < m_cols; ++j)
            {
                result.m_matrix[i][j] = m_matrix[i][j] * scalar;
            }
        }
        return result;
    }

    Matrix operator*(const Matrix& other) const
    {
        if (m_cols != other.m_rows)
        {
            throw invalid_argument("Matrices of different sizes cannot be multiplied");
        }

        Matrix result(m_rows, other.m_cols);
        for (int i = 0; i < m_rows; ++i)
        {
            for (int j = 0; j < other.m_cols; ++j)
            {
                result.m_matrix[i][j] = 0;
                for (int k = 0; k < m_cols; ++k)
                {
                    result.m_matrix[i][j] += m_matrix[i][k] * other.m_matrix[k][j];
                }
            }
        }
        return result;
    }

    void print() const
    {
        for (int i = 0; i < m_rows; ++i)
        {
            for (int j = 0; j < m_cols; ++j)
            {
                cout << m_matrix[i][j] << ' ';
            }
            cout << '\n';
        }
    }
};

class Vector
{
private:
    int* m_vector; 
    int m_size;

public:
    Vector(int size) : m_size(size)
    {
        cout << "Constructing Vector of size " << m_size << '\n';
        m_vector = new int[m_size]();
    }

    ~Vector()
    {
        cout << "Destructing Vector\n";
        delete[] m_vector;
    }

    friend Vector multiply(const Matrix& matrix, const Vector& vector);

    Vector operator*(int scalar) const
    {
        Vector result(m_size);
        for (int i = 0; i < m_size; ++i)
        {
            result.m_vector[i] = m_vector[i] * scalar;
        }
        return result;
    }

    int operator*(const Vector& other) const
    {
        if (m_size != other.m_size)
        {
            throw invalid_argument("vectors are not the same, multiplication is impossible");
        }

        int result = 0;
        for (int i = 0; i < m_size; ++i)
        {
            result += m_vector[i] * other.m_vector[i];
        }
        return result;
    }

    void print() const
    {
        for (int i = 0; i < m_size; ++i)
        {
            cout << m_vector[i] << ' ';
        }
        cout << '\n';
    }
};

Vector multiply(const Matrix& matrix, const Vector& vector)
{
    if (matrix.m_cols != vector.m_size)
    {
        throw invalid_argument("A matrix and a vector cannot be multiplied, the number of columns must be equal to the vector");
    }

    Vector result(matrix.m_rows);
    for (int i = 0; i < matrix.m_rows; ++i)
    {
        for (int j = 0; j < matrix.m_cols; ++j)
        {
            result.m_vector[i] += matrix.m_matrix[i][j] * vector.m_vector[j];
        }
    }
    return result;
}

int main()
{
    Matrix mat(2, 2);
    Vector vec(2);

    Matrix mat2 = mat * 2;
    mat2.print();

    Vector vec2 = vec * 2;
    vec2.print();

    Vector resultVec = multiply(mat, vec);
    resultVec.print();

    Matrix mat3 = mat * mat2;
    mat3.print();

    int scalarProduct = vec * vec2;
    cout << "Scalar product of vectors: " << scalarProduct << '\n';

    return 0;
}
