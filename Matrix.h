#include <iostream>
#include <string>
#include <vector>

using namespace std;
string error_size = "Different sizes";


template <class T = double>
class Matrix {
private:
    static unsigned int counter;
    unsigned int name;
    T** a;
    int m=2,n=2;
    void allocSpace() {
        a = new T*[m];
        for (int i=0; i < m; i++){
            a[i] = new T[n];
            for(int j=0; j < n; j++){
                a[i][j]=0;
            }
        }
    }
    Matrix<T> expHelper(const Matrix<T>& m, int num) {
        if (num == 0) {
            return createIdentity(m.m);
        } else if (num == 1) {
            return m;
        } else if (num % 2 == 0) {  // num is even
            return expHelper(m * m, num/2);
        } else {                    // num is odd
            return m * expHelper(m * m, (num-1)/2);
        }
    }
    bool CheckPlus(const Matrix<T>& object) {
        if(m==object.m&&n==object.n){
            return true;
        } else {
            return false;
        }
    }
    bool CheckMultiply(const Matrix<T>& object) {
        if(n==object.m){
            return true;
        } else {
            return false;
        }
    }
public:
    Matrix<T>() {
        allocSpace();
        counter++;
        name = counter;
    }
    Matrix<T>(int _m, int _n) {
        m=_m; n=_n;
        allocSpace();
        counter++;
        name = counter;
    }
    Matrix<T>(const Matrix<T> &object) {
        m=object.m; n=object.n;
        allocSpace();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = object.a[i][j];
            }
        }
        counter++;
        name = counter;
    }
    ~Matrix(){
        delete(a);
        counter--;
    }
    friend ostream& operator<<(ostream &out, const Matrix<T> &object) {
        cout<<"Matrix: #"<<object.name<<endl;
        for (int i=0; i < object.m; i++){
            out<<"| ";
            for(int j=0; j < object.n; j++){
                out<<object.a[i][j]<<" ";
            }
            out<<"|"<<endl;
        }
        return out;
    }
    friend istream& operator>>(istream &in, const Matrix<T> &object){
        for (int i=0; i < object.m; i++){
            for(int j=0; j < object.n; j++){
                in>>object.a[i][j];
            }
        }
        return in;
    }
    Matrix<T>& operator+=(const Matrix<T>& object) {
        if(CheckPlus(object)) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] += object.a[i][j];
                }
            }
            return *this;
        }
        else{
            throw error_size;
        }
    }
    Matrix<T>& operator-=(const Matrix<T>& object) {
        if(CheckPlus(object)) {
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    a[i][j] -= object.a[i][j];
                }
            }
            return *this;
        } else{
            throw error_size;
        }
    }
    Matrix<T>& operator*=(const Matrix<T>& object) {
        if(CheckMultiply(object)) {
            Matrix<T> temp(m, object.n);
            for (int i = 0; i < temp.m; ++i) {
                for (int j = 0; j < temp.n; ++j) {
                    for (int k = 0; k < n; ++k) {
                        temp.a[i][j] += (a[i][k] * object.a[k][j]);
                    }
                }
            }
            return (*this = temp);
        }else{
            throw error_size;
        }
    }
    Matrix<T>& operator*=(double num) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] *= num;
            }
        }
        return *this;
    }
    Matrix<T>& operator/=(double num) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] /= num;
            }
        }
        return *this;
    }
    Matrix<T> operator^(int num) {
        if(CheckPlus(*this)){
            Matrix<T> temp(*this);
            return expHelper(temp, num);
        }else{
            throw error_size;
        }
    }
    Matrix<T> createIdentity(int size) {
        Matrix<T> temp(size, size);
        for (int i = 0; i < temp.m; ++i) {
            for (int j = 0; j < temp.n; ++j) {
                if (i == j) {
                    temp.a[i][j] = 1;
                } else {
                    temp.a[i][j] = 0;
                }
            }
        }
        return temp;
    }
    Matrix<T> transpose() {
        Matrix<T> temp(m, n);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                temp.a[j][i] = a[i][j];
            }
        }
        return temp;
    }
    bool operator==(Matrix<T> const &right ){
        if(n!= right.n || m!=right.m){
            return false;
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if(a[i][j] != right.a[i][j])
                    return false;
            }
        }
        return true;
    }
    bool operator!=(Matrix<T> const &right ){
        return !operator==(right);
    }
    T getSumOfColumn(int _n){
        T sum=0;
        for(int i=0; i < m; i++){
            sum+=a[i][_n];
        }
        return sum;
    }
    T getSumOfRow(int _m){
        T sum=0;
        for(int i=0; i < m; i++){
            sum+=a[_m][i];
        }
        return sum;
    }
    T findMaxElement(){
        T max=a[0][0];
        for(int i=0; i < m; i++){
            for(int j=0; j < n; j++){
                if(a[i][j]>max) max = a[i][j];
            }
        }
        return max;
    }
    T findMinElement(){
        T min=a[0][0];
        for(int i=0; i < m; i++){
            for(int j=0; j < n; j++){
                if(a[i][j]<min) min = a[i][j];
            }
        }
        return min;
    }
    vector<T> getVector(){
        vector<T> vector1(n);
        for(int j=0; j < n; j++){
            T min=a[0][j];
            for(int i=0; i < n; i++){
                if(a[i][j]<min) min = a[i][j];
            }
            vector1[j] =min;
        }
        return vector1;
    }
};

template <class T>
unsigned int Matrix<T>::counter = 0;

template <class T>
Matrix<T> operator+(const Matrix<T> &left, const Matrix<T> &right){
    Matrix<T> temp(left);
    return (temp+= right);
}

template <class T>
Matrix<T> operator-(const Matrix<T> &left, const Matrix<T> &right){
    Matrix<T> temp(left);
    return (temp-= right);
}

template <class T>
Matrix<T> operator*(const Matrix<T> &left, const Matrix<T> &right){
    Matrix<T> temp(left);
    return (temp*= right);
}

template <class T>
Matrix<T> operator*(const Matrix<T> &left, double right){
    Matrix<T> temp(left);
    return (temp*= right);
}

template <class T>
Matrix<T> operator/(const Matrix<T> &left, double right){
    Matrix<T> temp(left);
    return (temp*= right);
}