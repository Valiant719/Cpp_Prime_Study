#include<iostream>

using namespace std;

void fn2_3() {
    cout << "\nex 2.3" << endl;
    unsigned u = 10, u2 = 42;
    cout << u2 - u << endl;
    cout << u - u2 << endl;

    int i = 10, i2 = 42;
    cout << i2 - i << endl;
    cout << i - i2 << endl;
    cout << i - u << endl;
    cout << u - i << endl;
}


void fn2_8() {
    cout << "\nex 2.8" << endl;
    cout << "2M\n2\tM" << endl;
}

void fn2_9() {
    // cin >> int input_value; // error：expected primary-expression before 'int'
    // int i = {3.14};  // error: narrowing conversion of '3.1400000000000001e+0' from 'double' to 'int' inside { } [-Wnarrowing]
    // cout << "i: " << i << endl;
    // double salary = wage = 9999.99; // wage未定义
    int i2 = 3.14;
    cout << "i2: " << i2 << endl;
}

void fn2_15() {
    cout << "\nex 2.15" << endl;
    int i3 = 1.01;
    cout << i3 << endl;  // 输出1，强制类型转换
}

void fn2_16() {
    cout << "\nex 2.16" << endl;
    int i = 0, &r1 = i;
    double d = 0, &r2 = d;
    r2 = 3.1415926;
    cout << r2 << endl;
    r2 = r1;
    cout << r2 << endl;
    i = r2;
    cout << i << endl;
    r1 = d;
    cout << r1 << endl;
}

void fn2_17() {
    cout << "\nex 2.17" << endl;
    int i, &ri = i;
    i = 5;
    ri = 10;
    cout << i << " " << ri << endl;
}

void fn2_18() {
    cout << "\nex 2.18" << endl;
    int i1, i2 = 10;
    int *p1 = &i1;
    cout << "*p1: " << *p1 << endl;
    *p1 = 20;
    cout << "*p1: " << *p1 << endl;
    cout << "p1: " << p1 << endl;
    p1 = &i2;
    cout << "p1: " << p1 << endl;
}

void fn2_20() {
    cout << "\nex 2.20" << endl;
    int i = 42;
    int *p = &i;
    *p = *p * *p;
    cout << "i: " << i << endl;
}

void fn2_21() {
    int i = 0;
    // double *dp = &i; // 类型不匹配
    // int *ip = i;  // i不是地址
    int *ip = &i;
    cout << "*ip: " << *ip << endl;
}


int main() {
    fn2_3();
    fn2_8();
    fn2_9();
    fn2_15();
    fn2_16();
    fn2_17();
    fn2_18();
    fn2_20();
    fn2_21();
    int null = 0, *p = &null;
    cout << "null: " << null << *p << endl;
}