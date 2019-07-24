#include "asignaciones.h"
#include "fecha.h"
#include <stdlib.h>
#include <stdio.h>

eAsignacion* asignacion_new(void)
{
    eAsignacion* new;
    new = (eAsignacion*) malloc (sizeof(eAsignacion));

    if(new != NULL)
    {

        new->idHermano = 0;
        new->asignacion = 0;
        new->fecha = *(newFecha(0,0,2000));
        new->sala = ' ';
    }
    else
    {
        printf("\n Error al crear asignacion");
        system("\npause");
    }

    return new;
}

eAsignacion* asignacion_newParametros(int* idHermano,int* asignacion,char* sala,eFecha* fecha)
{
    eAsignacion* new = NULL;
    if(idHermano != NULL && asignacion != NULL && sala != NULL && fecha != NULL )
    {
        new = (eAsignacion*) malloc (sizeof(eAsignacion));
        new->idHermano = *idHermano;
        new->asignacion = *asignacion;
        new->fecha = *fecha;
        new->sala = *sala;

    }
    else
    {
        printf("\n Error al crear asignacion\n");
        system("pause");
    }

    return new;
}

void printAsignacion(eAsignacion* elemento)
{
    eFecha* fecha;
    printf("\n\t%d\t\t  %c\t     ",elemento->idHermano,elemento->sala);
    switch(elemento->asignacion)
    {
    case 1:
        printf("Primera visita\t\t ");
        break;
    case 2:
        printf("Revisita\t\t ");
        break;
    case 3:
        printf("Curso biblico\t\t ");
        break;
    case 4:
        printf("Lectura biblica\t\t ");
        break;
    case 5:
        printf("Discurso biblico\t\t ");
        break;
    default:
        printf("(VACIO)\t\t ");
        break;
    }
    fecha = &(elemento->fecha);
    printFecha(fecha);
}

int asignacion_searchId(eAsignacion* element1, eAsignacion* element2)
{
    int found=0;
    if(element1->idHermano == element2->idHermano)
    {
        found=1;
    }
    return found;
}
int asignacion_searchFecha(eAsignacion* element1, eAsignacion* element2)
{
    int found=0;
    if(element1->fecha.dia == element2->fecha.dia && element1->fecha.mes == element2->fecha.mes && element1->fecha.anio == element2->fecha.anio)
    {
        found=1;
    }
    return found;
}
