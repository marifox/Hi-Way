#ifndef MACHINE_HPP_INCLUDED
#define MACHINE_HPP_INCLUDED

#include "msoftcon.h"
#include <math.h>

class Machine
{
private:
    double x, y;
public:
    Machine();
    ~Machine();
    double X();
    double Y();
    void MoveTo(double xp, double yp);
    void Move(double dx, double dy);
    void Draw();
    bool Intersects(Machine *m);
};

#endif // MACHINE_HPP_INCLUDED
