#include "asignaciones.h"
#include "LinkedList.h"
#include "hermanos.h"
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

void printAsignacion(eAsignacion* elemento,LinkedList* listaHermanos)
{
    eFecha* fecha;
    eHermano* hno = (eHermano*)malloc(sizeof(eHermano));
    hno=hermano_searchGetById(&(elemento->idHermano),listaHermanos);



    printf("\n %15s %15s          %d  \t\t %1c     ",hno->apellido,hno->nombre,elemento->idHermano,elemento->sala);

    switch(elemento->asignacion)
    {
    case 1:
        printf("%20s\t ","Lectura Biblica");
        break;
    case 2:
        printf("%20s\t ","Primera Conversacion");
        break;
    case 3:
        printf("%20s\t ","Primera Revisita");
        break;
    case 4:
        printf("%20s\t ","Segunda Conversacion");
        break;
    case 5:
        printf("%20s\t ","Curso Biblico");
        break;
    case 6:
        printf("%20s\t ","Discurso biblico");
        break;
    default:
        printf("%20s\t ","(VACIO)");
        break;
    }
    fecha = &(elemento->fecha);
    printFecha(fecha);
}

void printAsignaciones(LinkedList* this,LinkedList* listaHermanos)
{
    printf("        Apellido          Nombre    ID del hermano     Sala              Asignacion           Fecha");
    if(ll_len(this)!=0)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            printAsignacion(ll_get(this,i),listaHermanos);
        }
    }
    else
    {
        printf("\nNo ha resultados.");
    }


    printf("\n\n");
}


void printAsignacionesConHermanos(LinkedList* this,LinkedList* listaHermanos)
{
    printf("Nombre del Hermano   ID del hermano       Sala                   Asignacion             Fecha\n");
    eHermano* hno;
    eAsignacion* asig;
    if(ll_len(this)!=0 && ll_len(listaHermanos)!= 0)
    {
        for(int i=0; i<ll_len(this); i++)
        {
            asig = ll_get(this,i);
            hno = hermano_searchGetById(&(asig->idHermano),listaHermanos);
            printf("%20s %20s ",hno->apellido,hno->nombre);
            printAsignacion(ll_get(this,i),listaHermanos);
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
    int (*pFunc)();
    LinkedList* listaIdFechaAsig = ll_newLinkedList(); ///Almacenara los elementos que se retornaran
    LinkedList* listaIdAsig = ll_newLinkedList(); ///Almacena las asignaciones que coinciden con el ID
    eAsignacion* asig = (eAsignacion*)malloc(sizeof(eAsignacion)); ///Almacena una unica asignacion que coincide con el ID y la fecha
    asig->fecha = *fecha;
    asig->idHermano = *id;

    pFunc = asignacion_searchId; ///Funcion que compara ID
    listaIdAsig = ll_search(this,asig,pFunc); ///Busca todas las asignaciones que coinciden con el ID

    if(ll_len(listaIdAsig) == 0)
    {
        asig = NULL;
    }
    else
    {
        pFunc = asignacion_searchFecha; ///Funcion que compara fechas
        listaIdFechaAsig = ll_search(listaIdAsig,asig,pFunc); ///De la lista de asignaciones que coinciden con el ID busca cual coincide con la fecha

        if(ll_len(listaIdFechaAsig) == 0)
        {
            asig = NULL;
        }
        else
        {
            asig = ll_get(listaIdFechaAsig,0); ///Da el primer elemento que coincida con ID y Fecha. Ya que no pueden haber dos iguales.
        }


    }
    return asig;
}

int asignacion_sortByData(eAsignacion* this, eAsignacion* this2)
{
    int retorno = -1;
    if(this->fecha.anio == this2->fecha.anio)
    {
        if(this->fecha.mes == this2->fecha.mes)
        {
            if(this->fecha.dia == this2->fecha.dia)
            {
                retorno = 0;
            }
            else if(this->fecha.dia > this2->fecha.dia)
            {
                retorno = 1;
            }
        }
        else if(this->fecha.mes > this2->fecha.mes)
        {
            retorno = 1;
        }
    }
    else if(this->fecha.anio > this2->fecha.anio)
    {
        retorno = 1;
    }

    return retorno;
}

int asignacion_sortAsignacion(eAsignacion* element1, eAsignacion* element2)
{
    int r = 0;
    if(element1->asignacion > element2->asignacion)
    {
        r = 1;
    }
    else if(element1->asignacion < element2->asignacion)
    {
        r=-1;
    }
    return r;
}
