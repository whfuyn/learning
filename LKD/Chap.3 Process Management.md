# Chap.3 Process Management

## Important Data Structures

`current`
- arch-specific
- return the current `task_struct*`

`task_struct`
- common process info
- allocated via slab allocator.

`thread_info`
- stores arch-specific info
- lives in the end of the kernel stack.

When `CONFIG_THREAD_INFO_IN_TASK` is defined, `thread_info` lives in the head of `task_struct`, allowing casting `task_struct*` to `thread_info*`.

```C
#ifdef CONFIG_THREAD_INFO_IN_TASK
/*
 * For CONFIG_THREAD_INFO_IN_TASK kernels we need <asm/current.h> for the
 * definition of current, but for !CONFIG_THREAD_INFO_IN_TASK kernels,
 * including <asm/current.h> can cause a circular dependency on some platforms.
 */
#include <asm/current.h>
#define current_thread_info() ((struct thread_info *)current)
#endif

```

## Process State

- TASK_RUNNING
    - running.
    - ready but not running.
    - it's the only possible state for a process executing in user space.
- TASK_INTERRUPTIBLE
    - sleep but interruptible.
    - waiting for some condition.
    - become runable if it receives a signal.
- TASK_UNINTERRUPTIBLE
    - same as previous but not interruptible.
    - used when it must wait without interruption  or it's expected to be quick.
- __TASK_TRACED
    -  been traced by another process(e.g. debugger).
- __TASK_STOPPED
    - not running nor eligible to run
    - occurs if the task receives SIGSTOP, SIGTSTP, SIGTTIN or if it receives any signal while it's being debugged.


## Forking

Use some flags to control whether to share resources.

## Process Termination

do_exit():
- It sets `PF_EXITING` flag in `flags` of `task_struct`
- exit_*()
- During exit_notify(), tsk->exit_state = EXIT_ZOMBIE
- do_task_dead(), calls __schedule(..)

At this point, the only memory it occupies is its
- kernel stack
- `thread_info`
- `task_struct`

After the parent retrieves the info(`wait` family) or notify the kernel that it is uninterested. The remaining memory is freed.

When to deallocate process descriptor, release_task() is called


## Parentless Task
If a parent exits before its children, we need to reparent those children to a new process.

It's the processes in the same thread group or finally the `init`.

find_new_reaper

## Related Articles

[Why thread_info should be the first element in task_struct?](https://stackoverflow.com/questions/61886139/why-thread-info-should-be-the-first-element-in-task-struct)

[linux 进程内核栈](https://zhuanlan.zhihu.com/p/296750228)

https://notes.shichao.io/utlk/ch3/
