#include<iostream>
#include<cstdlib>
#include<assert.h>
#include<cmath>

class GenMatrix4x4f  {
    protected:
        float matrix[16]; // change this to be generic
        unsigned int rows, columns;
    public:
        /* Universal Constructor. Initializes matrix as zero. */
        GenMatrix4x4f(unsigned int mrows = 4, unsigned int mcolumns = 4) :
        rows(mrows), columns(mcolumns) {
            
            for(auto &i : matrix) {
                i = 0;
            }
        }

        /* Resize matrix (avoid using this, it may make you loose data) */
        void resize(unsigned int nrows, unsigned int ncolumns) {
            rows = nrows;
            columns = ncolumns;
        }

        /* Initializes this matrix with size_t elements from the given array. */
        void setMatrix(float array[], unsigned int size_t) {
            assert(size_t < rows*columns +1);
            for (int i = 0; i < size_t; i++) {
                matrix[i] = array[i];
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
                    std::cout << (*this)(i, j) << " ";
                }
                std::cout << std::endl;
            }std::cout << std::endl;
        }

        /* Gets the transpose matrix from this obj */
        GenMatrix4x4f getTranspose() {
            GenMatrix4x4f m(columns, rows);

            for (int i =0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    m(j, i) = (*this)(i, j);
                }
            }
            return m;
        }

        int getRows() {
            return rows;
        }

        int getColumns() {
            return columns;
        }

        float & operator[](std::pair<int , int> index){
            assert(index.first < 4 && index.second < 4);
            return (matrix[index.first*4 + index.second]);
            
        }


        // overloading () operator to make indexing: matrix(i, j) 
        float& operator()(unsigned int i, unsigned int j) {
            assert(i < 4 && j < 4);
            return (matrix[i*4 + j]);
        }

        GenMatrix4x4f operator+(GenMatrix4x4f& op) {
            assert(rows == op.rows && columns == op.columns);

            GenMatrix4x4f m(rows, columns);

            for (int i =0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    m(i, j) = (*this)(i, j) + op(i, j);
                }
            }
            return m;
        }

        GenMatrix4x4f operator-(GenMatrix4x4f& op) {
            assert(rows == op.rows && columns == op.columns);

            GenMatrix4x4f m(rows, columns);

            for (int i =0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    m(i, j) = (*this)(i, j) - op(i, j);
                }
            }
            return m;
        }

        GenMatrix4x4f operator*(GenMatrix4x4f& op) {
            std::cout << "assertion : " << columns << " " << op.rows << std::endl;
            assert(columns == op.rows);

            GenMatrix4x4f r(rows, op.columns);

            for ( int i = 0; i < rows ; i++) {
                for (int j = 0; j< op.columns ; j++) {

                    for (int o = 0 ; o < columns ; o++) {
                        r(i, j) += (*this)(i, o) * op(o, j);
                    }
                }
            }

            return r;
        }

        GenMatrix4x4f operator*(float scalar) {
            GenMatrix4x4f m(rows, columns);

            for (int i =0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    m(i, j) *= scalar;
                }
            }
            return m;
        }

        
};

/* ## Identity Matrix*/
class MatrixIdentity : public GenMatrix4x4f {
    public:
        MatrixIdentity(unsigned int size=4) {
            this->resize(size, size);

            for (int i = 0; i < rows; i++) {
                (*this)(i,i) = 1;
            }
        }
};

/* ## Translation matrix 
Inherits Universal Matrix to handle translation spacial transformations on the 3D Space.
*/
class MatrixTranslation : public GenMatrix4x4f {
    private:
        float *tx, *ty, *tz;

    public:
        MatrixTranslation(unsigned int size=4, float t_x=0, float t_y=0, float t_z=0) {
            this->resize(size, size);

            for (int i = 0; i < rows; i++) {
                (*this)(i,i) = 1;
            }

            tx = &(*this)(0, 3);
            ty = &(*this)(1, 3);
            tz = &(*this)(2, 3);

            *tx = t_x;
            *ty = t_y;
            *tz = t_z;
        }

        void x(float x) {
            *tx = x;
        }

        void y(float y) {
            *ty = y;
        }

        void z(float z) {
            *tz = z;
        }
            
        
};

/* Base class to be inherited by all rotation matrices */
class GenRotMat : public GenMatrix4x4f {
    protected:
        float ang;
    public:
        GenRotMat(unsigned int size=4, float angle) :  ang(angle) {
            this->resize(size, size);

            for (int i = 0; i < rows; i++) {
                (*this)(i,i) = 1;
            }
        }
    
};

class MatrixRotationX : public GenRotMat {
    public:
        void rot(float ang) {
            float s = sin(ang);
            float c = cos(ang);

            (*this)(1, 1) = c;
            (*this)(2, 2) = c;
            (*this)(1, 2) = s;
            (*this)(2, 1) = -s;
        }

        
};

class MatrixRotationY : public GenRotMat {
    public:
        void rot(float ang) {
            float s = sin(ang);
            float c = cos(ang);

            (*this)(0, 0) = c;
            (*this)(0, 2) = -s;
            (*this)(2, 0) = s;
            (*this)(2, 2) = c;
        }

        
};

class MatrixRotationZ : public GenRotMat {
    public:
        void rot(float ang) {
            float s = sin(ang);
            float c = cos(ang);

            (*this)(0, 0) = c;
            (*this)(0, 1) = -s;
            (*this)(1, 0) = s;
            (*this)(1, 1) = c;
        }
        
};

class MatrixScale : public GenMatrix4x4f {
    private:
        float *sx, *sy, *sz;
    public:
        MatrixScale(unsigned int size=4, float s_x =1, float s_y = 1, float s_z = 1) {
            this->resize(size, size);

            for (int i = 0; i < rows; i++) {
                (*this)(i,i) = 1;
            }
            sx = &(*this)(0, 3);
            sy = &(*this)(1, 3);
            sz = &(*this)(2, 3);

            *sx = s_x;
            *sy = s_y;
            *sz = s_z;
        }

        void x(float x) {
            *sx = x;
        }

        void y(float y) {
            *sy = y;
        }

        void z(float z) {
            *sz = z;
        }
};


class Matrix : public GenMatrix4x4f {

};

