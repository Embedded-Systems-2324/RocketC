static unsigned int y = 0;
int res = 0;

int CalcDOWhile(int y, int res)
{
    do
    {
        y++;
        res += 1;
    } while (y ==3);

    return res;
}

int CalcWhile (int y, int res)
{
    while (y < 4)
    {
        res += 1;
        y++;
    }
    
}

void ConfirmRes ()
{
    if (Res == 2)
    {
        CalCalcDOWhilec();
    }

    else 
        CalcWhile ();
}
