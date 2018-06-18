#include <iostream>
#include <string>

using namespace std;
#include "Matrix.h"

template <class T>
void Show(Matrix<T>** array, int size){
    for (int i = 0; i< size; i++){
        cout<< "Address: " << array[i] << endl;
        cout<< *(array[i]) << endl;
    }
}

int main() {
    int size = 5;
    Matrix<double> **array = new Matrix<double>*[size];
    for (int i = 0; i< size; i++){
        array[i] = new Matrix<double>();
    }
    Show(array, size);
    return 0;
}