#include "dominio.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "LinkedList.h"

eDominio* dominio_newParametros(char* idStr,char* dominioStr,char* anioStr,char tipo)
{
    int error = 1;
    eDominio* dom = (eDominio*) malloc (sizeof(eDominio));
    if(dom != NULL)
    {
        if(setId(dom,atoi(idStr))==0)
        {
            if(setDominio(dom,dominioStr)==0)
            {
                if(setAnio(dom,atoi(anioStr))==0)
                {
                    if(setTipo(dom,tipo)==0)
                    {
                        error = 0;

                    }
                }
            }
        }
        if (error)
        {
            free(dom);
            dom = NULL;
        }
    }
    return dom;
}


void printElemento(eDominio* p)
{
    printf("ID:%d dominio:%s anio: %d tipo: %c\r\n",p->id,p->dominio,p->anio,p->tipo);
}

int asignarTipo(eDominio* this)
{
    int retorno = 0;

    if(isdigit(this->dominio[0]))
    {
        setTipo(this,'M');
        retorno = 1;
    }
    else
    {
        setTipo(this,'A');
        retorno = 1;
    }
    return retorno;
}


/*void printElementos(LinkedList* this)
{
    for(int i=0; i<ll_len(this);i++)
    {
        printElemento(ll_get(this,i));
    }
}*/


///FUNCIONES QUE CALIFICAN

int esUnAuto(eDominio* this)
{
    int retorno = 0;
    if(this->tipo == 'A')
    {
        retorno = 1;
    }
    return retorno;
}

int esUnaMoto(eDominio* this)
{
    int retorno = 0;
    if(this->tipo == 'M')
    {
        retorno = 1;
    }
    return retorno;
}


int setDominio(eDominio* this,char* dominio)
{
    int error = 1;
    if(this != NULL && strlen(dominio)<7)
    {
        strcpy(this->dominio,dominio);
        error = 0;
    }

    return error;
}

int getDominio(eDominio* this,char* dominio)
{
    int error = 1;
    if (this != NULL || dominio!=NULL)
    {
        strcpy(dominio,this->dominio);
        error = 0;
    }
    return error;
}



int setTipo(eDominio* this,char tipo)
{
    int error = 1;

    if(this != NULL && (tipo == 'M' || tipo == 'A' || tipo == ' '))
    {
        this->tipo = tipo;
        error = 0;
    }
    return error;
}
int getTipo(eDominio* this,char* tipo)
{
    int error = 1;
    if (this != NULL || (*tipo == 'M' || *tipo == 'A'))
    {
        *tipo = this->tipo;
        error = 0;
    }
    return error;

}

int setId(eDominio* this,int id)
{
    int error = 1;

    if(this != NULL && id>0)
    {
        this->id = id;
        error = 0;
    }
    return error;
}
int getId(eDominio* this,int* id)
{
    int error = 1;
    if (this != NULL || id!=NULL)
    {
        *id = this->id;
        error = 0;
    }
    return error;

}

int setAnio(eDominio* this,int anio)
{
    int error = 1;

    if(this != NULL && anio>=0)
    {
        this->anio = anio;
        error = 0;
    }
    return error;
}
int getAnio(eDominio* this,int* anio)
{
    int error = 1;
    if (this != NULL || anio!=NULL)
    {
        *anio = this->anio;
        error = 0;
    }
    return error;

}

/*int ordenSegunNumero(void *elemento,void* elemento2)
{
    int retorno;
    if(elemento2>elemento)
    {
        retorno = 1;
    }
    else if(elemento2==elemento)
    {
        retorno = 0;
    }
    else
    {
        retorno = -1;
    }
    return retorno;
}*/

/*int ordenSegunAlfabeto(eDominio *cadena,void* cadena2)
{
    int retorno = strcmp(cadena);

    return retorno;
}*/

int idcmp(eDominio* elemento1, eDominio* elemento2)
{
    int retorno = -2;
    if(elemento1 != NULL && elemento2 != NULL)
    {
        if(elemento1->id>elemento2->id)
        {
            retorno = 1;
        }
        else if (elemento1->id < elemento2->id)
        {
            retorno = -1;
        }
        else
        {
            retorno = 0;
        }
    }
    return retorno;
}

int aniocmp(eDominio* elemento1, eDominio* elemento2)
{
    int retorno = -2;
    if(elemento1 != NULL && elemento2 != NULL)
    {
        if(elemento1->anio>elemento2->anio)
        {
            retorno = 1;
        }
        else if (elemento1->anio < elemento2->anio)
        {
            retorno = -1;
        }
        else
        {
            retorno = 0;
        }
    }
    return retorno;
}
