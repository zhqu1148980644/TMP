Five silent philosophers sit at a round table with bowls of spaghetti. Forks are placed between each pair of adjacent philosophers.

Each philosopher must alternately think and eat. However, a philosopher can only eat spaghetti when they have both left and right forks. Each fork can be held by only one philosopher and so a philosopher can use the fork only if it is not being used by another philosopher. After an individual philosopher finishes eating, they need to put down both forks so that the forks become available to others. A philosopher can take the fork on their right or the one on their left as they become available, but cannot start eating before getting both forks.

Eating is not limited by the remaining amounts of spaghetti or stomach space; an infinite supply and an infinite demand are assumed.

Design a discipline of behavior (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

The problem statement and the image above are taken from wikipedia.org

 

The philosophers' ids are numbered from 0 to 4 in a clockwise order. Implement the function void wantsToEat(philosopher, pickLeftFork, pickRightFork, eat, putLeftFork, putRightFork) where:

-    philosopher is the id of the philosopher who wants to eat.
-    pickLeftFork and pickRightFork are functions you can call to pick the corresponding forks of that philosopher.
-    eat is a function you can call to let the philosopher eat once he has picked both forks.
-    putLeftFork and pickRightFork are functions you can call to put down the corresponding forks of that philosopher.
-    The philosophers are assumed to be thinking as long as they are not asking to eat (the function is not being called with their number).

Five threads, each representing a philosopher, will simultaneously use one object of your class to simulate the process. It is possible that the function will be called for the same philosopher more than once, even before the last call ends.

 

```
Example 1:

Input: n = 1
Output: [[4,2,1],[4,1,1],[0,1,1],[2,2,1],[2,1,1],[2,0,3],[2,1,2],[2,2,2],[4,0,3],[4,1,2],[0,2,1],[4,2,2],[3,2,1],[3,1,1],[0,0,3],[0,1,2],[0,2,2],[1,2,1],[1,1,1],[3,0,3],[3,1,2],[3,2,2],[1,0,3],[1,1,2],[1,2,2]]
Explanation:
n is the number of times each philosopher will call the function.
The output array describes the calls you made to the functions controlling the forks and the eat function, its format is:
output[i] = [a, b, c] (three integers)
- a is the id of a philosopher.
- b specifies the fork: {1 : left, 2 : right}.
- c specifies the operation: {1 : pick, 2 : put, 3 : eat}.
```

 

#### Constraints:

-    1 <= n <= 60


#### Solutions

1. ##### mutex

- reference: https://blog.csdn.net/Yun_Ge/article/details/89177918
- deadlock example:
    - Both A and B need lock a and b.
    - When A acuquired the lock a, and at the same time B acuquired the lock b
    - Then A waits for b and B waits for a, this state would remain the same forever.
- Possible solutions
    - use another lock block the operation of acquiring a or b.
    - Let both A and B requires a first, then require b.    

```c++
class DiningPhilosophers {
public:
    mutex forks[5];
    mutex guard;

    DiningPhilosophers() {} 
    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int l = philosopher;
        int r = (philosopher + 1) % 5;
        guard.lock();
        forks[l].lock();
        forks[r].lock();
        pickLeftFork();
        pickRightFork();
        guard.unlock();
        eat();
        putLeftFork();
        putRightFork();
        forks[l].unlock();
        forks[r].unlock();
    }
};
```

Or

```c++
class DiningPhilosophers {
public:
    mutex forks[5];

    DiningPhilosophers() {} 
    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
        int l = philosopher;
        int r = (philosopher + 1) % 5;
        if (philosopher % 2) {
            forks[l].lock();
            forks[r].lock();
            pickLeftFork();
            pickRightFork();
        }
        else {
            forks[r].lock();
            forks[l].lock();
            pickLeftFork();
            pickRightFork();
        }
        eat();
        putLeftFork();
        putRightFork();
        forks[l].unlock();
        forks[r].unlock();
    }
};
```

```c++
class DiningPhilosophers {
public:
    vector<mutex> mts = vector<mutex>(5);
    DiningPhilosophers() {
        
    }

    void wantsToEat(int philosopher,
                    function<void()> pickLeftFork,
                    function<void()> pickRightFork,
                    function<void()> eat,
                    function<void()> putLeftFork,
                    function<void()> putRightFork) {
		scoped_lock lk(mts[philosopher], mts[(philosopher + 1) % 5]);
        pickLeftFork();
        pickRightFork();
        eat();
        putRightFork();
        putLeftFork();
    }
};
```

Python version

```python
class DiningPhilosophers:
    def __init__(self):
        from threading import Lock
        self.forks = [Lock() for i in range(5)]
        self.guard = Lock()

    # call the functions directly to execute, for example, eat()
    def wantsToEat(self,
                   philosopher: int,
                   pickLeftFork: 'Callable[[], None]',
                   pickRightFork: 'Callable[[], None]',
                   eat: 'Callable[[], None]',
                   putLeftFork: 'Callable[[], None]',
                   putRightFork: 'Callable[[], None]') -> None:
        l = self.forks[philosopher]
        r = self.forks[(philosopher + 1) % 5]
        self.guard.acquire()
        l.acquire()
        r.acquire()
        pickLeftFork()
        pickRightFork()
        self.guard.release()
        eat()
        putLeftFork()
        putRightFork()
        l.release()
        r.release()

        
```

2. ##### scoped lock

```c++

```