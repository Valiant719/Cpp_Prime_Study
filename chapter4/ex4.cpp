#include<iostream>
#include<vector>
#include<string>

using namespace std;

void fn4_2() {
    cout << "\nex 4.2" << endl;
    vector<int> vec;
    for (int i=5; i <= 10; ++i) {
        vec.push_back(i);
    }
    cout << vec[0] << endl;
    cout << "*vec.begin(): " << *(vec.begin()) << endl;
    cout << "*vec.begin() + 1: " << *vec.begin() + 1 << endl;
}

void fn4_4() {
    cout << "\nex 4.4" << endl;
    int x = 12 / 3 * 4 + 5 * 15 + 24 % 4 / 2;
    int y = ((12 / 3) * 4) + (5 * 15) + ((24 % 4) / 2);
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;
}

void fn4_6() {
    cout << "\nex 4.6" << endl;
    int i;
    cout << "请输入整数：" << endl;
    cin >> i;

    if(i%2 == 0) {
        cout << i << "是偶数" << endl;
    }else{
        cout << i << "是奇数" << endl;
    }
}

void fn4_10() {
    cout << "\nex 4.10" << endl;
    int i;
    cout << "请输入整数：" << endl;
    while (cin >> i) {
        if (i == 42) {
            cout << "遇到42，停止" << endl;
            break;
        }
    }
}

void fn4_15() {
    cout << "\nex 4.15" << endl;
    double dval;
    int ival;
    int *p;

    dval = ival = *p = 0;
    cout << dval << ival << *p << endl;
}

void fn4_25() {
    cout << "\nex 4.25" << endl;
    char q = 'q';
    cout << (~q << 6) << endl;
}

void fn4_27() {
    cout << "\nex 4.27" << endl;
    unsigned long ul1 = 3, ul2 = 7;
    cout << "ul1 & ul2 = " << (ul1 & ul2) << endl;
    cout << "ul1 | ul2 = " << (ul1 | ul2) << endl;
    cout << "ul1 && ul2 = " << (ul1 && ul2) << endl;
    cout << "ul1 || ul2 = " << (ul1 || ul2) << endl;
}

void fn4_28() {
    cout << "\nex 4.28" << endl;
    char a = 'a';
    short b = 10;
    int c = 10;
    long d = 10L;
    float e = 1.0F;
    double f = 1.0;
    bool g = true;
    cout << "sizeof char: " << sizeof a << endl;
    cout << "sizeof short: " << sizeof b << endl;
    cout << "sizeof int: " << sizeof c << endl;
    cout << "sizeof long: " << sizeof d << endl;
    cout << "sizeof float: " << sizeof e << endl;
    cout << "sizeof double: " << sizeof f << endl;
    cout << "sizeof bool: " << sizeof g << endl;
}

void fn4_29() {
    cout << "\nex4.29" << endl;
    int x[10];
    int *p = x;
    cout << sizeof(x) / sizeof(*p) << endl;
    cout << sizeof(p) / sizeof(*p) << endl;
    cout << "指针字节数:" << sizeof(p) << endl;
    cout << "int字节数:" << sizeof(*p) << endl;
}


void fn4_31() {
    cout << "\nex4.31" << endl;
    vector<int> ivec(10);
    vector<int>::size_type cnt = ivec.size();
    // for (vector<int>::size_type ix = 0; ix != ivec.size(); ++ix, --cnt
    // )
    //     ivec[ix] = cnt;

    for (vector<int>::size_type ix = 0; ix != ivec.size(); ix++, cnt--
    )
        ivec[ix] = cnt;

    cout << "ivec = ";
    for (const int &x : ivec)
        cout << x << " ";
    cout << endl;

    cout << "ivec.size = " << ivec.size() << endl;
}

void fn4_33() {
    cout << "\nex4.32" << endl;
    int x = 10, y = 20;
    bool v = false;
    int z;
    // 优先级 ++ -- > ? > 
    // 相当于 (v ? ++x, ++y : --x), --y
    z = v ? ++x, ++y : --x, --y;
    cout << z << endl;
}


int main()
    {
        fn4_2();
        fn4_4();
        // fn4_6();
        // fn4_10();
        fn4_15();
        fn4_25();
        fn4_27();
        fn4_28();
        fn4_29();
        fn4_31();
        fn4_33();

        return 0;
}