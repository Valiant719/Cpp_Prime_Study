#include <iostream>
#include <string>
#include <vector>
#include "ex6.h"    // 自定义头文件不能用 #include <ex6.h>

using namespace std;

int fact(int i) {
    if(i == 1)
        return 1;
    else
        return i * fact(i - 1);
}


int abs(int i) {
    return i > 0 ? i : -i;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void ex6_4 () {
    cout << "\nex6.4" << endl;
    int i;
    cout << "请输入i：" << endl;
    cin >> i;
    cout << "结果是：" << fact(i) << endl;
}

void ex6_5() {
    cout << "\nex6.5" << endl;
    int i;
    cout << "请输入i：" << endl;
    cin >> i;
    cout << "结果是：" << abs(i) << endl;
}

void ex6_10() {
    cout << "\nex6.10" << endl;
    int a = 10, b = 5;
    cout << "a = " << a << ", "
         << "b = " << b << endl;
    swap(&a, &b);
    cout << "a = " << a << ", "
         << "b = " << b << endl;
}

void ex6_12() {
    cout << "\nex6.12" << endl;
    int a = 10, b = 5;
    cout << "a = " << a << ", "
         << "b = " << b << endl;
    swap(&a, &b);
    cout << "a = " << a << ", "
         << "b = " << b << endl;
}

int main() {
    ex6_4();
    ex6_5();
    ex6_10();
    ex6_12();

    return 0;
}