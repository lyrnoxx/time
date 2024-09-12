Lab 3: Time, fork, exec, process, command, pipe, shared memory

Execution time of a given command using three different methods:
1. fork and exec(time is calculated by the parent)
2. shared memory to get the starting time from the child
3. pipe to pass message(start time) from child to parent

usage: filename(exe) <command> [args ...]

time taken:
1. simple = 0.00368 seconds
2. shared =  0.00354 seconds
3. pipe = 0.00381 seconds