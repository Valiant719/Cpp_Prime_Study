
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
