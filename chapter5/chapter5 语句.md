
# 5.1 简单语句

```c++
// 重复读入数据直至到达文件末尾或某次输入的值等于sought
while (cin >> s && s != sought)
    ;   // 空语句
```

```c++
while (val < 10) {
    sum += val;
    ++ val;
}   // 块不以分号作为结束
```

# 5.2 语句作用域

```c++
while (int i = get_num()) // 每次迭代时创建并初始化i
    cout << i << endl;
i = 0;  // 错误：在循环外部无法访问i
```

# 5.3 条件语句

## if语句

```c++
const vectr<string> scores = {"F", "D", "C", "B", "A", "A++"};
if (grade < 60)
    lettergrade = scores[0];
else {
    lettergrade = socres[(grade-50)/10];
    if (grade != 100)
        lettergrade += '+';
    else if (grade % 10 < 3)
        lettergrade += '-';
}
```

`else`与离它最近的尚未匹配的`if`匹配。

## switch语句

```c++ 
unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;
unsigned otherCnt = 0;
char ch;
while(cin >> ch) {
    switch(ch) {
        case 'a':   // case关键字和它对应的值一起被称为case标签（case label）
            ++aCnt;
            break;  // 一般都需要break，否则如果匹配该条会继续执行后面的case
                    // 如果没写break语句，最好加一段注释说清楚程序的逻辑
        case 'e':
            ++eCnt;
            break;  
        case 'i':
            ++iCnt;
            break;
        case 'o':
            ++oCnt;
            break;
        case 'u':
            ++uCnt;
            break;
        default:
            ++otherCnt;
            break;
    }
}
```

case标签必须是**整形常量**表达式。

#### switch内部的变量定义

C++语言规定，不允许跨过变量的初始化语句直接跳转到该变量作用域内的另一个位置。

```c++
case true:
    // 因为程序的执行流程可能绕开下面的**初始化语句**，所以该switch语句不合法
    string file_name;   // 错误：控制流绕过一个隐式初始化的变量
    int ival = 0;       // 错误：控制流绕过一个显示初始化的变量
    int jval;           // 正确：因为jval没有初始化
case false:
    // 正确：jval虽然在作用域内，但是它没有被初始化
    jval = next_num()   // 正确：给jval赋一个值
    if (file_name.empty())  // filename在作用域内，但是没有被初始化
```


# 5.4 迭代语句

## 5.4.1 while语句

定义在`while`条件部分或者`while`循环体内的变量每次迭代都经历从创建**到销毁**的过程。

```c++
vector<int> v;
int i;
// 重复读入数据，直至到达文件末尾或者遇到其他输入问题
while (cin >> i)
    v.push_back(i)
// 寻找第一个负值元素
auto beg = v.begin();
while(beg != v.end() && *beg >= 0)
    ++beg;
if (beg == v.end())
    // 此时我们知道v中的所有元素都大于等于0
```

## 5.4.2 传统的for语句

```c++
for (init-statement; condition; expression)
    statement;
```

`init-statement`可以定义多个对象，但是`init-statement`只能有一条声明语句，因此，所有变量的基础类型必须相同。

```c++
for (decltype(v.size() i = 0, sz = v.size(); i != sz; ++i))
    v.push_back(v[i])
```

for语句头能省略掉`init_statement`、`condition`和`expression`中的任何一个（或者全部）。


## 5.4.3 范围for语句

```c++
for (declaration: expression) 
    statement
```
expression必须拥有能返回迭代器的begin和end成员。


## 5.4.4 do while语句

```c++
do
    statement
while (condition);
```
不允许在条件部分定义变量


# 5.5 跳转语句

## 5.5.1 break语句

`break`语句只能出现在迭代语句或者`switch`语句内部。`break`语句的作用范围仅限于**最近**的循环或者`switch`

```c++
string buf;
while (cin >> buf && !buf.empty()) {
    switch(buf[0]) {
        case '-':
            // 处理到第一个空白为止
            for (auto it = buf.begin() + 1; it != buf.end(); ++it) {
                if (*it == ' ')
                    break;  // break #1: 离开for循环
            }
            // break #1将控制权转移到这里
            // 剩余的'-'处理：
            break;  // #2, 离开switch语句
        case '+':
            //...
    }   // 结束switch：break #2将控制权转移到这里
}   // 结束while
```

### 5.5.2 continue语句

`continue`语句中止最近的循环中的当前迭代并立即开始下一次迭代。`continue`仅作用于离他最近的循环。


### 5.5.3 goto语句（略）

不要再程序中使用`goto`语句，因为它使得程序既难理解又难修改。


## 5.6 try语句块和异常处理

### 5.6.1 throw表达式

```c++
#include<stdexcept>

Sales_item item1, item2;
cin >> item1 >> item2;
// 首先检查两条数据是否是关于同一种书籍的
if (item1.isbn() != item2.isbn())
    // runtime_error是标准库异常类型的一种，定义在stdexcept头文件中
    throw runtime_error("Data must refer to same ISBN")
// 如果程序执行到这里，表示两个ISBN是相同的
cout << item1 + item2 << endl;
```

### 5.6.2 try语句块

```c++
try {
    program-statements
} catch (exception-declaration) {
    handler-statements
} catch (exception-declaration) {
    handler-statements
} // ...
```

try块语句块内声明的变量在块外部无法访问，特别是**在catch字句中也无法访问**。

```c++
while (cin >> item1 >> item2) {
    try {
        // 执行添加两个Sales_item对象的代码
        // 如果添加失败，代码抛出一个runtime_error异常
    } catch (runtime_error err) {
        // 提醒用户两个ISBN必须一致，询问是否重新输入
        cout << err.what() // 每个标准库异常类都定义了名为what的成员函数。
             << "\nTry Again? Enter y on n" << endl;
        char c;
        cin >> c;
        if (!cin || c == 'n')
            break;
    }
}
```

异常抛出时，首先搜索抛出该异常的函数。如果没有找到匹配的`catch`子句，中止该函数，并在调用该函数的函数中继续寻找，由此类推，直到找到适当类型的catch子句。如果最终还是没能找到任何匹配的`catch`子句，程序转到名为**`terminate`**的标准库函数。该程序的行为与系统有关，一般情况下，执行该函数将导致程序非正常退出。

### 5.6.3 标准异常

C++标准库定义了一组类，用于报告标准库函数遇到的问题。它们分别定义在4个头文件中：
- `exception`头文件定义了最通用的异常类`exception`。它只报告异常的发生，不提供任何额外信息。
- `stdexcept`头文件定义了几种常见的异常类

    |exception名|说明|
    |:-:|:-:|
    |exception|最常见的问题|
    |runtime_error|只有在运行时才检测出的问题|
    |range_error|运行时错误：生成的结果超出了有意义的值域范围|
    |overflow_error|运行时错误：计算上溢|
    |underflow_error|运行时错误：计算下溢|
    |logic_error|程序逻辑错误|
    |domain_error|逻辑错误：参数对应的结果值不存在|
    |invalid_argument|逻辑错误：无效参数|
    |length_error|逻辑错误：试图创建一个超出该类型最大长度的对象|
    |out_of_range|逻辑错误：使用一个超出有效范围的值|

- `new`头文件定义了`bad_alloc`异常类型（12.1.2，page407）。
- `type_info`头文件定义了`bad_cast`异常类型（19.2 page731）