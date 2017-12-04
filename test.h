//
// Created by 12181 on 2017/12/3.
//

#ifndef DATA_STRUCTURES_AND_ALGORITHMS_TEST_H
#define DATA_STRUCTURES_AND_ALGORITHMS_TEST_H
#include <iostream>
using namespace std;

template <class T>
class Polygon {
protected:
    int width, height;
public:
    void set_values (int a, int b)
    { width=a; height=b;}
};

template <class T>
class Rectangle: public Polygon<T>{
    using Polygon<T>::width;
    using Polygon<T>::height;
public:
    int area ()
    { return width * height; }
};

int test () {
    Rectangle<int> rect;
    rect.set_values (4,5);
    cout << rect.area() << '\n';
    return 0;
}

#endif //DATA_STRUCTURES_AND_ALGORITHMS_TEST_H
