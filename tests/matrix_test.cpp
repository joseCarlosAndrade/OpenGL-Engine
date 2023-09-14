#include"../include/Matrices.hpp"
#include<iostream>
#include<vector>

int main() {
    float a[2] = {1, 2};
    float b[3] = { 5, 5, 5};
    UniversalMatrix4x4f mat(4, 4);
    UniversalMatrix4x4f mat_b(4, 4);
    mat(0, 3) = 1;
    // std::cout << mat. << std::endl;
    mat.setMatrix(a, 2);
    mat_b.setMatrix(b, 3);
    mat.printM();
    mat_b.printM();

    UniversalMatrix4x4f mat_sum = mat + mat_b;
    mat_sum.printM();
    UniversalMatrix4x4f point(4, 1);
    point(0, 0) = 1;
    point(1, 0) = 3;
    point(2, 0) = 2;
    point.print();
    UniversalMatrix4x4f mat_mult = mat*point;
    mat_mult.print();
}