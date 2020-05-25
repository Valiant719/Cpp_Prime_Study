

# 6.1 函数基础

```c++
// 函数
返回类型 函数名(形参1, 形参2){
    函数体
}
```

执行函数的第一步是（隐式地）**定义并初始化它的形参**。

和函数调用一样，`return`语句也完成两项工作：一是返回`return`语句中的值（如果有的话），二是将控制权从被调函数转移回主调函数。

### 形参与实参

实参是形参的初始值。

### 函数的形参列表

```c++
void f1() {/*...*/} // 隐式地定义空形参列表
void f2() {/*...*/} // 显式地定义空形参列表
```

```c++
int f3(int v1, v2) {/*...*/}        // 错误。每个形参都是含有一个声明符的声明。
int f3(int v1, int v2) {/*...*/}    // 正确
```

### 函数返回类型

函数的返回类型不能是**数组类型**或**函数类型**，但可以是指向数组或函数的指针。


## 6.1.1 局部对象

**在C++语言中，名字有作用域，对象有生命周期。**

- 名字的作用域是程序文本的一部分，名字在其中可见。
- 对象的生命周期是程序执行过程中该对象存在的一段时间。
  
形参和函数体内部定义的变量统称为**局部变量**，仅在函数的作用域内可见，同时局部变量还会**隐藏**在外层作用域中同名的其他所有声明中。

### 自动对象

我们把只存在于块执行期间的对象成为自动对象。当块执行结束后，块中创建的自动对象的值就变成未定义的了。

### 局部静态对象

局部静态对象（local static object）在程序的执行路径第一次经过对象定义语句时初始化，并且直到程序终止才销毁，在此期间即使对象所在的函数结束执行也不会对它有影响。

内置类型的局部静态变量默认初始化为0。

```c++
size_t count_calls() {
    static size_t ctr = 0;  // 调用结束后，这个值仍然有效
    return ++ctr;
}

int main() {
    for (size_t i = 0; i != 10; ++i)
        cout << count_calls() << endl;
    return 0;
}
```

## 6.1.2 函数声明

和变量类似，函数只能定义一次，但是可以声明多次。

函数三要素（返回类型、函数名、形参类型）描述了函数的接口，说明了调用该函数所需的全部信息。函数声明也称作**函数原型**（function prototype）。

### 在头文件中进行函数声明

含有函数声明的头文件应该被包含到定义函数的源文件中。

自定义头文件不能用`#include <ex6.h>`，要使用`#include "ex6.h"`。

## 6.1.3 分离式编译

分离式编译允许我们把程序分割到几个文件中去，每个文件独立编译。

TODO 编译过程：编译成成对象文件（`.obj`），然后链接生成可执行文件


# 6.2 参数传递

形参初始化的机理和变量初始化一样。

如果形参是引用类型，它将被绑定到对应的实参上；否则，将实参的值拷贝后赋给形参。

当形参是引用类型时，我们说她对应的实参被**引用传递（passed by reference）**或者函数被**传引用调用（called by reference）。

当实参的值拷贝给形参时，形参和实参是两个相互独立的对象。我们说这样的实参被**值传递（passed by value）**或者函数被**传值调用（called by value）。

## 6.2.1 传值参数

### 指针形参

在C++语言中，建议使用引用类型的形参替代指针。

```c++
void reset (int *p) {
    *ip = 0;    // 改变指针ip所指对象的值
    ip = 0;     // 只改变了ip的局部拷贝，实参未被改变
}

int i = 42;
reset(&i);      // 改变i的值而非i的地址
cout << "i = " << i << endl; // 输出i = 0
```


## 6.2.2 传引用参数

```c++
void reset(int &i) {// i是传给reset函数的对象的另一个名字
    i = 0           // 改变了i所引对象的值 
}
```

### 使用引用避免拷贝

如果函数无须改变引用形参的值，最好将其声明为常量引用。


### 使用引用形参返回额外信息

```c++
string::size_type find_char(const string &s, char c,
                            string::size_type &occurs) {
    auto ret = s.size();
    occurs = 0;     // 设置表示出现次数的形参的值
    for (decltype(ret) i = 0; i != s.size(); ++i) {
        if (s[i] == c) {
            if (ret == s.size())
                ret = i;
            ++occurs;
        }
    }
    return ret  // 出现次数通过occurs隐式地返回
}
```


## 6.2.3 const形参和实参

**和其他初始化过程一样，当用实参初始化形参时会忽略掉顶层`const`。当形参有顶层`const`时，传给它常量对象或者非常量对象都是可以的。**

```c++
void fcn(const int i) {/* fcn能够读取i，但是不能像i写值 */}
void fcn(int i) {/*因为前面一个函数形参忽略了顶层const，所以该函数和前一个函数的参数可以完全一样。*/}   // 错误：重复定义了fcn(int)
```

### 指针或引用形参与const

我们可以使用非常量初始化一个底层const对象，但是反过来不行；同时一个普通的引用必须用同类型的对象初始化。

```c++
// void reset(int *i)
// void reset(int &i)
int i = 0;
const int ci = i;
string::size_type ctr = 0;
reset(&i);      // 调用形参类型是int*的reset函数
reset(&ci);     // 错误：不能用指向const int对象的指针初始化int*
reset(i);       // 调用形参类型是int&的reset函数
reset(ci);      // 错误：不能把普通引用绑定到cosnt对象ci上
reset(42);      // 错误：不能把普通引用绑定到字面值上
reset(ctr);     // 错误：类型普匹配，ctr是无符号类型
// 正确：find_char的第一个形参对常量的引用
find_char("Hello World!", 'o', ctr)
```

### 尽量使用常量引用

我们不能把`const`对象、字面值或者需要类型转换的对象传递给普通的引用形参。


## 6.2.4 数组形参

因为不能拷贝数组，所以我们**无法以值传递的方式使用数组参数**。因为数组会被转换成指针，所以当我们为函数传递一个数组时，实际上传递的是指向数组首元素的指针。

```c++
// 尽管形式不同，但这三个print函数是等价的
// 每个函数都有一个const int*类型的形参
void print(const int*)
void print(const int[])
void print(const int[10])
```

```c++
int i = 0, j[2] = {0, 1};
print(&i)   // 正确：&i的类型是*int
print(j)    // 正确：j转换成int*并指向数组首元素的指针。
```

管理指针形参有三种常用技术

- 使用标记指定数组长度

    ```c++
    void print(const char *cp) {
         if (cp)    
            while (*cp)
                cout << *cp++;  // 输出当前字符并将指针向前移动一个位置
    }
    ```

- 使用标准库规范

    ```c++
    void print(const int  *beg, const int *end) {
    // 输出beg到end之间（不含end）的所有元素
        while (beg != end) 
            cout << *beg++  << endl; // 输出当前元素并将指针向前移动一个位置。
    }
    int j[2] = {0, 1};
    print(begin(j), end(j))
    ```

- 显式传递一个表示数组大小的形参

    ```c++
    void print(const int ia[], size_t size) {
        for (size_t i = 0; i != size; ++i) {
            cout << ia[i] << endls;
        }
    }

    int j[] = {0, 1}
    print(j, end (j) - begin(j))
    ```

### 数组形参和const

当函数不需要对数组元素执行写操作时，数组应该是指向const的指针。只有当函数确实要改变元素值得时候，才把形参定义成指向非常量的指针。

### 数组引用参数

```c++
// 正确：形参是数组的引用，维度是类型的一部分
// 限制：只能将函数作用于大小为10的数组
void print(int (&arr)[10]) {// arr是具有10个整数的整形数组的引用
    for (auto elem : arr)
        cout << elem << endl;
}

f(int &arr[10]) // 错误：将arr声明成了具有10个整形引用的数组。
```

### 传递多维数组

```c++
// 等价
void print(int (*matrix)[10], int rowSize) {/*...*/} // matrix是一个指向含有10个整数的数组的指针
void print(int matrix[][10], int rowSize) {/*...*/} // 编译器忽略掉第一个维度。
```


## 6.2.5 main：处理命令行选项

```c++
// 等价
int main(int argc, char *argv[]) {/*...*/}
int main(int argc, char **argv) {/*...*/}
```

`argv`是一个数组，它的元素是指向C风格字符串的指针；`argc`表示数组中字符串的数量。

当实参传给`main`函数之后，`argv`的第一个元素指向程序的名字或者一个空字符串，接下来的元素依次传递命令行提供的实参。最后一个指针之后的元素保证为0。

```c++
prog -d -o ofile data0

argv[0] = "prog";
argv[1] = "-d"; // 可选实参从此处开始
argv[2] = "-o";
argv[3] = "ofile";
argv[4] = "data0";
argv[5] = 0;
```

## 6.2.6 含有可变形参的函数

### initializer_list形参

传入`initializer_list`对象。

```c++
#include <initializer_list>

void error_msg(initializer_list<string> il) {
    for (auto beg = il.begin(); beg != il.end(); ++beg) 
        cout << *beg << " ";
    cout << endl;
}
```

```c++
// expected和actual是string对象
if (expected != actual)
    error_msg({"functionX", expected, actual});
else
    error_msg({"functionX", "okay"})
```

### 省略符形参(略)

省略符形参时为了便于C++程序访问某些特殊的C代码而设置的，这些代码使用了名为`varargs`的C标准库功能。

大多数类类型的对象在传递给省略符形参时都无法正确拷贝。

```c++
void foo(param_list, ...);  // ...只能在形参列表的最后一个位置
void foo(...);
```


# 6.3 返回类型和return语句

## 6.3.2 有返回值的函数

### 值是如何被返回的

返回一个值得方式和初始化一个变量或形参的方式完全一样：**返回值用于初始化调用点的有一个临时量**，该临时量就是函数调用的结果。

### 不要返回局部变量的引用或指针

局部变量在函数结束时会被销毁

### 引用返回左值

```c++
char &get_val(string &str, string:size_type ix) {
    return str[idx];
}

int main() {
    string s("a value");
    cout << s << endl;
    get_val(s, 0) = 'A';    // get_val返回左值，可以赋值
    cout << s << endl;      // 输出：A value
    return 0;
}
```

### 列表初始化返回值

```c++
vector<string> process() {
    // ...
    // expected和actual是string对象
    if (expected.empty())
        return {};                      // 返回一个空的vector对象
    else if (expected == actual)
        return {"functionX", "okey"};   // 返回列表初始化的vector对象
    else
        return {"functionX", expected, actual};
}
```


### 主函数main的返回值

```c++
#include <cstdlib>

int main() {
    if (some_failure)
        return EXIT_FAILURE;
    else
        return EXIT_SUCCESS;
}
```


## 6.3.3 返回数组指针

**因为数组不能被拷贝，所以函数不能返回数组。**

### 使用别名

```c++
typedef int arrt[10];   
using arrt = int[10];    // 两者等价

arrt *func(int i);      // func返回一个指向含有10个整数的数组的指针
```

### 一般方法

```c++
int (*func(int i))[10]  // 由内而外理解
```

### 使用尾置返回类型（trailing return type）

```c++
auto func(int i) -> int(*)[10]
```

### 使用`decltype`

```c++
int odd[] = {1, 3, 5, 7, 9};
int even[] = {0, 2, 4, 6, 8};

decltype(odd) *arrPtr(int i) {
    return (i % 2) ? &odd : & even;
}
```


# 6.4 函数重载

对于重载函数来说，它们应该在**形参数量**或**形参类型**上有所不同。

```c++
Record lookup(const Account&);
bool lookup(const Account&);    // 错误：与上一个函数相比只有返回类型不同
```

### 重载和const形参

顶层`const`不影响传入函数的对象。一个拥有**顶层**`const`的形参无法和另一个没有顶层`const`的形参区分开来。

```c++
Record lookup(Phone);
Record lookup(const Phone); // 重复声明了Record lookup(Phone)
```

通过区分指针或引用所指向的对象是常量还是非常量可以实现函数重载, 此时`const`是底层的。

```c++
Record lookup(Account &);   
Record lookup(const Account &); // 新函数，作用域常量引用
Record lookup(Account *);
Record lookup(const Account *); // 新函数，作用于指向常量的指针
```

如果传入的是非常量对象，优先使用非常量版本的函数。


### `const_cast`和重载

TODO


## 6.4.1 重载与作用域

一旦在当前作用域中找到了所需的名字，编译器就会忽略掉外层作用域中的同名实体。


# 6.5 特殊用途语言特性

## 6.5.1 默认实参

```c++
typedef string::size_type sz;
string screen(sz ht = 24; sz wid = 80, char backgrnd = ' ');

string window;
window = screen();
window = screen(66;)
```

### 默认实参声明

多次声明不能修改一个已经存在的默认值，但是可以添加默认实参。

```c++
string screen(sz, sz, char = ' ');
string screen(sz, sz, char = '*');      // 错误：重复声明
string screen(sz = 24, sz = 80, char);  // 正确：添加默认实参
```

### 默认实参初始值

局部变量不能作为默认实参。除此之外，只要表达式的类型能转换成形参所需的类型，该表达式就能作为默认实参。

```c++
sz wd = 80;
char def = ' ';
sz ht();
string screen(sz = ht(), sz = wd, char = def);
string window = screen();   // 调用screen(ht(), 80, ' ')

void f2() {
    def = '*';          // 改变默认实参的值
    sz wd = 100;        // 隐藏了外层定义的wd，但是没有改变默认值
    window = screen();  // 调用screen(ht(), 80, '*')
}
```

## 6.5.2 内联函数和`constexpr`函数

将函数指定为**内联函数**，通常就是将它在每个调用点上“内联地”展开。

一般来说，内联机制用于优化规模较小、流程直接、频繁调用的函数。

```c++
inline const string &shorterString(const string &s1, const string &s2) {
    return s1.size() <= s2.size() ? s1 : s2;
}
```

### `constexpr`函数

`constexpr`函数是指能用于常量表达式的函数。函数的返回类型以及所有形参的类型都得是**字面值类型**，而且函数体中**必须只有一条`return`语句**。

编译器把`constexpr`函数的调用替换成结果只。为了能在编译过程中随时展开，`constexpr`函数被隐式地指定为内联函数。

```c++
constexpr int new_sz() { return 42; }
constexpr int foo = new_size(); // 正确：foo是一个常量表达式
```

我们允许`constexpr`函数的返回值**并非一个常量**。

```c++
// 如果arg是常量表达式，则scale(arg)也是常量表达式
constexpr size_t scale(size_t cnt) { return new_size() * cnt;}
```

### 把内联函数和`constexpr`函数放在头文件内

内联函数和`constexpr`函数通常**定义**在头文件中。

## 6.5.3 调试帮助

### `assert`预处理宏

```c++
#include <cassert>

assert(expr)
```

### `NDEBUG`预处理变量

如果定义了`NDEBUG`，则assert什么也不做。默认状态下没有定义NDEBUG，此时`assert`将执行运行时检查。

```c++
void print(const int ia[], size_t size) {
    #ifndef NDEBUG
        // __func__是编译器定义的一个局部静态变量，用于存放函数的名字
        cerr << __func__ << ": array_size is " << size << endl;
    #endif
}
```

| 名字     | 说明                         |
| :------- | :---------------------------|
| __func__ | 函数名字                     |
| __FILE__ | 存放当前行号的整形字面值      |
| __LINE__ | 存放当前行号的整形字面值      |
| __TIME__ | 存放文件编译时间的字符串字面值 |
| __DATA__ | 存放文件编译日期的字符串字面值 |


# 6.6 函数匹配

### 确定候选函数和可行函数

- 第一步：选定候选函数。候选函数具备两个特征：一是与被调用的函数同名，二是其声明在调用点可见。
- 第二步：选出可行函数。可行函数也有两个特征：一是其形参数量与本次调用提供的实参数量相等，二是每个实参的类型与对应的形参类型相同，或者能转换成形参的类型。
- 第三步：从可行函数中选择与本次调用最匹配的函数。实参类型与形参类型越接近，它们匹配得越好。

### 含有多个形参的函数匹配

如果有且仅有一个函数满足下列条件，则匹配成功：

- 该函数每个实参的匹配都不劣于其他可行函数所需的匹配。
- 至少有一个实参的匹配优于其他可行函数提供的匹配。

## 6.6.1 实参类型转换

page219


# 6.7 函数指针

```c++
bool lengthCompare(const string &, const string &);
// (*pf)说明pf是一个指针，(const string &, cosnt string &)说明指向一个函数
bool (*pf)(const string &, const string &); // 函数指针，括号必不可少
```
