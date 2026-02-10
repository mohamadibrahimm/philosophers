This project has been created as part of the 42 curriculum by mohamaib.

Philosophers:
Description

This project implements the Dining Philosophers problem in C using threads and mutexes.
Each philosopher is a thread that must eat, sleep, and think while sharing forks safely.
The program detects when a philosopher dies if they do not eat within a given time.

Instructions to run

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]

Resources

Dining Philosophers: https://en.wikipedia.org/wiki/Dining_philosophers_problem
POSIX Threads: https://man7.org/linux/man-pages/man7/pthreads.7.html

Use of AI

AI was used to understand concurrency concepts, debug synchronization issues, and assist with