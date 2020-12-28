#include <boost/asio.hpp>
#include <iostream>

using namespace std;

boost::asio::steady_timer make_timer(boost::asio::io_context & ioContext)
{
    return boost::asio::steady_timer{
        ioContext,
        std::chrono::steady_clock::now() + std::chrono::seconds{3}
    };
}

int main(){
    boost::asio::io_context io_context(8);
    // auto t1 = make_timer(io_context);
    // cout << "Start to wait" << endl;
    // t1.wait();
    // cout << "Timer expired" << endl;

    auto t2 = make_timer(io_context);
    cout << "start async wait" << endl;
    t2.async_wait([](auto error){
        if(!error)
        {
            cout << "Timer expire handler called" << endl;
        }
    });
    cout << "after async wait" << endl;

    cout << "before io_context run" << endl;
    io_context.run();
    cout << "after io_context run" << endl;

}