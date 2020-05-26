#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

bool found(vector<int>::iterator begin, vector<int>::iterator end, int query) {
    while(begin != end) {
        if (*begin == query)
            return true;
        ++begin;
    }
    return false;
}

int &find(vector<int>::iterator begin, vector<int>::iterator end, int query) {
    while(begin != end) {
        if (*begin == query)
            return *begin;
        ++begin;
    }
    throw std::runtime_error("Not found");
}

void ex9_4() {
    cout << "\nex9_4" << endl;
    vector<int> x;
    for (int i = 0; i < 100; ++i) 
        x.push_back(i);
    int q1 = 99, q2 = 100;
    cout << q1 << (found(x.begin(), x.end(), q1) ? "在" : "不在")
         << "给定vector里" << endl;
    cout << q2 << (found(x.begin(), x.end(), q2) ? "在" : "不在")
         << "给定vector里" << endl;
}

void _ex9_5(vector<int>::iterator begin, vector<int>::iterator end, int query) {
    try {
        int res = find(begin, end, query);
        cout << query << " is found: " << res << endl;
    } catch (std::runtime_error err) {
        cout << "error info: " << err.what() << endl;
        cout << query << " is not found" << endl;
    }
}

void ex9_5() {
    cout << "\nex9_5" << endl;
    vector<int> x;
    for (int i = 0; i < 100; ++i) 
        x.push_back(i);
    int q1 = 99, q2 = 100;
    _ex9_5(x.begin(), x.end(), q1);
    _ex9_5(x.begin(), x.end(), q2);
}

void ex9_15() {
    cout << "\nex9_15" << endl;
    vector<int> v1 = {1, 2, 3, 5};
    vector<int> v2 = {1, 2, 3, 7};
    bool is_equal = (v1 == v2);
    cout << "is_equal: " << is_equal;
}

bool compareListVector(list<int> lst, vector<int> vec) {
    return vector(lst.begin(), lst.end()) != vec ? false : true;
}

void ex9_16() {
    cout << "\nex9_16" << endl;
    list<int> lst = {1, 2, 3, 5};
    vector<int> vec = {1, 2, 3, 5};
    cout << "is_equal" << compareListVector(lst, vec);
}


int main() {
    ex9_4();
    ex9_5();
    ex9_15();
    ex9_16();

    return 0;
}