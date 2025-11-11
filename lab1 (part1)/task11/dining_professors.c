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

We eliminated Circular wait.

It was achieved by using semaphore. To put it shortly a semaphore allows the code to run as usual
but on allows 4 processes at a time meaning the last professor needs to wait which in this case is
Silberschartz. Silberschartz can pick up his first chopstick as soon as any professor has eaten.

*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
// To prevent Deadlocks
#include <semaphore.h>

sem_t limit;

// Every professor has one chopstick to his left, total of 5
pthread_mutex_t chopsticks[5];
// Five professors
const char* names[5] = {
    "Tanenbaum", "Bos", "Lamport", "Stallings", "Silberschatz"
};

// Thinking for 1 to 5 seconds OR 2 to 8 seconds OR 5 to 10 seconds
int random_between(int max, int min) {
    int t = rand() % (max - min + 1) + min;
    return t;
}

void* professor(void* arg) {
    int id = *(int*)arg;
    int left = id;
    int right = (id + 1) % 5;

    sem_wait(&limit);

    // Let the professors think a random time between one and five seconds
    int t = random_between(5, 1);
    printf("%s: thinking for %d seconds\n", names[id], t);
    sleep(t);

    // Take the left chopstick
    printf("%s aquiring left chopstick as soon as it is avaialabe\n", names[id]);
    pthread_mutex_lock(&chopsticks[left]);
    printf("%s took the left chopstick\n", names[id]);

    // When they have gotten the left chopstick, let them think in two to eight seconds
    t = random_between(8, 2);
    printf("%s: thinking for %d seconds\n", names[id], t);
    sleep(t);

    // Take the right chopstick.
    printf("%s aquiring right chopstick as soon as it is avaialabe\n", names[id]);
    pthread_mutex_lock(&chopsticks[right]);
    printf("%s took the right chopstick\n", names[id]);

    // Let the professor eat for a random time between five-ten seconds, and then put down both chopsticks
    t = random_between(10, 5);
    printf("%s: eating for %d seconds\n", names[id], t);
    sleep(t);
    pthread_mutex_unlock(&chopsticks[left]);
    pthread_mutex_unlock(&chopsticks[right]);
    printf("%s: done eating\n", names[id]);

    sem_post(&limit);

    return NULL;
}

int main() {
    srand(time(NULL));
    // Every proffesor represent one thread, total of 5
    pthread_t professors[5];
    int ids[5];

    // Initializing chopsticks
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    sem_init(&limit, 0, 4); // Fixes deadlock by keeping one professor from picking up a chopstick.
    // By withholding one professor from equpining a chopstick this makes sure that atleast one pro-
    // fessor can eat, which will clear up space and repeat until all the professors have eaten.

    // Create threads
    for (int i = 0; i < 5; i++)
    {
        ids[i] = i;
        pthread_create(&professors[i], NULL, professor, &ids[i]);
    }

    // Wait for threads to finish (like await JavaScipt)
    for (int i = 0; i < 5; i++)
    {
        pthread_join(professors[i], NULL);
    }

    // Destroy
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_destroy(&chopsticks[i]);
    }
    sem_destroy(&limit);

    return 0;
}
