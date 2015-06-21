#ifndef INTERFACE_HPP_INCLUDED
#define INTERFACE_HPP_INCLUDED

#include "msoftcon.h"
#include "machine.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "player.hpp"
#include "scoretable.hpp"

#define MACHINE_COUNT 5

using namespace std;

class Interface
{
private:
    void Draw();
    Player *pr;
    Machine *mc[MACHINE_COUNT];
    Scoretable *sctable;
    int score;
    double speed;
    int lives;
    char pname[20];
    void MainLoop();
public:
    Interface();
    ~Interface();
    void Start();
};

#endif // INTERFACE_HPP_INCLUDED
