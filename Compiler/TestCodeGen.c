int x;        //0
int y;        //1
int* z;       //2
int array[6]; //3

int foo(int a, int b);

void main()
{
    int v;  //1023
    int x;  //1022

    if(x)
        return 0;

    int t;

    if(foo(v + y + 3, 2) > x)
    {
        x = array[4] * x * 5;
    }
    else 
    {
        x = x / 1 + v;
        x = 4;
    }
    
}

LD REG, #addr

LDX REGDST, REG_R2, #IMMED - 1

//ret addr 1021
//a 1020
//b 1019
int foo(int a, int b)   
{
    int c = 1; //
    int v = 2;

    a = 4;

    int z = 0;

    b = a + b + c;

    return c;
}

/* static unsigned int y = 0;
int res = 0;
int *x;

int func()
{
    return 1;
}


int CalcDOWhile(int y, int res)
{
    /* res =  0 -res + &y;

    int b = 4;
    int *a = &b;

    1 + ++res;
    
*/
/* 
    x = &res;
    int array[5]; 

    y = array[res++ + 1];

} */ 

