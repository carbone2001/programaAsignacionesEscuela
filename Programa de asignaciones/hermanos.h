#include "fecha.h"
#include "asignaciones.h"
#include "LinkedList.h"
#ifndef HERMANOS_H_INCLUDED
#define HERMANOS_H_INCLUDED


typedef struct
 {
     int id;
     char nombre[30];
     char apellido[30];
     char telefono[20];
     int servMinist; ///Servicio de ministerio (publicador, prec. aux, prec, reg, etc)
     int privilegio;
     eAsignacion ultimaAsignacion;
     int estado;
 }eHermano;

void printHermano(eHermano* p);
void printHermanos(LinkedList* this);
void harcodearHermanos(LinkedList* this);


eHermano* hermano_newParametrosStr(char* idStr,char* nombreStr,char* apellidoStr,char* telefonoStr,char* servMinistStr,char* privilegioStr,eAsignacion* ultimaAsignacionStr,char* estado);
eHermano* hermano_newParametros(int* idStr,char* nombreStr,char* apellidoStr,char* telefonoStr,int* servMinistStr,int* privilegioStr,eAsignacion* ultimaAsignacionStr,int* estado);


int setId(eHermano* this,int id);
int getId(eHermano* this,int* id);

int setNombre(eHermano* this,char* nombre);
int getNombre(eHermano* this,char* nombre);

int setApellido(eHermano* this,char* apellido);
int getApellido(eHermano* this,char* apellido);

int setTelefono(eHermano* this,char* telefono);
int getTelefono(eHermano* this,char* telefono);

int setServMinist(eHermano* this,int serv);
int getServMinist(eHermano* this,int* serv);

int setPrivilegio(eHermano* this,int priv);
int getPrivilegio(eHermano* this,int* priv);

int setUltAsig(eHermano* this, eAsignacion* ultAsig);
int getUltAsig(eHermano* this,eAsignacion* ultAsig);

int setEstado(eHermano* this,int estado);
int getEstado(eHermano* this,int* estado);



int otorgarID(LinkedList* this);

int hermano_searchId(eHermano* elemento1,eHermano* elemento2);
int hermano_searchName(eHermano* elemento1,eHermano* elemento2);
int hermano_searchSurname(eHermano* elemento1,eHermano* elemento2);
int hermano_searchPrivilegio(eHermano* elemento1,eHermano* elemento2);
int hermano_searchServicio(eHermano* elemento1,eHermano* elemento2);
int hermano_searchAsignacion(eHermano* elemento1,eHermano* elemento2);
int hermano_searchAsignacionSemana(eHermano* elemento1,eHermano* elemento2);
eHermano* hermano_searchGetById(int* id,LinkedList* this);

int hermano_ordenarId(eHermano* this1,eHermano* this2);
int hermano_ordenarString(eHermano* this1,eHermano* this2);

#endif // dominio_H_INCLUDED
