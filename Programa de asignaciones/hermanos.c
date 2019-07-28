#include "hermanos.h"
#include "asignaciones.h"
#include "fecha.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "LinkedList.h"

eHermano* hermano_newParametrosStr(char* idStr,char* nombreStr,char* apellidoStr,char* telefonoStr,char* servMinistStr,char* privilegioStr,eAsignacion* ultimaAsignacionStr,char* estado)
{
    int error = 1;
    eHermano* hno = (eHermano*) malloc (sizeof(eHermano));
    if(hno != NULL)
    {
        if(setId(hno,atoi(idStr))==0)
        {
            if(setNombre(hno,nombreStr)==0)
            {
                if(setApellido(hno,apellidoStr)==0)
                {
                    if(setTelefono(hno,telefonoStr)==0)
                    {
                        if(setServMinist(hno,atoi(servMinistStr))==0)
                        {
                            if(setPrivilegio(hno,atoi(privilegioStr))==0)
                            {
                                if(setUltAsig(hno,ultimaAsignacionStr)==0)
                                {
                                    if(setEstado(hno,atoi(estado))==0)
                                    {
                                        estado=0;
                                    }

                                }

                            }

                        }

                    }
                }
            }
        }
        if (error)
        {
            free(hno);
            hno = NULL;
        }
    }
    return hno;
}

eHermano* hermano_newParametros(int* id,char* nombre,char* apellido,char* telefono,int* servMinist,int* privilegio,eAsignacion* ultimaAsignacion,int* estado)
{
    eHermano* hno;




    if(id != NULL && nombre != NULL && apellido != NULL && telefono != NULL && servMinist != NULL && privilegio != NULL && ultimaAsignacion != NULL && estado != NULL)
    {

        hno = (eHermano*) malloc (sizeof(eHermano));
        if(hno != NULL)
        {
            hno->id = *id;
            strcpy(hno->nombre,nombre);
            strcpy(hno->apellido,apellido);
            strcpy(hno->telefono,telefono);
            hno->servMinist = *servMinist;
            hno->privilegio = *privilegio;
            hno->ultimaAsignacion = *ultimaAsignacion;
            hno->estado = *estado;
        }
    }
    return hno;
}


void printHermano(eHermano* p)
{
    printf("\n %4d %15s %15s %20s       ",p->id,p->nombre,p->apellido,p->telefono);
    switch(p->servMinist)
    {
    case 0:
        printf(" ");
        break;
    case 1:
        printf("%12s","Publicador ");
        break;
    case 2:
        printf("%12s","Prec. Aux ");
        break;
    case 3:
        printf("%12s","Prec. Reg ");
        break;
    case 4:
        printf("%12s","Prec. Esp ");
        break;
    }
    switch(p->privilegio)
    {
    case 1:
        printf("%20s","  Anciano");
        break;
    case 2:
        printf("%20s","  Siervo Minist.");
        break;
        case 3:
        printf("%20s","  Ninguno");
        break;
    }
    printf("             %2d/%2d/%4d",p->ultimaAsignacion.fecha.dia,p->ultimaAsignacion.fecha.mes,p->ultimaAsignacion.fecha.anio);
    if(p->estado)
    {
        printf("%20s","Habilitado");
    }
    else
    {
        printf("%20s","Deshabilitado");
    }
}



void printHermanos(LinkedList* this)
{
    printf("   ID          Nombre        Apellido             Telefono      Serv. Minist           Privilegio      Ultima Asignacion              Estado\n");
            if(ll_len(this)!=0)
            {
                for(int i=0; i<ll_len(this); i++)
                {
                    printHermano(ll_get(this,i));
                }
            }
            else
            {
                printf("\nNo hay resultados. ");
            }

            printf("\n");
}





int setNombre(eHermano* this,char* nombre)
{
    int error = 1;
    if(this != NULL && strlen(nombre)<30)
    {
        strcpy(this->nombre,nombre);
        error = 0;
    }

    return error;
}

int getNombre(eHermano* this,char* nombre)
{
    int error = 1;
    if (this != NULL || nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        error = 0;
    }
    return error;
}



int setApellido(eHermano* this,char* apellido)
{
    int error = 1;
    if(this != NULL && strlen(apellido)<30)
    {
        strcpy(this->apellido,apellido);
        error = 0;
    }

    return error;
}

int getApellido(eHermano* this,char* apellido)
{
    int error = 1;
    if (this != NULL || apellido!=NULL)
    {
        strcpy(apellido,this->apellido);
        error = 0;
    }
    return error;
}




int setTelefono(eHermano* this,char* telefono)
{
    int error = 1;
    if(this != NULL && strlen(telefono)<20)
    {
        strcpy(this->telefono,telefono);
        error = 0;
    }

    return error;
}

int getTelefono(eHermano* this,char* telefono)
{
    int error = 1;
    if (this != NULL || telefono!=NULL)
    {
        strcpy(telefono,this->telefono);
        error = 0;
    }
    return error;
}





int setId(eHermano* this,int id)
{
    int error = 1;

    if(this != NULL && id>0)
    {
        this->id = id;
        error = 0;
    }
    return error;
}
int getId(eHermano* this,int* id)
{
    int error = 1;
    if (this != NULL || id!=NULL)
    {
        *id = this->id;
        error = 0;
    }
    return error;

}



int setServMinist(eHermano* this,int serv)
{
    int error = 1;

    if(this != NULL && serv>0 && serv<=4)
    {
        this->servMinist = serv;
        error = 0;
    }
    return error;
}
int getServMinist(eHermano* this,int* serv)
{
    int error = 1;
    if (this != NULL || serv!=NULL)
    {
        *serv = this->servMinist;
        error = 0;
    }
    return error;

}




int setPrivilegio(eHermano* this,int priv)
{
    int error = 1;

    if(this != NULL && priv>0 && priv<=3)
    {
        this->privilegio = priv;
        error = 0;
    }
    return error;
}
int getPrivilegio(eHermano* this,int* priv)
{
    int error = 1;
    if (this != NULL || priv!=NULL)
    {
        *priv = this->privilegio;
        error = 0;
    }
    return error;

}


int setEstado(eHermano* this,int estado)
{
    int error = 1;

    if(this != NULL && (estado==0 || estado==1))
    {
        this->estado = estado;
        error = 0;
    }
    return error;
}
int getEstado(eHermano* this,int* estado)
{
    int error = 1;
    if (this != NULL || estado!=NULL)
    {
        *estado = this->estado;
        error = 0;
    }
    return error;

}

int setUltAsig(eHermano* this,eAsignacion* ultAsig)
{
    int error = 1;

    if(this != NULL && ultAsig!=NULL)
    {

        this->ultimaAsignacion = *ultAsig;
        error = 0;
    }
    return error;
}
int getUltAsig(eHermano* this,eAsignacion* ultAsig)
{
    int error = 1;
    if (this != NULL || ultAsig!=NULL)
    {
        *ultAsig = this->ultimaAsignacion;
        error = 0;
    }
    return error;

}



int idcmp(eHermano* elemento1, eHermano* elemento2)
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


int otorgarID(LinkedList* this)
{
    int maxId = 1;
    eHermano* hno;
    for(int i=0;i<ll_len(this);i++)
    {
        hno = ll_get(this,i);
        if(i==0)
        {
            maxId = hno->id;
        }
        else if(maxId < hno->id)
        {
            maxId = hno->id;
        }
        maxId++;

    }
    return maxId;
}


int hermano_searchId(eHermano* elemento1,eHermano* elemento2)
{
    int found=0;

    if(elemento1->id == elemento2->id)
    {
        found=1;

    }
    return found;
}


int hermano_searchName(eHermano* elemento1,eHermano* elemento2)
{
    int found=0;
    if(strcmp(elemento1->nombre,elemento2->nombre)==0)
    {
        found=1;
    }
    return found;
}


int hermano_searchSurname(eHermano* elemento1,eHermano* elemento2)
{
    int found=0;
    if(strcmp(elemento1->apellido,elemento2->apellido)==0)
    {
        found=1;
    }
    return found;
}

int hermano_searchPrivilegio(eHermano* elemento1,eHermano* elemento2)
{
    int found=0;

    if(elemento1->privilegio == elemento2->privilegio)
    {
        found=1;

    }
    return found;
}

int hermano_searchServicio(eHermano* elemento1,eHermano* elemento2)
{
    int found=0;
    if(elemento1->servMinist == elemento2->servMinist)
    {
        found=1;
    }
    return found;
}

int hermano_searchAsignacion(eHermano* elemento1,eHermano* elemento2)
{
    int found=0;
    if(elemento1->ultimaAsignacion.asignacion == elemento2->ultimaAsignacion.asignacion)
    {
        found=1;
    }
    return found;
}

int hermano_searchAsignacionSemana(eHermano* elemento1,eHermano* elemento2)
{
    int found=0;
    if(elemento1->ultimaAsignacion.fecha.dia == elemento2->ultimaAsignacion.fecha.dia)
    {
        if(elemento1->ultimaAsignacion.fecha.mes == elemento2->ultimaAsignacion.fecha.dia)
        {
            found=1;
        }
    }
    return found;
}

eHermano* hermano_searchGetById(int* id,LinkedList* this)
{
    eHermano* hno = (eHermano*) malloc (sizeof(eHermano));
    int len;
    int (*pFunc)();
    int* indices;
    if(setId(hno,*id)==0)
    {
        pFunc = hermano_searchId;
        indices = ll_search(this,hno,pFunc,&len);
        if(len == 0)
        {
            hno = NULL;
        }
        else
        {
            hno = ll_get(this,*indices);
        }
    }
    return hno;


}






void harcodearHermanos(LinkedList* this)
{
    eHermano* hno;

    int id[] = {1,2,3,4,5,6,7,8};
    char nombres[][30] = {"Juan","Esteban","Lucas","Alberto","Jose","Marcos","Rodolfo","Lucas"};
    char apellido[][30] = {"Perez","Rodriguez","Carbone","Giacomini","Avellaneda","Rosales","Etcheverria","Alvarez"};
    int privilegio[8]={1,3,2,2,1,3,1,3};
    int servicio[8]={1,3,3,4,2,3,1,2};
    char telefono[][20]={"42133238","43434343","54231321","67653321","55555555","59923631","12344321","01011010"};
    eAsignacion* ultimaAsignacion = asignacion_new();
    int estado =1;

    for(int i=0;i<8;i++)
    {
        hno=hermano_newParametros(&id[i],nombres[i],apellido[i],telefono[i],&servicio[i],&privilegio[i],ultimaAsignacion,&estado);
        ll_add(this,hno);
    }

}

int hermano_ordenarString(eHermano* this1,eHermano* this2)
{
    int retorno;
    retorno = strcmp(this1->apellido,this2->apellido);
    retorno = retorno;
}

int hermano_ordenarId(eHermano* this1,eHermano* this2)
{
    int retorno;
    if(this1->id == this2->id)
    {
        retorno = 0;
    }
    else if(this1->id > this2->id)
    {
        retorno = 1;
    }
    else
    {
        retorno = -1;
    }
    retorno = retorno;
}
