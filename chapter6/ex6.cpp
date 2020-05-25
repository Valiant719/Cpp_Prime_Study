#include <iostream>
#include <string>
#include <vector>
#include <cctype>   // 字符相关函数
#include <initializer_list>
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

bool containCapital(const string &s) {
    for (auto b = s.begin(); b != s.end(); ++b) 
        if (isupper(*b))
            return true;
    return false;
}

void capitalize(string &s) {
    for (auto &e : s)
        e = toupper(e);
}

void ex6_17() {
    cout << "\nex6.17" << endl;
    vector<string> v{"lower", "Upper"};
    for (auto e : v) 
        cout << e << " " << containCapital(e) << endl;
    for (auto &e : v)
        capitalize(e);
    for (auto e : v)
        cout << e << " ";
    cout << endl;
}

void swapPointer(int *a, int *b) {
    int *tmp = a;
    a = b;
    b = tmp;
}

int ex6_27(initializer_list<int> x) {
    cout << "\nex6_27" << endl;
    int sum = 0;
    for (auto i : x) {
        sum += i;
    }
    cout << "sum: " << sum << endl;
    return sum;
}

int &get(int *arry, int index) {
    return arry[index];
}

void ex6_32() {
    cout << "\nex6_32" << endl;
    int arr[10];
    for (int i = 0; i != 10; ++i) {
        get(arr, i) = i;
    }

    for (auto a : arr)
        cout << a << " ";
    cout << endl;
}


int
main()
{
    ex6_4();
    ex6_5();
    ex6_10();
    ex6_12();
    ex6_17();
    ex6_27({1, 2, 3, 4, 5});
    ex6_32();


    return 0;
}