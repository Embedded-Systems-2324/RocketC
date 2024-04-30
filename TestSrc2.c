

/*int main()
{

    float f;
    int x = 1 + (int)f;
}*/

int ze (int y, int z)
{
    z = -2;
    return 0;
}

int main()
{
    int x[2];
    x[0] = 2;
    x[1] = 3;
    int y = x[0] + x[1];

    ze (x[1], x[0]);

    volatile int a;


    return 0;
}