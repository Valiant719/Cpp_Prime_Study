

# 2.1 基本内置类型

## 2.1.1 算数类型

一个int至少了一个`short`一样大，一个`long`至少和一个`int`一样大，一个`long long`至少了一个`long`一样大。

可寻址的最小内存块称为“字节（`byte`）”，存储的基本单元称为“字（`word`）”，它通常由几个字节组成。大多数机器的字节由8比特（`bit`）构成，字则由32或64比特构成，也就是4或8字节。

大多数计算机将内存中的每个字节与一个数字（被称为“地址（address）”）关联起来，我们能够使用某个地址来表示从这个地址开始的大小不同的比特串。

### 建议：如何选择类型

- 当明确知晓数值不可能为负时，选用无符号类型。
- 使用int执行整数运算，如果数值超过了`int`的表示范围，选用`long long`。
- 在算数表达式中不要使用`char`或`bool`，只有在存放字符或布尔值时才使用它们。
- 执行浮点运算选用`double`，这是因为`float`通常精度不够而且双精度浮点数和单精度浮点数的计算代价相差无几。

## 2.1.2 类型转换

当在程序的某处我们使用了一种类型而其实对象应该取另一种类型，程序会自动进行类型转换。

```c++
bool b = 42;            // b为真；bool b = 0，则b为假
int i = b;              // i的值是1
i = 3.14;               // i的值是3
double pi = i;          // pi的值是3.0
unsigned char c = -1;   // 假设char占8bit，c的值为255
signed char c2 = 256;   // 假设char占8bit，c的值是未定义的 
```

程序应该尽量避免依赖于实现环境的行为。如果我们把`int`的尺寸看成是一个确定不变的已知量，那么这样的程序就称作不可移植的（nonportable）。

```c++
// 死循环。变量i永远也不会小于0， 循环条件一直成立
for (unsigned i = 10; i >= 0; --i) {
    std::cout << i << std:endl;
}
```

切勿混合带符号类型和无符号类型。


## 2.1.3 字面值常量literal

```c++
20      // 十进制
024     // 八进制
0x14    // 十六进制
```

### 字符和字符串字面值

```c++
'a'     // 字符字面值，单引号
"Hello" // 字符串字面值，双引号

// 分多行书写的字符串字面值
cout << "a really, really long string literal "
     << "that spans two lines" << endl;
```

字符串字面值实际上是**常量字符构成的数组（array）**。编译器在每个字符串的结尾处添加一个空字符（"\0"），因此**字符串字面值的实际长度要比它的内容多1**。


### 转义序列

如果反斜线`\`后面跟着的八进制数字超过3个，只有前3个数字与`\`构成转义序列。相反，`\x`要用到后面跟着的所有数字。

### 布尔字面值和指针字面值

```c++
bool test = false;
int *p = nullptr;
```


# 2.2 变量

## 2.2.1 变量定义

对象是具有某种数据类型的内存空间。

在C++中，初始化和赋值是两个完全不同的操作。初始化的含义是创建变量时赋予其一个初始值，而赋值的含义是把对象的当前值**擦除**，而以一个新值来替代。

### 列表初始化（list initialization）

```c++
int units_unsold{0}
```
当用于内置类型的变量时，这种初始化形式有一个**重要特点：如果我们使用列表初始化且初始值存在丢失信息的风险，则编译器将报错。**

```c++
long double ld = 3.1415926536
int a{ld}, b = {ld};   // 错误：转换未执行，因为存在丢失信息的风险
int c(ld), d = ld;     // 正确：转换执行，且确实丢失了部分信息
```

### 默认初始化

如果内置类型的变量未被显示初始化，它的值由定义的位置决定。定义于任何函数体之外的变量被初始化为0。定义于函数体内部的内置类型变量将不被初始化。一个未被初始化的内置类型变量的值是未定义的，如果试图拷贝或以其他形式访问此类值将引发错误。


### 2.2.2 变量声明和定义的关系

为了支持分离式编译，c++语言将声明和定义区别开来。声明（declaration）使得名字为程序所知，一个文件如果想使用别处定义的名字则必须包含对那个名字的声明。而定义（definition）负责创建和名字关联的实体。

变量声明规定了变量的类型和名字，在这一点上定义与之相同。但是除此之外，定义还申请存储空间，也可能会为变量赋一个初始值。

```c++
extern int i;   // 声明i而非定义i
int j;          // 声明并定义j
extern double pi = 3.1416   // 定义
```

任何包含了显示初始值的声明即成为定义。extern语句如果包含初始值就不再是声明，而变成定义了。

在函数体内部，如果试图初始化一个由extern关键字标记的变量，将引发错误。

**变量能且只能被定义一次，但是可以被多次声明。**如果要在多个文件中使用同一个变量，就必须将声明和定义分离。


### 2.2.3 标识符

标识符由由字母、数字和下划线组成，其中必须以字母或下划线开头。标识符长度没有限制，但是对大小写字母敏感。


## 2.3 复合类型

声明语句由一个**基本数据类型（base type）和紧随其后的一个声明符（declarator）列表组成。

### 2.3.1 引用

程序把引用和它的初始值绑定（bind）在一起，而不是将初始值拷贝给引用。**引用必须初始化**，一旦初始化完成，引用将和它的初始值绑定在一起，**无法令其重新绑定到另外一个对象**。

**引用并非对象，相反的，它只是一个已经存在的对象所起的另一个名字。**

```c++
int i = 1024;
int &r = i
int &r2 = 2048;  // 错误：引用类型的初始值必须是一个对象。
int i3 = 10;
double &r3 = i3;  // 错误：类型不匹配
```

### 2.3.2 指针

#### 指针与引用的不同点
- 指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象。
- 指针无须再定义时赋初值。

```c++
int ival = 42;
int *p = &ival;  // &：取地址符
cout << *p << endl;  // *: 解引用符
```

#### 指针值

指针的值（即地址）应属于下列四种状态之一：
1. 指向一个对象。
2. 指向紧邻对象所占空间的下一个位置。
3. 空指针，意味着指针没有指向任何对象。
4. 无效指针，也就是上述情况之外的其他值。

注意：2、3无法访问（假定）所指对象，4无法访问。


#### 空指针

```c++
int *p1 = nullptr;
int *p2 = 0;
// 需要首先#include cstdlib
int *p3 = NULL;

int zero = 0;
int *p4 = zero;  // 错误，不能把int变量直接赋给指针，即使它的值恰好是0也不行。
```

**建议：初始化所有指针。**

任何非0指针的条件值都是true，否则为false。

#### void* 指针

void*是一种特殊的指针类型，可以存放**任意对象**的地址。
可以拿void\*指针和其他指针比较、作为函数的输入和输出，或者赋值给另一个void\*指针。**但是不能直接操作void\*指针所指的对象**，因为我们并不知道这个对象到底是什么类型，也就无法确定能在这个对象上做哪些操作。


### 2.3.3 理解复合类型的声明

#### 指向指针的指针

```c++
int ival = 1024;
int *pi = &ival;
int **ppi = &pi;        // 指向int型指针
cout << **ppi << endl;  // 两次解引用获取ival的值
```

#### 指向指针的引用

```c++
int i = 42;
int *p;
int *&r = p;    // r引用的是一个int型指针
```

**从右向左阅读`r`的定义**，离变量名最近的符号对变量的类型具有最直接的影响，所以`r`是一个引用。


## 2.4 const限定符

**`const`对象必须初始化。**

默认情况下，`const`对象被设定为仅在文件内有效。当多个文件中出现了同名的`const`变量时，其实等同于在不同的文件中分别定义了独立的变量。

要只在一个文件中定义`const`，而在其他多个文件中声明并使用它，解决的办法是，对于`const`变量不管是声明还是定义都添加`extern`关键字。

```c++
// file_1.cc定义并初始化了一个常量，该常量能被其他文件访问
extern const int bufSize = fcn()
// file_1.h头文件
extern const int bufSize;   // 与file_1.cc中定义的bufSize是同一个
```

### 2.4.1 `const`的引用

**对常量的引用（reference to const，简称常量引用）**：引用绑定到`const`对象。

```c++
double dval = 3.14;
const int &ri = dval;   // 合法：dval可以转换为int

// 等价于
const int temp = dval;
const int &ri = temp;   // ri绑定临时量（temporary）
```

常量引用**仅对引用可参与的操作做了限定**，对于引用的对象本身是不是一个常量未做限定。

```c++
int i = 42;
int &r1 = i;
const int &r2 = i;  // r2绑定对象i，但是不允许通过r2修改i的值
r1 = 0;
r2 = 0; // 错误：r2是一个常量引用
```

### 2.4.2 指针和const

#### 指向常量的指针（pointer to const）

不能用于改变其所指对象的值。

要想存放常量对象的地址，**只能使用指向常量的指针**。

和常量引用一样，指向常量的指针也没有规定其所指的对象必须是一个常量，**只要求不能通过该指针改变对象的值。**


#### 常量指针

常量指针本身即为常量，**必须初始化**。一旦初始化完成，其值（即存放在指针中的地址）就不能再变了。

```c++
int errNumb = 0;
int *const curErr = &errNumb;   // currErr一直指向errNumb，可以改变errNumb的值
const double pi = 3.14159;
const double *const pip = &pi;  // pip是一个指向常量对象的常量指针，不可以改变pi的值
```

### 2.4.3 顶层const

用名词**顶层const**（top-level const）表示指针本身是个常量，**底层cosnt**（low-level const）表示指针所指的对象是一个常量。指针类型既可以是顶层const也可以是底层cosnt。

```c++
int i = 0;
int *cosnt p1 = &i; // 不能改变p1的值，这是一个顶层const
const int ci = 42;  // 不能改变c1的值，这是一个顶层const
const int *p2 = &ci; // 允许改变p2的值，这是一个底层const
const int *const p3 = p2; // 靠右的const是顶层const，靠左的const是底层const
const int &r = ci   // 用于声明引用的const都是底层const

i = ci;     // 正确：拷贝ci的值，ci是一个顶层const，对此操作无影响
p2 = p3;    // 正确：p2和p3指向的对象类型相同，p3顶层const的部分不影响

int *p = p3;    // 错误：p3包含底层const的定义，而p没有
p2 = &i;        // 正确：int*能转换成const int*
int &r = ci;    // 错误：普通的int&不能绑定到int常量。
const int &r2 = i;  // 正确：const int&可以绑定到一个普通int上
```

当执行对象拷贝操作时，拷入和拷出的对象必须具有相同的底层const资格，或者两个对象的数据类型必须能够转换。一般来说，非常量可以转换成常量，反之则不行。


### 2.4.4 `constexpr`和常量表达式

**常量表达式（const expression）是指值不会改变并且在编译过程就能得到计算结果的表达式。运行时获得结果的表达式不是常量表达式。

C++11规定，允许将变量声明为`constexpr`类型以便由编译器来验证变量的值是否是一个常量表达式。声明为`constexpr`的变量一定是一个常量，而且**必须用常量表达式来初始化。**

#### 字面值类型

算数类型、引用、指针属于字面值类型，可以被定义为`constexpr`。

#### 指针和`constexpr`

`constexpr`把它所定义的对象置为了顶层const。

```c++
const int *p = nullptr;     // p是一个指向整形常量的指针
constexpr int *q = nullptr; // q是一个指向整数的**常量指针**
```


## 2.5 处理类型

### 2.5.1 类型别名

```c++
// typedef
typedef double wages;       // wages是double的同义词
typedef wages base, *p      // base是double的同义词，p是double*的同义词

//别名声明（alias declaration）
using SI = Sales_item;      // SI是Sales_item的同义词
```

```c++
typedef char *pstring;
const pstring cstr = 0;     // cstr是指向char的**常量指针**
const char *cstr = 0;       // 是对const pstring cstr的错误理解
```

### 2.5.2 auto类型说明符


```c++
// 一条声明语句只能有一个基本数据类型
auto i = 0, *p = &i;    // 正确：i是整数、p是整形指针
auto sz = 0, pi = 3.14; // 错误：sz和pi的类型不一致
```

#### 复合类型、常量和auto

auto一般会忽略掉顶层const，同时底层const则会保留下来。如果希望推断出的auto类型是一个顶层const，需要明确指出。

```c++
int i = 0, &r = i;
auto a = r;             // a是一个整数（r是i的别名，而i是一个整数）
const int ci = i, &cr = ci;
auto b = ci;            // b是一个整数（ci的顶层const特性被忽略掉了）
auto c = cr;            // c是一个整数（cr是ci的别名，ci本身是一个顶层const）
auto d = &i;            // d是一个整形指针（整数的地址就是指向整数的指针）
auto e = &ci;           // e是一个指向整数常量的指针（对常量对象取地址是一种底层const）

const auto f = ci;      // ci的推演类型是int，f是const int，是顶层const

auto &g = ci;           // g是一个整形常量引用，绑定到ci
auto &h = 42;           // 错误：不能为非常量引用绑定字面值
const auto &j = 42;     // 正确：可以为常量引用绑定字面值

auto k = ci, &l = i;    // k是整数，l是整形引用
auto &m = ci, *p = &ci; // m是对整形常量的引用，p是指向整形常量的指针
auto &n = i, *p2 = &ci; // 错误：i的类型是int，而ci的类型是const int
```


### 2.5.3 `decltype`类型指示符

`decltype`的作用是选择并返回操作数的数据类型。在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。

```c++
decltype(f()) sum = x;  // sum的类型就是f的返回类型，编译器并不实际调用额函数f
```

与`auto`不同的是，如果`decltype`使用的表达式是一个变量，则`decltype`返回该变量的类型（包括顶层const和引用在内）

```c++
const int ci = 0, &cj = ci;
decltype(ci) x = 0;     // x的类型是const int
decltype(cj) y = x;     // y的类型是const int&，y绑定到变量x
decltype(cj) z;         // 错误：z是一个引用，**必须初始化**
```

#### `decltype`和引用

```c++
int i = 42, *p = &i, &r = i;
decltype(r+0) b;    // 正确：加法的结果是int，因此b是一个（未初始化的）int
decltype(*p) c;     // 错误：c是int&，必须初始化
```

**注意：`decltype((variable))`的结果永远是引用，而`decltype(variable)`结果只有当`variable`本身就是一个引用时才是引用。**


# 2.6 自定义数据结构

```c++
struct Sales_data {
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};  // 不要忘了分号

Sales_data accum, trans, *salesptr;
```

### 2.6.3 编写自己的头文件

为了确保各个文件中的类的定义一致，类通常被定义在头文件中，**而且类所在的头文件的名字应与类的名字一样。**

头文件通常包含那些**只能被定义一次的实体**，如类、const和constexpr变量等。

#### 预处理概述

确保头文件多次被包含仍能够安全工作的常用技术是预处理器（preprocessor）。

1. `#include`
当预处理器看到`#include`标记时就会用指定的头文件的内容代替`#include`

2. 头文件保护符（header guard）

    头文件保护符依赖于预处理变量。预处理变量有两种状态：已定义和未定义。`#define`指令把一个名字设定为预处理变量，`#ifdef`当且仅当变量未定义时为真，`#ifndef`当且仅当变量未定义时为真。一旦检查结果为真，则执行后续操作直至遇到`#endif`指令为止

    ```c++
    #ifndef SALES_DATA_H
    #define SALES_DATA_H
    #include <string> 
    struct Sales_data {
        std::string bookNo;
        unsigned units_sold = 0;
        double revenue =0.0;
    };
    # endif
    ```
