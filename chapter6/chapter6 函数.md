

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

### 6.2.6 含有可变形参的函数

