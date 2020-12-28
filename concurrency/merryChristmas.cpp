#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <thread>
#include <chrono>
#include <future>
#include <mutex>
#include <condition_variable>

using namespace std;
using namespace std::filesystem;

template<typename T>
class FileMonitor
{
public:
    void push_back(string file)
    {
        lock_guard<mutex> lck(_mutex);
        _allFiles.push_back(file);
        _cond.notify_one();
    }

    string pop_back()
    {
        unique_lock<mutex> lck(_mutex);
        _cond.wait(lck, [this](){return !_allFiles.empty();});
        string file = move(_allFiles.back());
        _allFiles.pop_back();
        return file;
    }
private:
    mutable mutex _mutex;
    condition_variable _cond;
    vector<T> messageQueue;
};


void listDir(path dir, FileMonitor & fileMonitor)
{
    for(auto file : directory_iterator(dir))
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        if(is_regular_file(file))
            fileMonitor.push_back(file.path().filename());
    }
}

void listDirs(vector<path> dirs)
{
    vector<future<void>> fus;
    FileMonitor fileMonitor;

    for(auto dir : dirs)
    {
        fus.emplace_back(async(listDir, dir, ref(fileMonitor)));
    }

    for(;;)
    {
        string file = fileMonitor.pop_back();
        cout << file << endl;
    }
}

void handleList()
{
    vector<path> dirs;
    for(auto dir : directory_iterator("/Users/xuelanmei/programing/practice"))
    {
        if(is_directory(dir))
            dirs.push_back(dir);
    }

    listDirs(dirs);
}

int main()
{
    bool exit = false;
    thread t;
    while(!exit)
    {
        string str;
        cout << "Input: ";
        cin >> str;
        if(str == "exit")
        {
            cout << "Bye bye !" << endl;
            exit = true;
        }
        else if(str == "list")
        {
            t = thread(handleList);
        }
        else
        {
            cout << "Merry Christmas! " << str << endl;
        }
    }
    if(t.joinable())
        t.join();
}
