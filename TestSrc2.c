float calculadora(char operador,float num1, float num2)
{
    float resultado;
    switch (operador) 
    {
        case 1:
            resultado = num1 + num2;
            break;
        case 2:
            resultado = num1 - num2;
            break;
        case 3:
            resultado = num1 * num2;
            break;
        case 4:
            if (num2 != 0) 
                resultado = num1 / num2;
            break;
        default:
            resultado = 0;
    }
    return resultado;
}


