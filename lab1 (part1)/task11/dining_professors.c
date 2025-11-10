/*
Task 11. Dining Professors, deadlock-free implementation
Modify the program from Task 10 so the program is deadlock-free, i.e., you can guarantee that no deadlock can occur.

Which are the four conditions for deadlock to occur?

Mutual Exclusion: At least one resource must be non-shareable, meaning only one process can use it at a time.
Hold and Wait: A process must be holding at least one resource while waiting to acquire additional resources held by other processes.
No Preemption: Resources cannot be forcibly taken away from a process; they can only be released voluntarily by the process holding them.
Circular Wait: A circular chain of processes must exist, where each process is waiting for a resource held by the next process in the chain

Which of the four conditions did you remove in order to get a deadlock-free program, and how did you do that in your
program?
*/