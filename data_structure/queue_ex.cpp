#ifndef QUEUE_EX
#define QUEUE_EX


#ifndef TEST
#define TEST
#define TEST_EX
#endif



#include "queue.cpp"

struct Customer
{
    int window;
    unsigned int time;
};

int bestWindow(Queue<Customer> windows[], int nWin);
void simulate(int nWin, int servTime);


void simulate(int nWin, int servTime)
{
    Queue<Customer> * windows = new Queue<Customer>[nWin];
    for (int now = 0; now < servTime; ++now)
    {
        if (rand() % (1 + nWin))
        {
            Customer c;
            c.time = 1 + rand() % 98;
            c.window = bestWindow(windows, nWin);
            windows[c.window].enqueue(c);
        }
        for (int i = 0; i < nWin; ++i)
        {
            if (!windows[i].empty())
                if (--windows[i].front().time <= 0)
                    windows[i].dequeue();
        }
    }
    delete [] windows;
}

int bestWindow(Queue<Customer> windows[], int nWin)
{
    int minsize = windows[0].size();
    int optWin = 0;
    for (size_t i = 0; i < nWin; ++i)
    {
        if (minsize > windows[i].size())
        {
            minsize = windows[i].size();
            optWin = i;
        }
    }
    return optWin;
}

#ifdef TEST_EX

int main()
{
    simulate(5, 3600);
}

#endif


#endif