
类的基本思想是**数据抽象**（data abstraction）和**封装**（encapsulation）。数据抽象是一种依赖于**接口**（interface）和**实现**（inplementation)分离的编程（及设计）技术。类的用户只能使用接口而无法访问实现部分。

# 7.1 定义抽象数据类型

## 7.1.2 定义改进的`Sales_data`类

成员函数的声明必须在类的内部，它的定义则既可以在类的内部也可以在类的外部。定义在类内部的函数是隐式地inline函数。

### 引入`this`

```c++
std::string isbn() const { return bookNo; }
std::string isbn() const { return this->bookNo}
```

成员函数通过一个名为**`this`**的额外的隐式参数来访问调用它的那个对象。当我们调用一个成员函数时，用请求该函数的对象地址初始化`this`。

```c++
total.isbn() => 伪码：Sales_data::isbn(&total)
```

`this`是一个常量指针，我们不允许改变`this`中保存的地址。

### 引入`const`成员函数

`isbn`中紧随参数列表的`cosnt`关键字的作用是隐式修改`this`指针的类型。`isbn`中`this`的类型为：`const Sales_data *const`。如果没有`cosnt`关键字，则`this`的类型为：`Sales_data *const`，只有非常量版本的对象可以调用该函数。

像这样使用`const`的成员函数被称作常量成员函数（const member function）。常量对象以及常量对象的引用或者指针只能调用常量成员函数

可以把`isbn`的函数体想象成：

```c++
std:string Sales_data::isbn(const Sales_data *const this) {
    return this->bookNo;
}
```

### 类作用域和成员函数

- 类本身就是一个作用域
- 编译器分两步处理类：首先编译成员的声明，然后才轮到成员函数体。因此成员函数可以随意使用类中的其他成员而无须在意这些成员出现的次序。

### 在类的外部定义成员函数

```c++
// 注意作用域运算符
double Sales_data::avg_price() const {
    if (units_sold)
        return revenue / units_sold;
    else
        return 0;
}
```

### 定义一个返回`this`对象的函数

```c++
Sales_data& Sales_data::combine(const Sales_data &rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}
```
`total.combine(trans)`返回的是`total`的引用。

## 7.1.3 定义类相关的非成员函数

一般来说，如果非成员函数时接口的组成部分，则这些函数的声明应该与类在同一个头文件内。

拷贝类的对象其实拷贝的是类的数据成员。


## 7.1.4 构造函数

不同于其他成员函数，构造函数不能被声明成`const`的。

### 合成的默认构造函数

类通过一个特殊的构造函数来控制默认初始化过程，这个函数叫做**默认构造函数**（default constructor）。默认构造函数无须任何实参。

如果我们的类没有显示的定义构造函数，那么编译器就会为我们隐式地定义一个默认构造函数。编译器构造的函数又被称为**合成的默认构造函数**（synthesized default constructor）。构造规则：
- 如果存在类内的初始值，用它来初始化成员。
- 否则，默认初始化该成员。

### 某些类不能依赖于合成的默认构造函数

一旦我们定义了一个其他的构造函数，那么除非我们再定义一个默认的构造函数，否则类将没有默认构造函数。

合成的默认函数可能执行错误的操作。

编译器不能为某些类合成默认构造函数。e.g. 成员没有默认构造函数

### 定义`Sales_data`的构造函数

```c++
struct Sales_data {
    Sales_data() = defualt;
    Sales_data(const std::string &s): bookNo(s) {};
    Sales_data(const std::string &s, unsigned n, double p): bookNo(s), units_sold(n), revenue(p*n);
    Sales_data(std::istream &);
    std::string isbn() const { return bookNo; };
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    std:: string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0
}
```


### `=default`的含义

要求编译器生成构造函数 

### 构造函数初始值列表

冒号以及花括号之间的部分称为**构造函数初始值列表**（constructor initialize list），负责为新创建的对象的一个或几个数据成员赋初值。

```c++
Sales_data(const std::string &s):
           bookNo(s), units_sold(0), revenue(0) { }
```

## 7.1.5 拷贝、赋值和析构

```c++
total = trans 

// Sales_data的默认赋值操作等价于：
total.bookNo = trans.bookNo;
total.units_sold = trans.units_sold;
total.revenue = trans.revenue;
```

当类需要分配类对象之外的资源时，合成版本常常会失效。

很多需要动态内存的类能（而且应该）使用`vector`对象或者`string`对象管理必要的存储空间。使用`vector`和`string`的类能避免分配和释放内存带来的复杂性。


## 7.2 访问控制与封装

访问说明符（access specifiers）：

- 定义在`public`之后的成员在整个程序内可被访问，`public`成员定义类的接口。
- 定义在`private`之后的成员可以被类的成员函数访问，但是不能被使用该类的代码访问，`private`部分封装（即隐藏了）类的实现细节。

`struct`和`class`关键字的唯一区别就是默认的访问权限：
- `struct`默认访问权限为`public`
- `class`默认访问权限为`private`

### 7.2.1 友元

类可以允许其他类或函数访问它的非公有成员，方法是令其他类或者函数成为它的**友元**（friend）

友元的声明仅仅制定了访问权限，而非一个通常意义上的函数声明。如果希望用户能够调用某个友元函数，必须在友元声明之外再专门对函数进行一次声明。

为了使友元函数对类的用户可见，我们通常把友元的声明和类的声明放置在同一个头文件中（类的外部）。

```c++
class Sales_data {
    // 为Sales_data的非成员函数所做的友元声明
    friend Sales_data add(const Sales_data&, const Sales_data&);
    friend std::istream &read(std::istream&, Sales_data&);
    friend std::ostream &print(std::ostream&, const Sales_data&);
    // 其他成员及访问符与之前一致
    public:
        Sales_data() == default;
        Sales_data(const std::string &s, unsigned n, double p):
                   bookNo(s), units_sold(n), revenue(p*n) {}
        Sales_data(std::string &s): bookNo(s) {}
        Sales_data(std::istream&);
        std::string isbn() const {return bookNo;}
        Sales_data &conbime(const Sales_data&);
    private:
        std::string bookNo;
        unsigned units_sold = 0;
        double revenue = 0.0;
};
// Sales_data接口的非成员函数部分的声明
Sales_data add(const Sales_data&, const Sales_data&);
std::istream &read(std::istream&, Sales_data&);
std::ostream &print(std::ostream&, const Sales_data&);
```

# 7.3 类的其他特性

## 7.3.1 类成员再探

```c++
class Screen {
    public:
        // using pos=std::string::size_type
        typedef std::string::size_type pos; // 类型别名，必须先定义再使用，所以通常定义再开头
        Screen() = default; //因为Screen有另一个构造函数，所以本函数是必需的
        Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht * wd, c) {}
        char get() const {return contents[cursor];} // 隐式内联
        inline char get(pos ht, pos wd) const;  // 显式内联
        Screen &move(pos r, pos c); // 能在之后被设为内联
    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};

inline Screen &move(pos r, pos c) {
    pos row = r * width;
    cursor = row + c;
    return *this;
}
char Screen::get(pos r, pos c) const {  // 类内显式声明为内联
    pos row = r * width;
    return contents[row + c];
}
```

最好只在类外部定义的地方说明`inline`。

**可变数据成员**

一个**可变数据成员（mutable data member）**永远不会是`const`，即使它是`const`对象的成员。

```c++
// 即使在一个const对象内也能被修改
mutable size_t access_ctr;
```

## 7.3.2 返回`*this`的成员函数

如果返回的是引用，可以以`myScreen.move(4.0).set('#')`的方式链式调用。

一个`const`成员函数如以引用的形式返回`*this`，那么它的返回类型将是一个常量引用。

因为非常量版本的函数对于常量对象是不可用的，所以我们只能在一个常量对象上调用`const`成员。

## 7.3.3 类类型

### 类的声明

```c++
class Screen;   // 前向声明
struct Screen;
```
前向声明（forward declaration）：它向程序中引入名字Screen并且指明Screen是一种类类型。其在声明之后定义之前是一个**不完全类型**。可以定义指向这种类型的指针或引用，也可以声明（但是不能定义）以不完全类型作为参数或者返回类型的函数，但只有在定义之后才能用引用或指针访问其成员。

一个类的成员类型不能是该类自己，但是可以是指向它自身类型的引用或指针：

```c++
class Link_screen {
    Screen window;
    Link_screen *next;
    Lind_screen *prev;
};
```

## 7.3.4 友元再探

### 类之间的友元关系

```c++
class Screen {
    // Window_mgr的成员可以访问Screen类的私有部分
    friend class Window_mgr;
    // Screen类的剩余部分
};

class Window_mgr {
public:
    // 窗口中每个屏幕的编号
    using ScreenIndex = std::vector<Screen>::size_type;
    // 按照编号将指定的Screen重置为空白
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    // 可以访问Screen的私有部分
    s.contents = string(s.height * s.weight, ' ');
}
```

**友元关系不存在传递性，每个类负责控制自己的友元类和友元函数**，A是B的友元，B是C的友元，不能推出A是C的友元。

### 令成员函数作为友元

```c++
class Screen {
    // Window_mgr::clear必须在Screen类之前被声明
    friend void Window_mgr::clear(ScreenIndex);
    // Screen类的剩余部分
}
```

**必须仔细组织程序的结构以满足声明和定义的彼此依赖关系：**
- 首先定义Window_mgr类，声明其clear函数，**但是不能定义它**。在clear使用Screen的成员之前必须先声明Screen。
- 接下来定义Screen，包括对于clear的友元声明。
- 最后定义clear，此时它才可以使用Screen成员。

### 函数重载和友元

重载函数是不同的函数，所有需要分别声明友元。


### 友元声明和作用域

```c++
struct X {
    friend void f() {/* 友元函数可以定义在类的内部 */}
    X() { f(); }    // 错误：f还没有被声明
    void g();
    void h();
};
void X::g() { return f(); } // 错误：f还没有被声明
void f();                   // 声明那个定义在X中的函数
void X::h() { return f(); } // 正确，现在f的声明在作用域内
```

**就算在类的内部定义友元函数，我们也必须在类的外部提供相应的声明从而使得函数可见。**
注：没有太看懂。


## 7.4 类的作用域

一个类就是一个作用域。
```c++
class Window_mgr {
public:
    ScreenIndex addScreen(const Screen&);
    // 其他成员与之前的版本一致
};

// 返回类型在Window_mgr作用域之外，所以需要使用Window_mgr::ScreenIndex
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s) {
    screens.push_back(s); // Window_mgr作用域内，可以使用Window_mgr成员screens
    return screens.size() - 1;
}
```


### 7.4.1 名字查找与类的作用域

类的定义分两步处理：1. 首先，编译成员的声明；2. 知道类全部可见后才编译函数体。这使得**成员函数**可以使用类中定义的任何名字。

声明中使用的名字，包括返回类型或者参数列表中使用的名字，**都必须在使用前确保可见**。

#### 用于类成员声明的名字查找

#### 类型名要特殊处理

```c++
typedef double Money;
class Account {
public:
    Money balance() { return bal; } // 使用外层作用域的Money，和数据成员bal
private:
    typedef double Money;   // 错误：不能重新定义Money
    Money bal;
}
```

#### 成员定义中的普通块作用域的名字查找

成员函数内 $\Longrightarrow$ 类内 $\Longrightarrow$ 在函数定义之前的作用域内继续查找

```c++
void Screen::dummy_fcn(pos height) {
    cursor = width * height         // 参数height，成员函数height被隐藏
    cursor = width * this->height;  // 成员height
    cursor = width * Screen::height // 成员height
}
```

#### 类作用域之后，在外围的作用域中查找


#### 在文件中名字的出现处对其进行解析

page 257


## 7.5 构造函数再探

### 构造函数的初始值有时必不可少

如果成员是cosnt、引用，或者属于某种未提供默认构造函数的了类型，我们必须通过构造函数初始值列表为这些成员提供初始值。

```c++
class ConstRef {
public:
    ConstRef(int ii);
private:
    int i;
    const int ci;
    int &ri;
}

ConstRef:ConstRef(int ii) { // 赋值
    i = ii;     // 正确
    ci = ii;    // 错误：不能给const赋值
    ri = i;     // 错误：ri没被初始化
}

// 正确：显示的初始化引用和const成员
ConstRef:ConstRef(int ii): i(ii), ci(ii), ri(i) {};
```

### 成员初始化的顺序

初始值列表的成员初始化顺序与它们在类定义中的出现顺序一致。

最好令构造函数初始值的顺序与成员函数声明的顺序保持一致。而且如果可能的话，尽量避免使用某些成员初始化其他成员。

```c++
class X {
    int i;
    int j;
public:
    // 虽然初始值列表中j在i直线，但实际的初始化顺序是先初始化i再初始化j
    X(int val): j(val), i(j) {} // 未定义的：i在j之前被初始化
}
```

### 默认实参和构造函数

如果一个构造函数为所有参数都提供了默认实参，则它实际上也定义了默认构造函数。

```c++
class Sales_data {
public:
    // 定义默认构造函数，令其与只接受一个string实参的构造函数功能相同
    Sales_data(std::string s, unsigned cnt, double rev):
        bookNo(s), units_sold(cnt), revenue(rev * cnt) {}
    Sales_data(std::istream &is) { read(is, *this); }
    // 其他成员与之前的版本一致
};
```

## 7.5.2 委托构造函数

```c++
class Sales_data {
public:
    // 非委托构造函数使用对应的实参初始化成员
    Sales_data(std::string s, unsigned cnt, double price):
        bookNo(s), units_sold(cnt), revenue(cnt*price) {}
    Sales_data(): Sales_data("", 0, 0) {}
    Sales_data(std::string s): Sales_data(s, 0, 0) {}
    Sales_data(std::istream &is): Sales_data() {
        read(is, *this);
    }
    // 其他成员与之前的版本一致
}
```
构造函数 $\Longrightarrow$ 受委托构造函数的初始值列表和函数体 $\longrightarrow$ 函数体


## 7.5.3 默认构造函数的作用

在实际中，如果定义了其他构造函数，那么最好也提供一个默认构造函数。

page 262


## 7.5.4 隐式地类类型转换

如果构造函数只接受一个实参，则它实际上定义了转换为此类型的隐式转换机制，有时我们把这种构造函数称为**转换构造函数（converting constructor）**。

```c++
string null_book = "9-999-99999-9"
// null_book => 构造一个临时的Sales_data对象 => 传入combine函数
// 该对象的units_sold和revenue等于0, bookNo等于null_book
item.combine(null_book); 
```

### 只允许一步类类型转换

```
// 错误：需要用户定义的两种转换：
// 1. 把"9-999-99999-9"转换成string
// 2. 再把这个临时的string转换成Sales_data
item.combine("9-999-99999-9");

// 以下两种正确
item.combine(string("9-999-99999-9"))
item.combine(Sales_data("9-999-99999-9"))
```

### 抑制构造函数定义的隐式转换

**只能在类内声明构造函数时使用explicit关键字**, 在类外定义时不应重复.

```c++
class Sales_data {
public:
    Sales_data() = default;
    Sales_data(const std::string &s, unsigned n, double p):
        bookNo(s), units_sold(n), revenue(p*n) {}
    explicit Sales_data(const std::string &s): bookNo(s) {}
    explicit Sales_data(std::string &);
    //其他成员与之前的版本一致
};

// 错误: explicit关键字阻止了隐式转换
item.combine(null_book); 
item.combine(cin);
```

**`explicit`构造函数只能用于直接初始化**

```c++
Sales_data item1(null_book);    // 正确: 直接初始化
Sales_data item2 = null_book;   // 错误: 不能将explicit构造函数用于拷贝形式的初始化过程.
```

尽管编译器不会将`explicit`的构造函数用于隐式转换过程, 但是我们可以使用这样的构造函数显式地强制进行转换.

```c++
// 正确: 实参是一个显示构造的Sales_data对象
item.combine(Sales_data(null_book));
// 正确: static_cast可以使用explicit的构造函数
item.combine(static_cast<Sales_data>(cin))
```

接受一个单参数的`cosnt char*`的`string`的构造函数不是`explicit`的. 接受一个容量参数的`vector`构造函数时`explicit`的. 

## 7.5.5 聚合类

如果一个类满足以下条件时, 我们说它是**聚合**的:

- 所有成员都是`public`的
- 没有定义任何构造函数
- 没有类内初始值
- 没有基类, 也没有`virtual`函数

```c++
struct Data {
    int ival;
    string s;
}

Data val1 = {0, "Anna"}
Data val2 = {"Anna", 0}     // 错误: 初始值的顺序必须与声明的顺序一致
```

注: 缺点参考page267, 不宜使用.


## 7.5.6 字面值常量类

注: page268, 有需要再深入


# 7.6 类的静态成员

## 声明静态成员

```c++
class Account {
public:
    void calculate() { amount += amount * interestRate; }
    static double rate() { return interestRate; }
    static void rate(double);
private:
    std::string owner;
    double amount;
    static double interestRate;
    static double initRate();
}
```

类的静态成员存在于任何对象之外, 对象中不包含任何与静态数据成员有关的数据. 静态成员函数不与任何对象绑定在一起, 它们不包含`this`指针. 作为结果, 静态成员函数不能声明成`const`的, 而且我们也不能在`static`函数体内使用`this`指针. 这一限制既适用于`this`的显示使用, 也对调用非静态成员的隐式使用有效.

## 使用类的静态成员

```c++
double r;
// 使用作用域运算符访问静态成员
r = Account::rate();

// 使用对象, 引用或者指针来访问静态成员
Account ac1;
Account *ac2 = &ac1;
r = ac1.rate();
r = ac2->rate();

// 成员函数不用通过作用域运算符就能直接使用静态成员
class Account {
public:
    void calculate() { amount += amount * interestRate; }
private:
    static double interestRate;
    // 其他成员与之前的版本一致
}
```

## 定义静态成员

当在类的外部定义静态成员时, 不能重复`static`关键字, 该关键字只出现在类内部的是声明语句(与`explicit`关键字类似).

```c++
void Account::rate(double newRate) {
    interestRate = newRate;
}
```

类似于全局变量, 静态数据成员定义在任何函数之外. 因此一旦它被定义, 就将**一直存在于程序的整个生命周期中**. 静态数据成员不是由类的构造函数初始化的, 而且一般的我们不能在类的内部初始化静态成员. 相反**我们必须在类的外部定义和初始化每个静态成员**. 和其他对象一样, 一个静态数据成员只能定义一次. 

```
double Account::interestRate = initRate();
```

要确保对象只定义一次, 最好的办法是把静态数据成员的定义与其他非内联函数的定义放在同一个文件中. 

## 静态成员的类内初始化

通常情况下, 类的静态成员不应该在类的内部初始化. 然而我们可以为静态类型提供`const`整数类型的类内初始值, 不过要求静态成员必须是字面值常量类型的`constexpr`. 初始值必须是常量表达式, 因为这些成员本身就是常量表达式, 所以它们能用在所有适合于常量表达式的地方.

```c++
class Account {
public:
    static double rate() { return interestRate; }
    static void rate(double);
private:
    static constexpr int period = 30;   // period是常量表达式
    double daily_tbl[period];
}
```

如果在类的内部提供了一个初始值, 则成员的定义不能再指定一个初始值了:
```c++
// 一个不带初始值的静态成员的定义
constexpr int Account::period;  // 初始值在类的定义内提供
```


## 静态成员能与同于某些场景, 而普通成员不行

非静态成员不能是不完全类型,静态成员可以

```c++
class Bar {
public:
    // ...
private:
    static Bar mem1;    // 正确: 静态成员可以是不完全类型
    Bar *mem2;          // 正确: 指针成员可以是不完全类型
    Bar mem3;           // 错误: 非静态成员必须是完全类型
}
```

非静态成员不能作为默认实参, 静态成员可以

```c++
class Screen {
public:
    Screen& clear(char = bkground);
private:
    static const char bkground;
}
```