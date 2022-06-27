
```rust
// 来自群友提问
use std::marker::Send;

struct SendPtr(*mut i32);
unsafe impl Send for SendPtr{}

fn f(_: impl FnOnce() + Send) {}

fn main(){
    let mut i = 42;
    let a: SendPtr = SendPtr(&mut i);
    f(move || {
        // 注释掉这一行会报"`*mut i32` cannot be sent between threads safely"。
        // 原因是2021版的disjoint-capture，没有这行只会move掉a.0。
        let a = a;
        let SendPtr(c) = a;
    });
}
```

```rust
#[derive(Debug)]
enum E {
    A(i32),
    B(i32),
}

fn main() {
    let e = E::A(42);
    let is_a = matches!(e, E::A(..));
    let (E::A(i) | E::B(i)) = e; // 注意这个pattern
    
    dbg!(i);
    if is_a {
        println!("is A");
    }
    dbg!(i);
}
```


`cargo rustc`和`cargo build`一样，但可以往rustc里传参数。`-C`意为codegen options。

```
cargo rustc -- -C link-args="-nostartfiles"
```

静态链接libc
```
cargo rustc -C target-feature=+crt-static
```


TODO: 这段什么意思呢？https://os.phil-opp.com/double-fault-exceptions/
> Reload code segment register: We changed our GDT, so we should reload cs, the code segment register. This is required since the old segment selector could point to a different GDT descriptor now (e.g. a TSS descriptor).


宏里用到unsafe要加个#[allow(unused_unsafe)]，不然如果用户在外面套了层unsafe会报warning。
