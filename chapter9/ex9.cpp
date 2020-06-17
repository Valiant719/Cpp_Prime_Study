#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <deque>
#include <forward_list>
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


void ex9_18() {
    cout << "\nex9_18" << endl;
    deque<string> deq;
    string tmp;
    cin.clear();
    while(cin >> tmp) 
        deq.push_back(tmp);

    for (auto b = deq.cbegin(); b != deq.cend(); ++b)
        cout << *b << '\t';
    cout << endl;
}

void ex9_19() {
    cout << "\nex9_19" << endl;
    list<string> lst;
    string tmp;
    cin.clear();
    while(cin >> tmp) 
        lst.push_back(tmp);

    for (auto b = lst.cbegin(); b != lst.cend(); ++b)
        cout << *b << '\t';
    cout << endl;
}


void ex9_20() {
    cout << "\nex9_20" << endl;
    list<int> lst;
    deque<int> even;
    deque<int> odd;

    for (int i = 0; i != 100; ++i)
        lst.push_back(i);

    for (auto b = lst.cbegin(); b != lst.cend(); ++b) {
        if (*b % 2)
            odd.push_back(*b);
        else
            even.push_front(*b);
    }

    for (auto b = even.cbegin(); b != even.cend(); ++b)
        cout << *b << ", ";
    cout << endl;
    for (auto b = odd.cbegin(); b != odd.cend(); ++b)
        cout << *b << ", ";
    cout << endl;
}


void ex9_22() {
    cout << "\nex9_22" << endl;
    vector<int> vec;
    for (int i = 0; i != 10; ++i)
        vec.push_back(i);
    cout << *vec.begin() << "\t"
         << vec.front() << "\t"
         << vec[0] << "\t"
         << vec.at(0) << "\t"
         << endl;
}   


void ex9_26() {
    cout << "\nex9_26" << endl;
    int ia[] = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    list<int> lst;
    vector<int> vec;
    for (int i = 0; i != size(ia); ++i) {
        lst.push_back(ia[i]);
        vec.push_back(ia[i]);
    }
    auto it_lst = lst.begin();
    auto it_vec = vec.begin();
    while (it_lst != lst.end())
        if (*it_lst % 2)
            it_lst = lst.erase(it_lst);
        else
           ++it_lst;
    while (it_vec != vec.end())
        if (*it_vec % 2)
            ++it_vec;
        else
            it_vec = vec.erase(it_vec);
    for (auto b = lst.cbegin(); b != lst.cend(); ++b)
        cout << *b << " ";
    cout << endl;
    for (auto b = vec.cbegin(); b != vec.cend(); ++b)
        cout << *b << " ";
    cout << endl;
}
    

void ex9_27() {
    cout << "\nex9_27" << endl;
    forward_list<int> flst = {0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89};
    vector<int> odd;
    auto prev = flst.before_begin();
    auto curr = flst.begin();
    while (curr != flst.end()) {
        if (*curr % 2) {
            odd.push_back(*curr);
            curr = flst.erase_after(prev);
        } else {
            prev = curr;
            ++curr;
        }
    }
    for (auto b = flst.cbegin(); b != flst.cend(); ++b)
        cout << *b << " ";
    cout << endl;
    for (auto b = odd.cbegin(); b != odd.cend(); ++b)
        cout << *b << " ";
    cout << endl;
}

void insert_after_auery(forward_list<string> flst, string query, string to_insert) {
    auto curr = flst.begin();
    auto prev = flst.before_begin();
    while (curr != flst.end()) {
        if (*curr == query){
            flst.insert_after(curr, to_insert);
            break;
        } else {
            ++curr;
            ++prev;
        }
    }
    if (curr == flst.end())
        flst.insert_after(prev, to_insert);
}

void ex9_28() {
    cout << "\nex9_27" << endl;
    forward_list<string> flst = {"aa", "bb", "cc"};
    string query = "dd", to_insert = "zz";
    insert_after_auery(flst, query, to_insert);

    for (auto b = flst.cbegin(); b != flst.cend(); ++b)
        cout << *b << " ";
    cout << endl;
}

void even_delete_odd_copy_lst(list<int> &lst) {
    auto iter = lst.begin();
    while (iter != lst.end()) {
        if (*iter % 2) {
            iter = lst.insert(iter, *iter);
            ++(++iter);
        } else
            iter = lst.erase(iter);
    }
}

void even_delete_odd_copy_flst(forward_list<int> &flst) {
    auto curr = flst.begin();
    auto prev = flst.before_begin();
    while (curr != flst.end()) {
        if (*curr % 2) {
            prev = flst.insert_after(prev, *curr);
            ++curr;
            ++prev;
        } else 
            curr = flst.erase_after(prev);        
    }
    
}

void ex9_31() {
    cout << "\nex9_31" << endl;
    list<int> lst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    forward_list<int> flst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    even_delete_odd_copy_lst(lst);
    for (auto b = lst.begin(); b != lst.end(); ++b)
        cout << *b << " ";
    cout << endl;

    even_delete_odd_copy_flst(flst);
    for (auto b = flst.begin(); b != flst.end(); ++b)
        cout << *b << " ";
    cout << endl;
}

void ex9_33() {
    cout << "\nex9_33" << endl;
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto begin = v.begin();

    while (begin != v.end()) {
        ++begin;
        // v.insert(begin, 42);
        begin = v.insert(begin, 42);
        ++begin;    // begin指向2，后面的指针无效了
    }

    for (auto b : v)
        cout << b << " ";
    cout << endl;
}

void ex9_34() {
    cout << "\nex9_34" << endl;
    vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    auto begin = v.begin();

    while (begin != v.end()) {
        if (*begin % 2)
            begin = v.insert(begin, *begin);
        cout << *begin;
        ++begin;
    }

    for (auto b : v)
        cout << b << " ";
    cout << endl;
}

void ex9_41() {
    cout << "\nex9_41" << endl;
    istringstream s("Hello World");
    vector<char> v;
    char tmp;

    while(s >> tmp)
        v.push_back(tmp);
    string out(v.begin(), v.end());
    cout << out << endl;
}    


int main() {
    ex9_4();
    ex9_5();
    ex9_15();
    ex9_16();
    ex9_18();
    ex9_19();
    ex9_20();
    ex9_22();
    ex9_26();
    ex9_27();
    ex9_28();
    ex9_31();
    ex9_33();
    // ex9_34();    // 死循环
    ex9_41();

    return 0;
}