#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <vector>

using namespace std;

class Account
{
public:
    Account():_balance(0){};
    void deposite(int sum)
    {
        lock_guard<recursive_mutex> lck(_mutex);
        _balance += sum;
    }

    int balance() const
    {
        lock_guard<recursive_mutex> lck(_mutex);
        return _balance;
    }

    recursive_mutex & getMutex()
    {
        return _mutex;
    }

private:
    mutable recursive_mutex _mutex;
    int _balance;
};

class Bank
{
public:
    Bank(int minBalance):_minBalance(minBalance)
    {
        acct[0].deposite(minBalance);
    };
    void transfer(int from, int to, int sum)
    {
        lock(acct[to].getMutex(), acct[from].getMutex());
        lock_guard<recursive_mutex> lck1(acct[to].getMutex(), adopt_lock);
        lock_guard<recursive_mutex> lck2(acct[from].getMutex(), adopt_lock);
        if(acct[from].balance() >= sum)
        {
            acct[from].deposite(-sum);
            acct[to].deposite(sum);
        }
 
    }
private:
    int _minBalance;
    Account acct[2];
};

future<void> trans(Bank & bank, int from, int to, int sum)
{
    return async(launch::async, [&bank](int from, int to, int sum)
    {
        bank.transfer(from, to, sum);
    }, from, to, sum);
}

int main()
{
    Bank bank(10);
    vector<future<void>> fus;
    for(int i = 0; i < 500; i++)
    {
        fus.emplace_back(trans(bank, 0, 1, 10));
        fus.emplace_back(trans(bank, 1, 0, 10));
    }

    for(auto & f: fus)
    {
        f.wait();
    }
}