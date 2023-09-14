#include<iostream>
#include<cstdlib>
#include<assert.h>

class UniversalMatrix4x4f  {
    protected:
        float matrix[16]; // change this to be generic
        unsigned int rows, columns;
    public:
        /* Universal Constructo. Initializes matrix as zero. */
        UniversalMatrix4x4f(unsigned int mrows = 4, unsigned int mcolumns = 4) :
        rows(mrows), columns(mcolumns) {
            
            for(auto &i : matrix) {
                i = 0;
            }
        }

        /* sets this matrix with size_t elements from the given vector.  */
        void setMatrix(float vector[], unsigned int size_t) {
            assert(size_t < rows*columns +1);
            for (int i = 0; i < size_t; i++) {
                matrix[i] = vector[i];
            }
        }

        // print functions for debugging pourposes
        void printM() {
            for (auto i : matrix) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
        }

        void print() {
            for (int i = 0; i < rows; i ++) {
                for (int  j = 0; j < columns; j++) {
                    std::cout << this->operator()(i, j) << " ";
                }
                std::cout << std::endl;
            }std::cout << std::endl;
        }

        // overloading () operator to make indexing: matrix(i, j) 
        float& operator()(unsigned int i, unsigned int j) {
            assert(i < 4 && j < 4);
            return (matrix[i*4 + j]);
        }

        UniversalMatrix4x4f operator+(UniversalMatrix4x4f& op) {
            assert(rows == op.rows && columns == op.columns);

            UniversalMatrix4x4f m(rows, columns);

            for (int i =0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    m(i, j) = this->operator()(i, j) + op(i, j);
                }
            }
            return m;
        }

        UniversalMatrix4x4f operator*(UniversalMatrix4x4f& op) {
            assert(columns == op.rows);

            UniversalMatrix4x4f r(rows, op.columns);

            for ( int i = 0; i < rows ; i++) {
                for (int j = 0; j< op.columns ; j++) {

                    for (int o = 0 ; o < columns ; o++) {
                        r(i, j) += this->operator()(i, o) * op(o, j);
                    }
                }
            }

            return r;
        }
};

class MatrixTranslation : public UniversalMatrix4x4f {

};

class MatrixRotation : public UniversalMatrix4x4f {

};

class MatrixScale : public UniversalMatrix4x4f {

};

class MatrixIdentity : public UniversalMatrix4x4f {

};

class Matrix : public UniversalMatrix4x4f {

};

