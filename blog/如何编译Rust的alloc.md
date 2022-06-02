# 如何编译Rust的alloc

把`Cargo.toml`里的这些东西都注释掉。

> 实际上我不太确定这么做的效果，但各种猜测让我这么试了一下，成功了。

```toml
[dependencies]
# core = { path = "../core" }
# compiler_builtins = { version = "0.1.40", features = ['rustc-dep-of-std'] }

[features]
# compiler-builtins-mem = ['compiler_builtins/mem']
# compiler-builtins-c = ["compiler_builtins/c"]
# compiler-builtins-no-asm = ["compiler_builtins/no-asm"]
# compiler-builtins-mangled-names = ["compiler_builtins/mangled-names"]

```

可以编译了，这里我想编译一份带private items的文档。

其它操作也是一样的，加上target和build-std。

```
$ cargo doc --open --document-private-items --target x86_64-unknown-linux-gnu -Z build-std=alloc
```
