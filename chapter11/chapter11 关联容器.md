
- map：key-value对
  - `map`
  - `multimap`：multi-允许重复key
  - `unordered_map`：unordered-无序，用哈希函数组织
  - `unordered_multimap`

- set：只包含key
  - `set`
  - `multiset`
  - `unordered_set`
  - `unordered_multiset`


# 11.1 使用关联容器

```c++
// 统计输入中每个单词出现的次数
map<string, size_t> word_count; // string到size_t的空map
set<string> exclude = {"The", "But", "And", "Or", "An", "A",
                       "the", "but", "and", "or", "an", "a"};
string word;
while (cin >> word)
    // find函数如果没有找到word，返回尾后迭代器
    if (exclude.find(word) == exclude.end())
        // 如果word不存在于word_count，则新建对象并初始化为0
        ++word_count[word]; //获取并递增word的计数器
```

# 11.2 关联容器概述

## 11.2.1 定义关联容器

```c++
map<string, size_t> word_count; // 空容器
// 列表初始化
set<string> exclude = {"The", "But", "And", "Or", "An", "A",
                       "the", "but", "and", "or", "an", "a"};
// 三个元素; authors将姓映射为名
map<string, string> authors = {
    {"Joyce", "James"}, // {key, value}
    {"Austen", "Jane"},
    {"Dickens", "Charles"}
}
```

### 初始化`multimap`或`multiset`

```c++
vector<int> ivec;
for (vector<int>::size_type i = 0; i != 10; ++i) {
    ivec.push_back(i);
    ivec.push_back(i);  // 每个数重复保存一次
}

// iset包含来自ivec的不重复元素; multiset包含所有20个元素
set<int> iset(ivec.cbegin(), ivec.cend());
multiset<int> miset(ivec.cbegin(), ivec.cend());
cout << ivec.size() << endl;    // 20
cout << isec.size() << endl;    // 10
cout << miset.size() << endl;   // 20
```

## 11.2.2 关键字类型的要求

### 有序容器的关键字类型

在实际编程中，如果一个类型定义了“行为正常”的`<`运算符，则它可以用作关键字类型。

### 使用关键字类型的比较函数

Q: 不是很理解

```c++
bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs) {
    return lhs.isbn() < rhs.isbn(); 
}

// bookstore中多条记录可以有相同的ISBN
// bookstore中的元素以ISBN的顺序进行排序
multiset<Sales_data, decltype(compareIsbn)*>
    bookstore(compareIsbn); // or bookstore(&compareIsbn)
    // 在使用一个函数的名字时，在需要的情况下它会自动转化为一个指针
```

## 11.2.3 `pair`类型

`pair`定义在`utility`中。`map`的元素是`pair`。

```c++
pair<string, string> author{"James", "Joyce"}
// author.first = "James", author.second = "Joyce" 
```

|||
|:-|:-|
|`pair<T1, T2> p`|`p`是一个`pair`，两个类型分别为`T1`和`T2`的成员都进行了值初始化|
|`pair<T1, T2> p(v1, v2)`|`p`是一个成员类型为`T1`和`T2`的`pair`;`first`和`second`成员分别用`v1`和`v2`进行初始化|
|`pair<T1, T2> p={v1, v2}`|和上面等价|
|`p.first`|返回`p`的名为`first`的公有数据成员|
|`p.second`|返回`p`的名为`second`的公有数据成员|
|`p1 relop p2`|关系运算符(`<`, `>`, `<=`, `>=`)按字典序定义：例如，当`p1.first < p2.first`或`!(p2.first < p1.first) && p1.second < p2.second`成立时，`p1 < p2`为`true`。关系运算利用元素的`<`运算符来实现|
|`p1 == p2`|当`first`和`second`成员分别相等时，连个`pair`相等。相等性判断利用元素的`==`运算符实现|

```c++
pair<string, int> process(vector<string> &v) {
    if (!v.empty())
        // return make_pari(v.back(), v.back().size())
        return {v.back(), v.back().size()}; // 列表初始化
    else
        return pair<string, int>();
}
```

# 11.3 关联容器操作

```c++
set<string>::value_type v1;
set<string>::key_type v2;   // set的value_type和key_type相同，此处均为string
map<string, int>::value_type v3;    // pair<const string, int>
map<string, int>::key_type v4;      // v4是一个string
map<string, int>::mapped_type v5;   // v5是一个int。只有个各种map类型才有mapped_type
```

## 11.3.1 关联容器迭代器

一个`map`的`value_type`是一个`pair`，我们可以改变`pair`的值，但不能改变关键字成员的值。

```c++
// 获得指向word_count中一个元素的迭代器
auto map_it = word_count.begin(); // *map_it是指向一个`pair<const string, size_t>对象的引用
cout << map_it->first;
cout << " " << map_it->second;
map_it->firt = "new key";   # 错误：关键字是const，不能修改
++map_it->second;           # 正确：可以通过迭代器改变元素
```

### `set`的迭代器是`const`的

### 遍历关联容器

