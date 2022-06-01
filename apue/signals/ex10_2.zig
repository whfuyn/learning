// Page 324
// zig build-exe ex10_2.zig -lc

// ➜  signals git:(master) ✗ ./ex10_2&
// [1] 6565
// ➜  signals git:(master) ✗ kill -USR1 6565
// recv SIGUSR1
// ➜  signals git:(master) ✗ kill -USR2 6565
// recv SIGUSR2
// ➜  signals git:(master) ✗ kill 6565
// [1]  + 6565 terminated  ./ex10_2

const std = @import("std");
const C = @cImport({
    @cInclude("unistd.h");
    @cInclude("errno.h");
    @cInclude("signal.h");
});

const Error = error{
    FailedToRegister,
};

fn sigUsr(signo: c_int) callconv(.C) void {
    const stdout = std.io.getStdOut().writer();
    const stderr = std.io.getStdErr().writer();
    switch (signo) {
        C.SIGUSR1 => {
            stdout.print("recv SIGUSR1\n", .{}) catch @panic("cannot print to stdout");
        },
        C.SIGUSR2 => {
            stdout.print("recv SIGUSR2\n", .{}) catch @panic("cannot print to stdout");
        },
        else => {
            stderr.print("recv unknown {}\n", .{signo}) catch @panic("cannot print to stderr");
        },
    }
}

pub fn main() !void {
    const stderr = std.io.getStdErr().writer();
    if (C.signal(C.SIGUSR1, sigUsr) == C.SIG_ERR) {
        try stderr.print("failed to register for SIGUSR1\n", .{});
        return Error.FailedToRegister;
    }
    if (C.signal(C.SIGUSR2, sigUsr) == C.SIG_ERR) {
        try stderr.print("failed to register for SIGUSR2\n", .{});
        return Error.FailedToRegister;
    }
    while (true) {
        _ = C.pause();
    }
}
