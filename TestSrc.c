static const unsigned int complexVar; 

extern float fVar, fVAr3, fVar4;

void function (int x, float y);

int main(){
    function(24, 3.5);
    return 0;
}

void function(int x, float y)
{
    if (x > y) {
        y++;
    }
    else if (x < y){
        y += 2;
    }
    else {
        y = (3 / x);
    }
    return;
}



