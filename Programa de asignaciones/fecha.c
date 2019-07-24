#include "fecha.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
eFecha strToData(char* str)
{
    eFecha fecha;
    /*char dia[3];
    char mes[3];
    char anio[5];
    if(str != NULL)
    {
        dia[0] = str[0];
        dia[1] = str[1];

        mes[0] = str[3];
        mes[1] = str[4];

        anio[0] = str[6];
        anio[1] = str[7];
    }*/
    return fecha;
}

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
    scanf("%d",&dia);
    printf("\n\tMes: ");
    scanf("%d",&mes);
    printf("\n\tAnio: ");
    scanf("%d",&anio);
    fechaAux = newFecha(dia,mes,anio);


    return fechaAux;
}

void printFecha(eFecha* fecha)
{
    printf("%d/",fecha->dia);
    printf("%d/",fecha->mes);
    printf("%d",fecha->anio);
}
