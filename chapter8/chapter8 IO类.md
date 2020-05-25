
# 8.1 IO类

`ifstream`和`istringstream`都继承自`istream`，`ofstream`和`ostringstream`都继承自`ostream`。

## 8.1.1 IO对象无拷贝或复制

我们不能拷贝或对IO对象赋值。所以也不能将形参或返回类型设置为流类型。

## 8.1.2 条件状态

||说明|
|:-|:-|
|`strm::iostate`|`strm`是一种IO类型。`iostate`是一种机器相关的类型，提供了表达条件状态的完整功能|
|`strm::badbit`|`strm::badbid`用来指出一个流已崩溃|
|`strm::failbit`|`strm::failbid`用来指出一个IO操作失败了|
|`strm::eofbit`|`strm::eofbit`用来指出流到达了文件结束|
|`strm::goodbit`|`strm::goodbit`用来指出流未处于错误状态。此值保证为0|
|`s.eof()`|若流`s`的`eofbit`置位，则返回`true`|
|`s.fail()`|若流`s`的`failbit`或`badbit`置位，则返回`true`|
|`s.bad()`|若流`s`的`badbit`置位，则返回`true`|
|`s.goodl()`|若流`s`处于有效状态，则返回`true`|
|`s.clear()`|将流`s`中所有条件状态位复位，将流的状态设为有效。返回`void`|
|`s.clear(flags)`|根据给定的`flags`标志位，将流`s`中对应条件状态位复位。`flags`的类型为`strm::iostate`。返回`void`|
|`s.setstate(flags)`|根据给定的`flags`标志位，将流`s`中对应条件状态置位。`flags`的类型为`strm::iostream`。返回`void`|
|`s.rdstate()`|返回流`s`的当前条件状态， 返回值类型为`strm::iostate`|


- 如果到达文件结束位置，`eofbit`和`failbit`都会被置位。
- 如果`badbit`、`failbit`和`eofbit`任一个被置位，则检测流状态的条件会失败。（等价于`!fail()）。

###  管理条件状态

```c++
// 复位failbit和badbit，保持其他标志位不变
cin.clear(cin.rdstate() & ~cin.failbit & ~cin.badbit)
```

## 8.1.3管理输出缓冲

导致缓存刷新的原因：page 281

```c++
cout << "hi!" << endl;  // 输出hi和一个换行，然后刷新缓冲区
cout << "hi!" << flush; // 输出hi，然后刷新缓冲区，不附加任何额外字符
cout << "hi!" << end;   // 输出hi和一个空字符，然后刷新缓冲区
```

```c++
cout << unitbuf;    // 所有输出操作后都会立即刷新缓冲区
// 任何输出都立即刷新，无缓冲
cout << nonunitbuf; // 回到正常的缓冲方式
```

### 关联输入和输出流

```c++
cin.tie(&cout)
ostream *old_tie = cin.tie(nullptr) # cin不在与其他流关联
cin.tie(&cerr) // 读取cin会刷新cerr而不是cout
cin.tie(old_tie)    // 重建cin和cout间的关联
```


# 8.2 文件输入输出