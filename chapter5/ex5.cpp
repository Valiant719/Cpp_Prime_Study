#include<iostream>
#include<vector>
#include<string>

using namespace std;
using std::cout;

void fn5_3() {
    cout << "\nex5.3" << endl;
    int val = 1, sum = 0;
    while (val <= 10) 
        sum += val, ++val;
    cout << sum << endl;
}

void fn5_5() {
    cout << "\nex5.5" << endl;
    const vector<string> scores = {"F", "D", "C", "B", "A", "A++"};
    int grade;
    string lettergrade;
    cout << "请输入成绩" << endl;
    cin >> grade;
    if (grade < 60)
        lettergrade = scores[0];
    else {
        lettergrade = scores[(grade-50)/10];
        if (grade != 100) {
            if (grade % 10 > 7)
                lettergrade += '+';
            else if (grade % 10 < 3)
                lettergrade += '-';
        }
    }
    cout << "数字成绩" << grade
         << "对应的字母成绩是：" << lettergrade << endl;
}

void fn5_6() {
    cout << "\nex5.6" << endl;
    const vector<string> scores = {"F", "D", "C", "B", "A", "A++"};
    int grade;
    string lettergrade;
    cout << "请输入成绩" << endl;
    cin >> grade;
    lettergrade = (grade < 60) ? scores[0] : scores[(grade - 50) / 10];
    lettergrade += (grade < 60) ? "": (grade % 10 > 7) ? "+" : (grade % 10 < 3 && grade != 100) ? "-" : "";

    cout << "数字成绩" << grade
         << "对应的字母成绩是：" << lettergrade << endl;
}

// void fn5_14() {
//     cout << "\nex5.14" << endl;
//     string kw, prev = "";
//     while(cin >> kw) {
//         if (kw == prev) {
            
//         }
//     }
// }

void fn5_17() {
    cout << "\nex5.17" << endl;
    vector<int> a = {0, 1, 1, 2};
    vector<int> b = {0, 1, 1, 2, 3, 5, 8};
    int min = (a.size() < b.size()) ? a.size() : b.size();
    cout << "min size: " << min << endl;
    bool is_prefix = true;
    for (int i = 0; i != min; ++i) {
        if (a[i] != b[i]) {
            is_prefix = false;
            break;
        }
    }
    cout << "result: " << is_prefix << endl;
}

void fn5_19() {
    cout << "\nex5.19" << endl;
    string a;
    string b;
    do {
        cout << "请输入字符串：" << endl;
        cin >> a >> b;
        cout << "较短的那个是: " 
             << (a.size() < b.size() ? a : b) << endl;
    } while (b.size() > 5);
}

void fn5_20() {
    cout << "\nex5.20" << endl;
    string prev;
    string curr;
    bool has_same = false;
    while(cin >> curr) {
        if (curr == prev) {
            has_same = true;
            cout << curr << "连续出现" << endl;
            break;
        }
        prev = curr;
    }
    if (!has_same) {
        cout << "没有单词连续重复出现" << endl;
    }

}



int main() {
    fn5_3();
    fn5_5();
    fn5_6();
    fn5_17();
    fn5_19();
    fn5_20();

    return 0;
}