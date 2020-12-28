#include <iostream>
#include <thread>
#include <vector>

using namespace std;

void sayHello()
{
    cout << "Hello from thread!" << endl;
};

vector<thread> spawn()
{
    vector<thread> ts;
    for(int i = 0; i < 16; i++)
    {
        ts.emplace_back([&i](){cout << "Hello from thread" << i << endl;});
    }
    return ts;
}

int main()
{
    vector<thread> ts = spawn();
    cout << "Hello from main" << endl;
    for(auto & t : ts)
        t.join();
}