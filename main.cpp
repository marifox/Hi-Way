#include <iostream>
#include "interface.hpp"

using namespace std;

int main()
{
    Interface *iface = new Interface();
    iface->Start();
    return 0;
}
