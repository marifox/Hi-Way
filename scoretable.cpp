#include "scoretable.hpp"

Scoretable::Scoretable()
{
    std::ifstream ifile;
    ifile.open("scores.dat");
    int i;
    for (i = 0; i < 5; i++)
    {
        if (ifile.is_open())
        {
            ifile >> pnames[i];
            char buff[10];
            ifile >> buff;
            scores[i] = atoi(buff);
        }
        else
        {
            pnames[i][0] = '\0'; //????
            scores[i] = 10;
        }
    }
    ifile.close();
}

Scoretable::~Scoretable()
{

}

int Scoretable::GetScore(int n)
{
    return this->scores[n];
}

char *Scoretable::GetName(int n)
{
    return this->pnames[n];
}

void Scoretable::Save()
{
    std::ofstream ofile;
    ofile.open("scores.dat");
    int i;
    for (i = 0; i < 5; i++)
    {
        ofile << pnames[i] << "\n" << scores[i] << "\n";
    }
    ofile.close();
}

int Scoretable::InputResult(char pname[20], int score)//????
{
    int rp = 0;
    int i;
    for (i = 4; i >= 0; i--)
    {
        if (score < scores[i])
        {
            rp = i + 1;
            break;
        }
    }
    if (rp>4)
    {
      return rp;
    }

    for (i = 3; i >= rp; i--)
    {
        scores[i + 1] = scores[i];

        strcpy(pnames[i + 1], pnames[i]);
    }
    scores[rp] = score;

    strcpy(pnames[rp], pname);

    return rp;
}
