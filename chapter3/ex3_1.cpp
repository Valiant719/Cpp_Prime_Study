#include<iostream>
#include<string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct Sales_data {
    string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

void fn1() {
    int i = 50;
    int sum = 0;
    while (i <= 100) {
        sum += i;
        ++i;
    };
    cout << "重做1.4.1-1：\n" << sum << endl; // 3825
}

void fn2() {
    cout << "重做1.4.1-2：" << endl;
    for (int i = 10; i >= 0; --i) {
        cout << i << ", ";
    };
    cout << endl;
}

void fn3() {
    cout << "重做1.4.1-3：" << endl;
    int start, end;
    cout << "输入start: ";
    cin >> start;
    cout << "输入end: ";
    cin>> end;
    for (int i = start; i <= end; ++i) {
        cout << i << ", ";
    };
    cout << endl;
}

int main() {
    fn1();
    fn2();
    fn3();
}
