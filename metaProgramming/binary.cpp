#include <iostream>
#include <boost/mpl/vector.hpp>

using namespace std;
using namespace mpl = boost::mpl;

typedef mpl::vector<mpl::int_<1>, mpl::int_<0>>::type lenght;
typedef mpl::vector<mpl::int_<0>, mpl::int_<1>>::type time;
typedef mpl::vector<mpl::int_<1>, mpl::int_<-1>>::type velocity;
typedef mpl::vector<mpl::int_<1>, mpl::int_<-2>>::type acceleration;

template<unsigned N>
struct binary
{
    static unsigned const value = binary<N/10>::value * 2 + N%2;
};

template<>
struct binary<0>
{
    static unsigned const value = 0;
};

template<int N>
struct INT_
{
    static int const value = N;
    typedef int value_type;
};

template<typename T1, typename T2>
struct pplus
{
    typedef INT_<T1::value + T2::value> type;
};

int main()
{
    <5> a;
    INT_<6> b;
    INT_<11> c;
    pplus<INT_<5>, INT_<6>>::type d;
    c = d;
    cout << binary<1001>::value << endl;
}

