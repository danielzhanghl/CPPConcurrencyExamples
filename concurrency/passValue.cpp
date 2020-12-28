#include <iostream>
#include <thread>
#include <future>
#include <memory>

using namespace std;

struct Counter
{
    Counter(int k):n(k){};
    int n;
};

struct Holder
{
    Holder(int n):c(new Counter{n}){};
    Counter * c;
}

int main()
{
    const Holder h{12};
    future<void> fut = async([](const Holder & p)
    {
        (h.c->n) ++;
        cout << "counter in thread: " << p.c->n << endl;
    }, ref(h));

    fut.wait();
    cout << "counter in main: " << h.c->n << endl;
}