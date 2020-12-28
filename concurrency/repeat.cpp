#include <iostream>
#include <thread>
#include <string>

using namespace std;

void repeat(string & str, int n)
{
    str[0] = '*';
    for(int i = 0; i < n; i ++)
    {
        cout << str << endl;
    }
}

int main()
{
    string str{"Sharon"};
    thread t(repeat, std::ref(str), 3);
    t.join();
    cout << str << endl;
}