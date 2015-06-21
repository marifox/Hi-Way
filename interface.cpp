#include "interface.hpp"

Interface::Interface()
{
    init_graphics();
    set_color(cWHITE, cBLACK);
    pr = new Player();

    srand(time(NULL));
    int i;
    for (i = 0; i < MACHINE_COUNT; i++)
    {
        mc[i] = new Machine();
    }

    sctable = new Scoretable();
}

Interface::~Interface()
{
    delete pr;
    delete sctable;
    int i;
    for (i = 0; i < MACHINE_COUNT; i++)
    {
        delete mc[i];
    }
}

void Interface::MainLoop()
{
    pr->MoveTo(2.0, 20.0);
    int i;
    for (i = 0; i < MACHINE_COUNT; i++)
    {
        mc[i]->MoveTo(double((rand() % 10) * 4) + 2, 1.0 - (double)(i * 5));
    }
    speed = 1.0;
    score = 0;
    lives = 3;
    while(!0)
    {
        clear_screen();
        if (kbhit())
        {
            char c = (char)getch();
            switch(c)
            {
            case '\x1B':
                {
                    return;
                    break;
                }
            case 'D':
            case 'd':
                {
                    if (pr->X() < 38)
                    {
                        pr->Move(2.0, 0.0);
                    }
                    break;
                }
            case 'A':
            case 'a':
                {
                    if (pr->X() > 3)
                    {
                        pr->Move(-2.0, 0.0);
                    }
                    break;
                }
            }
        }
        int i;
        for (i = 0; i < MACHINE_COUNT; i++)
        {
            mc[i]->Move(0.0, speed);
            if (mc[i]->Y() > 22.0)
            {
                do
                {
                    mc[i]->MoveTo((double)((rand() % 10) * 4) + 2, 1.0);
                    int j;
                    for (j = 0; j < MACHINE_COUNT; j++)
                    {
                        if (i != j && mc[j]->Intersects(mc[i]))
                        {
                            goto OVERBREAK;
                        }
                    }
                    break;
                    OVERBREAK:;
                } while (true);
            }
            if (pr->Intersects(mc[i]))
            {
                lives--;
                if (lives <= 0)
                {
                    return;
                }
                speed = 1.0;
                do
                {
                    pr->MoveTo((double)((rand() % 10) * 4) + 2, 20.0);
                    int j;
                    for (j = 0; j < MACHINE_COUNT; j++)
                    {
                        if (pr->Intersects(mc[i]))
                        {
                            goto OVERBREAK_2;
                        }
                    }
                    break;
                    OVERBREAK_2:;
                } while (true);
            }
        }
        this->Draw();

        speed *= 1.005;
        score++;
        wait(200);
    }
}

void Interface::Draw()
{
    pr->Draw();
    int i;
    for (i = 0; i < MACHINE_COUNT; i++)
    {
        mc[i]->Draw();
    }
    double ispeed = round(speed * 10.0) / 10.0;
    set_color(cDARK_GREEN);
    set_cursor_pos(45, 3);
    cout << "PLAYER ";
    set_color(cGREEN);
    cout << pname;
    set_color(cYELLOW);
    set_cursor_pos(45, 5);
    cout << "SPEED  " << ispeed;
    set_cursor_pos(45, 7);
    cout << "SCORE  " << score;
    set_cursor_pos(45, 9);
    cout << "LIVES  " << lives;
    set_cursor_pos(45, 12);
    cout << "BEST RESULTS";
    int j;
    for (j = 0; j < 5; j++)
    {
        set_color(cDARK_GREEN);
        set_cursor_pos(45, 14 + j);
        cout << sctable->GetName(j) << " ";
        set_color(cGREEN);
        cout << sctable->GetScore(j);
    }
    set_color(cBLUE);
    draw_line(41, 1, 41, 25);
    draw_line(1, 1, 1, 25);
}

void Interface::Start()
{
    clear_screen();
    set_color(cDARK_CYAN);
    set_cursor_pos(15, 6);
    cout << "WELCOME TO THE HI-ROAD";
    set_cursor_pos(15, 8);
    set_color(cDARK_GREEN);
    cout << "Enter your name: ";
    set_color(cWHITE);
    cin >> pname;
    do
    {
        char ans[10];
        this->MainLoop();
        int p = sctable->InputResult(pname, score);
        clear_screen();
        set_color(cRED);
        set_cursor_pos(15, 6);
        cout << "GAME OVER";
        set_color(cDARK_GREEN);
        set_cursor_pos(15, 8);
        cout << "You've got " << this->score << " points ";
        if (p < 5)
        {
            cout << "and took the " << p + 1 << " place";
        }
        else
        {
            cout << "but took no place";
        }
        set_cursor_pos(15, 10);
        set_color(cYELLOW);
        cout << "BEST RESULTS";
        int j;
        for (j = 0; j < 5; j++)
        {
            set_color(cDARK_GREEN);
            set_cursor_pos(15, 12 + j);
            cout << sctable->GetName(j) << " ";
            set_color(cGREEN);
            cout << sctable->GetScore(j);
        }
        sctable->Save();
        set_cursor_pos(15, 20);
        set_color(cGREEN);
        cout << "Would you like to play one more time? (y/n) ";
        cin >> ans;
        if (!strcmp(ans, "y"))
        {
            continue;
        }
        else
        {
            break;
        }
    } while(1);
}
