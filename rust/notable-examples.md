
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

