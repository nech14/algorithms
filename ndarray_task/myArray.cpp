

#include <iostream>
#include <typeinfo>
#include <locale.h>
#include "array.h"

template <class T> void test_mean(int mode, Array<T> b);
template <class T> void test_mean(Array<T> b);
template <class T> void test_min(int mode, Array<T> b);
template <class T> void test_min(Array<T> b);
template <class T> void test_max(int mode, Array<T> b);
template <class T> void test_max(Array<T> b);


int main()
{
    /*int a[] = { 2, 3 };
    int a1[] = { 3, 2 };

    Array<int> b(2, a);
    Array<int> b1(2, a1);
    
    b.fillOrder(); 
    b1.fillOrder();
    //b1.fillRandom();
    

    Array<int> b2;
    b2 = b.matmul(b1);


    test_mean(b1);
    test_mean(0, b1);
    test_mean(1, b1);

    std::cout << "\n";

    test_min(b1);
    test_min(0, b1);
    test_min(1, b1);

    std::cout << "\n";

    test_max(b1);
    test_max(0, b1);
    test_max(1, b1);

    std::cout << "\n";


    for (int i = 0; i < 6; i++) {
        std::cout << b1[i] << "\n";
    }



    
    std::cout << "\n";
    std::cout << "The end!\n";*/

}

template <class T> void test_mean(int mode, Array<T> b) {
    int n = b.giveSizeArray()[b.giveDimension() - mode - 1];
    std::cout << "dimension: " << mode << "\n mean: \n";
    for (int i = 0; i < n; i++)
        std::cout << "  " << i << ") " << b.mean(mode)[i] << '\n';

    std::cout << "\n";
}

template <class T> void test_mean(Array<T> b) {

    std::cout << "mean: " << b.mean() << '\n';

    std::cout << "\n";
}

template <class T> void test_min(int mode, Array<T> b) {
    int n = b.giveSizeArray()[b.giveDimension() - mode - 1];
    std::cout << "dimension: " << mode << "\n min: \n";
    for (int i = 0; i < n; i++)
        std::cout << "  " << i << ") " << b.min(mode)[i] << '\n';

    std::cout << "\n";
}

template <class T> void test_min(Array<T> b) {

    std::cout << "min: " << b.min() << '\n';

    std::cout << "\n";
}

template <class T> void test_max(int mode, Array<T> b) {
    int n = b.giveSizeArray()[b.giveDimension() - mode - 1];
    std::cout << "dimension: " << mode << "\n max: \n";
    for (int i = 0; i < n; i++)
        std::cout << "  " << i << ") " << b.max(mode)[i] << '\n';

    std::cout << "\n";
}

template <class T> void test_max(Array<T> b) {

    std::cout << "max: " << b.max() << '\n';

    std::cout << "\n";
}
