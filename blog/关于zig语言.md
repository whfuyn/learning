# 关于Zig语言

TODO

## 为什么想看Zig？

其实很早以前就知道这么个语言。当时知乎有个提问“如何评价zig语言”，下面几个高可信度的答主给的评价比较差，后面也就没有再深入了解了。

前段时间看到一则新闻，细节忘了，说是某个东西打算重构，作者想用Zig，但由于社区倾向而选择了Rust。

这让我对Zig产生了些兴趣，在某个无聊的晚上花了点时间学它。

## 看到的亮点

如果说Rust的定位是Better C++，那么Zig的定位就是Better C。

- 编译期计算，元编程、泛型、特化
- 比C快，无符号整数溢出的未定义行为
- 异步
- 交叉编译
- use C libraries better than C
- 堆分配需传allocator
- defer
- No hidden control flow; no hidden allocation; no preprocessor nor macros.
- error handling, error code
- 未定义行为检查
- competitive libc
- 可以编译C
- 作为C/C++的工具链（对比cmake）
- 成熟度（2025年）
- 非move，是guaranteed copy elision
- 传参数由编译器决定是by value还是by ref


### 比C语言更好地调用C的库


