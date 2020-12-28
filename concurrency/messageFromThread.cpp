#include <iostream>
#include <thread>
#include <future>
#include <string>
#include <exception>

using namespace std;

string getMessage()
{
    return "Message from thread";
}

int main(){
    future<string> receiver = async(getMessage);
    cout << "waiting message in main: " << endl;

    string message = receiver.get();
    cout << "main received: " << message << endl;
}