
**拷贝控制操作(copy control)**:

- 拷贝构造函数(copy constructor)
- 拷贝赋值运算符(copy-assignment operator)
- 移动赋值函数(move constructor)
- 移动赋值运算符(move-assignment operator)
- 析构函数(destructor)


# 13.1 拷贝、赋值与销毁

## 13.1.1 拷贝构造函数

拷贝构造函数的第一个参数是自身类类型的引用，且任何额外参数都有默认值。

与默认构造函数不同, 即使我们定义了其他构造函数，编译器也会为我们合成一个拷贝构造函数。

```c++
class Foo {
public:
    Foo();              // 默认构造函数
    Foo(const Foo&);    //拷贝构造函数
}
```

`Sales_data`类的合成拷贝构造函数等价于：

```c++
class Sales_data {
public:
    // 其他成员和构造函数的定义, 如前
    // 与合成的拷贝构造函数等价的拷贝构造函数的声明
    Sales_data(const Sales_data&);
private:
    std::string bookNo;
    int units_sold = 0;
    double revenue = 0.0;
};
// 与Sales_data的合成的拷贝构造函数等价
Sales_data::Sales_data(const Sales_data &orig):
    bookNo(orig.bookNo),            // 使用string的拷贝构造函数
    units_sold(orig.units_sold),    // 拷贝orig.units_sold
    revenue(orig.revenue)           // 拷贝orig.revenue
    {}
```

### 拷贝初始化

拷贝初始化依靠拷贝构造函数或移动构造函数来完成，其在下列情况下会发生：

- 用`=`定义变量
- 将一个对象作为实参传递给一个**非引用**类型的形参。这解释了为什么拷贝构造函数的参数必须是引用类型
- 从一个返回类型为**非引用**的函数返回一个对象
- 用花括号列表初始化一个数组中的元素或一个聚合类中的成员 [NOTE 不理解]
- 某些类类型会对他们所分配的对象使用拷贝初始化。例如，初始化标准库容器或调用`insert`或`push`成员时，容器会对其元素进行拷贝初始化; 而用`emplace`成员创建的元素进行直接初始化。

### 拷贝初始化的限制

参考page442, 与`explicit`构造函数有关

### 编译器可以绕过拷贝构造函数

```c++
// 编译器被允许将下面的代码
string null_book = "9-999-99999-9"; // 拷贝初始化
// 改写为
string null_book("9-999-99999-9");  // 编译器略过了拷贝构造函数
```

## 13.1.2 拷贝赋值运算符

如果类为定义自己的拷贝赋值运算符，编译器会为它合成一个。

重载运算符本质上式函数，其名字由`operator`关键字后接表示要定义的运算符号组成。赋值运算符就是一个名为`operator=`的函数。如果运算符是一个成员函数，其左侧运算对象就绑定到隐式地`this`参数。

赋值运算符通常应该返回一个指向其左侧运算对象的引用。

```c++
class Foo {
public:
    Foo& operator=(const Foo&); // 赋值运算符
}
```

### 合成拷贝赋值运算符

```c++
// 等价于合成拷贝赋值运算符
Sales_data& Sales_data::operator=(const Sales_data &rhs) {
    bookNo = rhs.bookNo;        //调用string::operator=
    units_sold = rhs.units_sold // 使用内置的int赋值
    revenue = rhs.revenue;      // 使用内置的double赋值
    return *this                // 返回一个此对象的引用
}
```

# 13.1.3 析构函数

```c++
class Foo {
public:
    ~Foo(); // 析构函数
    // 析构函数不接受参数，不能被重载
}
```

对于一个给定的类，只会有**唯一**一个析构函数。

### 析构函数完成什么工作

在一个析构函数中，首先执行函数体，然后销毁成员(析构部分)。析构部分是隐式的，销毁类类型需要执行成员的析构函数。成员按初始化顺序的逆序销毁。通常析构函数释放对象在生存期分配的所有资源。

隐式销毁一个内置指针类型的成员不会`delete`它所指向的对象。智能指针是类类型，具有析构函数，智能指针成员在析构阶段会被自动销毁。

### 什么时候会调用析构函数

无论何时一个对象被销毁，就会调用其析构函数：

- 变量在离开其作用域时被销毁。
- 当一个对象被销毁时，其成员被销毁。
- 容器(无论是标准容器还是数组)被销毁时，其元素被销毁。
- 对于动态分配的对象，当对指向它的指针应用`delete`运算符时被销毁。
- 对于临时对象，当创建它的完整表达式结束时被销毁。

```c++
{
    // p和p2指向动态分配的对象
    Sales_data *p = new Sales_data;     // p是一个内置指针
    auto p2 = make_share<Sales_data>(); // p2是一个shared_ptr
    Sales_data item(*p)                 // 拷贝构造函数将*p拷贝到item中
    vector<Sales_data> vec;             // 局部对象
    vec.push_back(*p2);                 // 拷贝p2指向的对象
    delete p;                           // 对p指向的对象执行析构函数
} // 退出局部作用域; 对item、p2和vec调用析构函数
  // 销毁p2会递减其引用计数; 如果引用计数变为0，对象被释放
  // 销毁vec会销毁它的元素
```

### 合成析构函数

当一个类未定义自己的析构函数时，编译器会为它定义一个**合成析构函数**。

```c++
// 等价于Sales_data的合成析构函数
class Sales_data {
public:
    // 成员会被自动销毁，除此之外不需要做其他事情
    ~Sales_data() {}
    // 其他成员的定义，如前
}
```

## 13.1.4 三/五法则

### 需要析构函数的类也需要拷贝和赋值操作

如果一个类需要自定义析构函数，几乎可以肯定它也需要自定义拷贝赋值运算和拷贝构造函数。

### 需要拷贝操作的类也需要赋值操作，反之亦然

但不意味着需要自定义析构函数

## 13.1.5 使用`=default`

通过将拷贝控制成员定义为`=default`来显式地要求编译器生成合成的版本。

只能对具有合成版本的成员函数，即默认构造函数和拷贝控制成员使用`=default`。(系统不会自动合成的话，当然不会有默认实现)

```c++
class Sales_data {
public:
    // 拷贝控制成员; 使用default
    Sales_data() = default; // 隐式内联。默认函数也可以使用default
    Sales_data(const Sales_data&) = default;
    Sales_data& operator=(const Sales_data&);
    ~Sales_data() = default;
};
// 非内联
Sales_data& Sales_data::operator=(const Sales_data&) = default;
```

## 13.1.6 阻止拷贝

大多数类应该定义默认构造函数、拷贝构造函数和拷贝赋值运算符，无论是隐式地还是显示地。但有些时候，拷贝或赋值没有合理的意义(e.g. `iostream`阻止拷贝)，此时需要使用`=delete`来通知编译器我们希望将其定义为删除的。

与`=default`不同，**`=delete`必须出现在函数第一次声明的时候。此外，我们可以对任何函数指定`=delete`。**

```c++
struct NoCopy {
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;             // 阻止拷贝
    NoCopy &operator=(const NoCopy&) = delete   // 阻止赋值
    ~NoCopy() = default;
    // 其他成员
}
```

### 析构函数不能是删除的成员

对于析构函数已删除的类型，不能定义该类型的变量或释放指向该类型动态分配对象的指针

```c++
struct NoDtor {
    NoDtor() = default;
    ~NoDtor() = delete; // 不能销毁NoDtor类型的对象
}
NoDtor nd;                  // 错误：NoDtor的析构函数是删除的，不能定义该类型变量
NoDtor *p = new NoDtor();   // 正确：可以动态分配该类型的对象，但是不能delete p
delete p;                   // 错误：NoDtor的析构函数是删除的
```

### 合成的拷贝控制成员可能使删除的

**如果一个类有数据成员不能默认构造、拷贝、赋值或销毁，则对应的成员函数将被定义为删除的。**
 
- 如果类的某个成员的**析构函数**是删除的或不可访问的(例如，是`private`的)，则类的**合成析构函数**和**合成拷贝构造函数**被定义为删除的。
- 如果类的某个成员的**拷贝构造函数**是删除的或不可访问的，则类的**合成拷贝构造函数**被定义为删除的。
- 如果类的某个成员的**拷贝赋值运算符**是删除的或不可访问的，或是类有一个`const`的或引用成员，则类的**合成拷贝赋值运算符**被定义为删除的。
- 如果类的某个成员的**析构函数**是删除的或不可访问的，或是一个引用成员没有类内初始化器，或是类有一个`const`成员没有类内初始化器且其类型未显示定义默认构造函数，则该类的**默认构造函数**被定义为删除的。

原因的说明参见page451

### `private`拷贝控制

希望阻止拷贝的类应该使用`=delete`来定义他们自己的拷贝控制构造函数和拷贝赋值运算符，而不应该将它们声明为`private`的。


# 13.2 拷贝控制和资源管理

## 13.2.1 行为像值得类

```c++
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s), i(0) {} // 构造函数动态分配内存
    // 对ps指向的string，每个HasPtr对象都有自己的拷贝
    HasPtr(const HasPtr &p):
        ps(new std::string(*p.ps)), i(p.i) {}
    HasPtr& operator=(const HasPtr &);
    ~HasPtr() { delete ps; }    // 析构函数释放动态分配的内存
private:
    std::string *ps;
    int i;
};

HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    auto newp = new string(*rhs.ps);    // 拷贝底层string
    delete ps;  // 释放旧内存
    ps = newP;  // 从右侧运算对象拷贝数据到本对象
    i = rhs.i
    return *this;   // 返回本对象
}
```

**关键概念：赋值运算符**

当编写赋值运算符时，有两点需要记住：

- 如果讲一个对象赋予它自身，赋值运算符必须能正确工作。
- 大多数赋值运算符组合了析构函数和拷贝构造函数的工作。

当编写一个赋值运算符时，一个好的模式是先将右侧运算对象拷贝到一个局部临时对象中，然后在销毁左侧对象并执行拷贝。

## 13.2.2 定义行为像指针的类

```c++
class HasPtr {
public:
    // 构造函数分配新的string和新的计数器，将计数器置为1
    HasPtr(const std::string &s = std::string()):
        ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
    // 拷贝构造函数拷贝所有三个数据成员，并递增计数器
    HasPtr(const HasPtr &p):
        ps(p.ps), i(p.i), use(p.use) { ++*use; }
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();
private:
    std::string *ps;
    int i;
    std::size_t *use;   // 用来记录有多少个对象共享*ps的成员
}

HasPtr::~HasPtr() {
    if (--*use == 0) { // 如果引用计数变为0，释放string和计数器的内存
        delete ps;
        delete use;
    }
}

HasaPtr& HasPtr::operator=(const HasPtr &rhs) {
    ++*rhs.use; // 递增右侧运算对象的引用计数
    if (--*use == 0) {  // 递减左侧运算对象的引用计数，如果计数为0，释放内存。
        delete ps;
        delete use;
    }
    ps = rhs.ps;    // 将数据从rhs拷贝到本对象
    i = rhs.i;
    use = rhs.use;
    return *this
}
```

# 13.3 交换操作

如果一个类定义了自己的`swap`，那么算法将使用类自定义的版本。否则将使用标准库定义的`swap`。对于那些与重排元素顺序的算法一起使用的类，定义`swap`是非常重要的，这类算法在需要交换两个元素时会调用`swap`

```c++
class HasPtr {
    friend void swap(HasPtr&, HasPtr&);
    // ...
}
inline void swap(HasPtr &lhs, HasPtr &rhs) {
    using std::swap;
    swap(lhs.ps, rhs.ps);   // 交换指针，而不是string数据
    swap(lhs.i, rhs.i);     // 交换int成员
}
```

```c++
void swap(Foo &lhs, Foo &rhs) {
    using std::swap;
    swap(lhs.h, rhs.h); // 使用HasPtr版本的swap，HasPtr的swap函数没有被隐藏
    // std::swap(lhs.h, rhs.h)  // 显示使用标准库版本的swap
}
```

## 在赋值运算符中使用`swap`

copy and swap技术，其自动处理了自赋值的情况且天然就是异常安全的。

```c++
// 注意rhs是按值传递的，意味着HasPtr的拷贝构造函数将右侧运算对象中的string拷贝到rhs
HasPtr& HasPtr::operator=(HasPtr rhs) { // 不是引用
    // 交换左侧运算对象和局部变量rhs的内容
    swap(*this, rhs);   // rhs现在指向本对象曾经使用的内存
    return *this;       // rhs被销毁，从而delete了rhs中的指针
}
```

# 13.4 拷贝控制示例

暂略，参见page460~464


# 13.5 动态内存管理类

赞略，参见page464~470，page428关于`allocator`分配内存

# 13.6 对象移动

标准库容器、`string`和`shared_ptr`类既支持移动也支持拷贝。IO类和`unique_ptr`类可以移动但不能拷贝。

## 13.6.1 右值引用

右值引用就是必须绑定到右值的引用，通过`&&`来获得右值引用。右值引用的一个重要性质是只能绑定到一个将要销毁的对象，因此我们可以自由的将一个右值引用的资源“移动”到另一个对象中。

```c++
int i = 42;
int &r = i;             // 正确：r引用i
int &&rr = i;           // 错误：不能将一个右值引用绑定到一个左值上
int &r2 = i * 42;       // 错误：i*42是一个右值
const int &r3 = i * 42; //正确：我们可以将一个const的引用绑定到一个右值上
int &&rr2 = i*42        // 正确：将rr2绑定到乘法结果上
```

### 左值持久，右值短暂

右值引用只能绑定到临时对象，我们得知：1.所引用的对象将要被销毁，2.该对象没有其他用户。因此使用右值引用的代码可以自由地接管所引用的对象的资源。

### 变量时左值

```c++
int &&rr1 = 42;     // 正确：字面常量是右值
int &&rr2 = rr1;    // 错误：表达式rr1是左值！
```

### 标准库`move`函数

```
#include<utility>

int &&rr3 = std::move(rr1); // 正确
```
我们可以销毁一个move后的源对象，也可以赋予它新值，但是不能使用一个move后源对象的值。

使用`move`的代码应该使用`std::move`而不是`move`。这样做可以避免潜在的名字冲突。

## 13.6.2 移动构造函数和移动赋值运算符

移动构造函数的第一个参数是该类型的一个右值引用，任何额外参数都必须有默认实参。

```c++
StrVec::StrVec(StrVec &&s) noexcept // 移动操作不应抛出任何异常
    // 成员函数接管s中的资源
    : elements(s.elements), first_free(s.first_free), cap(s.cap) {
        // 令s进入这样的状态：对其运行析构函数是安全的
        s.elements = s.first_free = s.cap = nullptr;
    }
```

### 移动操作、标准库容器和异常

我们必须在类头文件的声明中和定义中都指定`noexcept`。不抛出异常的移动构造函数和赋值运算符必须标记为`noexcept`

```c++
class StrVec {
public:
    StrVec(StrVec&&) noexcept;  // 移动构造函数
    // 其他成员的定义，如前
};

StrVec::StrVec(StrVec &&s) noexcept : /* 成员初始化器 */ {
    /* 构造函数体 */
}
```

### 移动赋值运算符

```c++
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
    // 直接检查自赋值
    if (this != &rhs) {
        free();                     // 释放已有元素
        elements = rhs.elements;    // 从rhs接管资源
        first_free = rhs.first_free;
        cap = rhs.cap;
        // 将rhs置于可析构的状态
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this
}
```

### 移后源对象必须可析构

但用户不能对其值进行任何假设。

### 合成的移动操作

只有当一个类没有定义任何自己版本的拷贝控制成员，且类的每个非`static`数据成员都可以移动时，编译器才会为它合成移动构造函数和移动赋值运算符。

移动操作永远不会隐式定义为删除的函数。





## 13.6.3 右值引用和成员函数

