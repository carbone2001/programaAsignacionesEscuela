#include "asignaciones.h"
#include "LinkedList.h"
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
        printf("%20s\t ","Primera visita");
        break;
    case 2:
        printf("%20s\t ","Revisita");
        break;
    case 3:
        printf("%20s\t ","Curso biblico");
        break;
    case 4:
        printf("%20s\t ","Lectura biblica");
        break;
    case 5:
        printf("%20s\t ","Discurso biblico");
        break;
    default:
        printf("%20s\t ","(VACIO)");
        break;
    }
    fecha = &(elemento->fecha);
    printFecha(fecha);
}

void printAsignaciones(LinkedList* this)
{
    printf("   ID del hermano       Sala                   Asignacion             Fecha\n");
    if(ll_len(this)!=0)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            printAsignacion(ll_get(this,i));
        }
    }
    else
    {
        printf("\nNo ha resultados.");
    }


    printf("\n\n");
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


int asignacion_searchFechaMes(eAsignacion* element1, eAsignacion* element2)
{
    int found=0;
    if(element1->fecha.mes == element2->fecha.mes && element1->fecha.anio == element2->fecha.anio)
    {
        found=1;
    }
    return found;
}


int asignacion_searchSala(eAsignacion* element1, eAsignacion* element2)
{
    int found=0;
    if(element1->sala == element2->sala)
    {
        found=1;
    }

    printf("\n(%c | %c) found=%d",element1->sala,element2->sala,found);

    return found;
}

int asignacion_searchAsignacion(eAsignacion* element1, eAsignacion* element2)
{
    int found=0;
    if(element1->asignacion == element2->asignacion)
    {
        found=1;
    }
    return found;
}

void harcodearAsignaciones(LinkedList* this)
{
    eAsignacion* asig = (eAsignacion*)malloc(sizeof(eAsignacion));
    int id[8]= {1,3,3,2,5,8,6,8};
    int asignaciones[8]= {1,5,2,3,3,4,5,1};
    char sala[8]= {'A','B','B','A','B','A','A','B'};
    eFecha fecha[8]= {{1,10,2001},
        {2,9,2009},
        {3,2,2019},
        {4,3,2018},
        {5,8,2021},
        {6,5,2022},
        {7,1,2015},
        {8,12,2005},
    };
    for(int i=0; i<8; i++)
    {
        asig = asignacion_newParametros(&id[i],&asignaciones[i],&sala[i],&fecha[i]);
        ll_add(this,asig);
    }


}


eAsignacion* asignacion_searchByIdData(int* id,eFecha* fecha,LinkedList* this)
{
    int len;
    int error=0;
    int (*pFunc)();
    int* indices;
    LinkedList* listaIdAsig = ll_newLinkedList();
    eAsignacion* asig = (eAsignacion*)malloc(sizeof(eAsignacion));
    asig->fecha = *fecha;
    asig->idHermano = *id;

    pFunc = asignacion_searchId;
    indices = ll_search(this,asig,pFunc,&len);
    if(len == 0)
    {
        asig = NULL;
    }
    else
    {
        for(int i=0; i<len; i++)
        {
            if(ll_add(listaIdAsig,ll_get(this,indices[i])))
            {
                printf("\n\n ERROR EN asignacion_searchByIdData\n\n");
                system("pause");
                error = 0;
            }
        }
        if(error == 0)
        {
            pFunc = asignacion_searchFecha;
            indices = ll_search(listaIdAsig,asig,pFunc,&len);
            if(len == 0)
            {
                asig = NULL;
            }
            else
            {
                asig = ll_get(listaIdAsig,indices[0]);
            }
        }

    }
    return asig;


}
