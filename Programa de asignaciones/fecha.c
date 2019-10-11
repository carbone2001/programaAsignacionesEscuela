#include "fecha.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

eFecha* newFecha(int dia,int mes,int anio)
{

    eFecha* fechaAux;
    if((dia >=0 && dia<=31) && (mes >= 0 && mes <= 12) && (anio >= 2000 && dia <= 2030))
    {

        fechaAux = (eFecha*) malloc (sizeof(eFecha));
        if(fechaAux != NULL)
        {
            fechaAux->dia = dia;
            fechaAux->mes = mes;
            fechaAux->anio = anio;
        }
        else
        {
            printf("\nError al crear fecha\n");
            fechaAux = NULL;
            system("pause");
        }
    }
    else
    {
        printf("\nError al crear fecha\n");
        fechaAux = NULL;
        system("pause");
    }

    return fechaAux;
}

eFecha* pedirFecha(void)
{

    int dia;
    int mes;
    int anio;
    eFecha* fechaAux;


    printf("\n\tDia: ");
    fflush(stdin);
    scanf("%d",&dia);
    printf("\n\tMes: ");
    fflush(stdin);
    scanf("%d",&mes);
    printf("\n\tAnio: ");
    fflush(stdin);
    scanf("%d",&anio);
    fechaAux = newFecha(dia,mes,anio);
    return fechaAux;
}

void printFecha(eFecha* fecha)
{
    printf("%02d/",fecha->dia);
    printf("%02d/",fecha->mes);
    printf("%04d",fecha->anio);
}

int fecha_searchFecha(eFecha* element1,eFecha* element2)
{
    int retorno = -1;
    if(element1->anio == element2->anio)
    {
        if(element1->mes == element2->mes)
        {
            if(element1->dia == element2->dia)
            {
                retorno = 0;
            }
            else if(element1->dia > element2->dia)
            {
                retorno = 1;
            }
        }
        else if(element1->mes > element2->mes)
        {
            retorno = 1;
        }
    }
    else if(element1->anio > element2->anio)
    {
        retorno = 1;
    }

    return retorno;

}

char* getMonthSpanish(int numberMounth)
{
    char* nombreMes = (char*)malloc(sizeof(char)*20);
    switch(numberMounth)
    {
    case 1:
        strcpy(nombreMes,"Enero ");
        break;
    case 2:
        strcpy(nombreMes,"Febrero ");
        break;
    case 3:
        strcpy(nombreMes,"Marzo ");
        break;
    case 4:
        strcpy(nombreMes,"Abril ");
        break;
    case 5:
        strcpy(nombreMes,"Mayo ");
        break;
    case 6:
        strcpy(nombreMes,"Junio ");
        break;
    case 7:
        strcpy(nombreMes,"Julio ");
        break;
    case 8:
        strcpy(nombreMes,"Agosto ");
        break;
    case 9:
        strcpy(nombreMes,"Septiembre ");
        break;
    case 10:
        strcpy(nombreMes,"Octubre ");
        break;
    case 11:
        strcpy(nombreMes,"Noviembre ");
        break;
    case 12:
        strcpy(nombreMes,"Diciembre ");
        break;
    }

    return nombreMes;

}
