#include "machine.hpp"

Machine::Machine()
{
    x = 1.0;
    y = 1.0;
}

Machine::~Machine()
{

}

double Machine::X()
{
    return this->x;
}

double Machine::Y()
{
    return this->y;
}

void Machine::MoveTo(double xp, double yp)
{
    this->x = xp;
    this->y = yp;
}

void Machine::Move(double dx, double dy)
{
    this->x += dx;
    this->y += dy;
}

void Machine::Draw()
{
    int xp = (int)round(this->x);
    int yp = (int)round(this->y);
    if (xp < 1 || yp < 1 || xp > (80 - 2) || yp > (25 - 3))
    {
        return;
    }
    set_color(cMAGENTA);
    set_fill_style(X_FILL);
    draw_line(xp + 1, yp, xp + 1, yp + 3);
    draw_line(xp, yp + 0, xp + 2, yp + 0);
    draw_line(xp, yp + 2, xp + 2, yp + 2);
}

bool Machine::Intersects(Machine *m)
{
    if (fabs(m->X() - this->x) < 3.0 && fabs(m->Y() - this->y) < 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}
