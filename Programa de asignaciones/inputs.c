#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "inputs.h"
int getIntIntentos(int* input,char* msj,char* eMsj,int minimo,int maximo,int reintentos)
{
    int i;
    int error;
    char numStr[15];
    int num;
    error=0;
    num=*input;
    printf("%s",msj);
    fflush(stdin);
    scanf("%s",numStr);
    num = atoi(numStr);
    if(num<minimo||num>maximo)
    {
        if(reintentos)
        {
            for(i=1; i<reintentos; i++)
            {
                printf("%s",eMsj);
                scanf("%s",numStr);
                num = atoi(numStr);
                if(num>=minimo&&num<=maximo)
                {
                    *input=num;
                    error=0;
                    break;
                }
                else
                {
                    error=1;
                }
            }
            reintentos = 0;
        }
        else
        {
            while(num<minimo||num>maximo)
            {
                printf("%s",eMsj);
                scanf("%s",numStr);
                num = atoi(numStr);
            }
            *input=num;
        }
    }
    else
    {
        *input=num;
    }
    return error;
}

int getInt(int* input,char*msj,char*eMsj,int minimo,int maximo)
{
    char numS[12];
    int num;
    int error = 0;
    printf("%s",msj);
    fflush(stdin);
    scanf("%s",numS);
    num = atoi(numS);

    if(num < minimo || num > maximo)
    {
        printf("%s",eMsj);
        system("pause");
        error = 1;
    }
    *input = num;

    return error;

}

int getRandom(int primerNumero, int ultimoNumero,int primeraVez)
{
    if(primeraVez)
    {
        srand(time(NULL));
    }
    int random;
    random=primerNumero+(rand()%((ultimoNumero+1)-primerNumero));
    return random;
}

char getChar(char*msj)
{
    char letraEntrada;
    printf("%s",msj);
    fflush(stdin);
    scanf("%c",&letraEntrada);
    return letraEntrada;
}
void getFloatPlus(float*input,char*msj,char*eMsj,float minimo,float maximo)
{
    printf("%s",msj);
    scanf("%f",input);
    while(*input>maximo || *input<minimo)
    {
        printf("%s",eMsj);
        scanf("%f",input);
    }
}
int getString(char* str,char*msj,char*eMsj,int limite)
{
    int error = 0;

    printf(msj);
    fflush(stdin);
    gets(str);
    if(strlen(str)>limite)
    {
        printf(eMsj);
        error=1;
    }
    return error;
}

