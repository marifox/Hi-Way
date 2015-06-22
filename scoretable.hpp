#ifndef SCORETABLE_HPP_INCLUDED
#define SCORETABLE_HPP_INCLUDED

#include <fstream>
#include <cstring>
#include <cstdlib>

class Scoretable
{
private:
    char pnames[5][20];
    int scores[5];
public:
    Scoretable();
    ~Scoretable();
    int InputResult(char pname[20], int score);
    int GetScore(int n);
    char *GetName(int n);
    void Save();
};

#endif // SCORETABLE_HPP_INCLUDED
