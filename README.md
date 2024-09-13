Lab 3: Time, fork, exec, process, command, pipe, shared memory

Execution time of a given command using three different methods:
1. fork and execute, time is calculated by the parent before and after
2. shared memory to get the starting time from the child, end time is calculated by the parent itself
3. pipe to pass message(start time) from child to parent

usage: filename(exe) <command> [args ...]

time taken:
1. simple = 0.00172 seconds
2. shared =  0.00092 seconds
3. pipe = 0.00100 seconds

average time taken(10 epochs):
1. simple = 1.31 ms
2. shared = 1.10 ms
3. pipe = 1.12 ms

* normal approach includes scheduling and context switch overhead. hence the most time taken is by this approach

* both pipe and shared gives much better results, although,  pipe takes a little more time than shared as there may be slight overhead due to pipe i/o operations