## 3.1. 命名空间的using说明

```c++
using namespace::name
```

每个名字都需要独立的using声明

头文件不应包含using说明。因为头文件会copy到所有引用它的文件中去，那么每个使用该头文件的文件都会有这个声明，容易造成名字冲突。

## 3.2. 标准库类型string

```c++
#include<string>
using std::string;
```

### 3.2.1. 定义和初始化string对象

```c++
string s1               // 默认初始化，s1是一个空串
string s2(s1)           // s2是s1的副本
string s2 = s1          // 等价于s2(s1)，s2是s1的副本
string s3("value")      // s3是字面值"value"的副本，除了字面量最后的那个空字符外
string s3 = "value"     // 等价于s3("value")，s3是字面值"value"的副本
string s4(n, 'c')       // 把s4初始化为由连续n个字符c组成的串
```

### 3.2.2. string对象上的操作

```c++
os << s             // 将s写到输出流os当中，返回os。
is >> s             // 从is中读取字符串赋给s，字符串以空白分割，返回is
getline(is, s)      // 从is中读取一行赋给s，返回is
s.empty()           // s为空返回true，否则返回false
s.size()            // 返回s中字符的个数
s[n]                // 返回s中第n个字符的**引用**，位置n从0开始
s1+s2               // 返回s1和s2连接的结果
s1=s2               // 用s2的副本代替s1中原来的字符
s1==s2              // 如果s2和s1中所含的字符完全一样，则它们相等，大小写敏感
s1!=s2
<, <=, >, >=        // 利用字符在字典中的顺序进行比较，对大小写敏感。
```

标准输入读取到s中，string对象会自动忽略开头的空白（即空格符、换行符、制表符等）并从第一个真正的字符开始读起，直到遇到下一处空白

#### 读取未知数量的string对象

```c++
int main() {
    string word;
    while (cin >> word)         // cin >> word返回cin
        cout << word << endl;
    return 0;
}
```

```c++
int main() {
    string line;
    while (getline(cin, line)) {        // 每次读入一行，直至到达文件末尾 
        cout << word << endl;
    return 0;
}
```

###