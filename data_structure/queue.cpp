#ifndef QUEUE
#define QUEUE

#ifndef TEST
#define TEST
#define TEST_QUEUE
#endif

#include "list.cpp"
#include "vector.cpp"
#include <string>
#include <time.h>

template <typename T, typename SEQUENCE = List<T>>
class Queue
{
    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef SEQUENCE container_type;

        void enqueue(T const & e)    { return array.push_back(e); }
        void enqueue(T && e)         { return array.push_back(std::move(e)); }
        T dequeue()                  { return array.pop_front(); }
        T & front()                  { return array.front(); }
        T const & front() const      { return array.front(); }
        size_t size() const          { return array.size(); }
        bool empty() const           { return array.empty(); }
    private:
        SEQUENCE array;
};

//    round-robin queue
template <typename T>
class Queue<T, Vector<T>>
{
    public:
        typedef T value_type;
        typedef size_t size_type;
        typedef Vector<T> container_type;

        Queue() : head(0), rear(0)       { len = array.capacity(); }

        void enqueue(T const & e)        { check_full(); array[rear] = e; rear = (rear + 1) % len; }
        void enqueue(T && e)             { check_full(); array[rear] = std::move(e); rear = (rear + 1) % len; }
        T dequeue()                      { T cur = array[head]; head = (head + 1) % len; return cur; }
        T & front()                      { return array[head]; }
        T const & front() const          { return array[head]; }
        bool empty() const               { return head == rear; }
        size_t size() const              { return (rear >= head) ? rear - head : len - (head - rear); }

    private:
        size_t head;
        size_t rear;
        size_t len;
        Vector<T> array;

        bool full() const                { return ((rear + 1) % len) == head; }
        void check_full();                   
};

template <typename T>
void Queue<T, Vector<T>>::check_full()
{
    if (!full())
        return;
    else
    {
        array.size() = (rear >= head) ? rear : len;
        array.resize(len + 1);
        if (rear < head)
        {
            for (size_t i = 0; i < rear; ++i)
            {
                array[len] = array[i];
                ++len;
            }
            rear = len;
        }
        len = array.capacity();
    }
}               


//// uncompleted .............
//template <typename T>
//class Deque
//{
//
//    T & front()                               {  }
//    T const & front() const                   {  }
//    T & back()                                {  }
//    T const & back() const                    {  }
//    void push_back(T const & e)               {  }
//    void push_back(T && e)                    {  }
//    T pop_back()                              {  }
//    void push_front(T const &)                {  }
//    void push_front(T && e)                   {  }
//    T pop_front()                             {  }
//
//    private:
//        SEQUENCE array;
//}


#ifdef TEST_QUEUE
int main()
{
    Queue<int> q;
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);
    cout << q.front() << endl;
    q.front() = 5;
    cout << q.front() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;
    cout << q.dequeue() << endl;

    // test vector queue   should ouput 3 3 4 5 0
    Queue<int, Vector<int>> vq1;
    vq1.enqueue(1);
    vq1.enqueue(2);
    cout << vq1.size() << endl;
    cout << vq1.dequeue() << endl;
    cout << vq1.dequeue() << endl;
    vq1.enqueue(3);
    vq1.enqueue(4);
    vq1.enqueue(5);
    cout << vq1.size() << endl;    
    cout << vq1.dequeue() << endl;
    cout << vq1.dequeue() << endl;
    cout << vq1.dequeue() << endl;
    cout << vq1.size() << endl;    
    
    // test speed of Vector queue and List queue
    int N = 30000000;
    int tmp;
    clock_t start;
    // List queue
    start = clock();
    Queue<int, List<int>> lq;
    for (int i = 0; i < N; ++i)
    {
        lq.enqueue(i);
    }
    while (!lq.empty())
        tmp = lq.dequeue();
    cout << "List queue handling: " << N << " element"
         << " cost " << clock() - start << endl;
    // Vector queue
    start = clock();
    Queue<int, Vector<int>> vq;
    for (int i = 0; i < N; ++i)
    {
        vq.enqueue(i);
    }
    while (!vq.empty())
        tmp = vq.dequeue();
    cout << "Vector queue handling: " << N << " element"
         << " cost " << clock() - start << endl;


}
#endif


















#endif