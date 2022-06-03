# 如何编译Rust的alloc

alloc的代码在`~/.rustup/toolchains/$TOOLCHAIN/lib/rustlib/src/rust/library/alloc`

建议cp一份出来，不要直接在toolchain里改。

直接编译会有蜜汁错误。

把alloc的`Cargo.toml`里的这些东西都注释掉。

> 实际上我不太确定这么做的效果，但是各种猜测让我这么试了一下，成功了。目测是用了编译器自带的。

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

现在可以正常编译了，这里我想编译一份带private items的文档。

> 之前以为要加`-Z --build-std=alloc`，删掉以后发现不用。

```
$ cargo doc --open --document-private-items
```
