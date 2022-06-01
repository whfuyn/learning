// Page 332
// zig build-exe ex10_5.zig -lc

// ➜  signals git:(master) ✗ ./ex10_5
// in signal handler
// in signal handler
// in signal handler
// in signal handler
// in signal handler
// return value corrupted, pw_name = root
// in signal handler
// in signal handler
// thread 10784 panic: getpwnam failed
// ...(stack trace omitted)...
// [1]    10784 abort      ./ex10_5

const std = @import("std");
const C = @cImport({
    @cInclude("unistd.h");
    @cInclude("errno.h");
    @cInclude("signal.h");
    @cInclude("pwd.h");
    @cInclude("string.h");
});

const Error = error{
    FailedToRegister,
};

fn myAlarm(_: c_int) callconv(.C) void {
    const stdout = std.io.getStdOut().writer();
    stdout.print("in signal handler\n", .{}) catch @panic("stdout print failed");

    var rootptr = C.getpwnam("root");
    if (rootptr == null) {
        @panic("getpwnam failed");
    }
    _ = C.alarm(1);
}

pub fn main() !void {
    const stdout = std.io.getStdOut().writer();
    const stderr = std.io.getStdErr().writer();

    if (C.signal(C.SIGALRM, myAlarm) == C.SIG_ERR) {
        try stderr.print("failed to register for SIGALARM\n", .{});
        return Error.FailedToRegister;
    }
    _ = C.alarm(1);

    var fyptr: [*c]C.struct_passwd = undefined;
    while (true) {
        fyptr = C.getpwnam("fy");
        if (fyptr == null) {
            @panic("getpwnam failed");
        }
        if (C.strcmp(fyptr.*.pw_name, "fy") != 0) {
            try stdout.print("return value corrupted, pw_name = {s}\n", .{fyptr.*.pw_name});
        }
    }
}
